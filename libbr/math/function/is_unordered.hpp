/**
 * @file
 * @brief is_unordered
 * @author Bromine0x23
 * @since 2016/10/17
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/is_nan.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_arithmetic.hpp>

extern "C" {

/**
 * like std::isunordered
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
#elif defined(BR_CLANG)
inline auto libbr_is_unordered_32(BR::Float32 x, BR::Float32 y) -> bool {
	bool res = false;
	asm("fucomi %1,%2;jnp 0f;mov $1,%0;0:":"=r"(res):"u"(x),"t"(y));
	return res;
}

inline auto libbr_is_unordered_64(BR::Float64 x, BR::Float64 y) -> bool {
	bool res = false;
	asm("fucomi %1,%2;jnp 0f;mov $1,%0;0:":"=r"(res):"u"(x),"t"(y));
	return res;
}
#else
inline auto libbr_is_unordered_32(BR::Float32 x, BR::Float32 y) -> bool {
	return libbr_is_nan_32(x) || libbr_is_nan_32(y);
}

inline auto libbr_is_unordered_64(BR::Float64 x, BR::Float64 y) -> bool {
	return libbr_is_nan_64(x) || libbr_is_nan_64(y);
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
inline auto is_unordered(Float32 x, Float32 y) -> bool {
	return libbr_is_unordered_32(x, y);
}

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto is_unordered(Float64 x, Float64 y) -> bool {
	return libbr_is_unordered_64(x, y);
}

template< typename TX, typename TY >
inline auto is_unordered(TX x, TY y) -> EnableIf< BooleanAnd< IsArithmetic<TX>, IsArithmetic<TY> >, bool > {
	return is_nan(x) || is_nan(y);
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR