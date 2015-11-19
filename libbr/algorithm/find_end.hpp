/**
 * @file
 * @brief find_end
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto find_end(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate predicate) -> TForwardIterator0;

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto find_end(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> TForwardIterator0 {
	return find_end(first0, last0, first1, last1, Equal<>());
}

namespace Detail {
namespace Algorithm {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto find_end(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate & predicate, ForwardTraversalTag, ForwardTraversalTag) -> TForwardIterator0 {
	auto result = last0;
	if (first1 == last1) {
		return result;
	}
	for (;;) {
		for (;;) {
			if (first0 == last0) {
				return result;
			}
			if (predicate(*first0, *first1)) {
				break;
			}
			++first0;
		}
		auto m0 = first0;
		auto m1 = first1;
		for (;;) {
			if (++m1 == last1) {
				result = first0;
				++first0;
				break;
			}
			if (++m0 == last0) {
				return result;
			}
			if (!predicate(*m0, *m1)) {
				++first0;
				break;
			}
		}
	}
};

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1, typename TBinaryPredicate >
auto find_end(TBidirectionalIterator0 first0, TBidirectionalIterator0 last0, TBidirectionalIterator1 first1, TBidirectionalIterator1 last1, TBinaryPredicate & predicate, BidirectionalTraversalTag, BidirectionalTraversalTag) -> TBidirectionalIterator0 {
	if (first1 == last1) {
		return last0;
	}
	auto l0 = last0;
	auto l1 = last1;
	for (--l1;;) {
		for (;;) {
			if (first0 == l0) {
				return last0;
			}
			if (pred(*--l0, *l1)) {
				break;
			}
		}
		auto m0 = l0;
		auto m1 = l1;
		for (;;) {
			if (m1 == first1) {
				return m0;
			}
			if (m0 == first0) {
				return last0;
			}
			if (!pred(*--m0, *--m1)) {
				break;
			}
		}
	}
}

template< typename TRandomAccessIterator0, typename TRandomAccessIterator1, typename TBinaryPredicate >
auto find_end(TRandomAccessIterator0 first0, TRandomAccessIterator0 last0, TRandomAccessIterator1 first1, TRandomAccessIterator1 last1, TBinaryPredicate & predicate, RandomAccessTraversalTag, RandomAccessTraversalTag) -> TRandomAccessIterator0 {
	auto length1 = last1 - first1;
	if (length1 == 0) {
		return last0;
	}
	auto length0 = last0 - first0;
	if (length0 < length1) {
		return last0;
	}
	auto const s = first0 + (length1 - 1);
	auto l0 = last0;
	auto l1 = last1;
	for (--l1;;) {
		for (;;) {
			if (s == l0) {
				return last0;
			}
			if (predicate(*--l0, *l1)) {
				break;
			}
		}
		auto m0 = l0;
		auto m1 = l1;
		for (;;) {
			if (m1 == first1) {
				return m0;
			}
			if (!predicate(*--m0, *--m1)) {
				break;
			}
		}
	}
}

} // namespace Algorithm
} // namespace Detail

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto find_end(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate predicate) -> TForwardIterator0 {
	return Detail::Algorithm::find_end(first0, last0, first1, last1, predicate, IteratorTraits<TForwardIterator0>::category(), IteratorTraits<TForwardIterator1>::category());
}

} // namespace BR
