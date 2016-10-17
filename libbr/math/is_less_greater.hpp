/**
 * @file
 * @brief is_less_greater
 * @author Bromine0x23
 * @since 2016/10/17
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/is_unordered.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/common.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_arithmetic.hpp>
#if defined(BR_GCC)
#  include <libbr/type_operate/common.hpp>
#else
#  include <libbr/math/is_unordered.hpp>
#endif

extern "C" {

/**
 * like islessgreater
 * @param x
 * @param y
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_less_greater_32(BR::Float32 x, BR::Float32 y) -> bool {
	return __builtin_islessgreater(x, y);
}

constexpr auto libbr_is_less_greater_64(BR::Float64 x, BR::Float64 y) -> bool {
	return __builtin_islessgreater(x, y);
}
#else
constexpr auto libbr_is_less_greater_32(BR::Float32 x, BR::Float32 y) -> bool {
	return !libbr_is_unordered_32(x, y) && (x < y || y < x);
}

constexpr auto libbr_is_less_greater_64(BR::Float64 x, BR::Float64 y) -> bool {
	return !libbr_is_unordered_64(x, y) && (x < y || y < x);
}
#endif
//@}

}

namespace BR {

constexpr auto is_less_greater(Float32 x, Float32 y) -> bool {
	return libbr_is_less_greater_32(x, y);
}

constexpr auto is_less_greater(Float64 x, Float64 y) -> bool {
	return libbr_is_less_greater_64(x, y);
}

#if defined(BR_GCC)
template< typename TX, typename TY >
constexpr auto is_less_greater(TX x, TY y) -> EnableIf< BooleanAnd< IsArithmetic<TX>, IsArithmetic<TY> >, bool > {
	return __builtin_islessgreater(Common<TX, TY>(x), Common<TX, TY>(y));
}
#else
template< typename TX, typename TY >
constexpr auto is_less_greater(TX x, TY y) -> EnableIf< BooleanAnd< IsArithmetic<TX>, IsArithmetic<TY> >, bool > {
	return !is_unordered_64(x, y) && (x < y || y < x);
}
#endif

} // namespace BR