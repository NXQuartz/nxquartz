#include <switch.h>

#include <stdio.h>
#include <stdlib.h>
#include <borealis.hpp>
#include <string>
#include <iostream>

#include "ui/about_tab.hpp"
#include "ui/account_tab.hpp"
#include "account.hpp"

#include "state/app_state.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

int main(int argc, char* argv[]) {
    #ifdef DEBUG_BUILD
        // Initialize sockets
        socketInitializeDefault();
        // Redirect stdout and stderr over the network to nxlink
        nxlinkStdio();
    #endif

    std::cout << "Initializing quartz" << std::endl;

    brls::Logger::setLogLevel(brls::LogLevel::DBG);
    i18n::loadTranslations();

    account::initAccountService();

    // Application state passed and shared between UI/Core
    AppState appState;

    // Init the app and i18n
    if (!brls::Application::init("main/name"_i18n)) {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    // Main window and page
    brls::TabFrame* rootFrame = new brls::TabFrame();
    rootFrame->setTitle("main/name"_i18n);
    rootFrame->setIcon(BOREALIS_ASSET("img/quartz_256.png"));

    rootFrame->addTab("main/tabs/account"_i18n, new ui::AccountTab(&appState.accountState));
    rootFrame->addSeparator();
    rootFrame->addTab("main/tabs/about"_i18n, new ui::AboutTab());

    brls::Application::pushView(rootFrame);

    // Run the app
    while (brls::Application::mainLoop());

    account::exitAccountService();

    #ifdef DEBUG_BUILD
        socketExit();
    #endif

    return EXIT_SUCCESS;
}
