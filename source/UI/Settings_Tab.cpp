#include "Settings_tab.hpp"

using namespace brls::literals;

SettingsTab::SettingsTab() {

    this->inflateFromXMLRes("xml/tabs/settings.xml");

    inject_save->title->setText("main/Settings/saveinject"_i18n);
    inject_save->setSelected(isInjectSave);
    inject_save->registerClickAction([this](brls::View* view) {
        isInjectSave = !isInjectSave;
        if (isInjectSave) {
            Utilities::InjectSave();
        }
        return true;
    }); 

    dbgInAppLog->title->setText("main/Settings/dbglogs"_i18n);
    dbgInAppLog->setSelected(isInAppLogSelected);
    dbgInAppLog->registerClickAction([this](brls::View* view) {
        isInAppLogSelected = !isInAppLogSelected;
        this->dbgInAppLog->setSelected(isInAppLogSelected);
        if (isInAppLogSelected) {
            brls::Application::enableDebuggingView(true);
        } else if (!isInAppLogSelected) {
            brls::Application::enableDebuggingView(false);
        }
        return true;
    });

    dbgWireFrame->title->setText("main/Settings/dbgwframe"_i18n);
    dbgWireFrame->setSelected(isWireFrameSelected);
    dbgWireFrame->registerClickAction([this](brls::View* view) {
        isWireFrameSelected = !isWireFrameSelected;
        this->dbgWireFrame->setSelected(isWireFrameSelected);
        if (isWireFrameSelected) {
            brls::View::setWireframeEnabled(true);
        } else if (!isWireFrameSelected) {
            brls::View::setWireframeEnabled(false);
        }
        return true;
    });
}

brls::View* SettingsTab::create()
{
    return new SettingsTab();
}
