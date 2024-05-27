#include <wx/wx.h>
#include <wx/textfile.h>
#include <wx/datetime.h>
#include <wx/textdlg.h>
#include <vector>
#include <utility>
#include "Zdaj_egzaminMain.h"

// Definicje statycznych identyfikatorów
const int Zdaj_egzaminFrame::ID_Start = wxNewId();
const int Zdaj_egzaminFrame::ID_Authors = wxNewId();
const int Zdaj_egzaminFrame::ID_Exit = wxNewId();
const int Zdaj_egzaminFrame::ID_Menu = wxNewId();
const int Zdaj_egzaminFrame::ID_Next = wxNewId();
const int Zdaj_egzaminFrame::ID_GameHistory = wxNewId();

wxBEGIN_EVENT_TABLE(Zdaj_egzaminFrame, wxFrame)
    EVT_BUTTON(ID_Start, Zdaj_egzaminFrame::OnStart)
    EVT_BUTTON(ID_Authors, Zdaj_egzaminFrame::OnAuthors)
    EVT_BUTTON(ID_Exit, Zdaj_egzaminFrame::OnExit)
    EVT_BUTTON(ID_Menu, Zdaj_egzaminFrame::OnReturnToMenu)
    EVT_BUTTON(ID_Next, Zdaj_egzaminFrame::OnNextQuestion)
    EVT_BUTTON(ID_GameHistory, Zdaj_egzaminFrame::OnGameHistory)
wxEND_EVENT_TABLE()

Zdaj_egzaminFrame::Zdaj_egzaminFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : wxFrame(parent, id, title, pos, size, style), m_currentQuestion(0), m_score(0)
{
    // Przykładowe pytania i odpowiedzi oraz poprawne odpowiedzi
    m_quizData.push_back(std::make_pair("Pytanie 1: Jaki jest kolor nieba?", std::vector<wxString>{"Niebieski", "Czerwony", "Zielony", "Żółty"}));
    m_quizData.push_back(std::make_pair("Pytanie 2: Ile wynosi 2 + 2?", std::vector<wxString>{"3", "4", "5", "6"}));
    m_correctAnswers.push_back(0); // Poprawna odpowiedź dla pierwszego pytania
    m_correctAnswers.push_back(1); // Poprawna odpowiedź dla drugiego pytania

    m_panel = new wxPanel(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_startButton = new wxButton(m_panel, ID_Start, "Start Quiz");
    sizer->Add(m_startButton, 0, wxALIGN_CENTER | wxALL, 5);

    m_authorsButton = new wxButton(m_panel, ID_Authors, "Authors");
    sizer->Add(m_authorsButton, 0, wxALIGN_CENTER | wxALL, 5);

    m_gameHistoryButton = new wxButton(m_panel, ID_GameHistory, "Historia gry");
    sizer->Add(m_gameHistoryButton, 0, wxALIGN_CENTER | wxALL, 5);
    m_gameHistoryButton->Hide(); // Ukrycie przycisku na początku

    m_exitButton = new wxButton(m_panel, ID_Exit, "Exit");
    sizer->Add(m_exitButton, 0, wxALIGN_CENTER | wxALL, 5);

    m_menuButton = new wxButton(m_panel, ID_Menu, "Return to Menu");
    sizer->Add(m_menuButton, 0, wxALIGN_CENTER | wxALL, 5);
    m_menuButton->Hide(); // Ukrycie przycisku na początku

    m_nextButton = new wxButton(m_panel, ID_Next, "Next");
    sizer->Add(m_nextButton, 0, wxALIGN_CENTER | wxALL, 5);
    m_nextButton->Hide(); // Ukrycie przycisku na początku

    m_infoText = new wxStaticText(m_panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    sizer->Add(m_infoText, 0, wxALIGN_CENTER | wxALL, 5);

    m_questionText = new wxStaticText(m_panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    sizer->Add(m_questionText, 0, wxALIGN_CENTER | wxALL, 5);
    m_questionText->Hide();

    m_panel->SetSizer(sizer);
    Layout();
}

void Zdaj_egzaminFrame::OnStart(wxCommandEvent &event)
{
    m_currentQuestion = 0;
    m_score = 0;
    ShowQuestion(m_currentQuestion);

    m_startButton->Hide();
    m_authorsButton->Hide();
    m_exitButton->Hide();
    m_infoText->Hide();

    m_questionText->Show();
    m_nextButton->Show();
    Layout();
}

void Zdaj_egzaminFrame::OnAuthors(wxCommandEvent &event)
{
    m_startButton->Hide();
    m_authorsButton->Hide();
    m_exitButton->Hide();

    m_menuButton->Show(true);
    m_infoText->SetLabel("Autorzy:\nJohn Doe\nJane Smith\n");
    m_infoText->Show(); // Upewnij się, że tekst z informacjami jest widoczny
    Layout(); // Odśwież układ elementów
}

void Zdaj_egzaminFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void Zdaj_egzaminFrame::OnReturnToMenu(wxCommandEvent &event)
{
    m_infoText->SetLabel("");
    m_startButton->Show(true);
    m_authorsButton->Show(true);
    m_exitButton->Show(true);

    m_questionText->Hide();
    m_menuButton->Hide(); // Ukryj przycisk "Return to Menu" tylko jeśli przycisk "Historia gry" nie jest widoczny
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

        // Pobierz podpis użytkownika
        wxString userName = wxGetTextFromUser("Podaj swoje imię lub pseudonim:", "Podpis");
        if (userName.IsEmpty())
        {
            userName = "Nieznany użytkownik";
        }

        // Pobierz bieżącą datę i czas
        wxDateTime now = wxDateTime::Now();
        wxString dateTimeStr = now.FormatISOCombined(' ');

        // Zapis wyniku do pliku
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

        wxCommandEvent evt; // Utworzenie tymczasowego obiektu wxCommandEvent
        OnReturnToMenu(evt);
    }
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
                m_panel->GetSizer()->Add(checkbox, 0, wxALIGN_LEFT | wxALL, 5);
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
    for (size_t i = 0; i < file.GetLineCount(); ++i)
    {
        history += file.GetLine(i) + "\n";
    }

    file.Close();

    wxMessageBox(history, "Historia gry", wxOK | wxICON_INFORMATION);

    // Po wyświetleniu historii gry pokaż przycisk powrotu do menu
    m_menuButton->Show(true);
}
