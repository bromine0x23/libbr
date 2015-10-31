#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename T, Size S >
BR_CONSTEXPR_AFTER_CXX11 inline auto end(CArray< T, S > & array) -> T * {
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