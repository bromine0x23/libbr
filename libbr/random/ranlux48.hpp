/**
 * @file
 * @brief Ranlux48
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/discard_block_engine.hpp>
#include <libbr/random/ranlux48_base.hpp>

namespace BR {
inline namespace Random {

using Ranlux48 = DiscardBlockEngine< Ranlux48Base, 389, 11 >;

} // namespace Random
} // namespace BR