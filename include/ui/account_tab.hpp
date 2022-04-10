#pragma once

#include <borealis.hpp>

namespace ui {
    class AccountTab : public brls::List {
        void addProfileSelector();
    public:
        AccountTab();
    };
}