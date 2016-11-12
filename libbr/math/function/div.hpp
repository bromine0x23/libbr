/**
 * @file
 * @brief div
 * @author Bromine0x23
 * @since 2015/11/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

namespace BR {

template< typename T >
constexpr auto div(T x, T y) -> EnableIf< IsIntegral<T>, Pair< TIntegral, TIntegral > > {
	return make_pair(x / y, x % y);
};

} // namespace BR