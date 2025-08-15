//
// Created by Lars on 16.08.2025.
//
#include "MainWindowFrame.hpp"

MainWindowFrame::MainWindowFrame()
: wxFrame(nullptr, wxID_ANY, "wxESRPatcher", wxDefaultPosition, wxSize(270, 115))
{
    sizer = new wxGridBagSizer(5, 5);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    _patchButton = new wxButton(this, wxID_ANY, "Patch ISO");
    _patchButton->Bind(wxEVT_BUTTON, &MainWindowFrame::PatchFile, this);
    _unpatchButton = new wxButton(this, wxID_ANY, "Un-Patch ISO");
    _unpatchButton->Bind(wxEVT_BUTTON, &MainWindowFrame::UnpatchFile, this);
    buttonSizer->Add(_patchButton, 0, wxRIGHT, 5); // 5px spacing
    buttonSizer->Add(_unpatchButton, 0);

    sizer->Add(buttonSizer, wxGBPosition(0, 0), wxGBSpan(1, 2), wxALL, 5);

    _textBox = new wxStaticText(this, wxID_ANY, "Ready to patch...");
    sizer->Add(_textBox, wxGBPosition(1, 0), wxGBSpan(1, 2), wxALL | wxEXPAND, 10);

    // Only row 1 (text box) grows
    sizer->AddGrowableRow(1);

    this->SetMinSize(wxSize(270, 115));
    this->SetSizer(sizer);

    // this->SetSize(270, 115);
}

void MainWindowFrame::PatchFile(wxCommandEvent &) {
    _fileDiag = new wxFileDialog(this, "Select ISO to Patch", "", "", "ISO Files (*.iso)|*.iso", wxFD_OPEN);
    if (_fileDiag->ShowModal() == wxID_OK) {
        _filename = static_cast<char*>(realloc(_filename, _fileDiag->GetPath().length() + 1));
        memmove(_filename, _fileDiag->GetPath().c_str(), _fileDiag->GetPath().length() + 1);
        _filenameLen = _fileDiag->GetPath().length() + 1;
    }
    else {
        _errDiag = new wxMessageDialog(this, "Please select an ISO", "Please select an ISO", wxICON_ERROR);
        if (_errDiag->ShowModal() == wxID_OK) {
            _errDiag->Destroy();
        }
    }
    _fileDiag->Destroy();
    try {
        Patcher::patch({_filename});
        _textBox->SetLabel("Patched " + wxString(_filename) + " Successfully!");
    } catch (const std::exception &ex) {
        _errDiag = new wxMessageDialog(this, std::string("Something went wrong!\n") + ex.what(), "Ooops!", wxICON_INFORMATION);
        _errDiag->ShowModal();
    }
    this->Layout();
    sizer->Fit(this);
}

void MainWindowFrame::UnpatchFile(wxCommandEvent &) {
        _fileDiag = new wxFileDialog(this, "Select ISO to Un-Patch", "", "", "ISO Files (*.iso)|*.iso", wxFD_OPEN);
        if (_fileDiag->ShowModal() == wxID_OK) {
            _filename = static_cast<char*>(realloc(_filename, _fileDiag->GetPath().length() + 1));
            memmove(_filename, _fileDiag->GetPath().c_str(), _fileDiag->GetPath().length() + 1);
            _filenameLen = _fileDiag->GetPath().length() + 1;
        }
        else {
            _errDiag = new wxMessageDialog(this, "Please select an ISO", "Please select an ISO", wxICON_ERROR);
            if (_errDiag->ShowModal() == wxID_OK) {
                _errDiag->Destroy();
            }
        }
        _fileDiag->Destroy();
        try {
            Patcher::unpatch({_filename});
            _textBox->SetLabel("Un-Patched " + wxString(_filename) + " Successfully!");
        } catch (const std::exception &ex) {
            _errDiag = new wxMessageDialog(this, std::string("Something went wrong!\n") + ex.what(), "Ooops!", wxICON_ERROR);
            _errDiag->ShowModal();
        }
    this->Layout();
    sizer->Fit(this);
    }


MainWindowFrame::~MainWindowFrame() {
    if (_filename) {
    free(_filename);
    }
}
