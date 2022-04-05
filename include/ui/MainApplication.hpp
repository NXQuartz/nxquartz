#pragma once

#include <pu/Plutonium>

#include "layout/MainMenu.hpp"

// Define your application (can't instantiate base class, so need to make a derived one)
namespace UI {
    class MainApplication : public pu::ui::Application {
    private:
        void UnloadMenuData();
        void OnInput(const u64 down, const u64 up, const u64 held);
        void UpdateValues();

        Layout::MainMenu::Ref mainMenuLayout;

        pu::ui::elm::TextBlock::Ref timeText;
        pu::ui::elm::TextBlock::Ref menuNameText;
        pu::ui::elm::TextBlock::Ref menuHeadText;
        
        std::string currentTime;
        std::chrono::time_point<std::chrono::steady_clock> startTime;
    public:
        using Application::Application;
        PU_SMART_CTOR(MainApplication)

        // We need to define this, and use it to initialize everything
        void OnLoad() override;
    };
}