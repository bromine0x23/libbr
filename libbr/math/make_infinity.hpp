/**
 * @file
 * @brief infinity
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
constexpr auto libbr_make_infinity_32() -> BR::Float32 {
	return __builtin_inf();
}

constexpr auto libbr_make_infinity_64() -> BR::Float64 {
	return __builtin_inf();
}
#else
inline auto libbr_make_infinity_32() -> BR::Float32 {
	BR::Detail::Math::Bind32 b = {0x7F800000U};
	return b.f;
}

inline auto libbr_make_infinity_64() -> BR::Float64 {
	BR::Detail::Math::Bind64 b = {0x7FF0000000000000ULL};
	return b.f;
}
#endif

}

namespace BR {

namespace Detail {
namespace Math {

template< typename T >
struct InfinityMaker {};

template<>
struct InfinityMaker<Float32> {
	static
#if defined(BR_GCC)
	constexpr
#endif // defined(BR_GCC)
	inline auto get() -> Float32 {
		return libbr_make_infinity_32();
	}
};

template<>
struct InfinityMaker<Float64> {
	static
#if defined(BR_GCC)
	constexpr
#endif // defined(BR_GCC)
	inline auto get() -> Float64 {
		return libbr_make_infinity_64();
	}
};

} // namespace Math
} // namespace Detail

inline namespace Math {

template< typename T >
#if defined(BR_GCC)
constexpr
#endif // defined(BR_GCC)
inline auto make_infinity() -> T {
	return Detail::Math::InfinityMaker<T>::get();
}

#if defined(BR_CXX14) && defined(BR_GCC)

template< typename T >
constexpr auto infinity = make_infinity<T>();

#endif // defined(BR_CXX14) && defined(BR_GCC)

} // inline namespace Math

} // namespace BR