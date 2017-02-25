/**
 * @file
 * @brief Random module
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

#include <libbr/random/linear_congruential_engine.hpp>
#include <libbr/random/mersenne_twister_engine.hpp>
#include <libbr/random/subtract_with_carry_engine.hpp>

#include <libbr/random/discard_block_engine.hpp>
#include <libbr/random/independent_bits_engine.hpp>

namespace BR {

/**
 * @brief Random
 */
inline namespace Random {
} // namespace Random

} // namespace BR