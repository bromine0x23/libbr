/**
 * @file
 * @brief Incrementable
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/_/empty.hpp>

namespace BR {

inline namespace Operators {

template< typename T, typename TBase = _::Operators::Empty<T> >
struct Incrementable : public TBase {
	friend constexpr auto operator++(T & x, int) -> T  {
		T nrv(x);
		++x;
		return nrv;
	}
};

} // namespace Operators

} // namespace BR

