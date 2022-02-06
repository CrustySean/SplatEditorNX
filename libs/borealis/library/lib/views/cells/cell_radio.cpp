/*
    Copyright 2021 XITRIX

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "borealis/views/cells/cell_radio.hpp"

namespace brls
{

const std::string radioCellXML = R"xml(
    <brls:Box
        width="auto"
        height="@style/brls/sidebar/item_height"
        focusable="true"
        paddingTop="12.5"
        paddingBottom="12.5"
        alignItems="center">

        <brls:Image
            id="brls/rediocell/image"
            imageAlign="left"
            scalingType="fit" />

        <brls:Label
            id="brls/rediocell/title"
            width="auto"
            height="auto"
            grow="1"
            fontSize="@style/brls/sidebar/item_font_size"
            marginLeft="@style/brls/listitem/descriptionIndent"
            marginRight="@style/brls/listitem/descriptionIndent" />

        <brls:CheckBox
            id="brls/rediocell/checkbox"
            visibility="gone"
            marginRight="@style/brls/listitem/descriptionIndent"/>

    </brls:Box>
)xml";

CheckBox::CheckBox()
{
    float size = Application::getStyle()["brls/listitem/selectRadius"] * 2;
    setWidth(size);
    setHeight(size);
}

void CheckBox::draw(NVGcontext* vg, float x, float y, float width, float height, Style style, FrameContext* ctx)
{
    float radius  = style["brls/listitem/selectRadius"];
    float centerX = x + width / 2;
    float centerY = y + height / 2;

    int thickness = roundf(radius * 0.10f);

    // Background
    nvgFillColor(vg, a(ctx->theme["brls/list/listItem_value_color"]));
    nvgBeginPath(vg);
    nvgCircle(vg, centerX, centerY, radius);
    nvgFill(vg);

    // Check mark
    nvgFillColor(vg, a(ctx->theme["brls/background"]));

    // Long stroke
    nvgSave(vg);
    nvgTranslate(vg, centerX, centerY);
    nvgRotate(vg, -NVG_PI / 4.0f);

    nvgBeginPath(vg);
    nvgRect(vg, -(radius * 0.55f), 0, radius * 1.3f, thickness);
    nvgFill(vg);
    nvgRestore(vg);

    // Short stroke
    nvgSave(vg);
    nvgTranslate(vg, centerX - (radius * 0.65f), centerY);
    nvgRotate(vg, NVG_PI / 4.0f);

    nvgBeginPath(vg);
    nvgRect(vg, 0, -(thickness / 2), radius * 0.53f, thickness);
    nvgFill(vg);

    nvgRestore(vg);
}

View* CheckBox::create()
{
    return new CheckBox();
}

RadioCell::RadioCell()
{
    this->inflateFromXMLString(radioCellXML);
}

void RadioCell::setSelected(bool selected)
{
    Theme theme = Application::getTheme();

    this->selected = selected;
    this->checkbox->setVisibility(selected ? Visibility::VISIBLE : Visibility::GONE);
    this->title->setTextColor(selected ? theme["brls/list/listItem_value_color"] : theme["brls/text"]);
}

bool RadioCell::getSelected()
{
    return this->selected;
}

View* RadioCell::create()
{
    return new RadioCell();
}

void RadioCell::setThumbnail(Image* image)
{
    if (this->image)
        delete this->image;
    if (image != NULL)
    {
        this->thumbnailView = image;
        this->image->setParent(this);
        this->invalidate();
    }
}

void RadioCell::setThumbnail(std::string imgPath) {
    if (this->image)
        this->image->setImageFromFile(imgPath);
    else
        this->thumbnailView = new Image();

    this->image->setSize(Size(100, 61)); // the difference is 39
    this->image->setParent(this);
    this->image->setScalingType(ImageScalingType::FIT);
    this->image->setImageAlign(ImageAlignment::LEFT);
    this->invalidate();
}

void RadioCell::setThumbnailwithSize(std::string imgPath, float width, float height) {
    if (this->image)
        this->image->setImageFromFile(imgPath);
    else
        this->thumbnailView = new Image();

    this->image->setSize(Size(width, height));
    this->image->setParent(this);
    this->image->setScalingType(ImageScalingType::FIT);
    this->invalidate();
}

void RadioCell::setThumbnail(unsigned char* buffer, size_t bufferSize)
{
    if (this->image)
        this->image->setImageFromMem(buffer, bufferSize);
    else
        this->thumbnailView = new Image();

    this->image->setParent(this);
    this->image->setScalingType(ImageScalingType::FIT);
    this->invalidate();
}

} // namespace brls
