/**
 * @file
 * @brief is_unordered
 * @author Bromine0x23
 * @since 2016/10/17
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_arithmetic.hpp>
#if defined(BR_GCC)
#  include <libbr/type_operate/common.hpp>
#else
#  include <libbr/math/is_unordered.hpp>
#endif

extern "C" {

/**
 * like isunordered
 * @param x
 * @param y
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_unordered_32(BR::Float32 x, BR::Float32 y) -> bool {
	return __builtin_isunordered(x, y);
}

constexpr auto libbr_is_unordered_64(BR::Float64 x, BR::Float64 y) -> bool {
	return __builtin_isunordered(x, y);
}
#else
constexpr auto libbr_is_unordered_32(BR::Float32 x, BR::Float32 y) -> bool {
	return libbr_is_nan_32(x) || libbr_is_nan_32(y);
}

constexpr auto libbr_is_unordered_64(BR::Float64 x, BR::Float64 y) -> bool {
	return libbr_is_nan_64(x) || libbr_is_nan_64(y);
}
#endif
//@}

}

namespace BR {

constexpr auto is_unordered(Float32 x, Float32 y) -> bool {
	return libbr_is_unordered_32(x, y);
}

constexpr auto is_unordered(Float64 x, Float64 y) -> bool {
	return libbr_is_unordered_64(x, y);
}

#if defined(BR_GCC)
template< typename TX, typename TY >
constexpr auto is_unordered(TX x, TY y) -> EnableIf< BooleanAnd< IsArithmetic<TX>, IsArithmetic<TY> >, bool > {
	return __builtin_isunordered(Common<TX, TY>(x), Common<TX, TY>(y));
}
#else
template< typename TX, typename TY >
constexpr auto is_unordered(TX x, TY y) -> EnableIf< BooleanAnd< IsArithmetic<TX>, IsArithmetic<TY> >, bool > {
	return is_nan(x) || is_nan(y);
}
#endif

} // namespace BR