#ifndef HISTORYFRAME_H
#define HISTORYFRAME_H

#include <wx/wx.h>

class HistoryFrame : public wxFrame {
public:
    HistoryFrame(const wxString& title);

private:
    void OnBackButton(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // HISTORYFRAME_H
