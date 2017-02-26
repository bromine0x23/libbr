/**
 * @file
 * @brief Ranlux24Base
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/subtract_with_carry_engine.hpp>

namespace BR {
inline namespace Random {

using Ranlux24Base = SubtractWithCarryEngine< UInt32, 24, 10, 24 >;

} // namespace Random
} // namespace BR