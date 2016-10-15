/**
 * @file
 * @brief is_inf
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
auto libbr_is_infinite_s(BR::SFloat f) -> bool;

auto libbr_is_infinite_d(BR::DFloat f) -> bool;

auto libbr_is_infinite_q(BR::QFloat f) -> bool;
//@}

}

namespace BR {

inline auto is_infinite(SFloat f) -> bool {
	return libbr_is_infinite_s(f);
}

inline auto is_infinite(DFloat f) -> bool {
	return libbr_is_infinite_d(f);
}

inline auto is_infinite(QFloat f) -> bool {
	return libbr_is_infinite_q(f);
}

template< typename T >
constexpr auto is_infinite(T x) -> EnableIf< IsIntegral<T>, bool > {
	return false;
}

} // namespace BR