#include "SlideShowFrame.h"
#include "QuizFrame.h"

wxBEGIN_EVENT_TABLE(SlideShowFrame, wxFrame)
    EVT_BUTTON(ID_SLIDESHOW_NEXT_BUTTON, SlideShowFrame::OnNextButton)
    EVT_BUTTON(ID_START_QUIZ_BUTTON, SlideShowFrame::OnStartQuizButton)
wxEND_EVENT_TABLE()

SlideShowFrame::SlideShowFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxGetDisplaySize(), wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE),
      currentImageIndex(0) {
    panel = new wxPanel(this, wxID_ANY);
    panel->SetSize(wxGetDisplaySize());

    wxSize displaySize = wxGetDisplaySize();
    imageDisplay = new wxStaticBitmap(panel, wxID_ANY, wxNullBitmap, wxPoint(0, 0), displaySize);
    nextButton = new wxButton(panel, ID_SLIDESHOW_NEXT_BUTTON, "Nastepny", wxPoint((displaySize.GetWidth() - 100) / 2, displaySize.GetHeight() - 60), wxSize(100, 50));
    startQuizButton = new wxButton(panel, ID_START_QUIZ_BUTTON, "Zacznij egzamin", wxPoint((displaySize.GetWidth() - 100) / 2, displaySize.GetHeight() - 60), wxSize(100, 50));
    startQuizButton->Hide();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(imageDisplay, 1, wxEXPAND | wxALL, 0);
    mainSizer->Add(nextButton, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    mainSizer->Add(startQuizButton, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    panel->SetSizerAndFit(mainSizer);
    mainSizer->Fit(this);

    nextButton->Raise();
}

void SlideShowFrame::OnNextButton(wxCommandEvent& event) {
    if (currentImageIndex + 1 < static_cast<int>(images.size())) {
        currentImageIndex++;
        ShowImage(currentImageIndex);
    } else {
        nextButton->Hide();
        startQuizButton->Show();
        panel->Layout();
    }
}

void SlideShowFrame::LoadImages(const std::vector<wxString>& imagePaths) {
    images = imagePaths;
    if (!images.empty()) {
        ShowImage(0);
    }
}

void SlideShowFrame::ShowImage(int index) {
    wxBitmap bitmap;
    bitmap.LoadFile(images[index], wxBITMAP_TYPE_JPEG);

    // Scaling the image to fit the display size
    wxImage image = bitmap.ConvertToImage();
    wxSize displaySize = wxGetDisplaySize();
    image.Rescale(displaySize.GetWidth(), displaySize.GetHeight(), wxIMAGE_QUALITY_HIGH);
    bitmap = wxBitmap(image);

    imageDisplay->SetBitmap(bitmap);
}

void SlideShowFrame::OnStartQuizButton(wxCommandEvent& event) {
    this->Hide();
    QuizFrame* quizFrame = new QuizFrame("Quiz");
    quizFrame->LoadQuestions("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/questions.txt");
    quizFrame->ShowFullScreen(true);
    quizFrame->Show(true);
}
