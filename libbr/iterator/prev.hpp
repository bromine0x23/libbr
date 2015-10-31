#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/type_operate/enable_if.hpp>

namespace BR {

template< typename TIterator, typename = EnableIf< typename IteratorTraits<TIterator>::IsBidirectionalIterator > >
inline auto prev(TIterator current, typename IteratorTraits<TIterator>::Difference step = 1) -> TIterator {
	advance(current, -step);
	return current;
}

} // namespace BR