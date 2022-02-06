#include "Loading_Overlay.hpp"

const std::string loadingOverlayXML = R"xml(
<brls:Box
    width="auto"
    height="auto"
    axis="column"
    justifyContent="center"
    alignItems="center">
    <brls:ProgressSpinner
        id="progress"
        size="large"
        width="92"
        height="92"/>
</brls:Box>
)xml";

LoadingOverlay::LoadingOverlay(Box* holder)
{
    this->inflateFromXMLString(loadingOverlayXML);
    
    detach();
    holder->addView(this);
    
    this->holder = holder;
    layout();
}

void LoadingOverlay::layout()
{
    if (holder)
    {
        setWidth(holder->getWidth());
        setHeight(holder->getHeight());
    }
}

void LoadingOverlay::setHidden(bool hide)
{
    setAlpha(hide ? 0 : 1);
    progress->animate(!hide);
}
