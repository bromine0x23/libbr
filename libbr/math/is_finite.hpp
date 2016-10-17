/**
 * @file
 * @brief is_finite
 * @author Bromine0x23
 * @since 2016/10/11
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#if !defined(BR_GCC)
#  include <libbr/math/detail/float.hpp>
#endif

extern "C" {

/**
 * like isfinite
 * @param f
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_finite_32(BR::Float32 f) -> bool {
	return __builtin_isfinite(f);
}

constexpr auto libbr_is_finite_64(BR::Float64 f) -> bool {
	return __builtin_isfinite(f);
}
#else
constexpr auto libbr_is_finite_32(BR::Float32 f) -> bool {
	return (((BR::Detail::Float::to_raw(f) & 0x7FFFFFFFU) - 0x7F800000U) >> 31) != 0;
}

constexpr auto libbr_is_finite_64(BR::Float64 f) -> bool {
	return (((BR::Detail::Float::to_raw_high(f) & 0x7FFFFFFFU) - 0x7FF00000U) >> 31) != 0;
}
#endif
//@}

}

namespace BR {

constexpr auto is_finite(Float32 f) -> bool {
	return libbr_is_finite_32(f);
}

constexpr auto is_finite(Float64 f) -> bool {
	return libbr_is_finite_64(f);
}

template< typename T >
constexpr auto is_finite(T x) -> EnableIf< IsIntegral<T>, bool > {
	return false;
}

} // namespace BR