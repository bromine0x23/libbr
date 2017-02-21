/**
 * @file
 * @brief ilog2
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/high_bits.hpp>
#include <libbr/math/function/low_bits.hpp>

extern "C" {

constexpr static BR::SInt8 LIBBR_ILOG2[] = {
//	 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, // 0
	 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, // 1
	 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, // 2
	 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, // 3
	 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 4
	 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 5
	 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 6
	 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, // 7
	 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // 8
	 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // 9
	 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // A
	 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // B
	 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // C
	 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // D
	 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // E
	 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // F
};

/**
 * integral log2
 * @param x
 * @return log2(x)
 */
//@{
constexpr auto libbr_ilog2_8(BR::UInt8 x) noexcept -> BR::SInt8 {
	return LIBBR_ILOG2[x];
}

constexpr auto libbr_ilog2_16(BR::UInt16 x) noexcept -> BR::SInt16 {
	return libbr_high_bits_16(x) != 0 ? libbr_ilog2_8(libbr_high_bits_16(x)) + BR::SInt16(8) : libbr_ilog2_8(libbr_low_bits_16(x));
}

constexpr auto libbr_ilog2_32(BR::UInt32 x) noexcept -> BR::SInt32 {
	return libbr_high_bits_32(x) != 0 ? libbr_ilog2_16(libbr_high_bits_32(x)) + BR::SInt32(16) : libbr_ilog2_16(libbr_low_bits_32(x));
}

constexpr auto libbr_ilog2_64(BR::UInt64 x) noexcept -> BR::SInt64 {
	return libbr_high_bits_64(x) != 0 ? libbr_ilog2_32(libbr_high_bits_64(x)) + BR::SInt64(32) : libbr_ilog2_32(libbr_low_bits_64(x));
}

#ifdef BR_HAS_INT128
constexpr auto libbr_ilog2_128(BR::UInt128 x) noexcept -> BR::SInt128 {
	return libbr_high_bits_128(x) != 0 ? libbr_ilog2_64(libbr_high_bits_128(x)) + BR::SInt128(64) : libbr_ilog2_64(libbr_low_bits_128(x));
}
#endif
//@}
}

namespace BR {
inline namespace Math {
inline namespace Function {

constexpr auto ilog2(UInt8 x) noexcept -> SInt8 {
	return libbr_ilog2_8(x);
}

constexpr auto ilog2(UInt16 x) noexcept -> SInt16 {
	return libbr_ilog2_16(x);
}

constexpr auto ilog2(UInt32 x) noexcept -> SInt32 {
	return libbr_ilog2_32(x);
}

constexpr auto ilog2(UInt64 x) noexcept -> SInt64 {
	return libbr_ilog2_64(x);
}

#ifdef BR_HAS_INT128
constexpr auto ilog2(UInt128 x) noexcept -> SInt128 {
	return libbr_ilog2_128(x);
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR