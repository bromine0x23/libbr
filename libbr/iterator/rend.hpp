#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/reverse_iterator.hpp>

namespace BR {

template< typename T, Size S >
inline BR_CONSTEXPR_AFTER_CPP11 T * rend(CArray< T, S > & array) {
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