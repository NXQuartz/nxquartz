#include "ui/layout/MainMenu.hpp"

namespace UI::Layout {
    MainMenu::MainMenu(pu::ui::Application* appRef) 
        : UI::Layout::BaseLayout(appRef) 
    {
        this->helloText = pu::ui::elm::TextBlock::New(300, 300, "Press X to answer my question");
        this->Add(this->helloText);
    }

    void MainMenu::OnInput(const u64 down, const u64 up, const u64 held) {
        // If X is pressed, start with our dialog questions!
        if (down & HidNpadButton_X) {
            int opt = appRef->CreateShowDialog("Question", "Do you like apples?", { "Yes!", "No...", "Cancel" }, true); // (using latest option as cancel option)
            // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
            if ((opt == -1) || (opt == -2)) {
                appRef->CreateShowDialog("Cancel", "Last question was canceled.", { "Ok" }, true); // If we will ignore the option, it doesn't matter if this is true or false
            } else {
                // Otherwise, opt will be the index of the options we passed to the dialog
                switch (opt) {
                    // "Yes!" was selected
                    case 0:  {
                        appRef->CreateShowDialog("Answer", "Really? I like apples too!", { "Ok" }, true); // Same here ^
                        break;
                    }
                    // "No..." was selected
                    case 1: {
                        appRef->CreateShowDialog("Answer", "Oh, bad news then...", { "Ok" }, true); // And here ^
                        break;
                    }
                }
            }
        }
    }
}
