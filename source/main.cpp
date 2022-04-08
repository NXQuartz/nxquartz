#include <switch.h>

#include <stdio.h>
#include <stdlib.h>
#include <borealis.hpp>
#include <string>

// #include "captioned_image.hpp"
// #include "components_tab.hpp"
#include "ui/main_activity.hpp"
// #include "recycling_list_tab.hpp"

using namespace brls::literals;

int main(int argc, char* argv[]) {
    // Set log level
    // We recommend to use INFO for real apps
    brls::Logger::setLogLevel(brls::LogLevel::DBG);

    // Init the app and i18n
    if (!brls::Application::init()) {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    brls::Application::createWindow("lang/title"_i18n);

    // Have the application register an action on every activity that will quit when you press BUTTON_START
    brls::Application::setGlobalQuit(true);

    // Create and push the main activity to the stack
    brls::Application::pushActivity(new ui::MainActivity());

    // Run the app
    while (brls::Application::mainLoop());

    // Exit
    return EXIT_SUCCESS;
}
