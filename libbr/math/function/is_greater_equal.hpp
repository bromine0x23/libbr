/**
 * @file
 * @brief is_greater_equal
 * @author Bromine0x23
 * @since 2016/10/17
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/is_unordered.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_arithmetic.hpp>

extern "C" {

/**
 * like std::isgreaterequal
 * @param x
 * @param y
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_greater_equal_32(BR::Float32 x, BR::Float32 y) -> bool {
	return __builtin_isgreaterequal(x, y);
}

constexpr auto libbr_is_greater_equal_64(BR::Float64 x, BR::Float32 y) -> bool {
	return __builtin_isgreaterequal(x, y);
}
#else
inline auto libbr_is_greater_equal_32(BR::Float32 x, BR::Float32 y) -> bool {
	return !libbr_is_unordered_32(x, y) && x >= y;
}

inline auto libbr_is_greater_equal_64(BR::Float64 x, BR::Float64 y) -> bool {
	return !libbr_is_unordered_64(x, y) && x >= y;
}
#endif
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto is_greater_equal(Float32 x, Float32 y) -> bool {
	return libbr_is_greater_equal_32(x, y);
}

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto is_greater_equal(Float64 x, Float64 y) -> bool {
	return libbr_is_greater_equal_64(x, y);
}

template< typename TX, typename TY >
inline auto is_greater_equal(TX x, TY y) -> EnableIf< BooleanAnd< IsArithmetic<TX>, IsArithmetic<TY> >, bool > {
	return !is_unordered(x, y) && x >= y;
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR