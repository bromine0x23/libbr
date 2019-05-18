/**
 * @file
 * @brief advance
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>

namespace BR {

inline namespace Iterators {

template< typename TIterator >
constexpr void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step);

} // namespace Iterators



namespace _ {
namespace Iterators {

template< typename TIterator >
constexpr inline void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step, IncrementableTraversalTag) {
	for (; step > 0; --step) {
		++iterator;
	}
}

template< typename TIterator >
constexpr inline void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step, BidirectionalTraversalTag) {
	if (step >= 0) {
		for (; step > 0; --step) {
			++iterator;
		}
	} else {
		for (; step < 0; ++step) {
			--iterator;
		}
	}
}

template< typename TIterator >
constexpr inline void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step, RandomAccessTraversalTag) {
	iterator += step;
}

} // namespace Iterators
} // namespace _

inline namespace Iterators {

template< typename TIterator >
constexpr inline void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step) {
	_::Iterators::advance(iterator, step, IteratorTraits<TIterator>::iterator_category());
}

} // namespace Iterators

} // namespace BR