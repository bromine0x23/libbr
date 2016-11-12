#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Detail {
namespace Float {

union Bind32 {
	Float32 f;
	UInt32 r;
#if defined(BR_LITTLE_ENDIAN)
	struct {
		UInt mantissa:23;
		UInt exponent:8;
		UInt negative:1;
	};
#endif
#if defined(BR_BIG_ENDIAN)
	struct {
		UInt negative:1;
		UInt exponent:8;
		UInt mantissa:23;
	};
#endif
	constexpr Bind32(Float32 f) : f(f) {}
	constexpr Bind32(UInt32 r) : r(r) {}
};

union Bind64 {
	Float64 f;
	UInt64 r;
	struct {
#if defined(BR_LITTLE_ENDIAN)
		UInt32 l;
		UInt32 h;
#endif
#if defined(BR_BIG_ENDIAN)
		UInt32 h
		UInt32 l;
#endif
	};
#if defined(BR_LITTLE_ENDIAN)
	struct {
		UInt mantissa1:32;
		UInt mantissa0:20;
		UInt exponent:11;
		UInt negative:1;
	};
#endif
#if defined(BR_BIG_ENDIAN)
	struct {
		UInt negative:1;
		UInt exponent:11;
		UInt mantissa0:20;
		UInt mantissa1:32;
	};
#endif
};

template< typename TFrom, typename TTo >
union Converter {
	TFrom f;
	TTo t;
};

inline auto to_raw(Float32 f) -> UInt32 {
	return Bind32{f}.r;
}

inline auto to_raw(Float64 f) -> UInt64 {
	return Bind64{f}.r;
}

inline auto to_raw_high(Float64 f) -> UInt32 {
	return Bind64{f}.h;
}

inline auto to_raw_low(Float64 f) -> UInt32 {
	return Bind64{f}.l;
}

inline auto to_float(UInt32 r) -> Float32 {
	return Converter< UInt32, Float32 >{r}.t;
}

inline auto to_float(UInt64 r) -> Float64 {
	return Converter< UInt64, Float64 >{r}.t;
}

struct Raw64 {
#if defined(BR_LITTLE_ENDIAN)
	UInt32 l, h;
#else
	UInt32 h, l;
#endif
};

inline auto to_float(UInt32 h, UInt32 l) -> Float64 {
	return Converter< Raw64, Float64 >{
#if defined(BR_LITTLE_ENDIAN)
		{ l, h }
#else
		{ h, l }
#endif
	}.t;
}

} // namespace Float
} // namespace Detail
} // namespace BR