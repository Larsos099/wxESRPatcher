//
// Created by Lars on 15.08.2025.
//
#ifndef MAINWINDOWFRAME_HPP
#define MAINWINDOWFRAME_HPP
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include "Patcher.hpp"
#ifdef _WIN32
static constexpr int MAXP = 260;
#endif

#if defined(__linux__) || defined(__APPLE__) || defined(__BSD__)
#include <limits.h>
static constexpr int MAXP = PATH_MAX;
#endif

class MainWindowFrame final : public wxFrame {
public:
    MainWindowFrame();
    ~MainWindowFrame() override;
private:
    wxButton* _patchButton = nullptr;
    wxButton* _unpatchButton = nullptr;
    wxStaticText* _textBox = nullptr;
    wxFileDialog* _fileDiag = nullptr;
    wxMessageDialog* _errDiag = nullptr;
    wxGridBagSizer* _sizer = nullptr;
    char* _filename = nullptr;
    size_t _filenameLen = 0;
    void PatchFile(wxCommandEvent&);
    void UnpatchFile(wxCommandEvent&);
};


#endif // MAINWINDOWFRAME_HPP