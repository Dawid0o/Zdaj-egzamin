#include <wx/wx.h>
#include "_Main.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* mainFrame = new MyFrame("Main Menu");
    mainFrame->ShowFullScreen(true); // Set the frame to full-screen mode
    return true;
}
