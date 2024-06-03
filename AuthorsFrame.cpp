#include "AuthorsFrame.h"

wxBEGIN_EVENT_TABLE(AuthorsFrame, wxFrame)
    EVT_BUTTON(2001, AuthorsFrame::OnBackButton)
wxEND_EVENT_TABLE()

AuthorsFrame::AuthorsFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxGetDisplaySize(), wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) {
    // Tutaj dodaj kod inicjalizujący okno, np. tło, przycisk powrotu, etc.
}

void AuthorsFrame::OnBackButton(wxCommandEvent& event) {
    this->Close(true);
    MyFrame *mainFrame = new MyFrame("Menu Główne");
    mainFrame->ShowFullScreen(true);
    mainFrame->Show(true);
}

