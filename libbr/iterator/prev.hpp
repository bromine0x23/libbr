#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_convertible.hpp>

namespace BR {

template< typename TIterator >
inline auto prev(TIterator current, typename IteratorTraits<TIterator>::Difference step = 1) -> EnableIf< IsConvertible< typename IteratorTraits<TIterator>::Category, BidirectionalTraversalTag >, TIterator >  {
	advance(current, -step);
	return current;
}

} // namespace BR