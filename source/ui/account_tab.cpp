#include "ui/account_tab.hpp"
#include "account.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

namespace ui {
    AccountTab::AccountTab() {
        auto* button = new brls::ListItem("main/account/select_profile"_i18n);
        button->registerAction("brls/hints/select"_i18n, brls::Key::A, [] () {
            account::SwitchAccount::selectAccount();
            return true;
        });

        this->addView(button);
    }
}