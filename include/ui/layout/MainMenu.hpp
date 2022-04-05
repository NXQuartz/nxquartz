#pragma once

#include <pu/Plutonium>
#include "ui/layout/BaseLayout.hpp"

namespace UI::Layout {
    class MainMenu : public BaseLayout {
    private:
        pu::ui::elm::TextBlock::Ref helloText;
    public:
        MainMenu(pu::ui::Application* appRef);
        void OnInput(const u64 down, const u64 up, const u64 held);

        // Have ::Ref alias and ::New() static constructor
        PU_SMART_CTOR(MainMenu)
    };
}