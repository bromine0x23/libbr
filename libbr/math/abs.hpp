/**
 * @file
 * @brief abs
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#if !defined(BR_GCC)
#  include <libbr/math/detail/float.hpp>
#endif

extern "C" {

#if defined(BR_GCC)

constexpr auto libbr_abs_32(BR::Float32 x) -> BR::Float32 {
	return __builtin_fabsf(x);
}

constexpr auto libbr_abs_64(BR::Float64 x) -> BR::Float64 {
	return __builtin_fabs(x);
}
#else
constexpr auto libbr_abs_32(BR::Float32 f) -> BR::Float32 {
	return BR::Detail::Float::ToFloat32{ BR::Detail::Float::to_raw(f) & 0x7FFFFFFFU }.f;
}

constexpr auto libbr_abs_64(BR::Float64 f) -> BR::Float64 {
	return BR::Detail::Float::combine_float64(BR::Detail::Float::to_raw_high(f) & 0x7FFFFFFFU, BR::Detail::Float::to_raw_low(f));
}
#endif

}

namespace BR {

constexpr inline auto abs(Float32 x) -> Float32 {
	return libbr_abs_32(x);
}

constexpr inline auto abs(Float64 x) -> Float64 {
	return libbr_abs_64(x);
}

#if defined(BR_GCC)
template< typename T >
constexpr auto abs(T x) -> EnableIf< IsIntegral<T>, T > {
	return __builtin_fabs(x);
}
#else
template< typename T >
constexpr auto abs(T x) -> EnableIf< IsIntegral<T>, T > {
	return x < 0 ? -x : x;
}
#endif


} // namespace BR