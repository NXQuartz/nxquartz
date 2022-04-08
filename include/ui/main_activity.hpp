#pragma once

#include <borealis.hpp>

namespace ui {
    class MainActivity : public brls::Activity {
    public:
        // Content at "resources/activity/xml/main.xml"
        CONTENT_FROM_XML_RES("activity/main.xml");
    };
}
