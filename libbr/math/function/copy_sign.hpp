/**
 * @file
 * @brief copy_sign
 * @author Bromine0x23
 * @since 2016/10/11
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/bind.hpp>
#include <libbr/type_traits/common.hpp>

extern "C" {

/**
 * @brief like copysign
 * @param x
 * @param s
 * @return
 */
//@{
inline auto libbr_copy_sign_32(BR::Float32 x, BR::Float32 s) -> BR::Float32 {
	BR::Detail::Math::Bind32 b{x};
	b.negative = BR::Detail::Math::Bind32{s}.negative;
	return b.f;
}

inline auto libbr_copy_sign_64(BR::Float64 x, BR::Float64 s) -> BR::Float64 {
	BR::Detail::Math::Bind64 b{x};
	b.negative = BR::Detail::Math::Bind64{s}.negative;
	return b.f;
}
//@}

}

namespace BR {

inline auto copy_sign(Float32 x, Float32 s) -> Float32 {
	return libbr_copy_sign_32(x, s);
}

inline auto copy_sign(Float64 x, Float64 s) -> Float64 {
	return libbr_copy_sign_64(x, s);
}

template< typename TX, typename TS >
inline auto copy_sign(TX x, TS s) -> Common<TX, TS> {
	using T = Common<TX, TS>;
	return copy_sign(T(x), T(s));
}

} // namespace BR