/**
 * @file
 * @brief Alignment
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#ifdef BR_AFTER_CXX14
#  include <new>
#endif

namespace BR {

inline namespace Memory {

#ifdef BR_AFTER_CXX14
using Alignment = std::align_val_t;
#endif

} // namespace Memory

} // namespace BR
