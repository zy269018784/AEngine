#ifdef PROJECT_USE_QT
#include <QApplication>
#endif

// QT must before x11
#include "../Window/QTWindow.h"
#include "../Window/SFMLWindow.h"
#include "../Window/X11Window.h"
#include "../Window/GLFWWindow.h"

#include "../AudioPlayer/SDL3AudioPlayer.h"
#include "../AudioPlayer/SFMLAudioPlayer.h"
#include "../AudioPlayer/IrrKlangAudioPlayer.h"

#include <iostream>
#include <memory>
#include <stdio.h>

#include "../AudioPlayer/IrrKlangAudioPlayer.h"

#include "../MultiMedia/AudioFile/PCM.h"
#include "../MultiMedia/AudioFile/MP3FileFormat.h"

int HelloFLTK() {
    //FLTKWindow Window;
    //return Fl::run();
    return 0;
}

int HelloX11()
{
    std::unique_ptr<IWindow> Window;
    Window.reset(new X11Window());
    Window->SetTitle("X11 Window");
    //Window->SetWidth(960);
    //Window->SetHeight(600);
    Window->Resize(960, 600);
    Window->SetPosition(960, 0);
    Window->Run();
    return 0;
}

int HelloGLFW()
{
#ifdef PROJECT_USE_GLFW
    glfwInit();
#endif
    std::unique_ptr<IWindow> Window;
    Window.reset(new GLFWWindow());
    Window->SetTitle("GLFW Window");
    Window->SetWidth(960);
    Window->SetHeight(600);
    Window->SetPosition(960, 0);
    Window->Run();
#ifdef PROJECT_USE_GLFW
    glfwTerminate();
#endif
    return 0;
}

int HelloSFML()
{
    std::unique_ptr<IWindow> Window;
    Window.reset(new SFMLWindow());
    Window->SetTitle("SFML Window");
    Window->Resize(960, 600);
    //Window->SetWidth(960);
    //Window->SetHeight(600);
    Window->SetPosition(960, 0);
    Window->Run();
    return 0;
}

int HelloQT(int argc, char **argv)
{
#ifdef PROJECT_USE_QT
    QApplication app(argc, argv);
#endif
    std::unique_ptr<IWindow> Window;
    Window.reset(new QTWindow());
    Window->SetTitle("QT Window");
    Window->SetWidth(960);
    Window->SetHeight(600);
    Window->SetPosition(960, 0);
    Window->Run();
#ifdef PROJECT_USE_QT
    return app.exec();
#else
    return 0;
#endif
}

int HelloIWindow() {

    std::unique_ptr<IWindow> Window;
    Window.reset(new X11Window());
    Window->Run();
    return 0;
}

int HelloSDL3AudioPlayer(int argc, char **argv)
{
    std::unique_ptr<IAudioPlayer> Player;
    Player.reset(new SDL3AudioPlayer());
    Player->Play(argv[1]);
    return 0;
}


int HelloSFMLAudioPlayer(int argc, char **argv)
{
    std::unique_ptr<IAudioPlayer> Player;
    Player.reset(new SFMLAudioPlayer());
    Player->Play(argv[1]);
    while (1);
    return 0;
}

int HelloIrrKlangAudioPlayer(int argc, char **argv)
{
    std::unique_ptr<IAudioPlayer> Player;
    Player.reset(new IrrKlangAudioPlayer());
    Player->Play(argv[1]);
    while (1);
    return 0;
}

int EncodeToMP3(char* InputFilename, char* OutputFilename)
{
    PCM pcm;
    pcm.SetChannels(2);
    pcm.SetBytesPerSample(2);
   // pcm.SetSampleRate(44100);
    pcm.SetSampleRate(48000);
    pcm.ReadFromRawFile(InputFilename);

    MP3FileFormat mp3ff;
    return mp3ff.LameEncoder(&pcm, OutputFilename);
}

int TestPortaudio();
int TestModbusServer(int argc, char *argv[]);
int ModuleTest(int argc, char **argv)
{
    return TestModbusServer(argc, argv);
    return HelloSFMLAudioPlayer(argc, argv);
    return EncodeToMP3(argv[1], argv[2]);
    return TestPortaudio();
#ifdef PROJECT_USE_FTLK
    std::cout << "PROJECT_USE_FTLK" << std::endl;
#endif
    //HelloX11();
    
    //HelloGLFW();
    //HelloSFML();
    return 0;
}