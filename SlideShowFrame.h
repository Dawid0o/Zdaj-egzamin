#ifndef SLIDESHOWFRAME_H
#define SLIDESHOWFRAME_H

#include <wx/wx.h>
#include <vector>

class SlideShowFrame : public wxFrame {
public:
    SlideShowFrame(const wxString& title);
    void LoadImages(const std::vector<wxString>& imagePaths);

private:
    void OnNextButton(wxCommandEvent& event);
    void OnStartQuizButton(wxCommandEvent& event);
    void ShowImage(int index);

    std::vector<wxString> images;
    int currentImageIndex;
    wxPanel* panel;
    wxStaticBitmap* imageDisplay;
    wxButton* nextButton;
    wxButton* startQuizButton;

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_SLIDESHOW_NEXT_BUTTON = 5001,
    ID_START_QUIZ_BUTTON = 5002
};

#endif // SLIDESHOWFRAME_H
