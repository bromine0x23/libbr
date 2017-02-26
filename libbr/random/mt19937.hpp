/**
 * @file
 * @brief MT19937
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/mersenne_twister_engine.hpp>

namespace BR {
inline namespace Random {

using MT19937 = MersenneTwisterEngine< UInt32, 32, 624, 397, 31, 0x9908B0DFU, 11, 0xFFFFFFFFU, 7, 0x9D2C5680U, 15, 0xEFC60000U, 18, 1812433253>;

} // namespace Random
} // namespace BR