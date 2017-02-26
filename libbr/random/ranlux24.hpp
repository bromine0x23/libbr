/**
 * @file
 * @brief Ranlux24
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/discard_block_engine.hpp>
#include <libbr/random/ranlux24_base.hpp>

namespace BR {
inline namespace Random {

using Ranlux24 = DiscardBlockEngine< Ranlux24Base, 223, 23 >;

} // namespace Random
} // namespace BR