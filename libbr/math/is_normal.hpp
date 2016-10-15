/**
 * @file
 * @brief is_normal
 * @author Bromine0x23
 * @since 2016/10/12
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
auto libbr_is_normal_s(BR::SFloat x) -> bool;

auto libbr_is_normal_d(BR::DFloat x) -> bool;

auto libbr_is_normal_q(BR::QFloat x) -> bool;
//@}

}

namespace BR {

inline auto is_normal(SFloat x) -> bool {
	return libbr_is_normal_s(x);
}

inline auto is_normal(DFloat x) -> bool {
	return libbr_is_normal_d(x);
}

inline auto is_normal(QFloat x) -> bool {
	return libbr_is_normal_q(x);
}

template< typename T >
constexpr auto is_normal(T x) -> EnableIf< IsIntegral<T>, bool > {
	return x != 0;
}

} // namespace BR