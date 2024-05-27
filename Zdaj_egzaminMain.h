#ifndef ZDAJ_EGZAMINMAIN_H
#define ZDAJ_EGZAMINMAIN_H

#include <wx/wx.h>
#include <vector>

class Zdaj_egzaminFrame : public wxFrame
{
public:
    Zdaj_egzaminFrame(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxEmptyString, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

private:
    void OnStart(wxCommandEvent &event);
    void OnAuthors(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnReturnToMenu(wxCommandEvent &event);
    void OnNextQuestion(wxCommandEvent &event);
    void ShowQuestion(size_t questionNumber);
    int CalculateScore();
    void OnGameHistory(wxCommandEvent& event); // Dodaj deklarację funkcji obsługi zdarzenia przycisku "Historia gry"

    wxButton *m_startButton;
    wxButton *m_authorsButton;
    wxButton *m_exitButton;
    wxButton *m_menuButton;
    wxButton *m_nextButton;
    wxButton *m_gameHistoryButton; // Dodaj deklarację przycisku "Historia gry"
    wxStaticText *m_infoText;
    wxStaticText *m_questionText;
    wxPanel *m_panel;

    size_t m_currentQuestion;
    int m_score;
    std::vector<std::pair<wxString, std::vector<wxString>>> m_quizData;
    std::vector<int> m_correctAnswers;
    std::vector<wxCheckBox*> m_answerCheckboxes;

    // Deklaracja statycznych identyfikatorów
    static const int ID_Start;
    static const int ID_Authors;
    static const int ID_Exit;
    static const int ID_Menu;
    static const int ID_Next;
    static const int ID_GameHistory; // Dodaj deklarację identyfikatora przycisku "Historia gry"

    wxDECLARE_EVENT_TABLE();
};

#endif // ZDAJ_EGZAMINMAIN_H
