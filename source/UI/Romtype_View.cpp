#include "Romtype_View.hpp"

std::unordered_map<std::string, u64> romtypes = {
    { "JP", 0x01003C700009C000 },
    { "US", 0x01003BC0000A0000 },
    { "EU", 0x0100F8F0000A2000 },
    { "EveJP", 0x0100D070040F8000 },
    { "EveUS", 0x01003870040FA000 },
    { "EveEU", 0x010086F0040FC000 },
    { "TrialJP", 0x01009C900D458000 },
    { "TrialUS", 0x01006BB00D45A000 },
    { "TrialEU", 0x01007E200D45C000 },
    { "TrialJP20", 0x0100998011330000 },
    { "TrialUS20", 0x01002120116C4000 },
    { "TrialEU20", 0x01007E200D45C000 },
    { "ShowFloor", 0x01009240116CC000 },
    { "ShowDL", 0x010000A00218E000 }
};

RomtypeView::RomtypeView() {
    this->inflateFromXMLRes("xml/views/romtype.xml");

    applet->setTitle("main/Tabs/romtype"_i18n);
    
    Label* label = new brls::Label();
    label->setText(brls::Hint::getKeyIcon(ControllerButton::BUTTON_BACK));
    label->setFontSize(24);
    label->setMargins(4, 16, 4, 16);
    
    Box* holder = new Box();
    holder->addView(label);
    holder->setFocusable(true);
    holder->setCornerRadius(6);
    holder->setMargins(18, 0, 8, 0);
    holder->addGestureRecognizer(new TapGestureRecognizer(holder));

    hintView = holder;
    getAppletFrameItem()->hintView = hintView;

    container->setHideHighlight(true);
    gridView = new GridView(6);
    container->addView(gridView);
    loader = new LoadingOverlay(this);
    hintView->setVisibility(Visibility::VISIBLE);

    loader->setHidden(true);

    for (const auto& [region, titleid] : romtypes) {
        CustomCell* cell = new CustomCell(region, Utilities::DumpAppControl(titleid), titleid);
        gridView->addView(cell);
    }
}

void RomtypeView::willAppear(bool resetState)
{
    Box::willAppear(resetState);
}

void RomtypeView::onLayout()
{
    Box::onLayout();
    
    if (loader)
        loader->layout();
}

View* RomtypeView::create() {
    return new RomtypeView();
}
