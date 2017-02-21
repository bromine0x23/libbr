/**
 * @file
 * @brief high_bits
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * high_bits
 * @param x
 * @return high_bits
 */
//@{
constexpr auto libbr_high_bits_16(BR::UInt16 x) noexcept -> BR::UInt8 {
	return BR::UInt8(x >> 8);
}

constexpr auto libbr_high_bits_32(BR::UInt32 x) noexcept -> BR::UInt16 {
	return BR::UInt16(x >> 16);
}

constexpr auto libbr_high_bits_64(BR::UInt64 x) noexcept -> BR::UInt32 {
	return BR::UInt32(x >> 32);
}

#ifdef BR_HAS_INT128
constexpr auto libbr_high_bits_128(BR::UInt128 x) noexcept -> BR::UInt64 {
	return BR::UInt64(x >> 64);
}
#endif
//@}
}

namespace BR {
inline namespace Math {
inline namespace Function {

constexpr auto high_bits(UInt16 x) noexcept -> UInt8 {
	return libbr_high_bits_16(x);
}

constexpr auto high_bits(UInt32 x) noexcept -> UInt16 {
	return libbr_high_bits_32(x);
}

constexpr auto high_bits(UInt64 x) noexcept -> UInt32 {
	return libbr_high_bits_64(x);
}

#ifdef BR_HAS_INT128
constexpr auto high_bits(UInt128 x) noexcept -> UInt64 {
	return libbr_high_bits_128(x);
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR