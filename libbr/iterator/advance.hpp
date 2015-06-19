#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

namespace Detail {
namespace Iterator {

template< typename TIterator >
inline void advance(TIterator & iterator, IteratorDifference< TIterator > step, InputIteratorTag) {
	for (; step > 0; --step) {
		++iterator;
	}
}

template< typename TIterator >
inline void advance(TIterator & iterator, IteratorDifference< TIterator > step, BidirectionalIteratorTag) {
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
inline void advance(TIterator & iterator, IteratorDifference< TIterator > step, RandomAccessIteratorTag) {
	iterator += step;
}

} // namespace Iterator
} // namespace Detail

template< typename TIterator >
inline void advance(TIterator & iterator, IteratorDifference< TIterator > step) {
	Detail::Iterator::advance(iterator, step, IteratorCategory< TIterator >());
}

} // namespace BR