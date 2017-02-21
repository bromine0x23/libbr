/**
 * @file
 * @brief is_power2
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/high_bits.hpp>
#include <libbr/math/function/low_bits.hpp>

extern "C" {

/**
 * is_power2
 * @param x
 * @return is power of 2
 */
//@{
constexpr auto libbr_is_power2_8(BR::UInt8 x) noexcept -> bool {
	return (x & (x - 1)) == 0;
}

constexpr auto libbr_is_power2_16(BR::UInt16 x) noexcept -> bool {
	return (x & (x - 1)) == 0;
}

constexpr auto libbr_is_power2_32(BR::UInt32 x) noexcept -> bool {
	return (x & (x - 1)) == 0;
}

constexpr auto libbr_is_power2_64(BR::UInt64 x) noexcept -> bool {
	return (x & (x - 1)) == 0;
}

#ifdef BR_HAS_INT128
constexpr auto libbr_is_power2_128(BR::UInt128 x) noexcept -> bool {
	return (x & (x - 1)) == 0;
}
#endif
//@}
}

namespace BR {
inline namespace Math {
inline namespace Function {

constexpr auto is_power2(UInt8 x) noexcept -> bool {
	return libbr_is_power2_8(x);
}

constexpr auto is_power2(UInt16 x) noexcept -> bool {
	return libbr_is_power2_16(x);
}

constexpr auto is_power2(UInt32 x) noexcept -> bool {
	return libbr_is_power2_32(x);
}

constexpr auto is_power2(UInt64 x) noexcept -> bool {
	return libbr_is_power2_64(x);
}

#ifdef BR_HAS_INT128
constexpr auto is_power2(UInt128 x) noexcept -> bool {
	return libbr_is_power2_128(x);
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR