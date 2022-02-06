#pragma once

#include <borealis.hpp>

class MainActivity : public brls::Activity {
  public:
    MainActivity();
    CONTENT_FROM_XML_RES("activity/main.xml");
};
