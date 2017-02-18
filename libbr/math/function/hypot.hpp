/**
 * @file
 * @brief hypot
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/float_promote.hpp>

extern "C" {
// TODO: implement it
/**
 * like std::hypot
 * @param x
 * @return
 */
//@{
auto libbr_hypot_32(BR::Float32 x, BR::Float32 y) -> BR::Float32;

auto libbr_hypot_64(BR::Float64 x, BR::Float64 y) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto hypot(Float32 x, Float32 y) -> Float32 {
	return libbr_hypot_32(x, y);
}

inline auto hypot(Float64 x, Float64 y) -> Float64 {
	return libbr_hypot_64(x, y);
}

template< typename TX, typename TY >
inline auto hypot(TX x, TY y) -> Detail::Math::FloatPromote2< TX, TY > {
	using T = Detail::Math::FloatPromote2< TX, TY >;
	return hypot(T(x), T(y));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR