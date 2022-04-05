#include "hos/common.hpp"

namespace hos {
    u32 GetBatteryLevel() {
        u32 bat = 0;
        psmGetBatteryChargePercentage(&bat);
        return bat;
    }

    bool IsCharging() {
        auto charger = PsmChargerType_Unconnected;
        psmGetChargerType(&charger);
        return charger != PsmChargerType_Unconnected;
    }

    std::string GetCurrentTime() {
        const auto posixTime = time(nullptr);
        const auto localTime = localtime((const time_t*)&posixTime);
        char time_str[0x10] = {0};
        sprintf(time_str, "%02d:%02d:%02d", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
        return time_str;
    }

    // std::string GetCurrentTime() {
    //     const auto posix_time = time(nullptr);
    //     const auto local_time = localtime((const time_t*)&posix_time);
    //     char time_str[0x10] = {0};
    //     sprintf(time_str, "%02d:%02d:%02d", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    //     return time_str;
    // }

    // std::string FormatHex128(const AccountUid user_id) {
    //     auto ptr = reinterpret_cast<const u8*>(user_id.uid);
    //     std::stringstream strm;
    //     strm << std::hex << std::uppercase;
    //     for(u32 i = 0; i < sizeof(AccountUid); i++) {
    //         strm << static_cast<u32>(ptr[i]);
    //     }
    //     return strm.str();
    // }

    // std::string FormatResult(const Result rc) {
    //     char res_err[0x10] = {};
    //     sprintf(res_err, "%04d-%04d", 2000 + R_MODULE(rc), R_DESCRIPTION(rc));
    //     return res_err;
    // }

    // std::string FormatTime(const u64 sec) {
    //     if(sec > 60) {
    //         const auto mins = sec / 60;
    //         const auto secs_rem = sec % 60;
    //         if(mins > 60) {
    //             const auto hours = mins / 60;
    //             const auto mins_rem = mins % 60;
    //             return std::to_string(hours) + " h" + ((mins_rem > 0) ? (" " + std::to_string(mins_rem) + " min") : "") + ((secs_rem > 0) ? (" " + std::to_string(secs_rem) + " s") : "");
    //         }
    //         return std::to_string(mins) + " min" + ((secs_rem > 0) ? (" " + std::to_string(secs_rem) + " s") : "");
    //     }
    //     return std::to_string(sec) + " s";
    // }

    // void LockAutoSleep() {
    //     if(GetLaunchMode() == LaunchMode::Application) {
    //         appletBeginBlockingHomeButton(0);
    //     }
    //     appletSetMediaPlaybackState(true);
    // }

    // void UnlockAutoSleep() {
    //     appletSetMediaPlaybackState(false);
    //     if(GetLaunchMode() == LaunchMode::Application) {
    //         appletEndBlockingHomeButton();
    //     }
    // }

    // u8 ReadSystemKeyGeneration() {
    //     FsStorage boot0;
    //     if(R_SUCCEEDED(fsOpenBisStorage(&boot0, FsBisPartitionId_BootPartition1Root))) {
    //         u32 keygen_ver = 0;
    //         fsStorageRead(&boot0, 0x2330, &keygen_ver, sizeof(u32));
    //         fsStorageClose(&boot0);
    //         return static_cast<u8>(keygen_ver);
    //     }
    //     return 0;
    // }

    // Result PerformShutdown (const bool do_reboot) {
    //     GLEAF_RC_TRY(spsmInitialize());
    //     GLEAF_RC_TRY(spsmShutdown(do_reboot));
    //     spsmExit();

    //     return 0;
    // }
}