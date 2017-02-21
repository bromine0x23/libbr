/**
 * @file
 * @brief count_leading_zeros
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/high_bits.hpp>
#include <libbr/math/function/low_bits.hpp>

extern "C" {

constexpr static BR::UInt8 LIBBER_COUNT_LEADING_ZEROS[] = {
//	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, // 0
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, // 1
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // 2
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // 3
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 4
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 5
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 6
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 7
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 8
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 9
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // A
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // B
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // C
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // D
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // E
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // F
};

/**
 * count leading zeros
 * @param x
 * @return number of leading zeros
 */
//@{
constexpr auto libbr_count_leading_zeros_8(BR::UInt8 x) noexcept -> BR::UInt8 {
	return LIBBER_COUNT_LEADING_ZEROS[x];
}

constexpr auto libbr_count_leading_zeros_16(BR::UInt16 x) noexcept -> BR::UInt8 {
	return x > 0xFFU ? libbr_count_leading_zeros_8(libbr_high_bits_16(x)) : libbr_count_leading_zeros_8(libbr_low_bits_16(x)) + 8;
}

constexpr auto libbr_count_leading_zeros_32(BR::UInt32 x) noexcept -> BR::UInt8 {
	return x > 0xFFFFU ? libbr_count_leading_zeros_16(libbr_high_bits_32(x)) : libbr_count_leading_zeros_16(libbr_low_bits_32(x)) + 16;
}

constexpr auto libbr_count_leading_zeros_64(BR::UInt64 x) noexcept -> BR::UInt8 {
	return x > 0xFFFFFFFFULL ? libbr_count_leading_zeros_32(libbr_high_bits_64(x)) : libbr_count_leading_zeros_32(libbr_low_bits_64(x)) + 32;
}

#ifdef BR_HAS_INT128
constexpr auto libbr_count_leading_zeros_128(BR::UInt128 x) noexcept -> BR::UInt8 {
	return x > 0xFFFFFFFFFFFFFFFFULL ? libbr_count_leading_zeros_64(libbr_high_bits_128(x)) : libbr_count_leading_zeros_64(libbr_low_bits_128(x)) + 64;
}
#endif
//@}
}

namespace BR {
inline namespace Math {
inline namespace Function {

constexpr auto count_leading_zeros(UInt8 x) noexcept -> UInt8 {
	return libbr_count_leading_zeros_8(x);
}

constexpr auto count_leading_zeros(UInt16 x) noexcept -> UInt8 {
	return libbr_count_leading_zeros_16(x);
}

constexpr auto count_leading_zeros(UInt32 x) noexcept -> UInt8 {
	return libbr_count_leading_zeros_32(x);
}

constexpr auto count_leading_zeros(UInt64 x) noexcept -> UInt8 {
	return libbr_count_leading_zeros_64(x);
}

#ifdef BR_HAS_INT128
constexpr auto count_leading_zeros(UInt128 x) noexcept -> UInt8 {
	return libbr_count_leading_zeros_128(x);
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR