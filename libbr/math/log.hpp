/**
 * @file
 * @brief log
 * @author Bromine0x23
 * @since 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

#if defined(BR_GCC)
constexpr auto libbr_log_s(BR::SFloat x) -> BR::SFloat {
	return __builtin_logf(x);
}
#else
extern "C" { auto libbr_log_s(BR::SFloat x) -> BR::SFloat; }
#endif
extern "C" { auto libbr_log_d(BR::DFloat x) -> BR::DFloat; }

namespace BR {

inline auto log(SFloat x) -> SFloat {
	return libbr_log_s(x);
}

inline auto log(DFloat x) -> DFloat {
	return libbr_log_d(x);
}

#if defined(BR_GCC)
template< typename T >
constexpr auto log(T x) -> EnableIf< IsIntegral<T>, T > {
	return __builtin_log(x);
}
#else
template< typename T >
constexpr auto log(T x) -> EnableIf< IsIntegral<T>, T > {
	return 0; // TODO
}
#endif

} // namespace BR