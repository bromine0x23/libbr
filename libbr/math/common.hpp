/**
 * @file
 * @brief common
 * @author Bromine0x23
 * @since 2015/11/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>

namespace BR {

template< typename TIntegral, typename _TDummy = EnableIf< IsIntegral<TIntegral> > >
constexpr auto abs(TIntegral i) -> TIntegral {
	return i < 0 ? -i : i;
};

template< typename TIntegral, typename _TDummy = EnableIf< IsIntegral<TIntegral> > >
constexpr auto div(TIntegral x, TIntegral y) -> Pair< TIntegral, TIntegral > {
	return make_pair(x / y, x % y);
};

} // namespace BR