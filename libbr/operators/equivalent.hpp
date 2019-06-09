/**
 * @file
 * @brief Equivalent
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/_/empty.hpp>

namespace BR {

inline namespace Operators {

template< typename TX, typename TY = TX, typename TBase = _::Operators::Empty<TX, TY> >
struct Equivalent;

} // namespace Operators



inline namespace Operators {

template< typename T, typename TBase>
struct Equivalent< T, T, TBase > : public TBase {
	friend constexpr auto operator!=(T const & x, T const & y) -> Boolean { return !static_cast<Boolean>(x == y); }
};

template< typename TX, typename TY, typename TBase >
struct Equivalent : public TBase {
	friend constexpr auto operator==(TY const & y, TX const & x) -> Boolean { return x == y; }
	friend constexpr auto operator!=(TX const & x, TY const & y) -> Boolean { return !static_cast<Boolean>(x == y); }
	friend constexpr auto operator!=(TY const & y, TX const & x) -> Boolean { return !static_cast<Boolean>(y == x); }
};

} // namespace Operators

} // namespace BR

