/**
 * @file
 * @brief Random
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

#include <libbr/random/linear_congruential_engine.hpp>
#include <libbr/random/mersenne_twister_engine.hpp>
#include <libbr/random/subtract_with_carry_engine.hpp>

#include <libbr/random/discard_block_engine.hpp>
#include <libbr/random/independent_bits_engine.hpp>
#include <libbr/random/shuffle_order_engine.hpp>

#include <libbr/random/predefined_engines.hpp>

#include <libbr/random/generate_canonical.hpp>

#include <libbr/random/uniform_real_distribution.hpp>
#include <libbr/random/bernoulli_distribution.hpp>

namespace BR {

/**
 * @brief Random
 */
inline namespace Random {
} // namespace Random

} // namespace BR