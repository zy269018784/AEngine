
int FileDownloader1(int argc, char** argv);
int ProgressDownloadermain(int argc, char** argv);
int HttpFileDownloader(int argc, char** argv)
{
#ifdef PROJECT_USE_BOOST
    return ProgressDownloadermain(argc, argv);
#endif
    return 0;
}