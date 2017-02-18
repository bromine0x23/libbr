/**
 * @file
 * @brief sqrt
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
 * like std::sqrt
 * @param x
 * @return
 */
//@{
auto libbr_sqrt_32(BR::Float32 x) -> BR::Float32;

auto libbr_sqrt_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto sqrt(Float32 x) -> Float32 {
	return libbr_sqrt_32(x);
}

inline auto sqrt(Float64 x) -> Float64 {
	return libbr_sqrt_64(x);
}

template< typename T >
inline auto sqrt(T x) -> EnableIf< IsIntegral<T>, T > {
	return sqrt(Detail::Math::FloatPromote<T>(x));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR