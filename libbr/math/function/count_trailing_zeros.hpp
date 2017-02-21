/**
 * @file
 * @brief count_trailing_zeros
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

constexpr static BR::UInt8 LIBBER_COUNT_TRAILING_ZEROS_MAGIC_8 = 0x17;

constexpr static BR::UInt8 LIBBER_COUNT_TRAILING_ZEROS_8[] = {
	0, 1, 2, 4, 7, 3, 6, 5
};

constexpr static BR::UInt16 LIBBER_COUNT_TRAILING_ZEROS_MAGIC_16 = 0x09AF;

constexpr static BR::UInt8 LIBBER_COUNT_TRAILING_ZEROS_16[] = {
//	 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	 0,  1,  2,  5,  3,  9,  6, 11, 15,  4,  8, 10, 14,  7, 13, 12
};

constexpr static BR::UInt32 LIBBER_COUNT_TRAILING_ZEROS_MAGIC_32 = 0x04653ADF;

constexpr static BR::UInt8 LIBBER_COUNT_TRAILING_ZEROS_32[] = {
//	 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	 0,  1,  2,  6,  3, 11,  7, 16,  4, 14, 12, 21,  8, 23, 17, 26, // 0
	31,  5, 10, 15, 13, 20, 22, 25, 30,  9, 19, 24, 29, 18, 28, 27, // 1
};

constexpr static BR::UInt64 LIBBER_COUNT_TRAILING_ZEROS_MAGIC_64 = 0x0218A392CD3D5DBFULL;

constexpr static BR::UInt8 LIBBER_COUNT_TRAILING_ZEROS_64[] = {
//	 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	 0,  1,  2,  7,  3, 13,  8, 19,  4, 25, 14, 28,  9, 34, 20, 40, // 0
	 5, 17, 26, 38, 15, 46, 29, 48, 10, 31, 35, 54, 21, 50, 41, 57, // 1
	63,  6, 12, 18, 24, 27, 33, 39, 16, 37, 45, 47, 30, 53, 49, 56, // 2
	62, 11, 23, 32, 36, 44, 52, 55, 61, 22, 43, 51, 60, 42, 59, 58, // 3
};

#ifdef BR_HAS_INT128
constexpr static BR::UInt128 LIBBER_COUNT_TRAILING_ZEROS_MAGIC_128 = (BR::UInt128(0x0106143891634793ULL) << 64) | BR::UInt128(0x2A5CD9D3EAD7B77FULL);

constexpr static BR::UInt8 LIBBER_COUNT_TRAILING_ZEROS_128[] = {
//	  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	  0,   1,   2,   8,   3,  15,   9,  22,   4,  29,  16,  36,  10,  43,  23,  50, // 0
	  5,  33,  30,  57,  17,  64,  37,  71,  11,  60,  44,  78,  24,  85,  51,  92, // 1
	  6,  20,  34,  48,  31,  69,  58,  90,  18,  67,  65,  99,  38, 101,  72, 106, // 2
	 12,  40,  61,  82,  45, 103,  79, 113,  25,  74,  86, 116,  52, 108,  93, 120, // 3
	127,   7,  14,  21,  28,  35,  42,  49,  32,  56,  63,  70,  59,  77,  84,  91, // 4
	 19,  47,  68,  89,  66,  98, 100, 105,  39,  81, 102, 112,  73, 115, 107, 119, // 5
	126,  13,  27,  41,  55,  62,  76,  83,  46,  88,  97, 104,  80, 111, 114, 118, // 6
	125,  26,  54,  75,  87,  96, 110, 117, 124,  53,  95, 109, 123,  94, 122, 121, // 7
};
#endif

/**
 * count trailing zeros
 * @param x
 * @return number of trailing zeros
 */
//@{
constexpr auto libbr_count_trailing_zeros_8(BR::UInt8 x) noexcept -> BR::UInt8 {
	return LIBBER_COUNT_TRAILING_ZEROS_8[BR::UInt8((x & (~x + 1)) * LIBBER_COUNT_TRAILING_ZEROS_MAGIC_8) >> (8 - 3)];
}

constexpr auto libbr_count_trailing_zeros_16(BR::UInt16 x) noexcept -> BR::UInt8 {
	return LIBBER_COUNT_TRAILING_ZEROS_16[BR::UInt16((x & (~x + 1)) * LIBBER_COUNT_TRAILING_ZEROS_MAGIC_16) >> (16 - 4)];
}

constexpr auto libbr_count_trailing_zeros_32(BR::UInt32 x) noexcept -> BR::UInt8 {
	return LIBBER_COUNT_TRAILING_ZEROS_32[BR::UInt32((x & (~x + 1)) * LIBBER_COUNT_TRAILING_ZEROS_MAGIC_32) >> (32 - 5)];
}

constexpr auto libbr_count_trailing_zeros_64(BR::UInt64 x) noexcept -> BR::UInt8 {
	return LIBBER_COUNT_TRAILING_ZEROS_64[BR::UInt64((x & (~x + 1)) * LIBBER_COUNT_TRAILING_ZEROS_MAGIC_64) >> (64 - 6)];
}

#ifdef BR_HAS_INT128
constexpr auto libbr_count_trailing_zeros_128(BR::UInt128 x) noexcept -> BR::UInt8 {
	return LIBBER_COUNT_TRAILING_ZEROS_128[BR::UInt128((x & (~x + 1)) * LIBBER_COUNT_TRAILING_ZEROS_MAGIC_128) >> (128 - 7)];
}
#endif
//@}
}

namespace BR {
inline namespace Math {
inline namespace Function {

constexpr auto count_trailing_zeros(UInt8 x) noexcept -> UInt8 {
	return libbr_count_trailing_zeros_8(x);
}

constexpr auto count_trailing_zeros(UInt16 x) noexcept -> UInt8 {
	return libbr_count_trailing_zeros_16(x);
}

constexpr auto count_trailing_zeros(UInt32 x) noexcept -> UInt8 {
	return libbr_count_trailing_zeros_32(x);
}

constexpr auto count_trailing_zeros(UInt64 x) noexcept -> UInt8 {
	return libbr_count_trailing_zeros_64(x);
}

#ifdef BR_HAS_INT128
constexpr auto count_trailing_zeros(UInt128 x) noexcept -> UInt8 {
	return libbr_count_trailing_zeros_128(x);
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR