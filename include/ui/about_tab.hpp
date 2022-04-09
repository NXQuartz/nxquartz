#pragma once

#include <borealis.hpp>

namespace ui {
    class AboutTab : public brls::List {
    public:
        AboutTab();

        View* getDefaultFocus() override {
            return nullptr;
        }
    };
}