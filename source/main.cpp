#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <borealis.hpp>
#include <switch.h>

#include "helper.hpp"
#include "utilities.hpp"
#include "config.hpp"
#include "cache.hpp"

#include "Editor_Tab.hpp"
#include "Settings_Tab.hpp"
#include "Romtype_View.hpp"
#include "Romtype_View.hpp"

using namespace brls::literals;

int main(int argc, char const* argv[])
{
    /* Make sure the app is running in title overriding mode. */
    if (appletGetAppletType() == AppletType_Application) {

        /* Set log level. */
        brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

        /* Init the app and i18n. */
        if (!brls::Application::init())
        {
            brls::Logger::error("Unable to init SplatEditor app");
            return EXIT_FAILURE;
        }

        brls::Application::createWindow("main/Title"_i18n);

        /* Have the application register an action on every activity that will quit when you press BUTTON_START. */
        brls::Application::setGlobalQuit(true);

        Utilities::Init();

        brls::Application::registerXMLView("EditorTab", EditorTab::create);
        brls::Application::registerXMLView("SettingsTab", SettingsTab::create);

        /* Add custom values to the theme. */
        brls::getLightTheme().addColor("captioned_image/caption", nvgRGB(2, 176, 183));
        brls::getDarkTheme().addColor("captioned_image/caption", nvgRGB(51, 186, 227));

        /* Add custom values to the style. */
        brls::getStyle().addMetric("about/padding_top_bottom", 50);
        brls::getStyle().addMetric("about/padding_sides", 75);
        brls::getStyle().addMetric("about/description_margin", 50);

        /* Check if a backup was already made. */
        if (!std::filesystem::exists("sdmc:/SplatEditor/Saves/save.dat")) {
            if (std::filesystem::is_empty(g_defaultPath + "/Cache")) {
                Cache::DownloadNecessary();
            }
            brls::Application::pushActivity(new brls::Activity(RomtypeView::create()));
        } else {
            brls::Application::pushActivity(new MainActivity());
        }   

        /* Run the app. */
        while (brls::Application::mainLoop())
            ;
        /* Exit. */
        accountExit();
        nsExit();
        return EXIT_SUCCESS;

    } else {
        brls::fatal("Applet mode is not supported\nYou need to launch the app by title overriding(hold R while launching a game");
        return EXIT_FAILURE;
    }
}
