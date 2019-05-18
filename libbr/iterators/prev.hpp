/**
 * @file
 * @brief prev
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/advance.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/utility/enable_if.hpp>

namespace BR {

inline namespace Iterators {

template< typename TIterator >
inline auto prev(
	TIterator current,
	typename IteratorTraits<TIterator>::Difference step = 1
) -> EnableIf< IsConvertible< typename IteratorTraits<TIterator>::IteratorCategory, BidirectionalTraversalTag >, TIterator >  {
	advance(current, -step);
	return current;
}

} // namespace Iterators

} // namespace BR