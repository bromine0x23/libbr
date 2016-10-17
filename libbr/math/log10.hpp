/**
 * @file
 * @brief log10
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

#if defined(BR_GCC)
constexpr auto libbr_log10_s(BR::SFloat x) -> BR::SFloat {
	return __builtin_log10f(x);
}
#else
extern "C" { auto libbr_log10_s(BR::SFloat x) -> BR::SFloat; }
#endif
extern "C" { auto libbr_log10_d(BR::DFloat x) -> BR::DFloat; }

namespace BR {

inline auto log10(SFloat x) -> SFloat {
	return libbr_log10_s(x);
}

inline auto log10(DFloat x) -> DFloat {
	return libbr_log10_d(x);
}

#if defined(BR_GCC)
template< typename T >
constexpr auto log10(T x) -> EnableIf< IsIntegral<T>, T > {
	return __builtin_log10(x);
}
#else
template< typename T >
constexpr auto log10(T x) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}
#endif

} // namespace BR