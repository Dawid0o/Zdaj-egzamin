#include "QuizFrame.h"
#include "SubmitHandler.h"
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <fstream>
#include <sstream>
#include <iostream> // Include for debugging
#include <ctime> // Include for date and time

wxBEGIN_EVENT_TABLE(QuizFrame, wxFrame)
    EVT_BUTTON(ID_QUIZ_NEXT_BUTTON, QuizFrame::OnNextButton)
    EVT_BUTTON(ID_QUIZ_SUBMIT_BUTTON, QuizFrame::OnSubmitButton)
wxEND_EVENT_TABLE()

QuizFrame::QuizFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxGetDisplaySize(), wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE),
      currentQuestionIndex(0), correctAnswers(0) {
    panel = new wxPanel(this, wxID_ANY);
    panel->SetSize(wxGetDisplaySize());

    wxSize displaySize = wxGetDisplaySize();

    // Set background
    wxImage::AddHandler(new wxJPEGHandler);
    wxBitmap background;
    if (!background.LoadFile(wxT("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/biurko_czyste.jpg"), wxBITMAP_TYPE_JPEG)) {
        wxMessageBox("Nie można załadować obrazu tła", "Błąd", wxICON_ERROR);
    }

    wxImage bgImage = background.ConvertToImage();
    bgImage = bgImage.Scale(displaySize.GetWidth(), displaySize.GetHeight());
    background = wxBitmap(bgImage);

    wxStaticBitmap* backgroundBitmap = new wxStaticBitmap(panel, wxID_ANY, background, wxPoint(0, 0), displaySize);

    int margin = 200; // Adjust margin to fit the brown area
    int fieldWidth = displaySize.GetWidth() - 2 * margin;

    nameText = new wxStaticText(panel, wxID_ANY, "Twoje Imie:", wxPoint(margin, displaySize.GetHeight() / 2 - 80), wxSize(fieldWidth, 30));
    nameInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(margin, displaySize.GetHeight() / 2 - 40), wxSize(fieldWidth, 30));

    questionText = new wxStaticText(panel, wxID_ANY, "", wxPoint(margin, displaySize.GetHeight() / 2 - 80), wxSize(fieldWidth, 30));
    answerInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(margin, displaySize.GetHeight() / 2 - 40), wxSize(fieldWidth, 30));
    nextButton = new wxButton(panel, ID_QUIZ_NEXT_BUTTON, "Nastepne", wxPoint((displaySize.GetWidth() - 100) / 2, displaySize.GetHeight() - 80), wxSize(100, 50));
    submitButton = new wxButton(panel, ID_QUIZ_SUBMIT_BUTTON, "Oddaj kartke", wxPoint((displaySize.GetWidth() - 100) / 2, displaySize.GetHeight() - 80), wxSize(100, 50));
    submitButton->Hide();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(backgroundBitmap, 1, wxEXPAND | wxALL, 0);

    panel->SetSizerAndFit(mainSizer);
    mainSizer->Fit(this);

    nameText->Raise();
    nameInput->Raise();
    nextButton->Raise();
    submitButton->Raise();

    // Hide question and answer inputs initially
    questionText->Hide();
    answerInput->Hide();
}

void QuizFrame::LoadQuestions(const wxString& filePath) {
    std::ifstream file(filePath.ToStdString());
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string question, answer;
        if (std::getline(iss, question, '|') && std::getline(iss, answer)) {
            questions.emplace_back(question, answer);
        }
    }
}

void QuizFrame::OnNextButton(wxCommandEvent& event) {
    if (nameInput->IsShown()) {
        name = nameInput->GetValue();
        nameText->Hide();
        nameInput->Hide();
        questionText->Show();
        answerInput->Show();
        answerInput->SetFocus();  // Set focus to the answer input field
        ShowQuestion(0);
        panel->Layout();
        return;
    }

    if (currentQuestionIndex < questions.size()) {
        if (answerInput->GetValue().ToStdString() == questions[currentQuestionIndex].second) {
            correctAnswers++;
        }

        currentQuestionIndex++;
        if (currentQuestionIndex < questions.size()) {
            ShowQuestion(currentQuestionIndex);
        } else {
            nextButton->Hide();
            submitButton->Show();
        }
        panel->Layout();
    }
}

void QuizFrame::OnSubmitButton(wxCommandEvent& event) {
    bool passed = (correctAnswers > static_cast<int>(questions.size()) / 2);
    SaveResult(passed);
    ShowResult(passed);
}

void QuizFrame::ShowQuestion(int index) {
    if (index < questions.size()) {
        questionText->SetLabel(questions[index].first);
        answerInput->Clear();
        answerInput->SetFocus();  // Ensure the answer input field has focus
    }
}

void QuizFrame::SaveResult(bool passed) {
    // Get current time
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    // Format the date and time
    char dateTimeBuffer[80];
    std::strftime(dateTimeBuffer, sizeof(dateTimeBuffer), "%Y-%m-%d %H:%M:%S", now);

    // Open history file and save result
    std::ofstream historyFile("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/historia.txt", std::ios::app);
    if (historyFile.is_open()) {
        historyFile << name.ToStdString() << " " << (passed ? "Zdane" : "Oblane") << " Wynik: " << correctAnswers << "/" << questions.size() << " o: " << dateTimeBuffer << "\n";
        historyFile.close();
    }
}

void QuizFrame::ShowResult(bool passed) {
    std::cout << "Debug: Creating SubmitHandler" << std::endl;
    panel->DestroyChildren(); // Clear the current content
    SubmitHandler* resultPanel = new SubmitHandler(panel, passed, correctAnswers, questions.size());
    panel->SetSizer(new wxBoxSizer(wxVERTICAL));
    panel->GetSizer()->Add(resultPanel, 1, wxEXPAND);
    panel->Layout();
    std::cout << "Debug: SubmitHandler displayed" << std::endl;
}
