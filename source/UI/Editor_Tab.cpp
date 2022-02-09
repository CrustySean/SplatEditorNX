#include "Editor_tab.hpp"

using namespace brls::literals;

bool isDone = false;

EditorTab::EditorTab()
{
    try {
        /* Inflate the tab from the XML file. */
        this->inflateFromXMLRes("xml/tabs/editor.xml");
        
        std::shared_ptr<SaveDataFactory> savefactory(new SaveDataFactory(g_savePath + "/save.dat"));

        SaveDataFactory::SaveFile* save_file = const_cast<SaveDataFactory::SaveFile*>(reinterpret_cast<const SaveDataFactory::SaveFile*>(savefactory->getSaveDecodedPtr()));

        if (std::filesystem::exists(g_savePath + "/save.dat")) {
            /* SaveDataCmn. */
            inklingGender->init(
                "main/SaveDataCmn/gender"_i18n, {
                    "InkGirl", "InkBoy", "OctGirl", "OctBoy", "Rival", "RivalOcta"
                }, save_file->SaveDataCmn.inklingPlayerModelType, [this, save_file](int choice) {
                    switch (choice) {
                        case 0:
                            save_file->SaveDataCmn.inklingPlayerModelType = 0;
                            break;
                        case 1:
                            save_file->SaveDataCmn.inklingPlayerModelType = 1;
                            break;
                        case 2:
                            save_file->SaveDataCmn.inklingPlayerModelType = 2;
                            break;
                        case 3:
                            save_file->SaveDataCmn.inklingPlayerModelType = 3;
                            break;
                        case 4:
                            save_file->SaveDataCmn.inklingPlayerModelType = 4;
                            break;
                        case 5:
                            save_file->SaveDataCmn.inklingPlayerModelType = 5;
                            break;
                        default:
                            save_file->SaveDataCmn.inklingPlayerModelType = 0;
                            break;
                    }
                }, g_defaultPath + "/Cache/test.png"
            );

            std::string tempimgpath = g_defaultPath + "/Cache/test.png";
            S_CREATEEDITORITEM(inklingHairID, "main/SaveDataCmn/hair"_i18n, save_file->SaveDataCmn.inklingPlayerHairId, save_file, SaveDataCmn.inklingPlayerHairId, "", 2, tempimgpath);
            S_CREATEEDITORITEM(inklingPantsID, "main/SaveDataCmn/pants"_i18n, save_file->SaveDataCmn.inklingPlayerSkinColorId, save_file, SaveDataCmn.inklingPlayerSkinColorId, "", 1, tempimgpath);
            S_CREATEEDITORITEM(inklingEyeID, "main/SaveDataCmn/eyes"_i18n, save_file->SaveDataCmn.inklingPlayerEyeColorId, save_file, SaveDataCmn.inklingPlayerEyeColorId, "", 1, tempimgpath);
            //equipped weapon
            //header MainWeapon
            S_CREATEWEAPON(mainWeapon, "main/SaveDataCmn/weapon"_i18n, save_file->SaveDataCmn.equippedWeapon.Main, save_file, SaveDataCmn.equippedWeapon.Main, "", 9999);
            S_CREATESUB(subWeapon, "main/SaveDataCmn/subweapon"_i18n, save_file->SaveDataCmn.equippedWeapon.Sub, save_file, SaveDataCmn.equippedWeapon.Sub, "", 1);
            S_CREATESPECIALS(special, "main/SaveDataCmn/weaponspecial"_i18n, save_file->SaveDataCmn.equippedWeapon.Special, save_file, SaveDataCmn.equippedWeapon.Special, "", 1);
            S_CREATEEDITORITEM(inkTurfed, "main/SaveDataCmn/inkturfed"_i18n, save_file->SaveDataCmn.equippedWeapon.InkTurfed, save_file, SaveDataCmn.equippedWeapon.InkTurfed, "", 9999, tempimgpath); // not sure about 9999  
            S_CREATESHOES(eqshoes, "main/SaveDataCmn/shoes"_i18n, save_file->SaveDataCmn.equippedShoesId, save_file, SaveDataCmn.equippedShoesId, "", 1);
            S_CREATECLOTHES(eqshirt, "main/SaveDataCmn/shirt"_i18n, save_file->SaveDataCmn.equippedClothesId, save_file, SaveDataCmn.equippedClothesId, "", 1);
            S_CREATEEDITORITEM_UNKNOWN(hstick, "main/SaveDataCmn/handsticksense"_i18n, save_file->SaveDataCmn.handheldStickSensitivity, save_file, SaveDataCmn.handheldStickSensitivity, "", 1); // %1f?
            S_CREATEEDITORITEM_UNKNOWN(hmsense, "main/SaveDataCmn/handmotionsense"_i18n, save_file->SaveDataCmn.handheldMotionSensitivity, save_file, SaveDataCmn.handheldMotionSensitivity, "", 1); // %1f?
            S_CREATEEDITORITEM_UNKNOWN(dssense, "main/SaveDataCmn/desticksense"_i18n, save_file->SaveDataCmn.detachedStickSensitivity, save_file, SaveDataCmn.detachedStickSensitivity, "", 1); // %1f?
            S_CREATEEDITORITEM_UNKNOWN(dmsense, "main/SaveDataCmn/demotionsense"_i18n, save_file->SaveDataCmn.detachedMotionSensitivity, save_file, SaveDataCmn.detachedMotionSensitivity, "", 1); // %1f?   
            S_CREATEEDITORITEM(money, "main/SaveDataCmn/money"_i18n, save_file->SaveDataCmn.money, save_file, SaveDataCmn.money, "", 9999999, "sdmc:/SplatEditor/Cache/money.png");
            S_CREATEEDITORITEM(sseasnails, "main/SaveDataCmn/seasnails"_i18n, save_file->SaveDataCmn.seaSnails, save_file, SaveDataCmn.seaSnails, "", 999, "sdmc:/SplatEditor/Cache/sseasnails.png");   
            S_CREATEEDITORITEM(ocgender, "main/SaveDataCmn/octogender"_i18n, save_file->SaveDataCmn.octolingPlayerModelType, save_file, SaveDataCmn.octolingPlayerModelType, "", 1, tempimgpath);
            S_CREATEEDITORITEM(ochair, "main/SaveDataCmn/octohair"_i18n, save_file->SaveDataCmn.octolingPlayerHairId, save_file, SaveDataCmn.octolingPlayerHairId, "", 2, tempimgpath);
            S_CREATEEDITORITEM(ocpants, "main/SaveDataCmn/octopants"_i18n, save_file->SaveDataCmn.octolingPlayerSkinColorId, save_file, SaveDataCmn.octolingPlayerSkinColorId, "", 1, tempimgpath);
            S_CREATEEDITORITEM(oceye, "main/SaveDataCmn/octoeyes"_i18n, save_file->SaveDataCmn.octolingPlayerEyeColorId, save_file, SaveDataCmn.octolingPlayerEyeColorId, "", 1, tempimgpath);
            S_CREATEEDITORITEM(isoc, "main/SaveDataCmn/octoling"_i18n, save_file->SaveDataCmn.isOctoling, save_file, SaveDataCmn.isOctoling, "", 1, tempimgpath);
            // SaveDataVss
            S_CREATEEDITORITEM_UNKNOWN(level, "main/SaveDataVss/level"_i18n, save_file->SaveDataVss.Level, save_file, SaveDataVss.Level, "", 2);
            S_CREATEEDITORITEM(exp, "main/SaveDataVss/experience"_i18n, save_file->SaveDataVss.Exp, save_file, SaveDataVss.Exp, "", 2, "sdmc:/SplatEditor/Cache/star.png"); // not sure
            S_CREATEEDITORITEM_UNKNOWN(starc, "main/SaveDataVss/starcount"_i18n, save_file->SaveDataVss.Stars, save_file, SaveDataVss.Stars, "", 2); // ^
            S_CREATEEDITORITEM_UNKNOWN(rainmrank, "main/SaveDataVss/rainmrank"_i18n, save_file->SaveDataVss.RainmakerRank, save_file, SaveDataVss.RainmakerRank, "", 2); // ^
            S_CREATEEDITORITEM_UNKNOWN(srank, "main/SaveDataVss/splatzrank"_i18n, save_file->SaveDataVss.SplatZonesRank, save_file, SaveDataVss.SplatZonesRank, "", 2); // ^
            S_CREATEEDITORITEM_UNKNOWN(trank, "main/SaveDataVss/tcontrolrank"_i18n, save_file->SaveDataVss.TowerControlRank, save_file, SaveDataVss.TowerControlRank, "", 2); // ^
            S_CREATEEDITORITEM_UNKNOWN(crank, "main/SaveDataVss/cblitzrank"_i18n, save_file->SaveDataVss.ClamBlitzRank, save_file, SaveDataVss.ClamBlitzRank, "", 2); // ^
            // MMR data
            // Turf War
            S_CREATEEDITORITEM_UNKNOWN(mmrtfpw, "main/MMR/power"_i18n, save_file->SaveDataVss.MMR[0].Power, save_file, SaveDataVss.MMR[0].Power, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrtfrd, "main/MMR/rdeviation"_i18n, save_file->SaveDataVss.MMR[0].Rd, save_file, SaveDataVss.MMR[0].Rd, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrtfv, "main/MMR/volatility"_i18n, save_file->SaveDataVss.MMR[0].Volatility, save_file, SaveDataVss.MMR[0].Volatility, "", 2); 
            // Rainmaker
            S_CREATEEDITORITEM_UNKNOWN(mmrrpw, "main/MMR/power"_i18n, save_file->SaveDataVss.MMR[1].Power, save_file, SaveDataVss.MMR[1].Power, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrrrd, "main/MMR/rdeviation"_i18n, save_file->SaveDataVss.MMR[1].Rd, save_file, SaveDataVss.MMR[1].Rd, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrrv, "main/MMR/volatility"_i18n, save_file->SaveDataVss.MMR[1].Volatility, save_file, SaveDataVss.MMR[1].Volatility, "", 2);  
            // Splat Zones
            S_CREATEEDITORITEM_UNKNOWN(mmrspw, "main/MMR/power"_i18n, save_file->SaveDataVss.MMR[2].Power, save_file, SaveDataVss.MMR[2].Power, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrsrc, "main/MMR/rdeviation"_i18n, save_file->SaveDataVss.MMR[2].Rd, save_file, SaveDataVss.MMR[2].Rd, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrsv, "main/MMR/volatility"_i18n, save_file->SaveDataVss.MMR[2].Volatility, save_file, SaveDataVss.MMR[2].Volatility, "", 2);  
            // Tower Control
            S_CREATEEDITORITEM_UNKNOWN(mmrtcw, "main/MMR/power"_i18n, save_file->SaveDataVss.MMR[3].Power, save_file, SaveDataVss.MMR[3].Power, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrtcd, "main/MMR/rdeviation"_i18n, save_file->SaveDataVss.MMR[3].Rd, save_file, SaveDataVss.MMR[3].Rd, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrtcv, "main/MMR/volatility"_i18n, save_file->SaveDataVss.MMR[3].Volatility, save_file, SaveDataVss.MMR[3].Volatility, "", 2); 
            // Clam Blitz
            S_CREATEEDITORITEM_UNKNOWN(mmrcw, "main/MMR/power"_i18n, save_file->SaveDataVss.MMR[4].Power, save_file, SaveDataVss.MMR[4].Power, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrcd, "main/MMR/rdeviation"_i18n, save_file->SaveDataVss.MMR[4].Rd, save_file, SaveDataVss.MMR[4].Rd, "", 2);
            S_CREATEEDITORITEM_UNKNOWN(mmrcv, "main/MMR/volatility"_i18n, save_file->SaveDataVss.MMR[4].Volatility, save_file, SaveDataVss.MMR[4].Volatility, "", 2); 

            this->registerAction("Save", brls::BUTTON_Y, [savefactory, this, save_file](brls::View* view) { 
                brls::Logger::debug("Y Button pressed");
                brls::Dialog* saveDialog = new brls::Dialog("main/Dialog/save"_i18n);
                brls::Dialog* done = new brls::Dialog("main/Dialog/done_file"_i18n);

                done->addButton("brls/hints/ok"_i18n , [] {});
                saveDialog->addButton("Yes", [savefactory, this, done, save_file] {

                    std::ofstream enc(g_editedPath + "/temp.dat", std::fstream::binary);
                    if (!enc) {
                        brls::Logger::error("Could not open save file for writing");
                        return;
                    }

                    enc.seekp(0, std::ios::beg);
                    enc.write((char*)savefactory->getSaveEncodedPtr(), savefactory->getEncodedSaveFileSize());
                    enc.close();

                    /* Hacky way to do it, but I'll keep it since it just works™. */
                    if (std::filesystem::exists(g_editedPath + "/temp.dat")) {
                        Utilities::splatsave(g_editedPath + "/temp.dat");
                    }

                    if (std::filesystem::exists(g_editedPath + "/temp.dat.dec")) {
                        Utilities::splatsave(g_editedPath + "/temp.dat.dec");
                    }
                    
                    std::filesystem::remove(g_editedPath + "/temp.dat");
                    std::filesystem::remove(g_editedPath + "/temp.dat.dec");
                    std::error_code ec;
                    std::filesystem::rename("sdmc:/SplatEditor/Edited/temp.dat.dec.enc", "sdmc:/SplatEditor/Edited/save.dat", ec);

                    if (!std::filesystem::exists(g_savePath + "/save.dat")) {
                        brls::Logger::error("Failed to rename file, due to: {}", ec.message());
                    }

                    done->open();
                });

                saveDialog->addButton("No", [] {});
                saveDialog->open();
                return true;
            }, false, brls::SOUND_HONK);

            isDone = true;

        } else {
            brls::Dialog* errDg = new brls::Dialog("Failed to open file");
            errDg->addButton("brls/hintss/ok"_i18n, [] {});
            errDg->open();
        }

    } catch (std::exception& ex) {
        brls::Dialog* errDg = new brls::Dialog("Failed to open file");
        errDg->addButton("brls/hints/ok"_i18n, [] {});
        errDg->open();
        brls::Logger::error("Exception: {}", ex.what());
    }

}

brls::View* EditorTab::create()
{
    brls::Threading::sync([]() {
        return new EditorTab();     
    });

    return new EditorTab();
    
}
