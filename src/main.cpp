#include <switch.h>

#include <borealis.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/file.h>

#include "profile.hpp"
#include "ui/about_tab.hpp"
#include "ui/account_tab.hpp"

#include "state/app_state.hpp"
#include "state/profile_state.hpp"

#include "logger.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

int main(int argc, char* argv[]) {
#ifndef NDEBUG
    // Initialize sockets
    socketInitializeDefault();
    // Redirect stdout and stderr over the network to nxlink
    nxlinkStdio();
#endif

    Logger::info("{}", "Initializing Quartz");

    brls::Logger::setLogLevel(brls::LogLevel::DBG);
    i18n::loadTranslations();

    ProfileService profileService;

    // Application state passed and shared between UI/Core
    AppState appState(&profileService);

    // Init the app and i18n
    if (!brls::Application::init("main/name"_i18n)) {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    // Main window and page
    brls::TabFrame* rootFrame = new brls::TabFrame();
    rootFrame->setTitle("main/name"_i18n);
    rootFrame->setIcon(BOREALIS_ASSET("img/quartz_256.png"));

    rootFrame->addTab(
        "main/tabs/account"_i18n,
        new ui::AccountTab(&appState.accountState, &appState.profileState));
    rootFrame->addSeparator();
    rootFrame->addTab("main/tabs/about"_i18n, new ui::AboutTab());

    brls::Application::pushView(rootFrame);

    // Run the app
    while (brls::Application::mainLoop())
        ;

#ifndef NDEBUG
    socketExit();
#endif

    return EXIT_SUCCESS;
}
