/**
 * @file
 * @brief round
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

#if defined(BR_GCC)
constexpr auto libbr_round_32(BR::Float32 x) -> BR::Float32 {
	return __builtin_roundf(x);
}
#else
auto libbr_round_32(BR::Float32 x) -> BR::Float32;
#endif

auto libbr_round_64(BR::Float64 x) -> BR::Float64;

}

namespace BR {

inline auto round(Float32 x) -> Float32 {
	return libbr_round_32(x);
}

inline auto round(Float64 x) -> Float64 {
	return libbr_round_64(x);
}

#if defined(BR_GCC)
template< typename T >
constexpr auto round(T x) -> EnableIf< IsIntegral<T>, T > {
	return __builtin_trunc(x);
}
#else
template< typename T >
constexpr auto round(T x) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}
#endif

} // namespace BR