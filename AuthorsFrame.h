#ifndef AUTHORS_FRAME_H
#define AUTHORS_FRAME_H

#include <wx/wx.h>

class AuthorsFrame : public wxFrame {
public:
    AuthorsFrame(const wxString& title);

private:
    void OnBackButton(wxCommandEvent& event);
    wxStaticText* authorsText; // Declare the wxStaticText control

    wxDECLARE_EVENT_TABLE();
};

#endif // AUTHORS_FRAME_H
