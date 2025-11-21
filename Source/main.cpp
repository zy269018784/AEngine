int Play(char *file);
int MusicPlayer(int argc, char** argv);
int HttpFileDownloader(int argc, char** argv);
int DxfWriter(int argc, char** argv);
int DXFWrite2(int argc, char **argv);
int main(int argc, char **argv)
{
	return DXFWrite2(argc, argv);
	return DxfWriter(argc, argv);
	return Play(argv[1]);
	return HttpFileDownloader(argc, argv);
	return MusicPlayer(argc,argv);
	return 0;
}
