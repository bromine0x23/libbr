#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

namespace Detail {
namespace Iterator {

template< typename TIterator >
inline void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step, IncrementableTraversalTag) {
	for (; step > 0; --step) {
		++iterator;
	}
}

template< typename TIterator >
inline void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step, BidirectionalTraversalTag) {
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
inline void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step, RandomAccessTraversalTag) {
	iterator += step;
}

} // namespace Iterator
} // namespace Detail

template< typename TIterator >
inline void advance(TIterator & iterator, typename IteratorTraits<TIterator>::Difference step) {
	Detail::Iterator::advance(iterator, step, IteratorTraits<TIterator>::category());
}

} // namespace BR