#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

namespace Detail {
namespace Iterator {

template< typename TIterator >
inline IteratorDifference< TIterator > distance(TIterator & head, TIterator & tail, RandomAccessIteratorTag) {
	return tail - head;
}

template< typename TIterator >
inline IteratorDifference< TIterator > distance(TIterator & head, TIterator & tail, InputIteratorTag) {
	IteratorDifference< TIterator > result(0);
	for (; head != tail; ++head) {
		++result;
	}
	return result;
}

} // namespace Iterator
} // namespace Detail

template< typename TIterator >
inline IteratorDifference< TIterator > distance(TIterator & head, TIterator & tail) {
	Detail::Iterator::distance(head, tail, IteratorCategory< TIterator >());
}

} // namespace BR