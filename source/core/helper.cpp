#include "helper.hpp"

using namespace brls;

brls::Dialog* createLoadingDialog(std::string text) {
    Style style = Application::getStyle();
    Box* holder = new Box(Axis::COLUMN);
    
    Label* label = new Label();
    label->setText(text);
    label->setFontSize(style["brls/dialog/fontSize"]);
    label->setHorizontalAlign(HorizontalAlign::CENTER);
    label->setMarginBottom(21);
    
    ProgressSpinner* spinner = new ProgressSpinner(ProgressSpinnerSize::LARGE);
    spinner->View::setSize(Size(92, 92));
    
    holder->addView(label);
    holder->addView(spinner);
    
    holder->setAlignItems(AlignItems::CENTER);
    holder->setJustifyContent(JustifyContent::CENTER);
    holder->setPadding(style["brls/dialog/paddingTopBottom"], style["brls/dialog/paddingLeftRight"], 28, style["brls/dialog/paddingLeftRight"]);

    Dialog* dialog = new Dialog(holder);
    dialog->setCancelable(false);
    dialog->setFocusable(true);
    dialog->setHideHighlight(true);
    return dialog;
}

std::string char16_to_string(const char16_t* s16)
{
    // https://stackoverflow.com/a/7235204/865719
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return convert.to_bytes(s16);
}

long char16_to_long(const char16_t* s16)
{
    return stol(char16_to_string(s16));
}

int char16_to_int(const char16_t* s16)
{
    return stoi(char16_to_string(s16));
}

auto utf8toutf16(std::string source) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert; 
    return convert.from_bytes(source);  
} 

std::string utf16toutf8(char16_t* source) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert; 
    return convert.to_bytes(source);     
}

void PushMainView() {
    if (std::filesystem::exists("sdmc:/SplatEditor/Splat2Font.ttf")) {
        brls::Application::loadFontFromFile("Splat2", "sdmc:/SplatEditor/Splat2Font.ttf");
        brls::Application::getFont("Splat2");
    }

    brls::Application::pushActivity(new MainActivity());
}

void PushRomtypeView() {
    if (std::filesystem::exists("sdmc:/SplatEditor/Splat2Font.ttf")) {
        brls::Application::loadFontFromFile("Splat2", "sdmc:/SplatEditor/Splat2Font.ttf");
        brls::Application::getFont("Splat2");
    }

    brls::Application::pushActivity(new MainActivity());
}
