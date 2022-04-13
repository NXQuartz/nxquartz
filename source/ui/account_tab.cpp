#include "ui/account_tab.hpp"
#include "ui/components/bar.hpp"
#include "account.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

namespace ui {
    AccountTab::AccountTab(AccountState* state) : StateListener(state) {
        addProfileSelector();
        addAtlasAccountData();
    }

    void AccountTab::onStateUpdate(const AccountState* state) {
        if (!state->loggedIn) {
            signButton->setLabel("main/account/atlas/sign_in"_i18n);
        } else {
            signButton->setLabel("main/account/atlas/sign_out"_i18n);
        }

        // signButton->setLabel("main/account/atlas/sign_out"_i18n);
        // ApplicationState::accountState->setLoggedIn()
        // if (!signedIn) {
        //     signButton->setLabel("main/account/atlas/sign_in"_i18n);
        // } else {
        //     signButton->setLabel("main/account/atlas/sign_out"_i18n);
        // }

        // auto* frame = new brls::AppletFrame(true, false);
        // // frame->
        // auto* content = new brls::List();
        // content->addView(new brls::ListItem("Test"));
        // // frame->setContentView(content);
        // auto* appletFrame = new brls::TabFrame();
        // appletFrame->addTab("Login", new brls::ListItem("Hello"));
        // appletFrame->addTab("Sign up", new brls::ListItem("Hello"));
        // appletFrame->setActionAvailable(brls::Key::PLUS, false);
        // brls::PopupFrame::open("Authenticate", appletFrame, "Authenticate with Atlas storage servers", "This must be done in order to use this app");
    }

    void AccountTab::addProfileSelector() {
        // Table so we can put the icon next to the button
        auto table = new brls::BoxLayout(brls::BoxLayoutOrientation::HORIZONTAL);
        table->setHeight(170); // Called so anything below will have spacing

        // Icon table needed for proper spacing and container for Image
        auto iconTable = new brls::BoxLayout(brls::BoxLayoutOrientation::VERTICAL);
        iconTable->setWidth(125);

        auto icon = account::SwitchAccount::getCurrentAccount()->icon; // Actual user icon
        auto* profileIcon = new brls::Image(icon.first, icon.second);
        profileIcon->setScaleType(brls::ImageScaleType::FIT);
        profileIcon->setHeight(70);
        profileIcon->setWidth(70);
        iconTable->addView(profileIcon);

        // Button to select profile
        auto* selectProfile = new brls::ListItem(
            "main/account/select_profile"_i18n,
            "main/account/select_profile_tooltip"_i18n
        );

        selectProfile->setValue(account::SwitchAccount::getCurrentAccount()->name);
        selectProfile->registerAction("brls/hints/select"_i18n, brls::Key::A, [profileIcon, selectProfile] () {
            if (auto account = account::SwitchAccount::selectAccount(); account != nullptr) {
                profileIcon->setImage(account->icon.first, account->icon.second);
                selectProfile->setValue(account->name);
            }

            return true;
        });

        // This is about the right width in order to make the icon + selector width the width of a normal ListItem
        selectProfile->setWidth(625);

        table->addView(selectProfile);
        table->addView(iconTable);

        this->addView(table);
    }

    void AccountTab::addAtlasAccountData() {
        // auto* bar = new ui::components::Bar(0.4, brls::Application::getTheme()->textColor);
        // this->addView(bar);

        this->addView(new brls::Header("main/account/atlas/header"_i18n));

        this->signButton = new brls::ListItem("main/account/atlas/sign_in"_i18n);

        auto* state = this->StateListener<AccountState>::getState();
        signButton->registerAction("brls/hints/select"_i18n, brls::Key::A, [state] () {
            state->setLoggedIn(!state->loggedIn);
            return true;
        });

        this->addView(signButton);
    }
}