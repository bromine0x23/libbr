#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TIterator, typename = EnableIf< typename IteratorTraits<TIterator>::IsForwardIterator > >
inline auto next(TIterator current, typename IteratorTraits<TIterator>::Difference step = 1) -> TIterator {
	advance(current, step);
	return current;
}

} // namespace BR