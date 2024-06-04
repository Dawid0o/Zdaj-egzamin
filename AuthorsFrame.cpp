#include "AuthorsFrame.h"
#include "_Main.h"
#include <wx/sizer.h>
#include <wx/statbmp.h>

wxBEGIN_EVENT_TABLE(AuthorsFrame, wxFrame)
    EVT_BUTTON(3001, AuthorsFrame::OnBackButton)
wxEND_EVENT_TABLE()

AuthorsFrame::AuthorsFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxGetDisplaySize(), wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) {
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    panel->SetSize(wxGetDisplaySize());

    const wxString basePath = wxT("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/");

    wxImage::AddHandler(new wxJPEGHandler);
    wxBitmap background;
    if (!background.LoadFile(basePath + wxT("biurko_czyste.jpg"), wxBITMAP_TYPE_JPEG)) {
        wxMessageBox("Nie można załadować obrazu tła: " + basePath + wxT("biurko_czyste.jpg"), "Błąd", wxICON_ERROR);
    }

    wxImage bgImage = background.ConvertToImage();
    wxSize displaySize = wxGetDisplaySize();
    bgImage = bgImage.Scale(displaySize.GetWidth(), displaySize.GetHeight());
    background = wxBitmap(bgImage);

    wxStaticBitmap *backgroundBitmap = new wxStaticBitmap(panel, wxID_ANY, background, wxPoint(0, 0), displaySize);

    wxSize buttonSize(100, 50);
    wxPoint buttonPos((displaySize.GetWidth() - buttonSize.GetWidth()) / 2, displaySize.GetHeight() - buttonSize.GetHeight() - 10);
    wxButton *backButton = new wxButton(panel, 3001, "Powrot", buttonPos, buttonSize);

    // Add the wxStaticText for "Autorzy:" in the center
    wxPoint textPos((displaySize.GetWidth() - 200) / 2, (displaySize.GetHeight() - 50) / 2);
    authorsText = new wxStaticText(panel, wxID_ANY, "Autorzy:", textPos, wxSize(200, 50), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    authorsText->SetForegroundColour(*wxBLACK);
    authorsText->SetBackgroundColour(wxColour(255, 255, 255, 200)); // semi-transparent background

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(backgroundBitmap, 1, wxEXPAND | wxALL, 0);

    panel->SetSizerAndFit(mainSizer);
    mainSizer->Fit(this);

    backButton->Raise();
    authorsText->Raise();

    panel->Layout();  // Ensure the panel lays out the controls correctly
}

void AuthorsFrame::OnBackButton(wxCommandEvent& event) {
    this->Close(true);
    MyFrame *mainFrame = new MyFrame("Menu Główne");
    mainFrame->ShowFullScreen(true);
    mainFrame->Show(true);
}
