/**
 * @file
 * @brief KnuthB
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/shuffle_order_engine.hpp>
#include <libbr/random/minimal_standard_1988.hpp>

namespace BR {
inline namespace Random {

using KnuthB = ShuffleOrderEngine< MinimalStandard1988, 256 >;

} // namespace Random
} // namespace BR