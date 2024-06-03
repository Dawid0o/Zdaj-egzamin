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

    wxDECLARE_EVENT_TABLE();
};

#endif // MAIN_H
