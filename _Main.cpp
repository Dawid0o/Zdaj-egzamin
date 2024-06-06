#include "_Main.h"
#include "HistoryFrame.h"
#include "AuthorsFrame.h"
#include "SlideShowFrame.h"
#include "QuizFrame.h"
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <vector>

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(1001, MyFrame::OnButton1)
    EVT_BUTTON(1002, MyFrame::OnButton2)
    EVT_BUTTON(1003, MyFrame::OnButton3)
    EVT_BUTTON(1004, MyFrame::OnButton4)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxGetDisplaySize(), wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    panel->SetSize(wxGetDisplaySize());

    const wxString basePath = wxT("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/");

    wxImage::AddHandler(new wxJPEGHandler);
    wxBitmap background;
    if (!background.LoadFile(basePath + wxT("menu.jpg"), wxBITMAP_TYPE_JPEG)) {
        wxMessageBox("Nie można załadować obrazu tła: " + basePath + wxT("menu.jpg"), "Błąd", wxICON_ERROR);
    }

    wxImage bgImage = background.ConvertToImage();
    wxSize displaySize = wxGetDisplaySize();
    bgImage = bgImage.Scale(displaySize.GetWidth(), displaySize.GetHeight());
    background = wxBitmap(bgImage);

    wxStaticBitmap* backgroundBitmap = new wxStaticBitmap(panel, wxID_ANY, background, wxPoint(0, 0), displaySize);

    wxBitmap button1Image(basePath + wxT("start.jpg"), wxBITMAP_TYPE_JPEG);
    wxBitmap button2Image(basePath + wxT("Autorzy.jpg"), wxBITMAP_TYPE_JPEG);
    wxBitmap button3Image(basePath + wxT("historia.jpg"), wxBITMAP_TYPE_JPEG);
    wxBitmap button4Image(basePath + wxT("Exit.jpg"), wxBITMAP_TYPE_JPEG);

    wxSize buttonSize(300, 100);

    wxImage button1Img = button1Image.ConvertToImage();
    wxImage button2Img = button2Image.ConvertToImage();
    wxImage button3Img = button3Image.ConvertToImage();
    wxImage button4Img = button4Image.ConvertToImage();

    button1Img = button1Img.Scale(buttonSize.GetWidth(), buttonSize.GetHeight());
    button2Img = button2Img.Scale(buttonSize.GetWidth(), buttonSize.GetHeight());
    button3Img = button3Img.Scale(buttonSize.GetWidth(), buttonSize.GetHeight());
    button4Img = button4Img.Scale(buttonSize.GetWidth(), buttonSize.GetHeight());

    button1Image = wxBitmap(button1Img);
    button2Image = wxBitmap(button2Img);
    button3Image = wxBitmap(button3Img);
    button4Image = wxBitmap(button4Img);

    int buttonXPos = (displaySize.GetWidth() - buttonSize.GetWidth()) / 2;
    wxBitmapButton* button1 = new wxBitmapButton(panel, 1001, button1Image, wxPoint(buttonXPos, 400), buttonSize);
    wxBitmapButton* button2 = new wxBitmapButton(panel, 1002, button2Image, wxPoint(buttonXPos, 500), buttonSize);
    wxBitmapButton* button3 = new wxBitmapButton(panel, 1003, button3Image, wxPoint(buttonXPos, 600), buttonSize);
    wxBitmapButton* button4 = new wxBitmapButton(panel, 1004, button4Image, wxPoint(buttonXPos, 700), buttonSize);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(backgroundBitmap, 1, wxEXPAND | wxALL, 0);

    panel->SetSizerAndFit(mainSizer);
    mainSizer->Fit(this);

    button1->Raise();
    button2->Raise();
    button3->Raise();
    button4->Raise();
}

void MyFrame::OnButton1(wxCommandEvent& event) {
    std::vector<wxString> imagePaths = {
        "C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/dialog0.jpg",
        "C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/dialog1.jpg",
        "C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/dialog2.jpg"
    };
    SlideShowFrame* slideShowFrame = new SlideShowFrame("Slideshow");
    slideShowFrame->LoadImages(imagePaths);
    slideShowFrame->ShowFullScreen(true);
    slideShowFrame->Show(true);
    this->Hide();
}

void MyFrame::OnButton2(wxCommandEvent& event) {
    AuthorsFrame* authorsFrame = new AuthorsFrame("Autorzy");
    authorsFrame->ShowFullScreen(true);
    authorsFrame->Show(true);
    this->Hide();
}

void MyFrame::OnButton3(wxCommandEvent& event) {
    HistoryFrame* historyFrame = new HistoryFrame("Historia Gier");
    historyFrame->ShowFullScreen(true);
    historyFrame->Show(true);
    this->Hide();
}

void MyFrame::OnButton4(wxCommandEvent& event) {
    Close(true);
}
