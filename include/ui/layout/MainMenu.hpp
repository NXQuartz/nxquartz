#pragma once

#include <pu/Plutonium>

namespace UI::Layout {
    class MainMenu : public pu::ui::Layout {
    private:
        pu::ui::elm::TextBlock::Ref helloText;
    public:
        MainMenu();

        // Have ::Ref alias and ::New() static constructor
        PU_SMART_CTOR(MainMenu)
    };
}