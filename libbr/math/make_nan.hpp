/**
 * @file
 * @brief nan
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#if !defined(BR_GCC)
#  include <libbr/math/detail/bind.hpp>
#endif

extern "C" {

#if defined(BR_GCC)
constexpr auto libbr_make_nan_32() -> BR::Float32 {
	return __builtin_nan("");
}

constexpr auto libbr_make_nan_64() -> BR::Float64 {
	return __builtin_nan("");
}
#else
inline auto libbr_make_nan_32() -> BR::Float32 {
	return BR::Detail::Math::Bind32{0x7FFFFFFFU}.f;
}

inline auto libbr_make_nan_64() -> BR::Float64 {
	return BR::Detail::Math::Bind64{0x7FFFFFFFFFFFFFFFULL}.f;
}
#endif

}

namespace BR {

namespace Detail {
namespace Math {

template< typename T >
struct NANMaker {};

template<>
struct NANMaker<Float32> {
	static
#if defined(BR_GCC)
	constexpr
#endif // defined(BR_GCC)
	inline auto get() -> Float32 {
		return libbr_make_nan_32();
	}
};

template<>
struct NANMaker<Float64> {
	static
#if defined(BR_GCC)
	constexpr
#endif // defined(BR_GCC)
	inline auto get() -> Float64 {
		return libbr_make_nan_64();
	}
};

} // namespace Math
} // namespace Detail

inline namespace Math {

template< typename T >
#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto make_nan() -> T {
	return Detail::Math::NANMaker<T>::get();
}

#if defined(BR_CXX14) && defined(BR_GCC)

template< typename T >
constexpr auto nan = make_nan<T>();

#endif // defined(BR_CXX14) && defined(BR_GCC)

} // inline namespace Math

} // namespace BR