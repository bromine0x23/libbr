/**
 * @file
 * @brief gcd
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TIntegral >
inline auto gcd(TIntegral x, TIntegral y) -> TIntegral {
	do {
		TIntegral t = x % y;
		x = y;
		y = t;
	} while (y != 0);
	return x;
}

} // namespace BR