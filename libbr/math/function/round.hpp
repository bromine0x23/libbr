/**
 * @file
 * @brief round
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * like std::round
 * @param x
 * @return
 */
//@{
auto libbr_round_32(BR::Float32 x) -> BR::Float32;

auto libbr_round_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

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

} // inline namespace Function
} // inline namespace Math
} // namespace BR