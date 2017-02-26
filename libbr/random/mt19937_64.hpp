/**
 * @file
 * @brief MT19937_64
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/mersenne_twister_engine.hpp>

namespace BR {
inline namespace Random {

using MT19937_64 = MersenneTwisterEngine< UInt64, 64, 312, 156, 31, 0xB5026F5AA96619E9ULL, 29, 0x5555555555555555ULL, 17, 0x71D67FFFEDA60000ULL, 37, 0xFFF7EEE000000000ULL, 43, 6364136223846793005ULL>;

} // namespace Random
} // namespace BR