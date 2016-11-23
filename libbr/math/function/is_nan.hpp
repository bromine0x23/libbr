/**
 * @file
 * @brief is_nan
 * @author Bromine0x23
 * @since 2016/10/11
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#if !(defined(BR_GCC) || defined(BR_CLANG))
#  include <libbr/math/detail/bind.hpp>
#endif

extern "C" {

/**
 * like std::isnan
 * @param x
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_nan_32(BR::Float32 x) -> bool {
	return __builtin_isnan(x);
}

constexpr auto libbr_is_nan_64(BR::Float64 x) -> bool {
	return __builtin_isnan(x);
}
#elif defined(BR_CLANG)
inline auto libbr_is_nan_32(BR::Float32 x) -> bool {
	bool result;
	asm("fucomi %%st(0),%%st;setp %[result]":[result]"=r"(result):"t"(x));
	return result;
}

inline auto libbr_is_nan_64(BR::Float64 x) -> bool {
	bool result;
	asm("fucomi %%st(0),%%st;setp %[result]":[result]"=r"(result):"t"(x));
	return result;
}
#else
inline auto libbr_is_nan_32(BR::Float32 x) -> bool {
	return ((0x7F800000U - (BR::Detail::Math::Bind32{x}.r & 0x7FFFFFFFU)) >> 31) != 0;
}

inline auto libbr_is_nan_64(BR::Float64 x) -> bool {
	return ((0x7FF00000U - (BR::Detail::Math::Bind64{x}.h & 0x7FFFFFFFU) | (BR::Detail::Math::Bind64{x}.l != 0)) >> 31) != 0;
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
inline auto is_nan(Float32 x) -> bool {
	return libbr_is_nan_32(x);
}

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto is_nan(Float64 x) -> bool {
	return libbr_is_nan_64(x);
}

template< typename T >
constexpr auto is_nan(T x) -> EnableIf< IsIntegral<T>, bool > {
	return false;
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR