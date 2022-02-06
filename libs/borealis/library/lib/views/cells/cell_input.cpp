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

#include "borealis/views/cells/cell_input.hpp"

#include <borealis/platforms/switch/swkbd.hpp>

#include "borealis/views/dropdown.hpp"

namespace brls
{

InputCell::InputCell()
{
    detail->setTextColor(Application::getTheme()["brls/list/listItem_value_color"]);

    this->registerClickAction([this](View* view) {
        Swkbd::openForText([&](std::string text) {
            this->setValue(text);
        },
            this->title->getFullText(), this->hint, this->maxInputLength, this->value, this->kbdDisableBitmask);

        return true;
    });
}

void InputCell::init(std::string title, std::string value, Event<std::string>::Callback callback, std::string placeholder, std::string hint, int maxInputLength, int kbdDisableBitmask)
{
    this->hint  = hint;
    this->value = value;
    this->title->setText(title);
    this->placeholder       = placeholder;
    this->maxInputLength    = maxInputLength;
    this->kbdDisableBitmask = kbdDisableBitmask;
    this->event.subscribe(callback);
    updateUI();
}

void InputCell::setValue(std::string value)
{
    this->event.fire(value);
    this->value = value;
    updateUI();
}

void InputCell::setPlaceholder(std::string placeholder)
{
    this->placeholder = placeholder;
    updateUI();
}

void InputCell::updateUI()
{
    Theme theme = Application::getTheme();
    if (this->value.empty())
    {
        this->detail->setText(placeholder);
        this->detail->setTextColor(theme["brls/text_disabled"]);
    }
    else
    {
        this->detail->setText(value);
        this->detail->setTextColor(theme["brls/list/listItem_value_color"]);
    }
}

View* InputCell::create()
{
    return new InputCell();
}

InputNumericCell::InputNumericCell()
{
    // image = new Image();
    // image->setImageFromFile("sdmc:/SplatEditor/Cache/test.png"); // not sure
    image->setSize(Size(90, 51));
    // image->setScalingType(ImageScalingType::FIT);
    // addView(image);
    // image->setImageAlign(ImageAlignment::LEFT); // has no effect
    
    // debug
    // brls::Logger::info("Image width: {} || Image height: {}", image->getOriginalImageWidth(), image->getOriginalImageHeight());

    detail->setTextColor(Application::getTheme()["brls/list/listItem_value_color"]);

    this->registerClickAction([this](View* view) {
        Swkbd::openForNumber([&](long number) {
            this->setValue(number);
        },
            this->title->getFullText(), this->hint, this->maxInputLength, std::to_string(this->value), "", "", this->kbdDisableBitmask);

        return true;
    });
}

void InputNumericCell::init(std::string title, long value, Event<long>::Callback callback, std::string hint, int maxInputLength, int kbdDisableBitmask, std::string imgpath) // < std::string imgpath
{
    this->image->setImageFromFile(imgpath); // this->image->setImageFromFile(imgpath);
    this->image->setScalingType(ImageScalingType::FIT);

    this->hint  = hint;
    this->value = value;

    // this->image->setImageAlign(ImageAlignment::LEFT);

    this->title->setText(title);
    
    this->maxInputLength    = maxInputLength;
    this->kbdDisableBitmask = kbdDisableBitmask;
    this->event.subscribe(callback);
    updateUI();
}

void InputNumericCell::setValue(long value)
{
    this->event.fire(value);
    this->value = value;
    updateUI();
}

void InputNumericCell::updateUI()
{
    Theme theme = Application::getTheme();
    this->detail->setText(std::to_string(value));
    this->detail->setTextColor(theme["brls/list/listItem_value_color"]);
}

View* InputNumericCell::create()
{
    return new InputNumericCell();
}

void InputNumericCell::setThumbnail(Image* image)
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

void InputNumericCell::setThumbnail(std::string imgPath) {
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

void InputNumericCell::setThumbnailwithSize(std::string imgPath, float width, float height) {
    if (this->image)
        this->image->setImageFromFile(imgPath);
    else
        this->thumbnailView = new Image();

    this->image->setSize(Size(width, height));
    this->image->setParent(this);
    this->image->setScalingType(ImageScalingType::FIT);
    this->invalidate();
}

void InputNumericCell::setThumbnail(unsigned char* buffer, size_t bufferSize)
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
