#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Iterator {

template< typename T, Size S >
inline BR_CONSTEXPR_AFTER_CPP11 T * begin(CArray< T, S > & array) {
	return array;
}

template< typename TContainer >
inline auto begin(TContainer & container) -> decltype(container.begin()) {
	return container.begin();
}

template< typename TContainer >
inline auto begin(TContainer const & container) -> decltype(container.begin()) {
	return container.begin();
}

} // namespace Iterator
} // namespace BR