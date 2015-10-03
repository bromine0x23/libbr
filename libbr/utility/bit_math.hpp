/**
 * @file
 * @brief 位运算实用函数
 * @author Bromine0x23
 * @since 2015/9/25
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

namespace Detail {
namespace BitMath {

constexpr auto half(UInt16 x) -> UInt8;

constexpr auto half(UInt32 x) -> UInt16;

constexpr auto half(UInt64 x) -> UInt32;

template< typename TInt >
constexpr auto half(TInt x) -> TInt;

constexpr auto bisect(UInt16 const & x) -> UInt8 const (&)[2] {
	return *reinterpret_cast< UInt8 const (*)[2] >(&x);
}

constexpr auto bisect(UInt32 const & x) -> UInt16 const (&)[2] {
	return *reinterpret_cast< UInt16 const (*)[2] >(&x);
}

constexpr auto bisect(UInt64 const & x) -> UInt32 const (&)[2] {
	return *reinterpret_cast< UInt32 const (*)[2] >(&x);
}

template< typename TUInt >
constexpr auto part0(TUInt x) -> decltype(bisect(x)[0]) {
	return bisect(x)[0];
}

template< typename TUInt >
constexpr auto part1(TUInt x) -> decltype(bisect(x)[1]) {
	return bisect(x)[1];
}

} // namespace BitMath
} // namespace Detail

constexpr bool is_power_of_2(UInt8  x) noexcept { return (x & (x - 1)) == 0; }

constexpr bool is_power_of_2(UInt16 x) noexcept { return (x & (x - 1)) == 0; }

constexpr bool is_power_of_2(UInt32 x) noexcept { return (x & (x - 1)) == 0; }

constexpr bool is_power_of_2(UInt64 x) noexcept { return (x & (x - 1)) == 0; }

namespace Detail {
namespace BitMath {

constexpr UInt8 COUNT_ONES[] = {
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

} // namespace BitMath
} // namespace Detail

/**
 * @brief 二进制表示中1的个数
 */
constexpr UInt8 count_ones(UInt8 x) noexcept {
	using namespace Detail::BitMath;
	return COUNT_ONES[x];
}

/**
 * @brief 二进制表示中1的个数
 */
template< typename TUInt >
constexpr UInt8 count_ones(TUInt x) noexcept {
	using namespace Detail::BitMath;
	return count_ones(part0(x)) + count_ones(part1(x));
}

namespace Detail {
namespace BitMath {

constexpr UInt8 PARITY[] = {
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

} // namespace BitMath
} // namespace Detail

/**
 * @brief 二进制表示中1个数的奇偶性
 * @return 0 -> 偶, 1 -> 奇
 */
constexpr UInt8 bits_parity(UInt8 x) noexcept {
	using namespace Detail::BitMath;
	return PARITY[x];
}

/**
 * @brief 二进制表示中1个数的奇偶性
 * @return 0 -> 偶, 1 -> 奇
 */
template< typename TUInt >
constexpr UInt8 bits_parity(TUInt x) noexcept {
	using namespace Detail::BitMath;
	return bits_parity(static_cast< decltype(half(x)) >(part0(x) ^ part1(x)));
}

namespace Detail {
namespace BitMath {

constexpr UInt8 COUNT_LEADING_ZEROS[] = {
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

} // namespace BitMath
} // namespace Detail

/**
 * @brief 前导0长度
 */
constexpr UInt8 count_leading_zeros(UInt8 x) noexcept {
	using namespace Detail::BitMath;
	return COUNT_LEADING_ZEROS[x];
}

/**
 * @brief 前导0长度
 */
constexpr UInt16 count_leading_zeros(UInt16 x) noexcept {
	return x > 0xFFU ? count_leading_zeros(UInt8(x >> 8)) : count_leading_zeros(UInt8(x)) + UInt16(8);
}

/**
 * @brief 前导0长度
 */
constexpr UInt32 count_leading_zeros(UInt32 x) noexcept {
	return x > 0xFFFFU ? count_leading_zeros(UInt16(x >> 16)) : count_leading_zeros(UInt16(x)) + UInt32(16);
}

/**
 * @brief 前导0长度
 */
constexpr UInt64 count_leading_zeros(UInt64 x) noexcept {
	return x > 0xFFFFFFFFU ? count_leading_zeros(UInt32(x >> 32)) : count_leading_zeros(UInt32(x)) + UInt64(32);
}

namespace Detail {
namespace BitMath {

constexpr UInt8 COUNT_TRAILING_ZEROS_8B[] = {
	0, 1, 2, 4, 7, 3, 6, 5
};

constexpr UInt8 COUNT_TRAILING_ZEROS_16B[] = {
//	 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	0,  1,  2,  5,  3,  9,  6, 11, 15,  4,  8, 10, 14,  7, 13, 12
};

constexpr UInt8 COUNT_TRAILING_ZEROS_32B[] = {
//	 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	 0,  1,  2,  6,  3, 11,  7, 16,  4, 14, 12, 21,  8, 23, 17, 26, // 0
	31,  5, 10, 15, 13, 20, 22, 25, 30,  9, 19, 24, 29, 18, 28, 27, // 1
};

constexpr UInt8 COUNT_TRAILING_ZEROS_64B[] = {
//	 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
	 0,  1,  2,  7,  3, 13,  8, 19,  4, 25, 14, 28,  9, 34, 20, 40, // 0
	 5, 17, 26, 38, 15, 46, 29, 48, 10, 31, 35, 54, 21, 50, 41, 57, // 1
	63,  6, 12, 18, 24, 27, 33, 39, 16, 37, 45, 47, 30, 53, 49, 56, // 2
	62, 11, 23, 32, 36, 44, 52, 55, 61, 22, 43, 51, 60, 42, 59, 58, // 3
};

constexpr UInt8 COUNT_TRAILING_ZEROS_MAGIC_8B = 0x17;

constexpr UInt16 COUNT_TRAILING_ZEROS_MAGIC_16B = 0x09AF;

constexpr UInt32 COUNT_TRAILING_ZEROS_MAGIC_32B = 0x077CB531;

constexpr UInt64 COUNT_TRAILING_ZEROS_MAGIC_64B = 0x0218A392CD3D5DBFULL;

} // namespace BitMath
} // namespace Detail

/**
 * @brief 尾随0长度
 */
constexpr Size count_trailing_zeros(UInt8 x) noexcept {
	using namespace Detail::BitMath;
	return COUNT_TRAILING_ZEROS_8B [((x & (~x + 1)) * COUNT_TRAILING_ZEROS_MAGIC_8B ) >> ( 8 - 3)];
}

/**
 * @brief 尾随0长度
 */
constexpr Size count_trailing_zeros(UInt16 x) noexcept {
	using namespace Detail::BitMath;
	return COUNT_TRAILING_ZEROS_16B[((x & (~x + 1)) * COUNT_TRAILING_ZEROS_MAGIC_16B) >> (16 - 4)];
}

/**
 * @brief 尾随0长度
 */
constexpr Size count_trailing_zeros(UInt32 x) noexcept {
	using namespace Detail::BitMath;
	return COUNT_TRAILING_ZEROS_32B[((x & (~x + 1)) * COUNT_TRAILING_ZEROS_MAGIC_32B) >> (32 - 5)];
}

/**
 * @brief 尾随0长度
 */
constexpr Size count_trailing_zeros(UInt64 x) noexcept {
	using namespace Detail::BitMath;
	return COUNT_TRAILING_ZEROS_64B[((x & (~x + 1)) * COUNT_TRAILING_ZEROS_MAGIC_64B) >> (64 - 6)];
}

namespace Detail {
namespace BitMath {

constexpr UInt8 REVERSE_BITS[] = {
//	   0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, // 0
	0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, // 1
	0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, // 2
	0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, // 3
	0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, // 4
	0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA, // 5
	0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, // 6
	0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, // 7
	0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1, // 8
	0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, // 9
	0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, // A
	0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD, // B
	0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, // C
	0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, // D
	0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, // E
	0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF, // F
};

} // namespace BitMath
} // namespace Detail

/**
 * @brief 按位倒置
 */
constexpr UInt8 reverse_bits(UInt8 x) noexcept {
	using namespace Detail::BitMath;
	return REVERSE_BITS[x];
}

/**
 * @brief 按位倒置
 */
constexpr UInt16 reverse_bits(UInt16 x) noexcept {
	return UInt16(reverse_bits(UInt8(x))) << 8 | UInt16(reverse_bits(UInt8(x >> 8)));
}

/**
 * @brief 按位倒置
 */
constexpr UInt32 reverse_bits(UInt32 x) noexcept {
	return UInt32(reverse_bits(UInt16(x))) << 16 | UInt32(reverse_bits(UInt16(x >> 16)));
}

/**
 * @brief 按位倒置
 */
constexpr UInt64 reverse_bits(UInt64 x) noexcept {
	return UInt64(reverse_bits(UInt32(x))) << 32 | UInt64(reverse_bits(UInt32(x >> 32)));
}

namespace Detail {
namespace BitMath {

constexpr SInt8 INTEGRAL_LOG2[] = {
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

} // namespace BitMath
} // namespace Detail

/**
 * @brief 二进制对数
 */
constexpr SInt8 integral_log2(UInt8 x) noexcept {
	using namespace Detail::BitMath;
	return INTEGRAL_LOG2[x];
}

/**
 * @brief 二进制对数
 */
constexpr SInt16 integral_log2(UInt16 x) noexcept {
	return (x >> 8) != 0 ? integral_log2(UInt8(x >> 8)) + SInt16(8) : integral_log2(UInt8(x));
}

/**
 * @brief 二进制对数
 */
constexpr SInt32 integral_log2(UInt32 x) noexcept {
	return (x >> 16) != 0 ? integral_log2(UInt16(x >> 16)) + SInt32(16) : integral_log2(UInt16(x));
}

/**
 * @brief 二进制对数
 */
constexpr SInt64 integral_log2(UInt64 x) noexcept {
	return (x >> 32) != 0 ? integral_log2(UInt32(x >> 32)) + SInt64(32) : integral_log2(UInt32(x));
}

namespace Detail {
namespace BitMath {

constexpr UInt16 INTERLEAVE[] = {
//	     0       1       2       3       4       5       6       7       8       9       A       B       C       D       E       F
	0x0000, 0x0001, 0x0004, 0x0005, 0x0010, 0x0011, 0x0014, 0x0015, 0x0040, 0x0041, 0x0044, 0x0045, 0x0050, 0x0051, 0x0054, 0x0055, // 0
	0x0100, 0x0101, 0x0104, 0x0105, 0x0110, 0x0111, 0x0114, 0x0115, 0x0140, 0x0141, 0x0144, 0x0145, 0x0150, 0x0151, 0x0154, 0x0155, // 1
	0x0400, 0x0401, 0x0404, 0x0405, 0x0410, 0x0411, 0x0414, 0x0415, 0x0440, 0x0441, 0x0444, 0x0445, 0x0450, 0x0451, 0x0454, 0x0455, // 2
	0x0500, 0x0501, 0x0504, 0x0505, 0x0510, 0x0511, 0x0514, 0x0515, 0x0540, 0x0541, 0x0544, 0x0545, 0x0550, 0x0551, 0x0554, 0x0555, // 3
	0x1000, 0x1001, 0x1004, 0x1005, 0x1010, 0x1011, 0x1014, 0x1015, 0x1040, 0x1041, 0x1044, 0x1045, 0x1050, 0x1051, 0x1054, 0x1055, // 4
	0x1100, 0x1101, 0x1104, 0x1105, 0x1110, 0x1111, 0x1114, 0x1115, 0x1140, 0x1141, 0x1144, 0x1145, 0x1150, 0x1151, 0x1154, 0x1155, // 5
	0x1400, 0x1401, 0x1404, 0x1405, 0x1410, 0x1411, 0x1414, 0x1415, 0x1440, 0x1441, 0x1444, 0x1445, 0x1450, 0x1451, 0x1454, 0x1455, // 6
	0x1500, 0x1501, 0x1504, 0x1505, 0x1510, 0x1511, 0x1514, 0x1515, 0x1540, 0x1541, 0x1544, 0x1545, 0x1550, 0x1551, 0x1554, 0x1555, // 7
	0x4000, 0x4001, 0x4004, 0x4005, 0x4010, 0x4011, 0x4014, 0x4015, 0x4040, 0x4041, 0x4044, 0x4045, 0x4050, 0x4051, 0x4054, 0x4055, // 8
	0x4100, 0x4101, 0x4104, 0x4105, 0x4110, 0x4111, 0x4114, 0x4115, 0x4140, 0x4141, 0x4144, 0x4145, 0x4150, 0x4151, 0x4154, 0x4155, // 9
	0x4400, 0x4401, 0x4404, 0x4405, 0x4410, 0x4411, 0x4414, 0x4415, 0x4440, 0x4441, 0x4444, 0x4445, 0x4450, 0x4451, 0x4454, 0x4455, // A
	0x4500, 0x4501, 0x4504, 0x4505, 0x4510, 0x4511, 0x4514, 0x4515, 0x4540, 0x4541, 0x4544, 0x4545, 0x4550, 0x4551, 0x4554, 0x4555, // B
	0x5000, 0x5001, 0x5004, 0x5005, 0x5010, 0x5011, 0x5014, 0x5015, 0x5040, 0x5041, 0x5044, 0x5045, 0x5050, 0x5051, 0x5054, 0x5055, // C
	0x5100, 0x5101, 0x5104, 0x5105, 0x5110, 0x5111, 0x5114, 0x5115, 0x5140, 0x5141, 0x5144, 0x5145, 0x5150, 0x5151, 0x5154, 0x5155, // D
	0x5400, 0x5401, 0x5404, 0x5405, 0x5410, 0x5411, 0x5414, 0x5415, 0x5440, 0x5441, 0x5444, 0x5445, 0x5450, 0x5451, 0x5454, 0x5455, // E
	0x5500, 0x5501, 0x5504, 0x5505, 0x5510, 0x5511, 0x5514, 0x5515, 0x5540, 0x5541, 0x5544, 0x5545, 0x5550, 0x5551, 0x5554, 0x5555, // F
};

} // namespace BitMath
} // namespace Detail

/**
 * @brief 按位交错
 *
 * x的0位为结果的0位，y的0位为结果的1位
 */
constexpr UInt16 interleave(UInt8 x, UInt8 y) noexcept {
	using namespace Detail::BitMath;
	return UInt16(INTERLEAVE[y]) << 1 | UInt16(INTERLEAVE[x]);
}

/**
 * @brief 按位交错
 *
 * x的0位为结果的0位，y的0位为结果的1位
 */
constexpr UInt32 interleave(UInt16 x, UInt16 y) noexcept {
	return UInt32(interleave(UInt8(x >> 8), UInt8(y >> 8))) | UInt32(interleave(UInt8(x), UInt8(y)));
}

/**
 * @brief 按位交错
 *
 * x的0位为结果的0位，y的0位为结果的1位
 */
constexpr UInt64 interleave(UInt32 x, UInt32 y) noexcept {
	return UInt64(interleave(UInt16(x >> 16), UInt16(y >> 16))) | UInt64(interleave(UInt16(x), UInt16(y)));
}

} // namespace BR
