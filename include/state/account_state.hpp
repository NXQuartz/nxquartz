#pragma once

#include "state/state.hpp"
#include <string>

class AccountState : public State<AccountState> {
public:
    AccountState() : State<AccountState>() { }

    bool loggedIn = false;

    void setLoggedIn(bool loggedIn) {
        this->loggedIn = loggedIn;
        dispatchUpdate();
    }
};