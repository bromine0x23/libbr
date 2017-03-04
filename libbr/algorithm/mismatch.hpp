/**
 * @file
 * @brief mismatch
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Finds the first position where two ranges differ.
 *
 * Returns the first mismatching pair of elements from two ranges: one defined by \f$ [first_0, last_0) \f$ and another defined by \f$ [first_1, first1_ + (last_0 - first_0)) \f$.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 which satisfies \em InputIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first0,last0 The first range of the elements.
 * @param first1 The beginning of the second range of the elements.
 * @param predicate Binary predicate which returns ​<code>true</code> if the elements should be treated as equal.
 * @return Pair<TInputIterator0, TInputIterator1> with iterators to the first two non-equivalent elements.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
auto mismatch(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1,
	TBinaryPredicate && predicate
) -> Pair< TInputIterator0, TInputIterator1 >;

/**
 * @brief Finds the first position where two ranges differ.
 *
 * Returns the first mismatching pair of elements from two ranges: one defined by \f$ [first_0, last_0) \f$ and another defined by \f$ [first_1, first1_ + (last_0 - first_0)) \f$.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 which satisfies \em InputIterator.
 * @param first0,last0 The first range of the elements.
 * @param first1 The beginning of the second range of the elements.
 * @return Pair<TInputIterator0, TInputIterator1> with iterators to the first two non-equivalent elements.
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto mismatch(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1
) -> Pair< TInputIterator0, TInputIterator1 >;

/**
 * @brief Finds the first position where two ranges differ.
 *
 * Returns the first mismatching pair of elements from two ranges: one defined by \f$ [first_0, last_0) \f$ and another defined by \f$ [first_1, last_1) \f$.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em InputIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first0,last0 The first range of the elements.
 * @param first1,last1 The second range of the elements.
 * @param predicate Binary predicate which returns ​<code>true</code> if the elements should be treated as equal.
 * @return Pair<TInputIterator0, TInputIterator1> with iterators to the first two non-equivalent elements.
 */
template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
auto mismatch(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1,
	TBinaryPredicate && predicate
) -> Pair< TInputIterator0, TInputIterator1 >;

/**
 * @brief Finds the first position where two ranges differ.
 *
 * Returns the first mismatching pair of elements from two ranges: one defined by \f$ [first_0, last_0) \f$ and another defined by \f$ [first_1, last_1) \f$.
 * @tparam TInputIterator0 Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TInputIterator1 Type of \p first1 & \p last1 which satisfies \em InputIterator.
 * @param first0,last0 The first range of the elements.
 * @param first1,last1 The second range of the elements.
 * @return Pair<TInputIterator0, TInputIterator1> with iterators to the first two non-equivalent elements.
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto mismatch(
	TInputIterator0 first0, TInputIterator0 last0,
	TInputIterator1 first1, TInputIterator1 last1
) -> Pair< TInputIterator0, TInputIterator1 >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TBinaryPredicate && predicate) -> Pair< TInputIterator0, TInputIterator1 > {
	for (; first0 != last0; ++first0, (void) ++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
			break;
		}
	}
	return make_pair(first0, first1);
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1) -> Pair< TInputIterator0, TInputIterator1 > {
	return mismatch(first0, last0, first1, Equal<void>());
}

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TBinaryPredicate && predicate) -> Pair< TInputIterator0, TInputIterator1 > {
	for (; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
			break;
		}
	}
	return make_pair(first0, first1);
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> Pair< TInputIterator0, TInputIterator1 > {
	return mismatch(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithm

} // namespace BR
