#include "account.hpp"

#include <unordered_map>
#include <chrono>
#include <thread>

namespace account {
    static std::unordered_map<AccountUid, const SwitchAccount*> accountMap;
    static auto lastSelected = std::chrono::steady_clock::now();

    Result initAccountService() {
        return accountInitialize(AccountServiceType_Administrator);
    }

    void exitAccountService() {
        for (const auto& accountPair : accountMap)
            delete accountPair.second;
        
        accountMap.clear();
        accountExit();
    }

    const SwitchAccount* SwitchAccount::fromId(AccountUid uid) {
        // If the user was already loaded
        if (accountMap.count(uid) > 0)
            return accountMap[uid];

        // Lookup and cache the users details
        AccountProfile profile;
        AccountProfileBase profileBase;
        if (R_SUCCEEDED(accountGetProfile(&profile, uid)) && R_SUCCEEDED(accountProfileGet(&profile, nullptr, &profileBase))) {
            auto username = std::string(profileBase.nickname, 0x20);
            accountProfileClose(&profile);

            auto account = new SwitchAccount {
                .id = uid,
                .name = username,
            };

            accountMap[uid] = account;

            return account;
        }

        // Invalid user
        return nullptr;
    }

    const SwitchAccount* SwitchAccount::selectAccount() {
        // Account select applet might still be open after call.
        // If applet still open atmosphere will crash so we wait 1 second to make sure it closed.
        using namespace std::chrono;
        if (duration_cast<milliseconds>(steady_clock::now() - lastSelected).count() < 1000)
            std::this_thread::sleep_for(seconds(1));

        const PselUserSelectionSettings selectionCfg = {};
        AccountUid outUid;

        if (R_SUCCEEDED(pselShowUserSelector(&outUid, &selectionCfg))) {
            lastSelected = std::chrono::steady_clock::now();
            return SwitchAccount::fromId(outUid);
        }

        return nullptr;
    }

    brls::Image* SwitchAccount::createIcon() {
        u8* iconBuffer;
        u32 imageSize, realSize;

        AccountProfile profile;
        if (R_SUCCEEDED(accountGetProfile(&profile, this->id)) && 
            R_SUCCEEDED(accountProfileGetImageSize(&profile, &imageSize)) && (iconBuffer = (u8*)malloc(imageSize)) != NULL &&
            R_SUCCEEDED(accountProfileLoadImage(&profile, iconBuffer, imageSize, &realSize))) {
            auto* brlsImage = new brls::Image(iconBuffer, imageSize);
            accountProfileClose(&profile);
            free(iconBuffer);

            return brlsImage;
        }

        return nullptr;
    }

    const std::vector<const SwitchAccount*> SwitchAccount::getAll() {
        AccountUid* uids = new AccountUid[ACC_USER_LIST_SIZE];
        s32 userCount;

        std::vector<const SwitchAccount*> users;
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