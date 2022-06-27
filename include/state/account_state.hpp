#pragma once

#include <string>
#include "state/state.hpp"

class AccountState : public State<AccountState> {
public:
    AccountState() : State<AccountState>() {}
    
    bool loggedIn = false;
    
    void setLoggedIn(bool loggedIn) {
        this->loggedIn = loggedIn;
        dispatchUpdate();
    }
};