#include "account.hpp"

#include <unordered_map>
#include <chrono>
#include <thread>

namespace account {
    static std::unordered_map<AccountUid, SwitchAccount*> accountMap;
    static auto lastSelected = std::chrono::steady_clock::now();
    static SwitchAccount* selectedAccount = nullptr;

    Result initAccountService() {
        return accountInitialize(AccountServiceType_Administrator);
    }

    void exitAccountService() {
        for (const auto& accountPair : accountMap)
            delete accountPair.second;
        
        accountMap.clear();
        accountExit();
    }

    SwitchAccount* SwitchAccount::getCurrentAccount() {
        if (selectedAccount != nullptr)
            return selectedAccount;

        selectedAccount = getAll()[0];
        return selectedAccount;
    }

    bool SwitchAccount::setCurrentAccount(AccountUid uid) {
        auto* account = fromId(uid);

        if (account == nullptr)
            return false;

        selectedAccount = account;
        return true;
    }

    SwitchAccount* SwitchAccount::fromId(AccountUid uid) {
        // If the user was already loaded
        if (accountMap.count(uid) > 0)
            return accountMap[uid];

        // Icon data
        u8* iconBuffer;
        u32 imageSize, realSize;

        // Lookup and cache the users details
        AccountProfile profile;
        AccountProfileBase profileBase;
        if (R_SUCCEEDED(accountGetProfile(&profile, uid)) && 
            R_SUCCEEDED(accountProfileGet(&profile, nullptr, &profileBase)) &&
            R_SUCCEEDED(accountProfileGetImageSize(&profile, &imageSize)) && (iconBuffer = (u8*)malloc(imageSize)) != NULL &&
            R_SUCCEEDED(accountProfileLoadImage(&profile, iconBuffer, imageSize, &realSize))) {
            auto username = std::string(profileBase.nickname, 0x20);
            accountProfileClose(&profile);

            auto account = new SwitchAccount {
                .id = uid,
                .name = username,
                .icon = std::make_pair(iconBuffer, imageSize)
            };

            accountMap[uid] = account;

            return account;
        }

        return nullptr;
    }

    SwitchAccount* SwitchAccount::selectAccount() {
        // Account select applet might still be open after call.
        // If applet still open atmosphere will crash so we wait 1 second to make sure it closed.
        using namespace std::chrono;
        if (duration_cast<milliseconds>(steady_clock::now() - lastSelected).count() < 1000)
            std::this_thread::sleep_for(seconds(1));

        const PselUserSelectionSettings selectionCfg = {};
        AccountUid outUid;

        if (R_SUCCEEDED(pselShowUserSelector(&outUid, &selectionCfg))) {
            lastSelected = std::chrono::steady_clock::now();
            selectedAccount = SwitchAccount::fromId(outUid);
            return selectedAccount;
        }

        return nullptr;
    }

    const std::vector<SwitchAccount*> SwitchAccount::getAll() {
        AccountUid* uids = new AccountUid[ACC_USER_LIST_SIZE];
        s32 userCount;

        std::vector<SwitchAccount*> users;
        if (R_SUCCEEDED(accountListAllUsers(uids, ACC_USER_LIST_SIZE, &userCount))) {
            for (int i = 0; i < userCount; i++) {
                // I'm not going to check null on fromId result.
                // It should never even be null if we got this far.
                users.push_back(SwitchAccount::fromId(uids[i]));
            }
        }
        
        delete[] uids;
        return users;
    }
}