#include "Custom_Cell.hpp"

CustomCell::CustomCell(std::string name, std::string imgpath, u64 titleid)
{
    this->inflateFromXMLRes("xml/cells/custom_cell.xml");

    title->setText(name);
    title->setTextColor(nvgRGB(255,255,255));

    image->setImageFromFile(imgpath);

    this->registerClickAction([this, titleid](View* view) {

        Utilities::CopySave(titleid);
        if (std::filesystem::exists(g_savePath + "/save.dat")) {
            brls::Application::popActivity();
            brls::Application::pushActivity(new MainActivity());
        }
        return true;
    });
}
