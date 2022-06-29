/**
 * @file util.hpp
 * @brief General utilities for making code cleaner and shorter. 
 * This file Should not contain application specific code
 */

#pragma once

#include <vector>
#include <algorithm>
#include <switch.h>
#include <string_view>
#include <stdexcept>
#include <fmt/format.h>

#include "logger.hpp"

template<class Container, class F>
auto erase_where(Container& c, F&& f) {
    return c.erase(std::remove_if(c.begin(), c.end(), std::forward<F>(f)), c.end());    
}

/**
 * @brief Logs error and throws std::runtime_error if result is an error
 *
 * @param result the result to test
 * @param operation attempted operation (eg. "do stuff")
 */
inline void assertResult(Result result, const std::string_view&& operation) {
	if (!R_SUCCEEDED(result)) {
		auto str = fmt::format("Failed to {} (code {})", operation, result);
		Logger::error(str);
		throw std::runtime_error(str);
	}
}