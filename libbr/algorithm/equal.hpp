/**
 * @file
 * @brief equal
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Determines if two sets of elements are the same.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 which satisfies \em InputIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first0,last0 The first range of the elements to compare.
 * @param first1 The beginning of the second range.
 * @param predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @retval true the range \f$ [first1, last1) \f$ is equal to the range \f$ [first2, first2 + (last1 - first1)) \f$.
 * @retval false Otherwise.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
auto equal(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1,
	TBinaryPredicate && predicate
) -> Boolean;

/**
 * @brief Determines if two sets of elements are the same.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 which satisfies \em InputIterator.
 * @param first0,last0 The first range of the elements to compare.
 * @param first1 The beginning of the second range.
 * @retval true the range \f$ [first1, last1) \f$ is equal to the range \f$ [first2, first2 + (last1 - first1)) \f$.
 * @retval false Otherwise.
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto equal(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1
) -> Boolean;

/**
 * @brief Determines if two sets of elements are the same.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em InputIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first0,last0 The first range of the elements to compare.
 * @param first1,last1 The second range of the elements to compare.
 * @param predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @retval true the range \f$ [first1, last1) \f$ is equal to the range \f$ [first2, last2) \f$.
 * @retval false Otherwise.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
auto equal(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TBinaryPredicate && predicate
) -> Boolean;

/**
 * @brief Determines if two sets of elements are the same.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em InputIterator.
 * @param first0,last0 The first range of the elements to compare.
 * @param first1,last1 The second range of the elements to compare.
 * @retval true the range \f$ [first1, last1) \f$ is equal to the range \f$ [first2, last2) \f$.
 * @retval false Otherwise.
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto equal(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1
) -> Boolean;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TSinglePassIterator0, typename TSinglePassIterator1, typename TBinaryPredicate >
inline auto equal(TSinglePassIterator0 first0, TSinglePassIterator0 last0, TSinglePassIterator1 first1, TSinglePassIterator1 last1, TBinaryPredicate && predicate, SinglePassTraversalTag, SinglePassTraversalTag) -> Boolean {
	for (; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
			return false;
		}
	}
	return first0 == last0 && first1 == last1;
}

template< typename TRandomAccessIterator0, typename TRandomAccessIterator1, typename TBinaryPredicate >
inline auto equal(TRandomAccessIterator0 first0, TRandomAccessIterator0 last0, TRandomAccessIterator1 first1, TRandomAccessIterator1 last1, TBinaryPredicate && predicate, RandomAccessTraversalTag, RandomAccessTraversalTag) -> Boolean {
	if (distance(first0, last0) != distance(first1, last1)) {
		return false;
	}
	return equal(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate), SinglePassTraversalTag(), SinglePassTraversalTag());
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TBinaryPredicate && predicate) -> Boolean {
	for (; first0 != last0; ++first0, (void)++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
			return false;
		}
	}
	return true;
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1) -> Boolean {
	return equal(first0, last0, first1, Equal<>());
}

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TBinaryPredicate && predicate) -> Boolean {
	return Detail::Algorithm::equal(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate), IteratorTraits<TInputIterator0>::category(), IteratorTraits<TInputIterator1>::category());
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> Boolean {
	return equal(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithm

} // namespace BR
