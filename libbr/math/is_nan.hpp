/**
 * @file
 * @brief is_nan
 * @author Bromine0x23
 * @since 2016/10/11
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

extern "C" {

/**
 * like isnan
 * @param f
 * @return
 */
//@{
auto libbr_is_nan_s(BR::SFloat x) -> bool;

auto libbr_is_nan_d(BR::DFloat x) -> bool;

auto libbr_is_nan_q(BR::QFloat x) -> bool;
//@}

}

namespace BR {

inline auto is_nan(SFloat x) -> bool {
	return libbr_is_nan_s(x);
}

inline auto is_nan(DFloat x) -> bool {
	return libbr_is_nan_d(x);
}

inline auto is_nan(QFloat x) -> bool {
	return libbr_is_nan_q(x);
}

template< typename T >
constexpr auto is_nan(T x) -> EnableIf< IsIntegral<T>, bool > {
	return false;
}

} // namespace BR