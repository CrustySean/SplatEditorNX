#pragma once

#include <borealis.hpp>
#include <switch.h>

#include "helper.hpp"
#include "utilities.hpp"

using namespace brls;

class CustomCell : public Box {
    public:
        CustomCell(std::string name, std::string imgpath, u64 titleid);
    
        BRLS_BIND(Image, image, "image");
        BRLS_BIND(Label, title, "title");
};
