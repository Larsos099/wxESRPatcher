#include <iostream>
#include <wx/wx.h>
#include "MainWindowFrame.hpp"

class wxESRPatcher final : public wxApp {
public:
    bool OnInit() override {
        auto mwf = new MainWindowFrame();
        mwf->Show();
        return true;
    }
};
wxIMPLEMENT_APP(wxESRPatcher);