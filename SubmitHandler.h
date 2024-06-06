#ifndef SUBMITHANDLER_H
#define SUBMITHANDLER_H

#include <wx/wx.h>

class SubmitHandler : public wxPanel {
public:
    SubmitHandler(wxWindow* parent, bool passed, int correctAnswers, int totalQuestions);

private:
    void OnBackToMenu(wxCommandEvent& event);
    wxButton* backToMenuButton;
};

#endif // SUBMITHANDLER_H
