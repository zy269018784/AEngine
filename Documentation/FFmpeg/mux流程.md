1.
    const AVOutputFormat *fmt;
    const char *filename;
    AVFormatContext *oc; 
    avformat_alloc_output_context2

    fmt = oc->oformat;


2. 添加流
   avformat_new_stream(oc, NULL
    