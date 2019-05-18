/**
 * @file
 * @brief distance
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>

namespace BR {

inline namespace Iterators {

template< typename TIterator >
constexpr auto distance(TIterator head, TIterator tail) -> typename IteratorTraits<TIterator>::Difference;

} // namespace Iterators



namespace _ {
namespace Iterators {

template< typename TIterator >
constexpr inline auto distance(TIterator head, TIterator tail, SinglePassTraversalTag) -> typename IteratorTraits<TIterator>::Difference {
	typename IteratorTraits<TIterator>::Difference result(0);
	for (; head != tail; ++head) {
		++result;
	}
	return result;
}

template< typename TIterator >
constexpr inline auto distance(TIterator head, TIterator tail, RandomAccessTraversalTag) -> typename IteratorTraits<TIterator>::Difference {
	return tail - head;
}

} // namespace Iterators
} // namespace _

inline namespace Iterators {

template< typename TIterator >
constexpr inline auto distance(TIterator head, TIterator tail) -> typename IteratorTraits<TIterator>::Difference {
	return _::Iterators::distance(head, tail, IteratorTraits<TIterator>::iterator_category());
}

} // namespace Iterators

} // namespace BR