#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename T, Size S >
inline BR_CONSTEXPR_AFTER_CPP11 T * end(CArray< T, S > & array) {
	return array + S;
}

template< typename TContainer >
inline auto end(TContainer & container) -> decltype(container.end()) {
	return container.end();
}

template< typename TContainer >
inline auto end(TContainer const & container) -> decltype(container.end()) {
	return container.end();
}

} // namespace BR