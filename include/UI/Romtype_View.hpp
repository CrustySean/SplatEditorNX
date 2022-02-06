#pragma once

#include <borealis.hpp>

#include "helper.hpp"

#include "Grid_View.hpp"
#include "Loading_Overlay.hpp"
#include "Custom_Cell.hpp"
#include "utilities.hpp"

#include <optional>

using namespace brls;

class RomtypeView : public Box
{
public:
    RomtypeView();
    
    void onLayout() override;
    void willAppear(bool resetState) override;

    static brls::View* create();
    
private:
    View* hintView = nullptr;
    bool loading = false;
    bool inputBlocked = false;
    LoadingOverlay* loader = nullptr;
    void blockInput(bool block);
    
    GridView* gridView;
    BRLS_BIND(AppletFrame, applet, "applet");
    BRLS_BIND(Box, container, "container");
};
