#include "wxWidgetWIndow.h"
#include <wx/wx.h>
wxWidgetWIndow::wxWidgetWIndow()
{

}

wxWidgetWIndow::~wxWidgetWIndow()
{

}

class DerivedApp : public wxApp
{
public:
    virtual bool OnInit() override;
};

wxIMPLEMENT_APP(DerivedApp);

bool DerivedApp::OnInit()
{
    wxFrame *the_frame = new wxFrame(nullptr, ID_MYFRAME, argv[0]);

    the_frame->Show(true);

    return true;
}