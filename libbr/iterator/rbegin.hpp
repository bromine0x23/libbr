#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/reverse_iterator.hpp>

namespace BR {

template< typename T, Size S >
BR_CONSTEXPR_AFTER_CXX11 inline auto rbegin(CArray< T, S > & array) -> T * {
	return ReverseIterator< T * >(array + S);
}

template< typename TContainer >
inline auto rbegin(TContainer & container) -> decltype(container.rbegin()) {
	return container.rbegin();
}

template< typename TContainer >
inline auto rbegin(TContainer const & container) -> decltype(container.rbegin()) {
	return container.rbegin();
}

} // namespace BR