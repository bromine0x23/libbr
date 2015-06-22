#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_signed.hpp>
#include <libbr/type_operate/is_unsigned.hpp>

namespace BR {

extern UInt8 const COUNT_ONES[];
extern UInt8 const PARITY[];
extern UInt8 const COUNT_LEADING_ZEROS[];
extern UInt8 const COUNT_TRAILING_ZEROS_8B[];
extern UInt8 const COUNT_TRAILING_ZEROS_16B[];
extern UInt8 const COUNT_TRAILING_ZEROS_32B[];
extern UInt8 const COUNT_TRAILING_ZEROS_64B[];
extern UInt8 const COUNT_TRAILING_ZEROS_MAGIC_8B;
extern UInt16 const COUNT_TRAILING_ZEROS_MAGIC_16B;
extern UInt32 const COUNT_TRAILING_ZEROS_MAGIC_32B;
extern UInt64 const COUNT_TRAILING_ZEROS_MAGIC_64B;
extern UInt8 const REVERSE_BITS[];
extern SInt8 const INTEGRAL_LOG2[];
extern UInt16 const INTERLEAVE[];

constexpr bool is_power_of_2(UInt8  x) noexcept { return (x & (x - 1)) == 0; }
constexpr bool is_power_of_2(UInt16 x) noexcept { return (x & (x - 1)) == 0; }
constexpr bool is_power_of_2(UInt32 x) noexcept { return (x & (x - 1)) == 0; }
constexpr bool is_power_of_2(UInt64 x) noexcept { return (x & (x - 1)) == 0; }

inline UInt8 count_ones(UInt8 x) noexcept {
	return COUNT_ONES[x];
}

inline UInt8 count_ones(UInt16 x) noexcept {
	using Pack = UInt8 [2];
	Pack const & p = *reinterpret_cast< Pack const * >(&x);
	return count_ones(p[0]) + count_ones(p[1]);
}

inline UInt8 count_ones(UInt32 x) noexcept {
	using Pack = UInt16 [2];
	Pack const & p = *reinterpret_cast< Pack const * >(&x);
	return count_ones(p[0]) + count_ones(p[1]);
};

inline UInt8 count_ones(UInt64 x) noexcept {
	using Pack = UInt32 [2];
	Pack const & p = *reinterpret_cast< Pack const * >(&x);
	return count_ones(p[0]) + count_ones(p[1]);
}

inline UInt8 bits_parity(UInt8 x) noexcept {
	return PARITY[x];
}

inline UInt8 bits_parity(UInt16 x) noexcept {
	using Pack = UInt8 [2];
	Pack const & p = *reinterpret_cast< Pack const * >(&x);
	return bits_parity(UInt8(p[0] ^ p[1]));
}

inline UInt8 bits_parity(UInt32 x) noexcept {
	using Pack = UInt16 [2];
	Pack const & p = *reinterpret_cast< Pack const * >(&x);
	return bits_parity(UInt8(p[0] ^ p[1]));
}

inline UInt8 bits_parity(UInt64 x) noexcept {
	using Pack = UInt32 [2];
	Pack const & p = *reinterpret_cast< Pack const * >(&x);
	return bits_parity(UInt8(p[0] ^ p[1]));
}

inline UInt8 count_leading_zeros(UInt8 x) noexcept {
	return COUNT_LEADING_ZEROS[x];
}

inline UInt16 count_leading_zeros(UInt16 x) noexcept {
	return x > 0xFFU ? count_leading_zeros(UInt8(x >> 8)) : count_leading_zeros(UInt8(x)) + UInt16(8);
}

inline UInt32 count_leading_zeros(UInt32 x) noexcept {
	return x > 0xFFFFU ? count_leading_zeros(UInt16(x >> 16)) : count_leading_zeros(UInt16(x)) + UInt32(16);
}

inline UInt64 count_leading_zeros(UInt64 x) noexcept {
	return x > 0xFFFFFFFFU ? count_leading_zeros(UInt32(x >> 32)) : count_leading_zeros(UInt32(x)) + UInt64(32);
}

inline Size count_trailing_zeros(UInt8 x) noexcept {
	return COUNT_TRAILING_ZEROS_8B [((x & -x) * COUNT_TRAILING_ZEROS_MAGIC_8B ) >> ( 8 - 3)];
}

inline Size count_trailing_zeros(UInt16 x) noexcept {
	return COUNT_TRAILING_ZEROS_16B[((x & -x) * COUNT_TRAILING_ZEROS_MAGIC_16B) >> (16 - 4)];
}

inline Size count_trailing_zeros(UInt32 x) noexcept {
	return COUNT_TRAILING_ZEROS_32B[((x & -x) * COUNT_TRAILING_ZEROS_MAGIC_32B) >> (32 - 5)];
}

inline Size count_trailing_zeros(UInt64 x) noexcept {
	return COUNT_TRAILING_ZEROS_64B[((x & -x) * COUNT_TRAILING_ZEROS_MAGIC_64B) >> (64 - 6)];
}

inline UInt8 reverse_bits(UInt8 x) noexcept {
	return REVERSE_BITS[x];
}

inline UInt16 reverse_bits(UInt16 x) noexcept {
	return UInt16(reverse_bits(UInt8(x))) << 8 | UInt16(reverse_bits(UInt8(x >> 8)));
}

inline UInt32 reverse_bits(UInt32 x) noexcept {
	return UInt32(reverse_bits(UInt16(x))) << 16 | UInt32(reverse_bits(UInt16(x >> 16)));
}

inline UInt64 reverse_bits(UInt64 x) noexcept {
	return UInt64(reverse_bits(UInt32(x))) << 32 | UInt64(reverse_bits(UInt32(x >> 32)));
}

inline SInt8 integral_log2(UInt8 x) noexcept {
	return INTEGRAL_LOG2[x];
}

inline SInt16 integral_log2(UInt16 x) noexcept {
	return (x >> 8) != 0 ? integral_log2(UInt8(x >> 8)) + SInt16(8) : integral_log2(UInt8(x));
}

inline SInt32 integral_log2(UInt32 x) noexcept {
	return (x >> 16) != 0 ? integral_log2(UInt16(x >> 16)) + SInt32(16) : integral_log2(UInt16(x));
}

inline SInt64 integral_log2(UInt64 x) noexcept {
	return (x >> 32) != 0 ? integral_log2(UInt32(x >> 32)) + SInt64(32) : integral_log2(UInt32(x));
}

inline UInt16 interleave(UInt8 x, UInt8 y) noexcept {
	return UInt16(INTERLEAVE[y]) << 1 | UInt16(INTERLEAVE[x]);
}

inline UInt32 interleave(UInt16 x, UInt16 y) noexcept {
	return UInt32(interleave(UInt8(x >> 8), UInt8(y >> 8))) | UInt32(interleave(UInt8(x), UInt8(y)));
}

inline UInt64 interleave(UInt32 x, UInt32 y) noexcept {
	return UInt64(interleave(UInt16(x >> 16), UInt16(y >> 16))) | UInt64(interleave(UInt16(x), UInt16(y)));
}

} // namespace BR
