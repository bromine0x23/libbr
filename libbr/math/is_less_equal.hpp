/**
 * @file
 * @brief is_less_equal
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
 * like islessequal
 * @param x
 * @param y
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_less_equal_32(BR::Float32 x, BR::Float32 y) -> bool {
	return __builtin_islessequal(x, y);
}

constexpr auto libbr_is_less_equal_64(BR::Float64 x, BR::Float64 y) -> bool {
	return __builtin_islessequal(x, y);
}
#else
constexpr auto libbr_is_less_equal_32(BR::Float32 x, BR::Float32 y) -> bool {
	return !libbr_is_unordered_32(x, y) && x <= y;
}

constexpr auto libbr_is_less_equal_64(BR::Float64 x, BR::Float64 y) -> bool {
	return !libbr_is_unordered_64(x, y) && x <= y;
}
#endif
//@}

}

namespace BR {

constexpr auto is_less_equal(Float32 x, Float32 y) -> bool {
	return libbr_is_less_equal_32(x, y);
}

constexpr auto is_less_equal(Float64 x, Float64 y) -> bool {
	return libbr_is_less_equal_64(x, y);
}

#if defined(BR_GCC)
template< typename TX, typename TY >
constexpr auto is_less_equal(TX x, TY y) -> EnableIf< BooleanAnd< IsArithmetic<TX>, IsArithmetic<TY> >, bool > {
	return __builtin_islessequal(Common<TX, TY>(x), Common<TX, TY>(y));
}
#else
template< typename TX, typename TY >
constexpr auto is_less_equal(TX x, TY y) -> EnableIf< BooleanAnd< IsArithmetic<TX>, IsArithmetic<TY> >, bool > {
	return !is_unordered_64(x, y) && x <= y;
}
#endif

} // namespace BR