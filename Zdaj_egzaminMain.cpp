#include <wx/wx.h>
#include <wx/textfile.h>
#include <wx/datetime.h>
#include <wx/textdlg.h>
#include <wx/sound.h>
#include <vector>
#include <utility>
#include <algorithm> // For std::shuffle
#include <random>    // For std::random_device and std::mt19937
#include "Zdaj_egzaminMain.h"

const int Zdaj_egzaminFrame::ID_Start = wxNewId();
const int Zdaj_egzaminFrame::ID_Authors = wxNewId();
const int Zdaj_egzaminFrame::ID_Exit = wxNewId();
const int Zdaj_egzaminFrame::ID_Menu = wxNewId();
const int Zdaj_egzaminFrame::ID_Next = wxNewId();
const int Zdaj_egzaminFrame::ID_GameHistory = wxNewId();
const int Zdaj_egzaminFrame::ID_ToggleMusic = wxNewId(); // Add this line

wxBEGIN_EVENT_TABLE(Zdaj_egzaminFrame, wxFrame)
    EVT_BUTTON(ID_Start, Zdaj_egzaminFrame::OnStart)
    EVT_BUTTON(ID_Authors, Zdaj_egzaminFrame::OnAuthors)
    EVT_BUTTON(ID_Exit, Zdaj_egzaminFrame::OnExit)
    EVT_BUTTON(ID_Menu, Zdaj_egzaminFrame::OnReturnToMenu)
    EVT_BUTTON(ID_Next, Zdaj_egzaminFrame::OnNextQuestion)
    EVT_BUTTON(ID_GameHistory, Zdaj_egzaminFrame::OnGameHistory)
    EVT_BUTTON(ID_ToggleMusic, Zdaj_egzaminFrame::OnToggleMusic) // Add this line
wxEND_EVENT_TABLE()

Zdaj_egzaminFrame::Zdaj_egzaminFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : wxFrame(parent, id, title, pos, size, style), m_currentQuestion(0), m_score(0), m_musicPlaying(false)
{
    m_quizData.push_back(std::make_pair("Pytanie 1: Jaki jest kolor nieba?", std::vector<wxString>{"Niebieski", "Czerwony", "Zielony", "Żółty"}));
    m_quizData.push_back(std::make_pair("Pytanie 2: Ile wynosi 2 + 2?", std::vector<wxString>{"3", "4", "5", "6"}));
    m_quizData.push_back(std::make_pair("Pytanie 3: Która planeta jest znana jako Czerwona Planeta?", std::vector<wxString>{"Mars", "Wenus", "Jowisz", "Saturn"}));
    m_quizData.push_back(std::make_pair("Pytanie 4: Ile boków ma kwadrat?", std::vector<wxString>{"Cztery", "Trzy", "Pięć", "Sześć"}));
    m_quizData.push_back(std::make_pair("Pytanie 5: Jakie jest największe zwierzę na świecie?", std::vector<wxString>{"Wieloryb", "Słoń", "Rekin", "Hipopotam"}));

    m_correctAnswers.push_back(0); // Poprawna odpowiedź dla pierwszego pytania
    m_correctAnswers.push_back(1); // Poprawna odpowiedź dla drugiego pytania
    m_correctAnswers.push_back(0); // Poprawna odpowiedź dla trzeciego pytania
    m_correctAnswers.push_back(0); // Poprawna odpowiedź dla czwartego pytania
    m_correctAnswers.push_back(0); // Poprawna odpowiedź dla piątego pytania

    m_panel = new wxPanel(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_infoText = new wxStaticText(m_panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    sizer->Add(m_infoText, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    m_infoText->Hide();

    m_questionText = new wxStaticText(m_panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    sizer->Add(m_questionText, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    m_questionText->Hide();

    // Create a scrolled window for game history
    m_scrolledWindow = new wxScrolledWindow(m_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    m_scrolledWindow->SetScrollRate(5, 5);
    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);
    m_historyText = new wxStaticText(m_scrolledWindow, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    scrolledSizer->Add(m_historyText, 1, wxEXPAND | wxALL, 10);
    m_scrolledWindow->SetSizer(scrolledSizer);
    sizer->Add(m_scrolledWindow, 1, wxEXPAND | wxALL, 10);
    m_scrolledWindow->Hide();

    m_startButton = new wxButton(m_panel, ID_Start, "Start Quiz");
    sizer->Add(m_startButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    m_authorsButton = new wxButton(m_panel, ID_Authors, "Authors");
    sizer->Add(m_authorsButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    m_gameHistoryButton = new wxButton(m_panel, ID_GameHistory, "Historia gry");
    sizer->Add(m_gameHistoryButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    m_exitButton = new wxButton(m_panel, ID_Exit, "Exit");
    sizer->Add(m_exitButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    m_menuButton = new wxButton(m_panel, ID_Menu, "Return to Menu");
    sizer->Add(m_menuButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    m_menuButton->Hide();

    m_nextButton = new wxButton(m_panel, ID_Next, "Next");
    sizer->Add(m_nextButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    m_nextButton->Hide();

    m_toggleMusicButton = new wxButton(m_panel, ID_ToggleMusic, "Toggle Music");
    sizer->Add(m_toggleMusicButton, 0, wxALIGN_BOTTOM | wxALL, 10);

    m_panel->SetSizer(sizer);
    Layout();

    // Make the frame full screen
    ShowFullScreen(true);

    // Load the background music
    m_backgroundMusic.Create("background.wav");
}

void Zdaj_egzaminFrame::OnStart(wxCommandEvent &event)
{
    m_currentQuestion = 0;
    m_score = 0;

    // Shuffle the questions
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_quizData.begin(), m_quizData.end(), g);
    std::shuffle(m_correctAnswers.begin(), m_correctAnswers.end(), g);

    ShowQuestion(m_currentQuestion);

    m_startButton->Hide();
    m_authorsButton->Hide();
    m_exitButton->Hide();
    m_infoText->Hide();
    m_gameHistoryButton->Hide();

    m_questionText->Show();
    m_nextButton->Show();
    Layout();
}

void Zdaj_egzaminFrame::OnAuthors(wxCommandEvent &event)
{
    m_startButton->Hide();
    m_authorsButton->Hide();
    m_exitButton->Hide();
    m_gameHistoryButton->Hide();

    m_infoText->SetLabel("Autorzy:\nJohn Doe\nJane Smith\n");
    m_infoText->Show();

    wxBoxSizer* authorsSizer = new wxBoxSizer(wxVERTICAL);
    authorsSizer->Add(m_infoText, 0, wxALIGN_LEFT | wxALL, 10);
    authorsSizer->Add(m_menuButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    m_menuButton->Show(true);

    m_panel->SetSizer(authorsSizer);
    m_panel->Layout();
    Layout();
}

void Zdaj_egzaminFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void Zdaj_egzaminFrame::OnReturnToMenu(wxCommandEvent &event)
{
    m_infoText->SetLabel("");
    m_scrolledWindow->Hide();
    m_historyText->SetLabel("");
    m_startButton->Show(true);
    m_authorsButton->Show(true);
    m_exitButton->Show(true);
    m_gameHistoryButton->Show(true);

    m_questionText->Hide();
    m_menuButton->Hide();
    m_nextButton->Hide();

    for (auto checkbox : m_answerCheckboxes)
    {
        checkbox->Hide();
    }
    Layout();
}

void Zdaj_egzaminFrame::OnNextQuestion(wxCommandEvent &event)
{
    int selectedAnswer = -1;
    for (size_t i = 0; i < m_answerCheckboxes.size(); ++i)
    {
        if (m_answerCheckboxes[i]->GetValue())
        {
            selectedAnswer = i;
            break;
        }
    }

    if (selectedAnswer == m_correctAnswers[m_currentQuestion])
    {
        m_score++;
    }

    m_currentQuestion++;
    if (m_currentQuestion < m_quizData.size())
    {
        ShowQuestion(m_currentQuestion);
    }
    else
    {
        wxString scoreMessage = wxString::Format("Koniec quizu! Twój wynik: %d/%d", m_score, (int)m_quizData.size());
        wxMessageBox(scoreMessage, "Wynik", wxOK | wxICON_INFORMATION);

        wxString userName = wxGetTextFromUser("Podaj swoje imię lub pseudonim:", "Podpis");
        if (userName.IsEmpty())
        {
            userName = "Nieznany użytkownik";
        }

        wxDateTime now = wxDateTime::Now();
        wxString dateTimeStr = now.FormatISOCombined(' ');

        wxString filePath = "wynik_quizu.txt";
        wxTextFile file;

        if (!wxFileExists(filePath))
        {
            file.Create(filePath);
        }
        else
        {
            file.Open(filePath);
        }

        wxString result = wxString::Format("Użytkownik: %s\nWynik: %d/%d\nData: %s\n\n", userName, m_score, (int)m_quizData.size(), dateTimeStr);
        file.AddLine(result);
        file.Write();
        file.Close();

        wxCommandEvent evt;
        OnReturnToMenu(evt);
    }
}

void Zdaj_egzaminFrame::OnGameHistory(wxCommandEvent& event)
{
    wxString filePath = "wynik_quizu.txt";
    wxTextFile file;

    if (!file.Open(filePath))
    {
        wxMessageBox("Nie można otworzyć pliku z historią gry.", "Błąd", wxOK | wxICON_ERROR);
        return;
    }

    wxString history;
    for (size_t i = file.GetLineCount(); i > 0; --i)
    {
        history += file.GetLine(i - 1) + "\n";
    }

    file.Close();

    m_startButton->Hide();
    m_authorsButton->Hide();
    m_exitButton->Hide();
    m_gameHistoryButton->Hide();
    m_infoText->Hide();

    m_historyText->SetLabel(history);
    m_scrolledWindow->Show();
    m_scrolledWindow->FitInside(); // Ensure scrollbar appears if needed
    m_scrolledWindow->SetScrollRate(5, 5);  // Ensure scrollbar appears if needed
    m_menuButton->Show();
    m_scrolledWindow->Layout();
    m_panel->Layout();
    Layout();
}

void Zdaj_egzaminFrame::OnToggleMusic(wxCommandEvent &event)
{
    if (m_musicPlaying)
    {
        m_backgroundMusic.Stop();
        m_toggleMusicButton->SetLabel("Play Music");
    }
    else
    {
        m_backgroundMusic.Play(wxSOUND_ASYNC | wxSOUND_LOOP);
        m_toggleMusicButton->SetLabel("Stop Music");
    }
    m_musicPlaying = !m_musicPlaying;
}

void Zdaj_egzaminFrame::ShowQuestion(size_t questionNumber)
{
    if (questionNumber < m_quizData.size())
    {
        m_questionText->SetLabel(m_quizData[questionNumber].first);

        if (m_answerCheckboxes.size() < m_quizData[questionNumber].second.size())
        {
            for (size_t i = m_answerCheckboxes.size(); i < m_quizData[questionNumber].second.size(); ++i)
            {
                wxCheckBox *checkbox = new wxCheckBox(m_panel, wxID_ANY, "");
                m_answerCheckboxes.push_back(checkbox);
                m_panel->GetSizer()->Add(checkbox, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
            }
        }

        for (size_t i = 0; i < m_quizData[questionNumber].second.size(); ++i)
        {
            m_answerCheckboxes[i]->SetLabel(m_quizData[questionNumber].second[i]);
            m_answerCheckboxes[i]->SetValue(false);
            m_answerCheckboxes[i]->Show();
        }

        for (size_t i = m_quizData[questionNumber].second.size(); i < m_answerCheckboxes.size(); ++i)
        {
            m_answerCheckboxes[i]->Hide();
        }

        Layout();
    }
}
