/**
 * @file
 * @brief bits_parity
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/high_bits.hpp>
#include <libbr/math/function/low_bits.hpp>

extern "C" {

constexpr static BR::UInt8 LIBBER_BITS_PARITY[] = {
//	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, // 0
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, // 1
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, // 2
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, // 3
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, // 4
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, // 5
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, // 6
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, // 7
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, // 8
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, // 9
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, // A
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, // B
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, // C
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, // D
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, // E
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, // F
};


/**
 * get parity of ones in x's binary representation
 * @param x
 * @return parity of ones
 */
//@{
constexpr auto libbr_bits_parity_8(BR::UInt8 x) noexcept -> BR::UInt8 {
	return LIBBER_BITS_PARITY[x];
}

constexpr auto libbr_bits_parity_16(BR::UInt16 x) noexcept -> BR::UInt8 {
	return libbr_count_ones_8(libbr_high_bits_16(x) ^ libbr_low_bits_16(x));
}

constexpr auto libbr_bits_parity_32(BR::UInt32 x) noexcept -> BR::UInt8 {
	return libbr_count_ones_16(libbr_high_bits_32(x) ^ libbr_low_bits_32(x));
}

constexpr auto libbr_bits_parity_64(BR::UInt64 x) noexcept -> BR::UInt8 {
	return libbr_bits_parity_32(libbr_high_bits_64(x) ^ libbr_low_bits_64(x));
}

#ifdef BR_HAS_INT128
constexpr auto libbr_bits_parity_128(BR::UInt128 x) noexcept -> BR::UInt8 {
	return libbr_bits_parity_64(libbr_high_bits_128(x) ^ libbr_low_bits_128(x));
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