#ifndef HISTORY_FRAME_H
#define HISTORY_FRAME_H

#include <wx/wx.h>

class HistoryFrame : public wxFrame {
public:
    HistoryFrame(const wxString& title);

private:
    void OnBackButton(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // HISTORY_FRAME_H
