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
constexpr auto libbr_log2_s(BR::SFloat x) -> BR::SFloat {
	return __builtin_log2f(x);
}
#else
extern "C" { auto libbr_log2_s(BR::SFloat x) -> BR::SFloat; }
#endif
extern "C" { auto libbr_log2_d(BR::DFloat x) -> BR::DFloat; }

namespace BR {

inline auto log2(SFloat x) -> SFloat {
	return libbr_log2_s(x);
}

inline auto log2(DFloat x) -> DFloat {
	return libbr_log2_d(x);
}

#if defined(BR_GCC)
template< typename T >
constexpr auto log2(T x) -> EnableIf< IsIntegral<T>, T > {
	return __builtin_log2(x);
}
#else
template< typename T >
constexpr auto log2(T x) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}
#endif

} // namespace BR