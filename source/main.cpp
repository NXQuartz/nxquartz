#include <switch.h>

#include <stdio.h>
#include <stdlib.h>
#include <borealis.hpp>
#include <string>

#include "ui/about_tab.hpp"
#include "ui/account_tab.hpp"
#include "account.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

int main(int argc, char* argv[]) {
    brls::Logger::setLogLevel(brls::LogLevel::DBG);
    i18n::loadTranslations();

    account::initAccountService();

    // Init the app and i18n
    if (!brls::Application::init("main/name"_i18n)) {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    // Main window and page
    brls::TabFrame* rootFrame = new brls::TabFrame();
    rootFrame->setTitle("main/name"_i18n);
    rootFrame->setIcon(BOREALIS_ASSET("img/quartz_256.png"));

    rootFrame->addTab("main/tabs/account"_i18n, new ui::AccountTab());
    rootFrame->addSeparator();
    rootFrame->addTab("main/tabs/about"_i18n, new ui::AboutTab());

    brls::Application::pushView(rootFrame);

    // Run the app
    while (brls::Application::mainLoop());

    account::exitAccountService();

    return EXIT_SUCCESS;
}
