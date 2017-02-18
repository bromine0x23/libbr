/**
 * @file
 * @brief arcsin
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
 * like std::asin
 * @param x
 * @return
 */
//@{
auto libbr_arcsin_32(BR::Float32 x) -> BR::Float32;

auto libbr_arcsin_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto arcsin(Float32 x) -> Float32 {
	return libbr_arcsin_32(x);
}

inline auto arcsin(Float64 x) -> Float64 {
	return libbr_arcsin_64(x);
}

template< typename T >
inline auto arcsin(T x) -> EnableIf< IsIntegral<T>, T > {
	return arcsin(Detail::Math::FloatPromote<T>(x));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR