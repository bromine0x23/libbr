/**
 * @file
 * @brief count_ones
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/high_bits.hpp>
#include <libbr/math/function/low_bits.hpp>

extern "C" {

constexpr static BR::UInt8 LIBBER_COUNT_ONES[] = {
//	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, // 0
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 1
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 2
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 3
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 4
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 5
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 6
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // 7
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, // 8
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // 9
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // A
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // B
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, // C
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // D
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, // E
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, // F
};

/**
 * count ones in binary representation
 * @param x
 * @return number of ones
 */
//@{
constexpr auto libbr_count_ones_8(BR::UInt8 x) noexcept -> BR::UInt8 {
	return LIBBER_COUNT_ONES[x];
}

constexpr auto libbr_count_ones_16(BR::UInt16 x) noexcept -> BR::UInt8 {
	return libbr_count_ones_8(libbr_high_bits_16(x)) + libbr_count_ones_8(libbr_low_bits_16(x));
}

constexpr auto libbr_count_ones_32(BR::UInt32 x) noexcept -> BR::UInt8 {
	return libbr_count_ones_16(libbr_high_bits_32(x)) + libbr_count_ones_16(libbr_low_bits_32(x));
}

constexpr auto libbr_count_ones_64(BR::UInt64 x) noexcept -> BR::UInt8 {
	return libbr_count_ones_32(libbr_high_bits_64(x)) + libbr_count_ones_32(libbr_low_bits_64(x));
}

#ifdef BR_HAS_INT128
constexpr auto libbr_count_ones_128(BR::UInt128 x) noexcept -> BR::UInt8 {
	return libbr_count_ones_64(libbr_high_bits_128(x)) + libbr_count_ones_64(libbr_low_bits_128(x));
}
#endif
//@}
}

namespace BR {
inline namespace Math {
inline namespace Function {

constexpr auto count_ones(UInt8 x) noexcept -> UInt8 {
	return libbr_count_ones_8(x);
}

constexpr auto count_ones(UInt16 x) noexcept -> UInt8 {
	return libbr_count_ones_16(x);
}

constexpr auto count_ones(UInt32 x) noexcept -> UInt8 {
	return libbr_count_ones_32(x);
}

constexpr auto count_ones(UInt64 x) noexcept -> UInt8 {
	return libbr_count_ones_64(x);
}

#ifdef BR_HAS_INT128
constexpr auto count_ones(UInt128 x) noexcept -> UInt8 {
	return libbr_count_ones_128(x);
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR