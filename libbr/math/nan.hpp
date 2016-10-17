/**
 * @file
 * @brief nan
 * @author Bromine0x23
 * @since 2016/10/15
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

#if defined(BR_GCC)
constexpr auto libbr_nan_32() -> BR::Float32 {
	return __builtin_nan("");
}

constexpr auto libbr_nan_64() -> BR::Float64 {
	return __builtin_nan("");
}
#else
constexpr auto libbr_nan_32() -> BR::Float32 {
	return BR::Detail::Float::ToFloat32{0x7FFFFFFFU}.f;
}

constexpr auto libbr_nan_64() -> BR::Float64 {
	return BR::Detail::Float::ToFloat64{0x7FFFFFFFFFFFFFFFULL}.f;
}
#endif

}

namespace BR {

namespace Detail {
namespace Math {

template< typename T >
struct NANGetter {};

template<>
struct NANGetter<Float32> {
	static constexpr auto get() -> Float32 {
		return libbr_nan_32();
	}
};

template<>
struct NANGetter<Float64> {
	static constexpr auto get() -> Float64 {
		return libbr_nan_64();
	}
};

} // namespace Math
} // namespace Detail

template< typename T >
constexpr auto nan() -> T {
	return Detail::Math::NANGetter<T>::get();
}

} // namespace BR