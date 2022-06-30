#pragma once

#include <borealis.hpp>

#include "state/app_state.hpp"

namespace ui {
class AccountTab : public brls::List,
                   State<AccountState>::Listener,
                   State<ProfileState>::Listener {
public:
    AccountTab(AccountState& accountState, ProfileState& profileState);
    void onStateUpdate(AccountState& state) override;
    void onStateUpdate(ProfileState& state) override;

private:
    void addProfileSelector();
    void addAtlasAccountData();

    brls::ListItem* signButton;

    brls::Image* profileIcon;
    brls::ListItem* profileName;
};
} // namespace ui