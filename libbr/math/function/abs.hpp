/**
 * @file
 * @brief abs
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#if !defined(BR_GCC)
#  include <libbr/math/detail/bind.hpp>
#endif

extern "C" {

/**
 * like std::fabs
 * @param x
 * @return |x|
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_abs_32(BR::Float32 x) -> BR::Float32 {
	return __builtin_fabsf(x);
}

constexpr auto libbr_abs_64(BR::Float64 x) -> BR::Float64 {
	return __builtin_fabs(x);
}
#elif defined(BR_CLANG)
inline auto libbr_abs_32(BR::Float32 x) -> BR::Float32 {
	asm volatile("fabs" : "=t"(x) : "0"(x));
	return x;
}

inline auto libbr_abs_64(BR::Float64 x) -> BR::Float64 {
	asm volatile("fabs" : "=t"(x) : "0"(x));
	return x;
}
#elif defined(BR_MSVC)
inline auto libbr_abs_32(BR::Float32 x) -> BR::Float32 {
	__asm {
		fld x
		fabs
		fst x
	}
	return f;
}

inline auto libbr_abs_64(BR::Float64 x) -> BR::Float64 {
	__asm {
		fld x
		fabs
		fst x
	}
	return f;
}
#else
inline auto libbr_abs_32(BR::Float32 x) -> BR::Float32 {
	BR::Detail::Math::Bind32 b{x};
	b.r &= 0x7FFFFFFFU;
	return b.f;
}

inline auto libbr_abs_64(BR::Float64 x) -> BR::Float64 {
	BR::Detail::Math::Bind64 b{x};
	b.h &= 0x7FFFFFFFU;
	return b.f;
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
inline auto abs(Float32 x) -> Float32 {
	return libbr_abs_32(x);
}

#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto abs(Float64 x) -> Float64 {
	return libbr_abs_64(x);
}

template<typename T>
constexpr auto abs(T x) -> EnableIf <IsIntegral<T>, T> {
	return x < 0 ? -x : x;
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR