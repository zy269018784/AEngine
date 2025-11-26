#pragma once
#include "IWindow.h"
#ifdef PROJECT_USE_QT
#include <QWindow>
#endif

class QTWindow : public IWindow
{
public:
    QTWindow(IWindow *Parent = nullptr);
    ~QTWindow();
    virtual void Run() override final;
#ifdef PROJECT_USE_QT
public:
    QWindow *GetHandle();
#endif
public:
    void SetTitle(const char *Title) override final;
    void Resize(int W, int H) override final;
    void SetWidth(int arg) override final;
    void SetHeight(int arg) override final;
    void SetPosition(int X, int Y) override final;
private:
#ifdef PROJECT_USE_QT
    QWindow *Handle;
#endif
};

