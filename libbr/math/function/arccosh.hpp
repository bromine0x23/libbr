/**
 * @file
 * @brief arccosh
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/float_promote.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {
// TODO: implement it
/**
 * like std::asinh
 * @param x
 * @return
 */
//@{
auto libbr_arccosh_32(BR::Float32 x) -> BR::Float32;

auto libbr_arccosh_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto arccosh(Float32 x) -> Float32 {
	return libbr_arccosh_32(x);
}

inline auto arccosh(Float64 x) -> Float64 {
	return libbr_arccosh_64(x);
}

template< typename T >
inline auto arccosh(T x) -> EnableIf< IsIntegral<T>, T > {
	return arccosh(Detail::Math::FloatPromote<T>(x));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR