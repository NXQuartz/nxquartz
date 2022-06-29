#pragma once

#include "account_state.hpp"
#include "profile_state.hpp"

/**
 * @brief Container of all states in the application
 */
class AppState {
public:
    AppState(ProfileService* profileService) :
        profileState(profileService) { }

    AccountState accountState;
    ProfileState profileState;
};