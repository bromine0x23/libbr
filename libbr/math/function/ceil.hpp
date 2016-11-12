/**
 * @file
 * @brief ceil
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * like std::ceil
 * @param x
 * @return
 */
//@{
auto libbr_ceil_32(BR::Float32 x) -> BR::Float32;

auto libbr_ceil_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto ceil(Float32 x) -> Float32 {
	return libbr_ceil_32(x);
}

inline auto ceil(Float64 x) -> Float64 {
	return libbr_ceil_64(x);
}

#if defined(BR_GCC)
template< typename T >
constexpr auto ceil(T x) -> EnableIf< IsIntegral<T>, T > {
	return __builtin_ceil(x);
}
#else
template< typename T >
constexpr auto ceil(T x) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}
#endif

} // inline namespace Function
} // inline namespace Math
} // namespace BR