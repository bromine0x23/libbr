/**
 * @file
 * @brief 最大公约数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Math {

/**
 * @brief 最大公约数
 * @tparam TIntegral 整型类型
 * @param x,y
 * @return 最大公约数
 */
template< typename TIntegral >
constexpr inline auto gcd(TIntegral x, TIntegral y) -> TIntegral {
	do {
		TIntegral t = x % y;
		x = y;
		y = t;
	} while (y != 0);
	return x;
}

} // namespace Math
} // namespace BR