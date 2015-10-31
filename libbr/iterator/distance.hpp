#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

namespace Detail {
namespace Iterator {

template< typename TIterator >
inline auto distance(TIterator head, TIterator tail, InputIteratorTag _dummy) -> typename IteratorTraits<TIterator>::Difference {
	typename IteratorTraits<TIterator>::Difference result(0);
	for (; head != tail; ++head) {
		++result;
	}
	return result;
}

template< typename TIterator >
inline auto distance(TIterator head, TIterator tail, RandomAccessIteratorTag _dummy) -> typename IteratorTraits<TIterator>::Difference {
	return tail - head;
}

} // namespace Iterator
} // namespace Detail

template< typename TIterator >
inline auto distance(TIterator head, TIterator tail) -> typename IteratorTraits<TIterator>::Difference {
	return Detail::Iterator::distance(head, tail, IteratorTraits<TIterator>::category());
}

} // namespace BR