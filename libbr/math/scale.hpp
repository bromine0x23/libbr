/**
 * @file
 * @brief log2
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

#if defined(BR_GCC)
constexpr auto libbr_scale_s(BR::SFloat x, BR::SInt n) -> BR::SFloat {
	return __builtin_scalbn(x, n);
}
#else
extern "C" { auto libbr_scale_s(BR::SFloat x, BR::SInt n) -> BR::SFloat; }
#endif
extern "C" { auto libbr_scale_d(BR::DFloat x, BR::SInt n) -> BR::DFloat; }

namespace BR {

inline auto scale(SFloat x, SInt n) -> SFloat {
	return libbr_scale_s(x, n);
}

inline auto scale(DFloat x, SInt n) -> DFloat {
	return libbr_scale_d(x, n);
}

#if defined(BR_GCC)
template< typename T >
constexpr auto scale(T x, SInt n) -> EnableIf< IsIntegral<T>, T > {
	return __builtin_scalbn(x);
}
#else
template< typename T >
constexpr auto scale(T x, SInt n) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}
#endif

} // namespace BR