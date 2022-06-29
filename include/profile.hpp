#pragma once

#include <borealis.hpp>
#include <chrono>
#include <map>
#include <string>
#include <switch.h>
#include <vector>

// Use AccountUid as map key
namespace std {
template <>
struct hash<AccountUid> {
    size_t operator()(const AccountUid& a) const {
        return ((hash<u64>()(a.uid[0]) ^ (hash<u64>()(a.uid[1]) << 1)) >> 1);
    }
};
} // namespace std

inline bool operator==(const AccountUid& x, const AccountUid& y) {
    return x.uid[0] == y.uid[0] && x.uid[1] == y.uid[1];
}

inline bool operator==(const AccountUid& x, u64 y) {
    return x.uid[0] == y && x.uid[1] == y;
}

inline bool operator<(const AccountUid& x, const AccountUid& y) {
    return x.uid[0] < y.uid[0] && x.uid[1] == y.uid[1];
}

/**
 * @brief Nintendo switch user profile
 */
class SwitchProfile {
public:
    const AccountUid id;
    const std::string name;
    const std::pair<unsigned char*, size_t> icon;
};

/**
 * @brief Account operations.
 * Only one instance of this may exist per applet.
 */
class ProfileService {
public:
    ProfileService();
    ~ProfileService();

    /**
     * @brief Gets an account by their Uid.
     *
     * @param uid the uid of the user
     * @return a SwitchProfile* or nullptr if the user was not found
     */
    SwitchProfile* fromId(AccountUid uid);

    /**
     * @brief Opens selection dialogue on the switch for user to select.
     *
     * @return SwitchProfile* or nullptr if cancelled
     */
    SwitchProfile* selectAccount();

    /**
     * @brief Get the registered user accounts
     *
     * @return all user accounts
     */
    const std::vector<SwitchProfile*> getAll();

private:
    std::unordered_map<AccountUid, SwitchProfile*> accountMap;
    std::chrono::steady_clock::time_point lastSelected = std::chrono::steady_clock::now();
};