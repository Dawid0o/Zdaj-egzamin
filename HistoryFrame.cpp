#include "HistoryFrame.h"
#include "_Main.h"
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/textfile.h>

wxBEGIN_EVENT_TABLE(HistoryFrame, wxFrame)
    EVT_BUTTON(2001, HistoryFrame::OnBackButton)
wxEND_EVENT_TABLE()

HistoryFrame::HistoryFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxGetDisplaySize(), wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) {
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

    wxSize textCtrlSize(600, 400);
    wxPoint textCtrlPos((displaySize.GetWidth() - textCtrlSize.GetWidth()) / 2, (displaySize.GetHeight() - textCtrlSize.GetHeight()) / 2);
    wxTextCtrl *historyText = new wxTextCtrl(panel, wxID_ANY, "", textCtrlPos, textCtrlSize, wxTE_MULTILINE | wxTE_READONLY);

    wxTextFile historyFile("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/historia.txt");
    if (historyFile.Open()) {
        wxString str;
        for (str = historyFile.GetFirstLine(); !historyFile.Eof(); str = historyFile.GetNextLine()) {
            historyText->AppendText(str + "\n");
        }
        historyFile.Close();
    } else {
        historyText->SetValue("Brak historii gier.");
    }

    wxSize buttonSize(100, 50);
    wxPoint buttonPos((displaySize.GetWidth() - buttonSize.GetWidth()) / 2, displaySize.GetHeight() - buttonSize.GetHeight() - 10);
    wxButton *backButton = new wxButton(panel, 2001, "Powrot", buttonPos, buttonSize);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(backgroundBitmap, 1, wxEXPAND | wxALL, 0);

    panel->SetSizerAndFit(mainSizer);
    mainSizer->Fit(this);

    backButton->Raise();
    historyText->Raise();
}

void HistoryFrame::OnBackButton(wxCommandEvent& event) {
    this->Close(true);
    MyFrame *mainFrame = new MyFrame("Menu Główne");
    mainFrame->ShowFullScreen(true);
    mainFrame->Show(true);
}
