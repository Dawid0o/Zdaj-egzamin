#include "SubmitHandler.h"
#include "_Main.h"  // Include MyFrame header
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <iostream> // Include for debugging

SubmitHandler::SubmitHandler(wxWindow* parent, bool passed, int correctAnswers, int totalQuestions)
    : wxPanel(parent, wxID_ANY) {

    std::cout << "Debug: Inside SubmitHandler constructor" << std::endl;

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Load background image
    wxString resultImagePath = passed ?
                               wxT("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/gratulacje.jpg") :
                               wxT("C:/Users/Len/Desktop/Projekt PO/Zdaj egzamin v2/1/grafika/negatywny.jpg");
    wxBitmap resultBitmap(resultImagePath, wxBITMAP_TYPE_JPEG);
    wxImage resultImage = resultBitmap.ConvertToImage();
    resultImage = resultImage.Scale(wxGetDisplaySize().GetWidth(), wxGetDisplaySize().GetHeight(), wxIMAGE_QUALITY_HIGH);
    wxBitmap scaledResultBitmap(resultImage);
    wxStaticBitmap* backgroundDisplay = new wxStaticBitmap(this, wxID_ANY, scaledResultBitmap);

    // Create the result panel with a white background
    wxPanel* resultPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300));
    resultPanel->SetBackgroundColour(wxColour(255, 255, 255));
    wxBoxSizer* resultSizer = new wxBoxSizer(wxVERTICAL);

    resultSizer->AddStretchSpacer(1);
    resultSizer->AddStretchSpacer(1);
    resultPanel->SetSizer(resultSizer);

    // Create a sizer for centering the result panel
    wxBoxSizer* centerSizer = new wxBoxSizer(wxVERTICAL);
    centerSizer->AddStretchSpacer(1);
    centerSizer->Add(resultPanel, 0, wxALIGN_CENTER);
    centerSizer->AddStretchSpacer(1);

    // Add the background image and the center sizer to the main sizer
    mainSizer->Add(backgroundDisplay, 1, wxEXPAND);
    mainSizer->Add(centerSizer, 1, wxEXPAND);

    // Add a "Back to Menu" button at the bottom
    backToMenuButton = new wxButton(this, wxID_ANY, "Powrot do menu");
    backToMenuButton->Bind(wxEVT_BUTTON, &SubmitHandler::OnBackToMenu, this);
    mainSizer->Add(backToMenuButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);
    Layout();

    std::cout << "Debug: SubmitHandler setup complete" << std::endl;
}

void SubmitHandler::OnBackToMenu(wxCommandEvent& event) {
    std::cout << "Debug: Back to Menu button clicked" << std::endl;
    wxWindow* parent = GetParent();
    while (parent->GetParent() != nullptr) {
        parent = parent->GetParent();
    }
    parent->Close();  // Close the current frame

    MyFrame* mainFrame = new MyFrame("Main Menu");
    mainFrame->Show(true);
    mainFrame->ShowFullScreen(true);
}

