#include "ui/layout/MainMenu.hpp"

namespace UI::Layout {
    MainMenu::MainMenu() : Layout::Layout() {
        this->helloText = pu::ui::elm::TextBlock::New(300, 300, "Press X to answer my question");
        this->Add(this->helloText);
    }
}
