#pragma once

#include <borealis.hpp>
#include <filesystem>
#include <fstream>

#include "utilities.hpp"
#include "SaveDataFactory.h"
#include "helper.hpp"
#include "Macros.h"

class EditorTab : public brls::Box
{
  public:
    EditorTab();

    // BRLS_BIND(brls::InputNumericCell, inklingGender, "inklingGender");
    BRLS_BIND(brls::SelectorCell, inklingGender, "inklingGender");
    BRLS_BIND(brls::InputNumericCell, inklingHairID, "inklingHairID");
    BRLS_BIND(brls::InputNumericCell, inklingPantsID, "inklingPantsID");
    BRLS_BIND(brls::InputNumericCell, inklingEyeID, "inklingEyeID");

    BRLS_BIND(brls::InputNumericCell, mainWeapon, "mainWeapon");
    BRLS_BIND(brls::InputNumericCell, subWeapon, "subWeapon");
    BRLS_BIND(brls::InputNumericCell, special, "special");
    BRLS_BIND(brls::InputNumericCell, inkTurfed, "inkTurfed");

    BRLS_BIND(brls::InputNumericCell, eqshoes, "eqshoes");
    BRLS_BIND(brls::InputNumericCell, eqshirt, "eqshirt");

    BRLS_BIND(brls::InputNumericCell, hstick, "hstick");
    BRLS_BIND(brls::InputNumericCell, hmsense, "hmsense");
    BRLS_BIND(brls::InputNumericCell, dssense, "dssense");
    BRLS_BIND(brls::InputNumericCell, dmsense, "dmsense");

    BRLS_BIND(brls::InputNumericCell, money, "money");
    BRLS_BIND(brls::InputNumericCell, sseasnails, "sseasnails");

    BRLS_BIND(brls::InputNumericCell, ocgender, "ocgender");
    BRLS_BIND(brls::InputNumericCell, ochair, "ochair");
    BRLS_BIND(brls::InputNumericCell, ocpants, "ocpants");
    BRLS_BIND(brls::InputNumericCell, oceye, "oceye");
    BRLS_BIND(brls::InputNumericCell, isoc, "isoc");

    // SaveDataVSS
    BRLS_BIND(brls::InputNumericCell, level, "level");
    BRLS_BIND(brls::InputNumericCell, exp, "exp");
    BRLS_BIND(brls::InputNumericCell, starc, "starc");
    BRLS_BIND(brls::InputNumericCell, rainmrank, "rainmrank");
    BRLS_BIND(brls::InputNumericCell, srank, "srank");
    BRLS_BIND(brls::InputNumericCell, trank, "trank");
    BRLS_BIND(brls::InputNumericCell, crank, "crank");

    // MMR data
    BRLS_BIND(brls::InputNumericCell, mmrtfpw, "mmrtfpw");
    BRLS_BIND(brls::InputNumericCell, mmrtfrd, "mmrtfrd");
    BRLS_BIND(brls::InputNumericCell, mmrtfv, "mmrtfv");

    BRLS_BIND(brls::InputNumericCell, mmrrpw, "mmrrpw");
    BRLS_BIND(brls::InputNumericCell, mmrrrd, "mmrrrd");
    BRLS_BIND(brls::InputNumericCell, mmrrv, "mmrrv");

    BRLS_BIND(brls::InputNumericCell, mmrspw, "mmrspw");
    BRLS_BIND(brls::InputNumericCell, mmrsrc, "mmrsrc");
    BRLS_BIND(brls::InputNumericCell, mmrsv, "mmrsv");

    BRLS_BIND(brls::InputNumericCell, mmrtcw, "mmrtcw");
    BRLS_BIND(brls::InputNumericCell, mmrtcd, "mmrtcd");
    BRLS_BIND(brls::InputNumericCell, mmrtcv, "mmrtcv");

    BRLS_BIND(brls::InputNumericCell, mmrcw, "mmrcw");
    BRLS_BIND(brls::InputNumericCell, mmrcd, "mmrcd");
    BRLS_BIND(brls::InputNumericCell, mmrcv, "mmrcv");

    static brls::View* create();

    private:
    std::string path = "sdmc:/SplatEditor/Edited/save.dat";
    std::string decpath = "sdmc:/SplatEditor/Edited/save.dat.dec";
};
