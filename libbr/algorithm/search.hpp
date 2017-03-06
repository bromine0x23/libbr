/**
 * @file
 * @brief search
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Searches for a range of elements.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param[in] first0,last0 The range of elements to examine.
 * @param[in] first1,last1 The range of elements to search for.
 * @param[in] predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @return Iterator to the beginning of first subsequence \f$ [first_1, last_1) \f$  in the range \f$  [first_0, last_0 - (last_1 - first_1)) \f$ .
 *         If no such subsequence is found, \p last is returned.
 *         If \f$ [first_1, last_1) \f$ is empty, first is returned.
 */
template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto search(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1, TForwardIterator1 last1,
	TBinaryPredicate && predicate
) -> TForwardIterator0;

/**
 * @brief Searches for a range of elements.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @param[in] first0,last0 The range of elements to examine.
 * @param[in] first1,last1 The range of elements to search for.
 * @return Iterator to the beginning of first subsequence \f$ [first_1, last_1) \f$  in the range \f$  [first_0, last_0 - (last_1 - first_1)) \f$ .
 *         If no such subsequence is found, \p last is returned.
 *         If \f$ [first_1, last_1) \f$ is empty, first is returned.
 */
template< typename TForwardIterator0, typename TForwardIterator1 >
auto search(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1, TForwardIterator1 last1
) -> TForwardIterator0;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto search(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate, ForwardTraversalTag, ForwardTraversalTag) -> TForwardIterator0 {
	if (first1 == last1) {
		return first0;
	}
	for (;;) {
		for (;; ++first0) {
			if (first0 == last0) {
				return last0;
			}
			if (forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
				break;
			}
		}
		auto i0 = first0;
		auto i1 = first1;
		for (;;) {
			if (++i1 == last1) {
				return first0;
			}
			if (++i0 == last0) {
				return last0;
			}
			if (!forward<TBinaryPredicate>(predicate)(*i0, *i1)) {
				++first0;
				break;
			}
		}
	}
}

template< typename TRandomAccessIterator0, typename TRandomAccessIterator1, typename TBinaryPredicate >
auto search(TRandomAccessIterator0 first0, TRandomAccessIterator0 last0, TRandomAccessIterator1 first1, TRandomAccessIterator1 last1, TBinaryPredicate && predicate, RandomAccessTraversalTag, RandomAccessTraversalTag) -> TRandomAccessIterator0 {
	auto const length1 = last1 - first1;
	if (length1 == 0) {
		return first0;
	}
	auto const length0 = last0 - first0;
	if (length0 < length1) {
		return last0;
	}
	for (auto const start = last0 - (length1 - 1);;) {
		for (;; ++first0) {
			if (first0 == start) {
				return last0;
			}
			if (forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
				break;
			}
		}
		auto i0 = first0;
		auto i1 = first1;
		for (;;) {
			if (++i1 == last1) {
				return first0;
			}
			++i0;
			if (!forward<TBinaryPredicate>(predicate)(*i0, *i1)) {
				++first0;
				break;
			}
		}
	}
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto search(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate) -> TForwardIterator0 {
	return Detail::Algorithm::search(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate), typename IteratorTraits<TForwardIterator0>::Category{}, typename IteratorTraits<TForwardIterator1>::Category{});
}

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto search(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> TForwardIterator0 {
	return search(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithm

} // namespace BR
