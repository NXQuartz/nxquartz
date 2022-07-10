#include "profile.hpp"

#include <chrono>
#include <thread>
#include <unordered_map>

#include "util.hpp"

ProfileService::ProfileService() {
    assertResult(accountInitialize(AccountServiceType_Administrator),
        "initialize account service");
    Logger::info("Initialized profile service.");
}

ProfileService::~ProfileService() {
    for (const auto& accountPair : accountMap)
        delete accountPair.second;

    accountMap.clear();
    accountExit();

    Logger::info("Account service has been shut down.");
}

SwitchProfile* ProfileService::fromId(AccountUid uid) {
    // If the user was already loaded
    if (accountMap.count(uid) > 0)
        return accountMap[uid];

    // Icon data
    u8* iconBuffer;
    u32 imageSize, realSize;

    // Lookup and cache the users details
    AccountProfile profile;
    AccountProfileBase profileBase;
    if (R_SUCCEEDED(accountGetProfile(&profile, uid)) && R_SUCCEEDED(accountProfileGet(&profile, nullptr, &profileBase)) && R_SUCCEEDED(accountProfileGetImageSize(&profile, &imageSize)) && (iconBuffer = (u8*)malloc(imageSize)) != NULL && R_SUCCEEDED(accountProfileLoadImage(&profile, iconBuffer, imageSize, &realSize))) {
        auto username = std::string(profileBase.nickname, 0x20);
        accountProfileClose(&profile);

        auto account = new SwitchProfile {
            .id   = uid,
            .name = username,
            .icon = std::make_pair(iconBuffer, imageSize)
        };

        accountMap[uid] = account;

        return account;
    }

    return nullptr;
}

SwitchProfile* ProfileService::selectAccount() {
    // Account select applet might still be open after call.
    // If applet still open atmosphere will crash so we wait 1 second to make
    // sure it closed.
    using namespace std::chrono;
    if (duration_cast<milliseconds>(steady_clock::now() - lastSelected).count() < 1000)
        std::this_thread::sleep_for(seconds(1));

    const PselUserSelectionSettings selectionCfg = {};
    AccountUid outUid;

    if (R_SUCCEEDED(pselShowUserSelector(&outUid, &selectionCfg))) {
        this->lastSelected = std::chrono::steady_clock::now();
        return this->fromId(outUid);
    }

    return nullptr;
}

const std::vector<SwitchProfile*> ProfileService::getAll() {
    AccountUid* uids = new AccountUid[ACC_USER_LIST_SIZE];
    s32 userCount;

    std::vector<SwitchProfile*> users;
    if (R_SUCCEEDED(accountListAllUsers(uids, ACC_USER_LIST_SIZE, &userCount))) {
        for (int i = 0; i < userCount; i++) {
            // I'm not going to check null on fromId result.
            // It should never even be null if we got this far.
            users.push_back(fromId(uids[i]));
        }
    }

    delete[] uids;
    return users;
}
