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
        this->mainMenuLayout = Layout::MainMenu::New();

        APP_MENU_SET_BASE(this->mainMenuLayout);

        this->AddRenderCallback(std::bind(&MainApplication::UpdateValues, this));
        this->SetOnInput(std::bind(&MainApplication::OnInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        this->LoadLayout(this->mainMenuLayout);
        this->startTime = std::chrono::steady_clock::now();

        // // Create the layout (calling the smart constructor above)
        // this->layout = Layout::MainMenu::New();

        // // Load the layout. In applications layouts are loaded, not added into a container (you don't select an added layout, just load it from this function)
        // // Simply explained: loading layout = the application will render that layout in the very next frame
        // this->LoadLayout(this->layout);

        // // Set a function when input is caught. This input handling will be the first one to be handled (before Layout or any Elements)
        // // Using a lambda function here to simplify things
        // // You can use member functions via std::bind() C++ wrapper
        // this->SetOnInput([&](const u64 keys_down, const u64 keys_up, const u64 keys_held, const pu::ui::TouchPoint touch_pos) {
        //     // If X is pressed, start with our dialog questions!
        //     if(keys_down & HidNpadButton_X) {
        //         int opt = this->CreateShowDialog("Question", "Do you like apples?", { "Yes!", "No...", "Cancel" }, true); // (using latest option as cancel option)
        //         // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
        //         if((opt == -1) || (opt == -2))  {
        //             this->CreateShowDialog("Cancel", "Last question was canceled.", { "Ok" }, true); // If we will ignore the option, it doesn't matter if this is true or false
        //         }
        //         else {
        //             // Otherwise, opt will be the index of the options we passed to the dialog
        //             switch(opt) {
        //                 // "Yes!" was selected
        //                 case 0:  {
        //                     this->CreateShowDialog("Answer", "Really? I like apples too!", { "Ok" }, true); // Same here ^
        //                     break;
        //                 }
        //                 // "No..." was selected
        //                 case 1: {
        //                     this->CreateShowDialog("Answer", "Oh, bad news then...", { "Ok" }, true); // And here ^
        //                     break;
        //                 }
        //             }
        //         }
        //     }
        //     // If + is pressed, exit application
        //     else if(keys_down & HidNpadButton_Plus) {
        //         this->Close();
        //     }
        // });
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