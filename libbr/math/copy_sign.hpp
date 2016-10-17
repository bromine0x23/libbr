/**
 * @file
 * @brief copy_sign
 * @author Bromine0x23
 * @since 2016/10/11
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/float.hpp>

extern "C" {

/**
 * like copysign
 * @param f
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_copy_sign_32(BR::Float32 x, BR::Float32 s) -> BR::Float32 {
	return __builtin_copysignf(x, s);
}
#else
constexpr auto libbr_copy_sign_32(BR::Float32 x, BR::Float32 s) -> BR::Float32 {
	return BR::Detail::Float::to_float(
		(BR::Detail::Float::to_raw(x) & 0x7FFFFFFFU) | (BR::Detail::Float::to_raw(s) & 0x80000000U)
	);
}
#endif

constexpr auto libbr_copy_sign_64(BR::Float64 x, BR::Float64 s) -> BR::Float64 {
	return BR::Detail::Float::to_float(
		(BR::Detail::Float::to_raw_high(x) & 0x7FFFFFFFU) | (BR::Detail::Float::to_raw_high(s) & 0x80000000U),
		BR::Detail::Float::to_raw_low(x)
	);
}
//@}

}

namespace BR {

constexpr auto copy_sign(Float32 x, Float32 s) -> Float32 {
	return libbr_copy_sign_32(x, s);
}

constexpr auto copy_sign(Float64 x, Float64 s) -> Float64 {
	return libbr_copy_sign_64(x, s);
}

} // namespace BR