#include "CEFWindow.h"
#include <include/cef_app.h>
#include <include/wrapper/cef_helpers.h>
CEFWindow::CEFWindow()
{

}

CEFWindow::~CEFWindow()
{

}

class SimpleClient : public CefClient, public CefLifeSpanHandler {
public:
    SimpleClient() {}

    // CefClient methods
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    // CefLifeSpanHandler methods
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
        CEF_REQUIRE_UI_THREAD();
    }

    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override {
        CEF_REQUIRE_UI_THREAD();
        CefQuitMessageLoop();
    }

private:
    IMPLEMENT_REFCOUNTING(SimpleClient);
};

class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
    SimpleApp() {}

    // CefApp methods
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
        return this;
    }

    // CefBrowserProcessHandler methods
    virtual void OnContextInitialized() override {
        CEF_REQUIRE_UI_THREAD();

        CefWindowInfo window_info;

        CefBrowserSettings browser_settings;
        std::string url = "https://www.google.com"; // or "file:///path/to/your/hello_world.html"

        CefRefPtr<SimpleClient> client(new SimpleClient());
        CefBrowserHost::CreateBrowser(window_info, client, url, browser_settings, {}, {});
    }

private:
    IMPLEMENT_REFCOUNTING(SimpleApp);
};

int CEFMain(int argc, char* argv[])
{
    CefMainArgs main_args(argc, argv);

    // Execute sub-process logic, if any
    int exit_code = CefExecuteProcess(main_args, {}, {});
    if (exit_code >= 0) {
        return exit_code;
    }

    // Initialize CEF
    CefSettings settings;
    CefRefPtr<SimpleApp> app(new SimpleApp());

    // Initialize CEF
    CefInitialize(main_args, settings, app.get(), NULL);

    // Run message loop
    CefRunMessageLoop();

    // Shutdown CEF
    CefShutdown();

    return 0;
}