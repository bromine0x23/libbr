/**
 * @file
 * @brief arctanh
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
 * like std::atanh
 * @param x
 * @return
 */
//@{
auto libbr_arctanh_32(BR::Float32 x) -> BR::Float32;

auto libbr_arctanh_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto arctanh(Float32 x) -> Float32 {
	return libbr_arctanh_32(x);
}

inline auto arctanh(Float64 x) -> Float64 {
	return libbr_arctanh_64(x);
}

template< typename T >
inline auto arctanh(T x) -> EnableIf< IsIntegral<T>, T > {
	return arctanh(Detail::Math::FloatPromote<T>(x));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR