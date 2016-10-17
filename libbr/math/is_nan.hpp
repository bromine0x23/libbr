/**
 * @file
 * @brief is_nan
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
 * like isnan
 * @param f
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_nan_32(BR::Float32 f) -> bool {
	return __builtin_isnan(f);
}

constexpr auto libbr_is_nan_64(BR::Float64 f) -> bool {
	return __builtin_isnan(f);
}
#else
constexpr auto libbr_is_nan_32(BR::Float32 f) -> bool {
	return ((0x7F800000U - (BR::Detail::Float::ToRaw32{f}.r & 0x7FFFFFFFU)) >> 31) != 0;
}

constexpr auto libbr_is_nan_64(BR::Float64 f) -> bool {
	return ((0x7FF00000U - (BR::Detail::Float::ToRaw64{f}.h & 0x7FFFFFFFU) | (BR::Detail::Float::ToRaw64{f}.l != 0)) >> 31) != 0;
}
#endif
//@}

}

namespace BR {

constexpr auto is_nan(Float32 x) -> bool {
	return libbr_is_nan_32(x);
}

constexpr auto is_nan(Float64 x) -> bool {
	return libbr_is_nan_64(x);
}

template< typename T >
constexpr auto is_nan(T x) -> EnableIf< IsIntegral<T>, bool > {
	return false;
}

} // namespace BR