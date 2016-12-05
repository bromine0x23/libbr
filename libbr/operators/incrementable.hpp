/**
 * @file
 * @brief Incrementable
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/detail/empty.hpp>

namespace BR {

inline namespace Operators {

template< typename T, typename TB = Detail::Operators::Empty<T> >
struct Incrementable  {
	friend T operator++(T & x, int) {
		T nrv(x);
		++x;
		return nrv;
	}
};

} // namespace Operators

} // namespace BR

