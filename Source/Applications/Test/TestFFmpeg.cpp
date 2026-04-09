#include <iostream>
#include <VideoAudioCodec/CodecContext.h>
#include <VideoAudioCodec/FormatContext.h>
#include <VideoAudioCodec/Frame.h>
#include <VideoAudioCodec/Encoder.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern  "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavutil/opt.h>
    #include <libavutil/imgutils.h>
    #include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

static void encode(AVCodecContext *enc_ctx, CodecContext *Context, AVFrame *frame, AVPacket *pkt,
                   FILE *outfile)
{
    int ret;

    /* send the frame to the encoder */
    if (frame)
        printf("Send frame %d\n", frame->pts);


    ret = Context->SendFrame(frame);
    if (ret < 0) {
        fprintf(stderr, "Error sending a frame for encoding\n");
        exit(1);
    }

    while (ret >= 0) {
        ret = Context->ReceivePacket(pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error during encoding\n");
            exit(1);
        }

        printf("Write packet %d (size=%5d)\n", pkt->pts, pkt->size);
        fwrite(pkt->data, 1, pkt->size, outfile);
        av_packet_unref(pkt);
    }
}


int TestFFmpeg(int argc, char** argv)
{
    const char *filename, *codec_name;
    const AVCodec *codec;
    AVCodecContext *c= NULL;
    //CodecContext *Context = NULL;
    Encoder *Encoder = NULL;
    int i, ret, x, y;
    FILE *f;
    AVPacket *pkt;
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };

    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <output file> <codec name>\n", argv[0]);
        exit(0);
    }
    filename = argv[1];
    codec_name = argv[2];

    /* find the mpeg1video encoder */
    codec = avcodec_find_encoder_by_name(codec_name);
    if (!codec) {
        fprintf(stderr, "Codec '%s' not found\n", codec_name);
        exit(1);
    }

    // 1.
   // Context = new CodecContext(codec);
    Encoder = new ::Encoder(codec_name);
    //Context = Encoder->CodecContext;
    c = Encoder->CodecContext->GetHandle();
    if (!Encoder->CodecContext->GetHandle()) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    pkt = av_packet_alloc();
    if (!pkt)
        exit(1);

    Encoder->SetBitRate(400000);
    /* resolution must be a multiple of two */
    Encoder->SetWidth(352);
    Encoder->SetHeight(288);
    Encoder->SetFrameRate(25);
    Encoder->SetTimeBase(25);
    Encoder->SetGopSize(10);
    Encoder->SetMaxBFrames(1);
    Encoder->SetPixelFormat(AV_PIX_FMT_YUV420P);


    if (codec->id == (enum AVCodecID)AV_CODEC_ID_H264)
        av_opt_set(c->priv_data, "preset", "slow", 0);

    /* open it */
    ret = Encoder->CodecOpen2(NULL);
    if (ret < 0) {
       // fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
        exit(1);
    }

    f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Could not open %s\n", filename);
        exit(1);
    }


    if (!Encoder->Frame->GetHandle()) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }

    ret = Encoder->Frame->GetBuffer(0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate the video frame data\n");
        exit(1);
    }

    /* encode 1 second of video */
    for (i = 0; i < 25; i++) {
        fflush(stdout);

        /* Make sure the frame data is writable.
           On the first round, the frame is fresh from av_frame_get_buffer()
           and therefore we know it is writable.
           But on the next rounds, encode() will have called
           avcodec_send_frame(), and the codec may have kept a reference to
           the frame in its internal structures, that makes the frame
           unwritable.
           av_frame_make_writable() checks that and allocates a new buffer
           for the frame only if necessary.
         */
        Encoder->Frame->MakeWritable();
        if (ret < 0)
            exit(1);

        /* Prepare a dummy image.
           In real code, this is where you would have your own logic for
           filling the frame. FFmpeg does not care what you put in the
           frame.
         */
        /* Y */
        for (y = 0; y < c->height; y++) {
            for (x = 0; x < c->width; x++) {
                Encoder->Frame->GetHandle()->data[0][y * Encoder->Frame->GetHandle()->linesize[0] + x] = x + y + i * 3;
            }
        }

        /* Cb and Cr */
        for (y = 0; y < c->height/2; y++) {
            for (x = 0; x < c->width/2; x++) {
                Encoder->Frame->GetHandle()->data[1][y * Encoder->Frame->GetHandle()->linesize[1] + x] = 128 + y + i * 2;
                Encoder->Frame->GetHandle()->data[2][y * Encoder->Frame->GetHandle()->linesize[2] + x] = 64 + x + i * 5;
            }
        }

        Encoder->Frame->GetHandle()->pts = i;

        /* encode the image */
        encode(c, Encoder->CodecContext, Encoder->Frame->GetHandle(), pkt, f);
    }

    /* flush the encoder */
    encode(c, Encoder->CodecContext, NULL, pkt, f);

    /* Add sequence end code to have a real MPEG file.
       It makes only sense because this tiny examples writes packets
       directly. This is called "elementary stream" and only works for some
       codecs. To create a valid file, you usually need to write packets
       into a proper file format or protocol; see mux.c.
     */
    if (codec->id == AV_CODEC_ID_MPEG1VIDEO || codec->id == AV_CODEC_ID_MPEG2VIDEO)
        fwrite(endcode, 1, sizeof(endcode), f);
    fclose(f);

    delete Encoder;

    av_packet_free(&pkt);

    return 0;
}

int TestFFmpegDemux(int argc, char** argv)
{
    int ret = 0;
    printf("debug 1\n");
    FormatContext *FC = new FormatContext();
    //AVFormatContext *fmt_ctx = NULL;
    //ret = avformat_open_input(&fmt_ctx, argv[1], NULL, NULL);
    printf("debug 2\n");
    ret = FC->OpenInput(argv[1],NULL, NULL);
    if (ret < 0)
    {
        fprintf(stderr, "Cannot open input file\n");
    }

    printf("debug 3\n");
    ret = FC->FindStreamInfo(NULL);
    if (ret < 0)
    {
        fprintf(stderr, "Cannot find stream information\n");
    }

    printf("nb_streams %d\n", FC->GetStreamCount());
    for (unsigned int i = 0; i < FC->GetStreamCount(); i++)
    {
        const AVCodec *codec = avcodec_find_decoder(FC->GetGetStreamCodecID(i));
        auto CodeType = FC->GetGetStreamCodecType(i);
        if (CodeType == AVMEDIA_TYPE_VIDEO)
        {
            printf("[%d]video stream, codec %s\n", i, codec->long_name);
        }
        else if (CodeType == AVMEDIA_TYPE_AUDIO)
        {
            printf("[%d]audio stream, codec %s\n", i, codec->long_name);
        }
        else if (CodeType == AVMEDIA_TYPE_SUBTITLE)
        {
            printf("[%d]subtitle stream, codec %s\n", i, codec->long_name);
        }
    }
    return 0;
}

int TestSWSContext(int argc, char** argv)
{
    printf("TestSWSContext\n");

    uint8_t *src_data[4], *dst_data[4];
    int src_linesize[4], dst_linesize[4];
    enum AVPixelFormat src_pix_fmt = AV_PIX_FMT_RGB24, dst_pix_fmt = AV_PIX_FMT_YUV420P;

    struct SwsContext *sws_ctx;

    int w = 8, h = 8;

    /* create scaling context */
    sws_ctx = sws_getContext(w, h, src_pix_fmt,
                             w, h, dst_pix_fmt,
                             SWS_BILINEAR, NULL, NULL, NULL);
#if 0
    const int* src_coeffs = sws_getCoefficients(SWS_CS_ITU709);  // 输入使用 BT.709
    const int* dst_coeffs = sws_getCoefficients(SWS_CS_ITU709);  // 输出也使用 BT.709

    int src_range = 0; // 0 表示输入是有限范围 (TV Range)
    int dst_range = 0; // 0 表示输出也是有限范围

    // 2. 设置默认的亮度、对比度、饱和度 (这些是标准值)
    int brightness = 0;
    int contrast = 1 << 16;   // 1.0 用定点数表示
    int saturation = 1 << 16; // 1.0 用定点数表示

    // 3. 应用这些颜色空间细节
    sws_setColorspaceDetails(sws_ctx,          // 你的 SwsContext
                             src_coeffs,       // YUV -> RGB 的转换表 (这里我们设为了 BT.709)
                             src_range,        // 输入范围
                             dst_coeffs,       // RGB -> YUV 的转换表 (这里我们设为了 BT.709)
                             dst_range,        // 输出范围
                             brightness,
                             contrast,
                             saturation);
#endif
    av_image_alloc(src_data, src_linesize,w, h, src_pix_fmt, 16);

    av_image_alloc(dst_data, dst_linesize,w, h, dst_pix_fmt, 1);
    for (int i = 0; i < 4; i++)
    {
        printf("src_linesize %d dst_linesize %d\n", src_linesize[i], dst_linesize[i]);
    }

 //   for (int i = 0; i < 4; i++)
    {
        src_data[0][0 * 32 + 0]  = 255;
        src_data[0][0 * 32 + 1]  = 100;
        src_data[0][0 * 32 + 2]  = 30;


        src_data[0][0 * 32 + 3]  = 254;
        src_data[0][0 * 32 + 4]  = 100;
        src_data[0][0 * 32 + 5]  = 30;


        src_data[0][1 * 32 + 0]  = 253;
        src_data[0][1 * 32 + 1]  = 100;
        src_data[0][1 * 32 + 2]  = 30;


        src_data[0][1 * 32 + 3]  = 252;
        src_data[0][1 * 32 + 4] = 100;
        src_data[0][1 * 32 + 5] = 30;
    }

    /* convert to destination format */
    sws_scale(sws_ctx, (const uint8_t * const*)src_data,
              src_linesize, 0, h, dst_data, dst_linesize);
    printf("Y plane: ");
    for(int i = 0; i < w * h; i++)
        printf("%d ", dst_data[0][i]);  // 输出: 138 138 138 138
    printf("\n");

    printf("U plane:\n");
    for (int i = 0; i < w * h / 4; i++)
    {
        printf("%d ", dst_data[1][i]);  // 输出: 75
    }
    printf("\n");

    printf("V plane:\n");
    for (int i = 0; i < w * h / 4; i++)
    {
        printf("%d ", dst_data[2][i]);
    }
    printf("\n");
    return 0;
}