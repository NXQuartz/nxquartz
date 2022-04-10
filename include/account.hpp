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

        /**
         * @brief Gets an account by their Uid.
         * 
         * @param uid the uid of the user
         * @return a SwitchAccount* or nullptr if the user was not found
         */
        static const SwitchAccount* fromId(AccountUid uid);

        /**
         * @brief Opens selection dialogue on the switch for user to select.
         * 
         * @return SwitchAccount* or nullptr if cancelled
         */
        static const SwitchAccount* selectAccount();

        /**
         * @brief Get the registered user accounts
         * 
         * @return all user accounts 
         */
        static const std::vector<const SwitchAccount*> getAll();

        /**
         * @brief Retrieve the users icon as a heap allocated image pointer.
         * Do not call this unless you are adding it to another brls view, otherwise you may have memory leaks.
         * 
         * @return brls::Image* 
         */
        brls::Image* createIcon();
    };
}