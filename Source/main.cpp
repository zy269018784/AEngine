int Play(char *file);
int MusicPlayer(int argc, char** argv);
int HttpFileDownloader(int argc, char** argv);
int DxfWriter(int argc, char** argv);
int DXFWrite2(int argc, char **argv);
int RHIExample();
int CEFMain(int argc, char* argv[]) ;
int main(int argc, char **argv)
{
	//return CEFMain(argc, argv);
	Play(argv[1]);
	return RHIExample();
	//return DXFWrite2(argc, argv);
	return Play(argv[1]);
	return HttpFileDownloader(argc, argv);
	return MusicPlayer(argc,argv);
	return 0;
}
