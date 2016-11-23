/**
 * @file
 * @brief log10
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * like std::log10
 * @param x
 * @return
 */
//@{
auto libbr_log10_32(BR::Float32 x) -> BR::Float32;

auto libbr_log10_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto log10(Float32 x) -> Float32 {
	return libbr_log10_32(x);
}

inline auto log10(Float64 x) -> Float64 {
	return libbr_log10_64(x);
}

template< typename T >
constexpr auto log10(T x) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR