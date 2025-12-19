// minimal_rtsp_client.cpp
//extern "C"
//{
#ifdef PROJECT_USE_LIVE555
    #include <liveMedia/liveMedia.hh>
    #include <BasicUsageEnvironment/BasicUsageEnvironment.hh>
#endif
//}
UsageEnvironment* env;
#ifdef PROJECT_USE_LIVE555
// Callback handlers
//static void continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString);
void responseHandler(RTSPClient* rtspClient,
                 int resultCode, char* resultString)
{

}

static void continueAfterSETUP(RTSPClient* rtspClient,
                               int resultCode, char* resultString);
static void continueAfterPLAY(RTSPClient* rtspClient,
                              int resultCode, char* resultString);
#endif
int Live555Main(int argc, char** argv) {
#ifdef PROJECT_USE_LIVE555
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rtsp-url>\n", argv[0]);
        return 1;
    }

    // 1. Create task scheduler and environment
    TaskScheduler* scheduler = BasicTaskScheduler::createNew();
    env = BasicUsageEnvironment::createNew(*scheduler);

    // 2. Create RTSP client
    RTSPClient* rtspClient = RTSPClient::createNew(*env, argv[1],
                                                   0,
                                                   "myRTSPClient");
    if (rtspClient == NULL) {
        *env << "Failed to create RTSP client: " << env->getResultMsg() << "\n";
        return 1;
    }

    // 3. Start the RTSP session
    rtspClient->sendDescribeCommand(responseHandler);

    // 4. Run the event loop
    env->taskScheduler().doEventLoop();
#endif
    return 0;
}