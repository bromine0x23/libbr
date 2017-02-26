/**
 * @file
 * @brief pow
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/float_promote.hpp>

extern "C" {
// TODO: implement it
/**
 * like std::pow
 * @param base
 * @param exponent
 * @return
 */
//@{
auto libbr_pow_32(BR::Float32 base, BR::Float32 exponent) -> BR::Float32;

auto libbr_pow_64(BR::Float64 base, BR::Float64 exponent) -> BR::Float64;
//@}

}

namespace BR {
inline namespace Math {
inline namespace Function {

inline auto pow(Float32 base, Float32 exponent) -> Float32 {
	return libbr_pow_32(base, exponent);
}

inline auto pow(Float64 base, Float64 exponent) -> Float64 {
	return libbr_pow_64(base, exponent);
}

template< typename TBase, typename TExponent >
inline auto pow(TBase base, TExponent exponent) -> Detail::Math::FloatPromote2< TBase, TExponent > {
	using T = Detail::Math::FloatPromote2< TBase, TExponent >;
	return pow(T(base), T(exponent));
}

} // inline namespace Function
} // inline namespace Math
} // namespace BR