#pragma once

#include <libbr/config.hpp>

// #include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/is_signed.hpp>
#include <libbr/type_operate/is_unsigned.hpp>

namespace BR {

typedef Size BitIndex;

typedef bool Bit;

template< typename bits_type >
constexpr inline Bit get_bit(bits_type bits, BitIndex index) {
    return bits & (1 << index);
}

template< typename bits_type >
constexpr inline bits_type turn_bit(bits_type bits, BitIndex index) {
    return bits ^ (1 << index);
}

template< typename bits_type >
constexpr inline bits_type set_bit_on(bits_type bits, BitIndex index) {
    return bits | (1 << index);
}

template< typename bits_type >
constexpr inline bits_type set_bit_off(bits_type bits, BitIndex index) {
    return bits & ~(1 << index);
}

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

namespace {

union UInt8_8 {
	UInt64 u64;
	struct {
		UInt8 u8[sizeof(UInt64) / sizeof(UInt8)];
	};
};

inline UInt64 reverse_bits(UInt8_8 const & x) {
	return
		  (static_cast<UInt64>(REVERSE_BITS[x.u8[0]]) << 56)
		| (static_cast<UInt64>(REVERSE_BITS[x.u8[1]]) << 48)
		| (static_cast<UInt64>(REVERSE_BITS[x.u8[2]]) << 40)
		| (static_cast<UInt64>(REVERSE_BITS[x.u8[3]]) << 32)
		| (static_cast<UInt64>(REVERSE_BITS[x.u8[4]]) << 24)
		| (static_cast<UInt64>(REVERSE_BITS[x.u8[5]]) << 16)
		| (static_cast<UInt64>(REVERSE_BITS[x.u8[6]]) <<  8)
		| (static_cast<UInt64>(REVERSE_BITS[x.u8[7]])      );
}

template< Size byte_length >
struct Reinterpreter {
	typedef UInt8(Type)[byte_length];

	template< typename type >
	static inline Type const & pack(type const & x) {
		return *reinterpret_cast<Type const *>(&x);
	}

	template< typename type >
	static inline Type & pack(type & x) {
		return *reinterpret_cast<Type *>(&x);
	}

	template< typename type >
	static inline type & unpack(Type & x) {
		return *reinterpret_cast<type *>(&x);
	}
};

} // namespace [anonymous]

constexpr bool is_power_of_2(UInt8 x) {
	return (x & (x - 1)) == 0;
}

constexpr bool is_power_of_2(UInt16 x) {
	return (x & (x - 1)) == 0;
}

constexpr bool is_power_of_2(UInt32 x) {
	return (x & (x - 1)) == 0;
}

constexpr bool is_power_of_2(UInt64 x) {
	return (x & (x - 1)) == 0;
}

inline Size count_ones(UInt8 x) {
	return COUNT_ONES[x];
}

inline Size count_ones(UInt16 x) {
	typedef Reinterpreter<sizeof(UInt16)> Reinterpreter;
	Reinterpreter::Type const & p = Reinterpreter::pack(x);
	return COUNT_ONES[p[0]] + COUNT_ONES[p[1]];
}

inline Size count_ones(UInt32 x) {
	typedef Reinterpreter<sizeof(UInt32)> Reinterpreter;
	Reinterpreter::Type const & p = Reinterpreter::pack(x);
	return COUNT_ONES[p[0]] + COUNT_ONES[p[1]] + COUNT_ONES[p[2]] + COUNT_ONES[p[3]];
}

inline Size count_ones(UInt64 x) {
	typedef Reinterpreter<sizeof(UInt64)> Reinterpreter;
	Reinterpreter::Type const & p = Reinterpreter::pack(x);
	return
		  COUNT_ONES[p[0]] + COUNT_ONES[p[1]] + COUNT_ONES[p[2]] + COUNT_ONES[p[3]]
		+ COUNT_ONES[p[4]] + COUNT_ONES[p[5]] + COUNT_ONES[p[6]] + COUNT_ONES[p[7]];
}

inline UInt8 bits_parity(UInt8 x) {
	return PARITY[x];
}

inline UInt8 bits_parity(UInt16 x) {
	typedef Reinterpreter<sizeof(UInt16)> Reinterpreter;
	Reinterpreter::Type const & p = Reinterpreter::pack(x);
	return PARITY[p[0] ^ p[1]];
}

inline UInt8 bits_parity(UInt32 x) {
	typedef Reinterpreter<sizeof(UInt32)> Reinterpreter;
	Reinterpreter::Type const & p = Reinterpreter::pack(x);
	return PARITY[p[0] ^ p[1] ^ p[2] ^ p[3]];
}

inline UInt8 bits_parity(UInt64 x) {
	typedef Reinterpreter<sizeof(UInt64)> Reinterpreter;
	Reinterpreter::Type const & p = Reinterpreter::pack(x);
	return PARITY[p[0] ^ p[1] ^ p[2] ^ p[3] ^ p[4] ^ p[5] ^ p[6] ^ p[7]];
}

inline Size count_leading_zeros(UInt8 x) {
	return COUNT_LEADING_ZEROS[x];
}

inline Size count_leading_zeros(UInt16 x) {
	return x > 0x00FF ? COUNT_LEADING_ZEROS[x >> 8] : COUNT_LEADING_ZEROS[x] + 8;
}

inline Size count_leading_zeros(UInt32 x) {
	return
		x > 0x00FFFFFF ? COUNT_LEADING_ZEROS[x >> 24] +  0:
		x > 0x0000FFFF ? COUNT_LEADING_ZEROS[x >> 16] +  8:
		x > 0x000000FF ? COUNT_LEADING_ZEROS[x >>  8] + 16:
		                 COUNT_LEADING_ZEROS[x >>  0] + 24;
}

inline Size count_leading_zeros(UInt64 x) {
	return
		x > 0x00FFFFFFFFFFFFFFULL ? COUNT_LEADING_ZEROS[x >> 56] +  0:
		x > 0x0000FFFFFFFFFFFFULL ? COUNT_LEADING_ZEROS[x >> 48] +  8:
		x > 0x000000FFFFFFFFFFULL ? COUNT_LEADING_ZEROS[x >> 40] + 16:
		x > 0x00000000FFFFFFFFULL ? COUNT_LEADING_ZEROS[x >> 32] + 24:
		x > 0x0000000000FFFFFFULL ? COUNT_LEADING_ZEROS[x >> 24] + 32:
		x > 0x000000000000FFFFULL ? COUNT_LEADING_ZEROS[x >> 16] + 40:
		x > 0x00000000000000FFULL ? COUNT_LEADING_ZEROS[x >>  8] + 48:
		                            COUNT_LEADING_ZEROS[x >>  0] + 56;
}

inline Size count_trailing_zeros(UInt8 x) {
	return COUNT_TRAILING_ZEROS_8B [((x & -x) * COUNT_TRAILING_ZEROS_MAGIC_8B ) >> ( 8 - 3)];
}

inline Size count_trailing_zeros(UInt16 x) {
	return COUNT_TRAILING_ZEROS_16B[((x & -x) * COUNT_TRAILING_ZEROS_MAGIC_16B) >> (16 - 4)];
}

inline Size count_trailing_zeros(UInt32 x) {
	return COUNT_TRAILING_ZEROS_32B[((x & -x) * COUNT_TRAILING_ZEROS_MAGIC_32B) >> (32 - 5)];
}

inline Size count_trailing_zeros(UInt64 x) {
	return COUNT_TRAILING_ZEROS_64B[((x & -x) * COUNT_TRAILING_ZEROS_MAGIC_64B) >> (64 - 6)];
}

inline UInt8 reverse_bits(UInt8 x) {
	return REVERSE_BITS[x];
}

inline UInt16 reverse_bits(UInt16 x) {
	return
		  (static_cast< UInt16 >(REVERSE_BITS[(x     ) & 0xFF]) << 8)
		| (static_cast< UInt16 >(REVERSE_BITS[(x >> 8)       ])     );
}

inline UInt32 reverse_bits(UInt32 x) {
	return
		  (static_cast< UInt32 >(REVERSE_BITS[(x      ) & 0xFF]) << 24)
		| (static_cast< UInt32 >(REVERSE_BITS[(x >>  8) & 0xFF]) << 16)
		| (static_cast< UInt32 >(REVERSE_BITS[(x >> 16) & 0xFF]) <<  8)
		| (static_cast< UInt32 >(REVERSE_BITS[(x >> 24)       ])      );
}

inline UInt64 reverse_bits(UInt64 x) {
	return reverse_bits(*reinterpret_cast<UInt8_8 *>(&x));
}

inline SInt8 integral_log2(UInt8 x) {
	return INTEGRAL_LOG2[x];
}

inline SInt16 integral_log2(UInt16 x) {
	return x >> 8 ? integral_log2(static_cast<UInt8>(x >> 8)) + SInt16(8) : integral_log2(static_cast<UInt8>(x));
}

inline SInt32 integral_log2(UInt32 x) {
	return x >> 16 ? integral_log2(static_cast<UInt16>(x >> 16)) + SInt32(16) : integral_log2(static_cast<UInt16>(x));
}

inline SInt64 integral_log2(UInt64 x) {
	return x >> 32 ? integral_log2(static_cast<UInt32>(x >> 32)) + SInt64(32) : integral_log2(static_cast<UInt32>(x));
}

inline UInt16 interleave(UInt8 x, UInt8 y) {
	return static_cast< UInt16 >(INTERLEAVE[y]) << 1 | static_cast< UInt16 >(INTERLEAVE[x]);
}

inline UInt32 interleave(UInt16 x, UInt16 y) {
	return
		  static_cast< UInt32 >(INTERLEAVE[(y >> 8)       ]) << 17
		| static_cast< UInt32 >(INTERLEAVE[(x >> 8)       ]) << 16
		| static_cast< UInt32 >(INTERLEAVE[(y     ) & 0xFF]) <<  1
		| static_cast< UInt32 >(INTERLEAVE[(x     ) & 0xFF]);
}

inline UInt64 interleave(UInt32 x, UInt32 y) {
	return
		  static_cast< UInt64 >(INTERLEAVE[(y >> 24)       ]) << 49
		| static_cast< UInt64 >(INTERLEAVE[(x >> 24)       ]) << 48
		| static_cast< UInt64 >(INTERLEAVE[(y >> 16) & 0xFF]) << 33
		| static_cast< UInt64 >(INTERLEAVE[(x >> 16) & 0xFF]) << 32
		| static_cast< UInt64 >(INTERLEAVE[(y >>  8) & 0xFF]) << 17
		| static_cast< UInt64 >(INTERLEAVE[(x >>  8) & 0xFF]) << 16
		| static_cast< UInt64 >(INTERLEAVE[(y      ) & 0xFF]) <<  1
		| static_cast< UInt64 >(INTERLEAVE[(x      ) & 0xFF]);
}

} // namespace BR
