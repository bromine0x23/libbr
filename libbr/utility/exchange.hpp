#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename T0, typename T1 = T0 >
inline T0 exchange(T0 & object, T1 && new_value) {
	T0 old_value = move(object);
	object = forward<T1>(new_value);
	return old_value;
}

} // namespace BR
