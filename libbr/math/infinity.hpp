/**
 * @file
 * @brief infinity
 * @author Bromine0x23
 * @since 2016/10/15
 */
#pragma once

#include <libbr/config.hpp>
#if !defined(BR_GCC)
#  include <libbr/math/detail/float.hpp>
#endif

extern "C" {
#if defined(BR_GCC)
constexpr auto libbr_infinity_32() -> BR::Float32 {
	return __builtin_inf();
}

constexpr auto libbr_infinity_64() -> BR::Float64 {
	return __builtin_inf();
}
#else
constexpr auto libbr_infinity_32() -> BR::Float32 {
	return BR::Detail::Float::to_float(0x7F800000U);
}

constexpr auto libbr_infinity_64() -> BR::Float64 {
	return BR::Detail::Float::to_float(0x7FF0000000000000ULL);
}
#endif

}

namespace BR {

namespace Detail {
namespace Math {

template< typename T >
struct InfinityGetter {};

template<>
struct InfinityGetter<Float32> {
	static constexpr auto get() -> Float32 {
		return libbr_infinity_32();
	}
};

template<>
struct InfinityGetter<Float64> {
	static constexpr auto get() -> Float64 {
		return libbr_infinity_64();
	}
};

} // namespace Math
} // namespace Detail

template< typename T >
auto infinity() -> T {
	return Detail::Math::InfinityGetter<T>::get();
}

} // namespace BR