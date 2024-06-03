#include "_App.h"
#include "_Main.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("Full Screen with Buttons and Background");
    frame->ShowFullScreen(true);
    frame->Show(true);
    return true;
}
