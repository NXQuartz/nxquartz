#pragma once

#include <map>
#include <string>
#include <vector>
#include <switch.h>
#include <borealis.hpp>

// Use AccountUid as map key
namespace std {
    template <>
    struct hash<AccountUid> {
        size_t operator() (const AccountUid& a) const { 
            return ((hash<u64>()(a.uid[0]) ^ (hash<u64>()(a.uid[1]) << 1)) >> 1); 
        }
    };
}

inline bool operator==(const AccountUid& x, const AccountUid& y) {
    return x.uid[0] == y.uid[0] && x.uid[1] == y.uid[1];
}

inline bool operator==(const AccountUid& x, u64 y) {
    return x.uid[0] == y && x.uid[1] == y;
}

inline bool operator<(const AccountUid& x, const AccountUid& y) {
    return x.uid[0] < y.uid[0] && x.uid[1] == y.uid[1];
}

namespace account {
    // Must be called before using any SwitchAccount operations
    Result initAccountService();

    // Call when done doing SwitchAccount operations
    void exitAccountService();

    class SwitchAccount {
    public:
        const AccountUid id;
        const std::string name;
        const std::pair<unsigned char*, size_t> icon;

        /**
         * @brief Gets an account by their Uid.
         * 
         * @param uid the uid of the user
         * @return a SwitchAccount* or nullptr if the user was not found
         */
        static SwitchAccount* fromId(AccountUid uid);

        /**
         * @brief Opens selection dialogue on the switch for user to select.
         * 
         * @return SwitchAccount* or nullptr if cancelled
         */
        static SwitchAccount* selectAccount();

        /**
         * @brief Get the registered user accounts
         * 
         * @return all user accounts 
         */
        static const std::vector<SwitchAccount*> getAll();

        /**
         * @brief Get currently selected account.
         * This will return the first found user if no profile was set
         * 
         * @return current account
         */
        static SwitchAccount* getCurrentAccount();

        /**
         * @brief Set the current account object.
         * 
         * @param uid user identifier
         * @return account found
         */
        static bool setCurrentAccount(AccountUid uid); 
    };
}