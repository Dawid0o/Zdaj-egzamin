#ifndef ZDAJ_EGZAMINMAIN_H
#define ZDAJ_EGZAMINMAIN_H

#include <wx/wx.h>
#include <wx/sound.h>
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
    void OnGameHistory(wxCommandEvent& event);
    void OnToggleMusic(wxCommandEvent &event); // Add this line
    void ShowQuestion(size_t questionNumber);

    wxButton *m_startButton;
    wxButton *m_authorsButton;
    wxButton *m_exitButton;
    wxButton *m_menuButton;
    wxButton *m_nextButton;
    wxButton *m_gameHistoryButton;
    wxButton *m_toggleMusicButton; // Add this line
    wxStaticText *m_infoText;
    wxStaticText *m_questionText;
    wxStaticText *m_historyText;
    wxScrolledWindow *m_scrolledWindow;
    wxPanel *m_panel;
    wxSound m_backgroundMusic; // Add this line
    bool m_musicPlaying; // Add this line

    size_t m_currentQuestion;
    int m_score;
    std::vector<std::pair<wxString, std::vector<wxString>>> m_quizData;
    std::vector<int> m_correctAnswers;
    std::vector<wxCheckBox*> m_answerCheckboxes;

    static const int ID_Start;
    static const int ID_Authors;
    static const int ID_Exit;
    static const int ID_Menu;
    static const int ID_Next;
    static const int ID_GameHistory;
    static const int ID_ToggleMusic; // Add this line

    wxDECLARE_EVENT_TABLE();
};

#endif // ZDAJ_EGZAMINMAIN_H
