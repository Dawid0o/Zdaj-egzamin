#include "Zdaj_egzaminApp.h"

wxIMPLEMENT_APP(Zdaj_egzaminApp);

bool Zdaj_egzaminApp::OnInit()
{
    Zdaj_egzaminFrame *frame = new Zdaj_egzaminFrame(nullptr, wxID_ANY, "Tytuł okna");
    frame->Show(true);
    return true;
}
