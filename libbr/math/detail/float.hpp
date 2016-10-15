#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bitwise_cast.hpp>

namespace BR {
namespace Detail {
namespace Float {

template< typename TFrom, typename TTo >
union Converter {
	TFrom f;
	TTo t;
};

constexpr auto to_raw(Float32 f) -> SInt32 {
	return Converter< Float32, SInt32 >{f}.t;
}

constexpr auto to_raw(Float64 f) -> SInt64 {
	return Converter< Float64, SInt64 >{f}.t;
}

#if defined(BR_HAS_INT128)
constexpr auto to_raw(Float128 f) -> SInt128 {
	return Converter< Float128, SInt128 >{f}.t;
}
#else
#endif

constexpr auto to_float32(SInt32 f) -> Float32 {
	return Converter< SInt32, Float32 >{f}.t;
}

constexpr auto to_float64(SInt64 f) -> Float64 {
	return Converter< SInt64, Float64 >{f}.t;
}

constexpr auto get_high_part(Float64 f) -> SInt32 {
	return SInt32(to_raw(f) >> 32);
}

constexpr auto get_low_part(Float64 f) -> UInt32 {
	return to_raw(f) & 0xFFFFFFFFU;
}

constexpr auto to_float64(SInt32 h, UInt32 l) -> Float64 {
	return to_float64((SInt64(h) << 32) | l);
}

} // namespace Float
} // namespace Detail
} // namespace BR