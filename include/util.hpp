/**
 * @file util.hpp
 * @brief General utilities for making code cleaner and shorter. 
 * This file Should not contain application specific code
 */

#pragma once

#include <vector>
#include <algorithm>

template<class Container, class F>
auto erase_where(Container& c, F&& f) {
    return c.erase(std::remove_if(c.begin(), c.end(), std::forward<F>(f)), c.end());    
}