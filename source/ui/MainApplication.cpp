#include <ui/MainApplication.hpp>

#include <hos/common.hpp>

namespace UI {
    #define APP_MENU_SET_BASE(layout) { \
        layout->Add(this->timeText); \
        layout->Add(this->menuNameText); \
        layout->Add(this->menuHeadText); \
    };

    void MainApplication::OnLoad() {
        this->timeText = pu::ui::elm::TextBlock::New(1124, 18, "...");
        this->menuNameText = pu::ui::elm::TextBlock::New(120, 85, "...");

        this->menuHeadText = pu::ui::elm::TextBlock::New(120, 120, "...");
        this->menuHeadText->SetFont(pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::Medium));

        this->UnloadMenuData();

        // Load layouts
        this->mainMenuLayout = Layout::MainMenu::New(this);

        APP_MENU_SET_BASE(this->mainMenuLayout);

        this->AddRenderCallback(std::bind(&MainApplication::UpdateValues, this));
        this->SetOnInput(std::bind(&MainApplication::OnInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        this->LoadLayout(this->mainMenuLayout);
        this->startTime = std::chrono::steady_clock::now();
    }

    void MainApplication::UpdateValues() {
        const auto currentTime = hos::GetCurrentTime();

        if (this->currentTime != currentTime)  {
            this->timeText->SetText(currentTime);
            this->currentTime = currentTime;
        }
    }

    void MainApplication::UnloadMenuData() {
        this->menuNameText->SetVisible(false);
        this->menuHeadText->SetVisible(false);
    }

    void MainApplication::OnInput(const u64 down, const u64 up, const u64 held) {
        if (down & HidNpadButton_Plus)
            this->CloseWithFadeOut();
    }
}