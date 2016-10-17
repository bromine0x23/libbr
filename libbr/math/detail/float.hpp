#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Detail {
namespace Float {

union Bind32 {
	Float32 f;
	UInt32 r;
};

union Bind64 {
	Float64 f;
	UInt64 r;
	struct {
#if defined(BR_LITTLE_ENDIAN)
		UInt32 l;
		UInt32 h;
#else
		UInt32 h
		UInt32 l;
#endif
	};
};

template< typename TFrom, typename TTo >
union Converter {
	TFrom f;
	TTo t;
};

constexpr auto to_raw(Float32 f) -> UInt32 {
	return Bind32{f}.r;
}

constexpr auto to_raw(Float64 f) -> UInt64 {
	return Bind64{f}.r;
}

constexpr auto to_raw_high(Float64 f) -> UInt32 {
	return Bind64{f}.h;
}

constexpr auto to_raw_low(Float64 f) -> UInt32 {
	return Bind64{f}.l;
}

constexpr auto to_float(UInt32 r) -> Float32 {
	return Converter< UInt32, Float32 >{r}.t;
}

constexpr auto to_float(UInt64 r) -> Float64 {
	return Converter< UInt64, Float64 >{r}.t;
}

struct Raw64 {
#if defined(BR_LITTLE_ENDIAN)
	UInt32 l, h;
#else
	UInt32 h, l;
#endif
};

constexpr auto to_float(UInt32 h, UInt32 l) -> Float64 {
	return Converter< Raw64, Float64 >{
#if defined(BR_LITTLE_ENDIAN)
		l, h
#else
		h, l
#endif
		}.t;
}

} // namespace Float
} // namespace Detail
} // namespace BR