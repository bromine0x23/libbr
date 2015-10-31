/**
 * @file
 * @brief 等于比较
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TBinaryPredicate & predicate, InputIteratorTag _dummy0, InputIteratorTag _dummy1) -> bool {
	for (; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		if (!predicate(*first0, *first1)) {
			return false;
		}
	}
	return first0 == last0 && first1 == last1;
}

template< typename TRandomAccessIterator0, typename TRandomAccessIterator1, typename TBinaryPredicate >
inline auto equal(TRandomAccessIterator0 first0, TRandomAccessIterator0 last0, TRandomAccessIterator1 first1, TRandomAccessIterator1 last1, TBinaryPredicate & predicate, RandomAccessIteratorTag _dummy0, RandomAccessIteratorTag _dummy1) -> bool {
	if (distance(first0, last0) != distance(first1, last1)) {
		return false;
	}
	return equal(first0, last0, first1, last1, predicate, InputIteratorTag(), InputIteratorTag());
}

} // namespace Algorithm
} // namespace Detail

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TBinaryPredicate && predicate) -> bool {
	for (; first0 != last0; ++first0, (void)++first1) {
		if (!predicate(*first0, *first1)) {
			return false;
		}
	}
	return true;
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1) -> bool {
	return equal(first0, last0, first1, Equal<>());
}

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TBinaryPredicate && predicate) -> bool {
	return Detail::Algorithm::equal(first0, last0, first1, last1, predicate, IteratorTraits<TInputIterator0>::category(), IteratorTraits<TInputIterator1>::category());
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> bool {
	return Detail::Algorithm::equal(first0, last0, first1, last1, Equal<>(), IteratorTraits<TInputIterator0>::category(), IteratorTraits<TInputIterator1>::category());
}

} // namespace BR
