#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename T, Size S >
constexpr inline auto begin(CArray< T, S > & array) -> T * {
	return array;
}

template< typename TContainer >
BR_CONSTEXPR_AFTER_CXX11 inline auto begin(TContainer & container) -> decltype(container.begin()) {
	return container.begin();
}

template< typename TContainer >
BR_CONSTEXPR_AFTER_CXX11 inline auto begin(TContainer const & container) -> decltype(container.begin()) {
	return container.begin();
}

} // namespace BR