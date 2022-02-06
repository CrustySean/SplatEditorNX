#pragma once

#include <borealis.hpp>

#include "utilities.hpp"

#include "helper.hpp"

#include "Romtype_View.hpp"
#include "config.hpp"
#include "cache.hpp"

class SettingsTab : public brls::Box
{
  public:
    SettingsTab();

    BRLS_BIND(brls::RadioCell, radio, "radio");
    BRLS_BIND(brls::BooleanCell, boolean, "boolean");
    BRLS_BIND(brls::InputCell, input, "input");
    BRLS_BIND(brls::InputNumericCell, inputNumeric, "inputNumeric");
    BRLS_BIND(brls::RadioCell, dbgInAppLog, "dbgInAppLog");
    BRLS_BIND(brls::RadioCell, dbgWireFrame, "dbgWireFrame");
    BRLS_BIND(brls::RadioCell, inject_save, "inject_save");

    BRLS_BIND(brls::Image, mImage, "image");

    static brls::View* create();

  private:
   bool isInAppLogSelected = false;
   bool isWireFrameSelected = false;
   bool isInjectSave = false;
};
