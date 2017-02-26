/**
 * @file
 * @brief Ranlux48Base
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/subtract_with_carry_engine.hpp>

namespace BR {
inline namespace Random {

using Ranlux48Base = SubtractWithCarryEngine< UInt64, 48,  5, 12 >;

} // namespace Random
} // namespace BR