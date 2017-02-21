/**
 * @file
 * @brief low_bits
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * low_bits
 * @param x
 * @return high_bits
 */
//@{
constexpr auto libbr_low_bits_16(BR::UInt16 x) noexcept -> BR::UInt8 {
	return BR::UInt8(x & 0xFFU);
}

constexpr auto libbr_low_bits_32(BR::UInt32 x) noexcept -> BR::UInt16 {
	return BR::UInt16(x & 0xFFFFU);
}

constexpr auto libbr_low_bits_64(BR::UInt64 x) noexcept -> BR::UInt32 {
	return BR::UInt32(x & 0xFFFFFFFFU);
}

#ifdef BR_HAS_INT128
constexpr auto libbr_low_bits_128(BR::UInt128 x) noexcept -> BR::UInt64 {
	return BR::UInt64(x & 0xFFFFFFFFFFFFFFFFULL);
}
#endif
//@}
}

namespace BR {
inline namespace Math {
inline namespace Function {

constexpr auto low_bits(UInt16 x) noexcept -> UInt8 {
	return libbr_low_bits_16(x);
}

constexpr auto low_bits(UInt32 x) noexcept -> UInt16 {
	return libbr_low_bits_32(x);
}

constexpr auto low_bits(UInt64 x) noexcept -> UInt32 {
	return libbr_low_bits_64(x);
}

#ifdef BR_HAS_INT128
constexpr auto low_bits(UInt128 x) noexcept -> UInt64 {
	return libbr_low_bits_128(x);
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR