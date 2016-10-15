/**
 * @file
 * @brief is_finite
 * @author Bromine0x23
 * @since 2016/10/11
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * like isinf
 * @param f
 * @return
 */
//@{
#if defined(BR_GCC)
constexpr auto libbr_is_finite_s(BR::SFloat f) -> bool {
	return __builtin_isinf(f);
}

constexpr auto libbr_is_finite_d(BR::DFloat f) -> bool {
	return __builtin_isinf(f);
}

constexpr auto libbr_is_finite_q(BR::QFloat f) -> bool {
	return __builtin_isinf(f);
}
#else
auto libbr_is_finite_s(BR::SFloat f) -> bool;

auto libbr_is_finite_d(BR::DFloat f) -> bool;

auto libbr_is_finite_q(BR::QFloat f) -> bool;
#endif
//@}

}

namespace BR {

inline auto is_finite(SFloat f) -> bool {
	return libbr_is_finite_s(f);
}

inline auto is_finite(DFloat f) -> bool {
	return libbr_is_finite_d(f);
}

inline auto is_finite(QFloat f) -> bool {
	return libbr_is_finite_q(f);
}

template< typename T >
constexpr auto is_finite(T x) -> EnableIf< IsIntegral<T>, bool > {
	return false;
}

} // namespace BR