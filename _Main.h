#ifndef MAIN_H
#define MAIN_H

#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnButton1(wxCommandEvent& event);
    void OnButton2(wxCommandEvent& event);
    void OnButton3(wxCommandEvent& event);
    void OnButton4(wxCommandEvent& event);
    void OnButton5(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_BUTTON1 = 1001,
    ID_BUTTON2,
    ID_BUTTON3,
    ID_BUTTON4,
    ID_BUTTON5
};

#endif // MAIN_H
