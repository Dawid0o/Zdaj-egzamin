#ifndef QUIZFRAME_H
#define QUIZFRAME_H

#include <wx/wx.h>
#include <vector>
#include <string>

class QuizFrame : public wxFrame {
public:
    QuizFrame(const wxString& title);
    void LoadQuestions(const wxString& filePath);

private:
    void OnNextButton(wxCommandEvent& event);
    void OnSubmitButton(wxCommandEvent& event);
    void ShowQuestion(int index);
    void SaveResult(bool passed);
    void ShowResult(bool passed);

    std::vector<std::pair<std::string, std::string>> questions; // pair of question and answer
    int currentQuestionIndex;
    int correctAnswers;
    wxString name;

    wxStaticText* nameText;
    wxTextCtrl* nameInput;
    wxStaticText* questionText;
    wxTextCtrl* answerInput;
    wxButton* nextButton;
    wxPanel* panel;
    wxButton* submitButton;

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_QUIZ_NEXT_BUTTON = 4001,
    ID_QUIZ_SUBMIT_BUTTON = 4002
};

#endif // QUIZFRAME_H
