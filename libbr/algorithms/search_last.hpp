/**
 * @file
 * @brief search_last
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Searches for the last subsequence of elements \f$ [first_1, last_1) \f$ in the range \f$ [first_0, last_0) \f$.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first0,last0 The range of elements to examine.
 * @param first1,last1 The range of elements to search for.
 * @param predicate Binary predicate which returns ​<code>true</code> if the elements should be treated as equal.
 * @return Iterator to the beginning of last subsequence \f$ [first_1, last_1) \f$ in range \f$ [first_0, last_0) \f$.
 *         If \f$ [first_1, last_1) \f$ is empty or if no such subsequence is found, \p last0 is returned.
 */
template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
constexpr auto search_last(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1, TForwardIterator1 last1,
	TBinaryPredicate predicate
) -> TForwardIterator0;

/**
 * @brief Searches for the last subsequence of elements \f$ [first_1, last_1) \f$ in the range \f$ [first_0, last_0) \f$.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @param first0,last0 The range of elements to examine.
 * @param first1,last1 The range of elements to search for.
 * @return Iterator to the beginning of last subsequence \f$ [first_1, last_1) \f$ in range \f$ [first_0, last_0) \f$.
 *         If \f$ [first_1, last_1) \f$ is empty or if no such subsequence is found, \p last0 is returned.
 */
template< typename TForwardIterator0, typename TForwardIterator1 >
constexpr auto search_last(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1, TForwardIterator1 last1
) -> TForwardIterator0;

} // namespace Algorithms



namespace _::Algorithms {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
constexpr auto search_last(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate, ForwardTraversalTag, ForwardTraversalTag) -> TForwardIterator0 {
	auto result = last0;
	if (first1 == last1) {
		return result;
	}
	for (;;) {
		for (;;) {
			if (first0 == last0) {
				return result;
			}
			if (forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
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
			if (!forward<TBinaryPredicate>(predicate)(*m0, *m1)) {
				++first0;
				break;
			}
		}
	}
}

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1, typename TBinaryPredicate >
constexpr auto search_last(TBidirectionalIterator0 first0, TBidirectionalIterator0 last0, TBidirectionalIterator1 first1, TBidirectionalIterator1 last1, TBinaryPredicate && predicate, BidirectionalTraversalTag, BidirectionalTraversalTag) -> TBidirectionalIterator0 {
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
			if (forward<TBinaryPredicate>(predicate)(*--l0, *l1)) {
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
			if (!forward<TBinaryPredicate>(predicate)(*--m0, *--m1)) {
				break;
			}
		}
	}
}

template< typename TRandomAccessIterator0, typename TRandomAccessIterator1, typename TBinaryPredicate >
constexpr auto search_last(TRandomAccessIterator0 first0, TRandomAccessIterator0 last0, TRandomAccessIterator1 first1, TRandomAccessIterator1 last1, TBinaryPredicate && predicate, RandomAccessTraversalTag, RandomAccessTraversalTag) -> TRandomAccessIterator0 {
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
			if (forward<TBinaryPredicate>(predicate)(*--l0, *l1)) {
				break;
			}
		}
		auto m0 = l0;
		auto m1 = l1;
		for (;;) {
			if (m1 == first1) {
				return m0;
			}
			if (!forward<TBinaryPredicate>(predicate)(*--m0, *--m1)) {
				break;
			}
		}
	}
}

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
constexpr inline auto search_last(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate predicate) -> TForwardIterator0 {
	return search_last(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate), IteratorTraits<TForwardIterator0>::iterator_category(), IteratorTraits<TForwardIterator1>::iterator_category());
}

} // namespace _::Algorithms

inline namespace Algorithms {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
constexpr inline auto search_last(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate predicate) -> TForwardIterator0 {
	return _::Algorithms::search_last(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate));
}

template< typename TForwardIterator0, typename TForwardIterator1 >
constexpr inline auto search_last(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> TForwardIterator0 {
	return search_last(first0, last0, first1, last1, Equal<>{});
}

} // namespace Algorithm

} // namespace BR
