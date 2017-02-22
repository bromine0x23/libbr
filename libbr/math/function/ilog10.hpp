/**
 * @file
 * @brief ilog10
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/high_bits.hpp>
#include <libbr/math/function/low_bits.hpp>
#include <libbr/math/function/combine_bits.hpp>

extern "C" {

/**
 * integral log2
 * @param x
 * @return log2(x)
 */
//@{
constexpr auto libbr_ilog10_8(BR::UInt8 x) noexcept -> BR::UInt8 {
	return
		(x >= 100) ? 2 :
		(x >= 10) ? 1 : 0;
}

constexpr auto libbr_ilog10_16(BR::UInt16 x) noexcept -> BR::UInt16 {
	return
		(x >= 10000U) ? 4 :
		(x >= 1000U) ? 3 :
		(x >= 100U) ? 2 :
		(x >= 10U) ? 1 : 0;
}

constexpr auto libbr_ilog10_32(BR::UInt32 x) noexcept -> BR::UInt32 {
	return
		(x >= 1000000000U) ? 9 :
		(x >= 100000000U) ? 8 :
		(x >= 10000000U) ? 7 :
		(x >= 1000000U) ? 6 :
		(x >= 100000U) ? 5 :
		(x >= 10000U) ? 4 :
		(x >= 1000U) ? 3 :
		(x >= 100U) ? 2 :
		(x >= 10U) ? 1 : 0;
}

constexpr auto libbr_ilog10_64(BR::UInt64 x) noexcept -> BR::UInt64 {
	return
		(x >= 10000000000000000000ULL) ? 19 :
		(x >= 1000000000000000000ULL) ? 18 :
		(x >= 100000000000000000ULL) ? 17 :
		(x >= 10000000000000000ULL) ? 16 :
		(x >= 1000000000000000ULL) ? 15 :
		(x >= 100000000000000ULL) ? 14 :
		(x >= 10000000000000ULL) ? 13 :
		(x >= 1000000000000ULL) ? 12 :
		(x >= 100000000000ULL) ? 11 :
		(x >= 10000000000ULL) ? 10 :
		(x >= 1000000000U) ? 9 :
		(x >= 100000000U) ? 8 :
		(x >= 10000000U) ? 7 :
		(x >= 1000000U) ? 6 :
		(x >= 100000U) ? 5 :
		(x >= 10000U) ? 4 :
		(x >= 1000U) ? 3 :
		(x >= 100U) ? 2 :
		(x >= 10U) ? 1 : 0;
}

#ifdef BR_HAS_INT128
constexpr auto libbr_ilog10_128(BR::UInt128 x) noexcept -> BR::UInt128 {
	return
		(x >= libbr_combine_bits_128(0x4B3B4CA85A86C47AULL, 0x098A224000000000ULL)) ? 38 :
		(x >= libbr_combine_bits_128(0x0785EE10D5DA46D9ULL, 0x00F436A000000000ULL)) ? 37 :
		(x >= libbr_combine_bits_128(0x00C097CE7BC90715ULL, 0xB34B9F1000000000ULL)) ? 36 :
		(x >= libbr_combine_bits_128(0x0013426172C74D82ULL, 0x2B878FE800000000ULL)) ? 35 :
		(x >= libbr_combine_bits_128(0x0001ED09BEAD87C0ULL, 0x378D8E6400000000ULL)) ? 34 :
		(x >= libbr_combine_bits_128(0x0000314DC6448D93ULL, 0x38C15B0A00000000ULL)) ? 33 :
		(x >= libbr_combine_bits_128(0x000004EE2D6D415BULL, 0x85ACEF8100000000ULL)) ? 32 :
		(x >= libbr_combine_bits_128(0x0000007E37BE2022ULL, 0xC0914B2680000000ULL)) ? 31 :
		(x >= libbr_combine_bits_128(0x0000000C9F2C9CD0ULL, 0x4674EDEA40000000ULL)) ? 30 :
		(x >= libbr_combine_bits_128(0x00000001431E0FAEULL, 0x6D7217CAA0000000ULL)) ? 29 :
		(x >= libbr_combine_bits_128(0x00000000204FCE5EULL, 0x3E25026110000000ULL)) ? 28 :
		(x >= libbr_combine_bits_128(0x00000000033B2E3CULL, 0x9FD0803CE8000000ULL)) ? 27 :
		(x >= libbr_combine_bits_128(0x000000000052B7D2ULL, 0xDCC80CD2E4000000ULL)) ? 26 :
		(x >= libbr_combine_bits_128(0x0000000000084595ULL, 0x161401484A000000ULL)) ? 25 :
		(x >= libbr_combine_bits_128(0x000000000000D3C2ULL, 0x1BCECCEDA1000000ULL)) ? 24 :
		(x >= libbr_combine_bits_128(0x000000000000152DULL, 0x02C7E14AF6800000ULL)) ? 23 :
		(x >= libbr_combine_bits_128(0x000000000000021EULL, 0x19E0C9BAB2400000ULL)) ? 22 :
		(x >= libbr_combine_bits_128(0x0000000000000036ULL, 0x35C9ADC5DEA00000ULL)) ? 21 :
		(x >= libbr_combine_bits_128(0x0000000000000005ULL, 0x6BC75E2D63100000ULL)) ? 20 :
		(x >= 10000000000000000000ULL) ? 19 :
		(x >= 1000000000000000000ULL) ? 18 :
		(x >= 100000000000000000ULL) ? 17 :
		(x >= 10000000000000000ULL) ? 16 :
		(x >= 1000000000000000ULL) ? 15 :
		(x >= 100000000000000ULL) ? 14 :
		(x >= 10000000000000ULL) ? 13 :
		(x >= 1000000000000ULL) ? 12 :
		(x >= 100000000000ULL) ? 11 :
		(x >= 10000000000ULL) ? 10 :
		(x >= 1000000000U) ? 9 :
		(x >= 100000000U) ? 8 :
		(x >= 10000000U) ? 7 :
		(x >= 1000000U) ? 6 :
		(x >= 100000U) ? 5 :
		(x >= 10000U) ? 4 :
		(x >= 1000U) ? 3 :
		(x >= 100U) ? 2 :
		(x >= 10U) ? 1 : 0;
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