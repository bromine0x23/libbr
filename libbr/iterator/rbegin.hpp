#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/reverse_iterator.hpp>

namespace BR {
namespace Iterator {

template< typename T, Size S >
inline BR_CONSTEXPR_AFTER_CPP11 T * rbegin(CArray< T, S > & array) {
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

} // namespace Iterator
} // namespace BR