/**
 * @file
 * @brief gcd
 * @author Bromine0x23
 * @since 2015/10/27
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

extern template auto gcd(SInt8, SInt8) -> SInt8;

extern template auto gcd(UInt8, UInt8) -> UInt8;

extern template auto gcd(SInt16, SInt16) -> SInt16;

extern template auto gcd(UInt16, UInt16) -> UInt16;

extern template auto gcd(SInt32, SInt32) -> SInt32;

extern template auto gcd(UInt32, UInt32) -> UInt32;

extern template auto gcd(SInt64, SInt64) -> SInt64;

extern template auto gcd(UInt64, UInt64) -> UInt64;

} // namespace BR