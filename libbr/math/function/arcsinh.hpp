/**
 * @file
 * @brief arcsinh
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
auto libbr_arcsinh_32(BR::Float32 x) -> BR::Float32;

auto libbr_arcsinh_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto arcsinh(Float32 x) -> Float32 {
	return libbr_arcsinh_32(x);
}

inline auto arcsinh(Float64 x) -> Float64 {
	return libbr_arcsinh_64(x);
}

template< typename T >
inline auto arcsinh(T x) -> EnableIf< IsIntegral<T>, T > {
	return arcsinh(Detail::Math::FloatPromote<T>(x));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR