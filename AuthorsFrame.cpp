#include "AuthorsFrame.h"
#include "_Main.h"
#include <wx/sizer.h>
#include <wx/statbmp.h>

// Rozpoczecie definicji tabeli zdarzen dla klasy AuthorsFrame
wxBEGIN_EVENT_TABLE(AuthorsFrame, wxFrame)
    EVT_BUTTON(3001, AuthorsFrame::OnBackButton)  // Przypisanie przycisku z ID 3001 do metody OnBackButton
wxEND_EVENT_TABLE()

// Konstruktor klasy AuthorsFrame
AuthorsFrame::AuthorsFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxGetDisplaySize(), wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) {
    wxPanel *panel = new wxPanel(this, wxID_ANY);  // Utworzenie nowego panelu
    panel->SetSize(wxGetDisplaySize());  // Ustawienie rozmiaru panelu na rozmiar ekranu

    const wxString basePath = wxT("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/");

    wxImage::AddHandler(new wxJPEGHandler);  // Dodanie obslugi obrazow JPEG
    wxBitmap background;
    if (!background.LoadFile(basePath + wxT("biurko_czyste.jpg"), wxBITMAP_TYPE_JPEG)) {
        wxMessageBox("Nie mozna zaladowac obrazu tla: " + basePath + wxT("biurko_czyste.jpg"), "Blad", wxICON_ERROR);
    }

    wxImage bgImage = background.ConvertToImage();  // Konwersja bitmapy na obraz
    wxSize displaySize = wxGetDisplaySize();
    bgImage = bgImage.Scale(displaySize.GetWidth(), displaySize.GetHeight());  // Skalowanie obrazu do rozmiaru ekranu
    background = wxBitmap(bgImage);  // Konwersja z powrotem na bitmapę

    wxStaticBitmap *backgroundBitmap = new wxStaticBitmap(panel, wxID_ANY, background, wxPoint(0, 0), displaySize);  // Utworzenie statycznej bitmapy z tlem

    wxSize buttonSize(100, 50);
    wxPoint buttonPos((displaySize.GetWidth() - buttonSize.GetWidth()) / 2, displaySize.GetHeight() - buttonSize.GetHeight() - 10);
    wxButton *backButton = new wxButton(panel, 3001, "Powrot", buttonPos, buttonSize);  // Utworzenie przycisku "Powrot"

    // Dodanie wxStaticText dla "Autorzy:" na srodku
    wxSize textSize(200, 50);
    wxPoint textPos((displaySize.GetWidth() - textSize.GetWidth()) / 2, (displaySize.GetHeight() - textSize.GetHeight()) / 2);
    wxStaticText *authorsText = new wxStaticText(panel, wxID_ANY, "Autorzy:", textPos, textSize, wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    authorsText->SetForegroundColour(*wxBLACK);  // Ustawienie koloru czcionki na czarny
    authorsText->SetBackgroundColour(wxColour(255, 255, 255, 200));  // Ustawienie koloru tla na przezroczysty biały

    // Uzywanie absolutnego pozycjonowania do wycentrowania tekstu
    authorsText->SetPosition(wxPoint((displaySize.GetWidth() - authorsText->GetSize().GetWidth()) / 2, (displaySize.GetHeight() - authorsText->GetSize().GetHeight()) / 2));

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);  // Utworzenie pionowego sizer'a
    mainSizer->Add(backgroundBitmap, 1, wxEXPAND | wxALL, 0);  // Dodanie tla do sizer'a
    mainSizer->Add(backButton, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);  // Dodanie przycisku do sizer'a

    panel->SetSizerAndFit(mainSizer);  // Ustawienie sizer'a dla panelu i dostosowanie jego rozmiaru
    panel->Layout();  // Wykonanie layoutu panelu
}

// Metoda obslugujaca klikniecie przycisku "Powrot"
void AuthorsFrame::OnBackButton(wxCommandEvent& event) {
    this->Close(true);  // Zamkniecie obecnego okna
    MyFrame *mainFrame = new MyFrame("Menu Glowne");  // Utworzenie nowego okna glownego
    mainFrame->ShowFullScreen(true);  // Wyswietlenie okna glownego na pelnym ekranie
    mainFrame->Show(true);  // Pokazanie okna glownego
}
