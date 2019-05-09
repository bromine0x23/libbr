/**
 * @file
 * @brief Alignment
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#ifdef BR_SINCE_CXX17
#  include <new>
#endif

namespace BR {

inline namespace Memory {

#ifdef BR_SINCE_CXX17
using Alignment = std::align_val_t;
#endif

} // namespace Memory

} // namespace BR
