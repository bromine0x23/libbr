#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/reverse_iterator.hpp>

namespace BR {

template< typename T, Size S >
BR_CONSTEXPR_AFTER_CXX11 inline auto rend(CArray< T, S > & array) -> T * {
	return ReverseIterator< T * >(array);
}

template< typename TContainer >
inline auto rend(TContainer & container) -> decltype(container.rend()) {
	return container.rend();
}

template< typename TContainer >
inline auto rend(TContainer const & container) -> decltype(container.rend()) {
	return container.rend();
}

} // namespace BR