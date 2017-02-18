/**
 * @file
 * @brief tan
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
 * like std::tan
 * @param x
 * @return
 */
//@{
auto libbr_tan_32(BR::Float32 x) -> BR::Float32;

auto libbr_tan_64(BR::Float64 x) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto tan(Float32 x) -> Float32 {
	return libbr_tan_32(x);
}

inline auto tan(Float64 x) -> Float64 {
	return libbr_tan_64(x);
}

template< typename T >
inline auto tan(T x) -> EnableIf< IsIntegral<T>, T > {
	return tan(Detail::Math::FloatPromote<T>(x));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR