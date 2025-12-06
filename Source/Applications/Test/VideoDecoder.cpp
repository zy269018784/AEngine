// VideoDecoder.cpp
#include "VideoDecoder.h"

bool VideoDecoder::Open(const char* filename) {
    Cleanup();

    // 打开文件
    if (avformat_open_input(&formatCtx, filename, nullptr, nullptr) < 0) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return false;
    }

    // 查找流信息
    if (avformat_find_stream_info(formatCtx, nullptr) < 0) {
        std::cerr << "无法查找流信息" << std::endl;
        return false;
    }

    // 查找视频流
    videoStreamIndex = -1;
    for (int i = 0; i < formatCtx->nb_streams; i++) {
        if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1) {
        std::cerr << "未找到视频流" << std::endl;
        return false;
    }

    // 获取解码器
    AVCodecParameters* codecParams = formatCtx->streams[videoStreamIndex]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codecParams->codec_id);
    if (!codec) {
        std::cerr << "找不到解码器" << std::endl;
        return false;
    }

    // 创建解码器上下文
    codecCtx = avcodec_alloc_context3(codec);
    if (!codecCtx) {
        std::cerr << "无法分配解码器上下文" << std::endl;
        return false;
    }

    if (avcodec_parameters_to_context(codecCtx, codecParams) < 0) {
        std::cerr << "无法复制编解码器参数到上下文" << std::endl;
        return false;
    }

    if (avcodec_open2(codecCtx, codec, nullptr) < 0) {
        std::cerr << "无法打开解码器" << std::endl;
        return false;
    }

    std::cout << "成功打开视频: " << filename
        << " 尺寸: " << codecCtx->width << "x" << codecCtx->height
        << " 格式: " << av_get_pix_fmt_name(codecCtx->pix_fmt) << std::endl;

    return true;
}

void VideoDecoder::Start() {
    if (running) return;

    running = true;
    decodeThread = std::thread(&VideoDecoder::DecodeLoop, this);
}

void VideoDecoder::Stop() {
    running = false;
    if (decodeThread.joinable()) {
        decodeThread.join();
    }

    // 清理队列
    std::lock_guard<std::mutex> lock(queueMutex);
    while (!frameQueue.empty()) {
        frameQueue.pop();
    }
}

void VideoDecoder::DecodeLoop() {
    AVPacket* packet = av_packet_alloc();
    AVFrame* frame = av_frame_alloc();

    if (!packet || !frame) {
        std::cerr << "无法分配 packet 或 frame" << std::endl;
        if (packet) av_packet_free(&packet);
        if (frame) av_frame_free(&frame);
        return;
    }

    std::cout << "开始解码循环..." << std::endl;

    while (running) {
        int ret = av_read_frame(formatCtx, packet);

        if (ret < 0) {
            // 文件结束或错误，短暂等待后继续
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        if (packet->stream_index == videoStreamIndex) {
            // 发送包到解码器
            ret = avcodec_send_packet(codecCtx, packet);
            if (ret < 0) {
                av_packet_unref(packet);
                continue;
            }

            // 接收解码后的帧
            while (avcodec_receive_frame(codecCtx, frame) == 0) {
                auto rgbFrame = ConvertToRGB(frame);
                if (rgbFrame) {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    if (frameQueue.size() >= maxQueueSize) {
                        frameQueue.pop(); // 丢弃最旧的帧
                    }
                    frameQueue.push(std::move(rgbFrame));
                    lock.unlock();
                    queueCV.notify_one();
                }
            }
        }

        av_packet_unref(packet);
    }

    av_packet_free(&packet);
    av_frame_free(&frame);
    std::cout << "解码循环结束" << std::endl;
}

std::unique_ptr<VideoFrame> VideoDecoder::ConvertToRGB(AVFrame* frame) {
    if (!frame || !frame->data[0]) {
        return nullptr;
    }

    // 初始化缩放上下文
    if (!swsCtx) {
        swsCtx = sws_getContext(
            frame->width, frame->height, (AVPixelFormat)frame->format,
            frame->width, frame->height, AV_PIX_FMT_RGB24,
            SWS_BILINEAR, nullptr, nullptr, nullptr
        );

        if (!swsCtx) {
            std::cerr << "无法创建缩放上下文" << std::endl;
            return nullptr;
        }
    }

    // 创建目标帧
    auto rgbFrame = std::make_unique<VideoFrame>(frame->width, frame->height);

    // 设置目标帧参数
    uint8_t* dstData[1] = { rgbFrame->data.get() };
    int dstLinesize[1] = { frame->width * 3 }; // RGB24

    // 执行转换
    int result = sws_scale(swsCtx,
        frame->data, frame->linesize,
        0, frame->height,
        dstData, dstLinesize);

    if (result <= 0) {
        std::cerr << "sws_scale 失败: " << result << std::endl;
        return nullptr;
    }

    // 设置时间戳
    rgbFrame->pts = frame->pts;
    if (frame->pts != AV_NOPTS_VALUE) {
        AVRational time_base = formatCtx->streams[videoStreamIndex]->time_base;
        rgbFrame->timestamp = frame->pts * av_q2d(time_base);
    }

    return rgbFrame;
}

std::unique_ptr<VideoFrame> VideoDecoder::GetFrame() {
    std::unique_lock<std::mutex> lock(queueMutex);
    if (frameQueue.empty()) {
        return nullptr;
    }

    auto frame = std::move(frameQueue.front());
    frameQueue.pop();
    return frame;
}

void VideoDecoder::Cleanup() {
    Stop();

    if (swsCtx) {
        sws_freeContext(swsCtx);
        swsCtx = nullptr;
    }

    if (codecCtx) {
        avcodec_free_context(&codecCtx);
    }

    if (formatCtx) {
        avformat_close_input(&formatCtx);
    }
}