/**
 * @file
 * @brief MinimalStandard1988
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/linear_congruential_engine.hpp>

namespace BR {
inline namespace Random {

using MinimalStandard1988 = LinearCongruentialEngine< UInt32, 16807, 0, 0x7FFFFFFFU >;

} // namespace Random
} // namespace BR