#pragma once

#include <borealis.hpp>

#include "state/app_state.hpp"

namespace ui {
    class AccountTab : public brls::List, public StateListener<AccountState> {
        void addProfileSelector();
        void addAtlasAccountData();

        brls::ListItem* signButton;
    public:
        AccountTab(AccountState* state);
        void onStateUpdate(const AccountState* state) override;
    };
}