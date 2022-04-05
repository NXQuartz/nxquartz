#pragma once

#include <switch.h>
#include <string>

namespace hos {
    /**
     * @brief Get the Battery Level of the system
     */
    u32 GetBatteryLevel();

    /**
     * @brief Check if the console is charging
     */
    bool IsCharging();

    /**
     * @brief Get the Current time formatted as %02d:%02d:%02d
     */
    std::string GetCurrentTime();
}