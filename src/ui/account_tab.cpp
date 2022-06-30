#include "ui/account_tab.hpp"
#include "profile.hpp"
#include "ui/components/bar.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

namespace ui {
AccountTab::AccountTab(AccountState* accountState, ProfileState* profileState)
    : State<AccountState>::Listener(accountState),
      State<ProfileState>::Listener(profileState) {
    addProfileSelector();
    addAtlasAccountData();
}

void AccountTab::onStateUpdate(AccountState* state) {
    if (!state->loggedIn) {
        signButton->setLabel("main/account/atlas/sign_in"_i18n);
    } else {
        signButton->setLabel("main/account/atlas/sign_out"_i18n);
    }

    // signButton->setLabel("main/account/atlas/sign_out"_i18n);
    // // ApplicationState::accountState->setLoggedIn();
    // AccountState::setLoggedIn(true);
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
    // brls::PopupFrame::open("Authenticate", appletFrame, "Authenticate with
    // Atlas storage servers", "This must be done in order to use this app");
}

void AccountTab::onStateUpdate(ProfileState* state) {
    // profileState->icon.first;
    auto profile = state->getCurrentProfile();
    profileIcon->setImage(profile->icon.first, profile->icon.second);
    profileName->setValue(profile->name);
}

void AccountTab::addProfileSelector() {
    // Table so we can put the icon next to the button
    auto table = new brls::BoxLayout(brls::BoxLayoutOrientation::HORIZONTAL);
    table->setHeight(170); // Called so anything below will have spacing

    // Icon table needed for proper spacing and container for Image
    auto iconTable = new brls::BoxLayout(brls::BoxLayoutOrientation::VERTICAL);
    iconTable->setWidth(125);

    auto& profileState = *State<ProfileState>::Listener::getState();
    auto profile       = profileState.getCurrentProfile();

    profileIcon = new brls::Image(profile->icon.first, profile->icon.second);
    profileIcon->setScaleType(brls::ImageScaleType::FIT);
    profileIcon->setHeight(70);
    profileIcon->setWidth(70);
    iconTable->addView(profileIcon);

    // Button to select profile
    profileName = new brls::ListItem("main/account/select_profile"_i18n,
        "main/account/select_profile_tooltip"_i18n);

    profileName->setValue(profile->name);
    profileName->registerAction(
        "brls/hints/select"_i18n, brls::Key::A, [&profileState]() {
            if (auto profile = profileState->selectAccount(); profile != nullptr)
                profileState.setCurrentProfile(profile);

            return true;
        });

    // This is about the right width in order to make the icon + selector width
    // the width of a normal ListItem
    profileName->setWidth(625);

    table->addView(profileName);
    table->addView(iconTable);

    this->addView(table);
}

void AccountTab::addAtlasAccountData() {
    // auto* bar = new ui::components::Bar(0.4,
    // brls::Application::getTheme()->textColor); this->addView(bar);

    this->addView(new brls::Header("main/account/atlas/header"_i18n));

    this->signButton = new brls::ListItem("main/account/atlas/sign_in"_i18n);

    auto* state = State<AccountState>::Listener::getState();
    signButton->registerAction("brls/hints/select"_i18n, brls::Key::A, [state]() {
        state->setLoggedIn(!state->loggedIn);
        return true;
    });

    this->addView(signButton);
}
} // namespace ui