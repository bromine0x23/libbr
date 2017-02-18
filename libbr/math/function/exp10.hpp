/**
 * @file
 * @brief exp10
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/float_promote.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * exp10
 * @param x
 * @return
 */
//@{
auto libbr_exp10_32(BR::Float32 x) -> BR::Float32;

auto libbr_exp10_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto exp10(Float32 x) -> Float32 {
	return libbr_exp10_32(x);
}

inline auto exp10(Float64 x) -> Float64 {
	return libbr_exp10_64(x);
}

template< typename T >
inline auto exp10(T x) -> EnableIf< IsIntegral<T>, T > {
	return exp10(Detail::Math::FloatPromote<T>(x));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR