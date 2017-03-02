/**
 * @file
 * @brief accumulate
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/plus.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Sums up a range of elements.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TValue Type of \p initial
 * @tparam TBinaryFunctor Type of \p functor.
 * @param first,last The range of elements to sum.
 * @param initial Initial value of the sum.
 * @param functor Binary operation function object that will be applied.
 * @return
 */
template< typename TInputIterator, typename TValue, typename TBinaryFunctor >
auto accumulate(
	TInputIterator first, TInputIterator last,
	TValue initial,
	TBinaryFunctor && functor
) -> TValue;

/**
 * @brief Sums up a range of elements.
 * @tparam TInputIterator Type of \p first & \p last which satisfies InputIterator.
 * @tparam TValue Type of \p initial
 * @param first,last The range of elements to sum.
 * @param init Initial value of the sum.
 * @return
 */
template< typename TInputIterator, typename TValue >
auto accumulate(
	TInputIterator first, TInputIterator last,
	TValue initial
) -> TValue;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TValue, typename TBinaryFunctor >
inline auto accumulate(TInputIterator first, TInputIterator last, TValue initial, TBinaryFunctor && functor) -> TValue {
	for (; first != last; ++first) {
		initial = forward<TBinaryFunctor>(functor)(initial, *first);
	}
	return initial;
}

template< typename TInputIterator, typename TValue >
inline auto accumulate(TInputIterator first, TInputIterator last, TValue initial) -> TValue {
	return accumulate(first, last, initial, Plus<>());
}

} // namespace Algorithm

} // namespace BR