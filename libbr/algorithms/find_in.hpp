/**
 * @file
 * @brief find_in
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Searches the range \f$ [first_0, last_0) \f$ for any of the elements in the range \f$ [first_1, last_1) \f$.
 * @tparam TInputIterator Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TForwardIterator Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first0,last0 The range of elements to examine.
 * @param first1,last1 The range of elements to search for.
 * @param predicate Binary predicate which returns ​<code>true</code> if the elements should be treated as equal.
 * @return Iterator to the first element in the range \f$ [first_0, last_0) \f$ that is equal to an element from the range \f$ [first_1, last_1) \f$.
 *         If no such element is found, \p last0 is returned.
 */
template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
constexpr auto find_in(
	TInputIterator first0, TInputIterator last0,
	TForwardIterator first1, TForwardIterator last1,
	TBinaryPredicate && predicate
) -> TInputIterator;


/**
 * @brief Searches the range \f$ [first_0, last_0) \f$ for any of the elements in the range \f$ [first_1, last_1) \f$.
 * @tparam TInputIterator Type of \p first0 & \p last0 which satisfies \em InputIterator.
 * @tparam TForwardIterator Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @param first0,last0 The range of elements to examine.
 * @param first1,last1 The range of elements to search for.
 * @return Iterator to the first element in the range \f$ [first_0, last_0) \f$ that is equal to an element from the range \f$ [first_1, last_1) \f$.
 *         If no such element is found, \p last0 is returned.
 */
template< typename TInputIterator, typename TForwardIterator >
constexpr auto find_in(
	TInputIterator first0, TInputIterator last0,
	TForwardIterator first1, TForwardIterator last1
) -> TInputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
constexpr auto find_in(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1, TBinaryPredicate && predicate) -> TInputIterator {
	for (; first0 != last0; ++first0) {
		for (auto i = first1; i != last1; ++i) {
			if (forward<TBinaryPredicate>(predicate)(*first0, *i)) {
				return first0;
			}
		}
	}
	return last0;
}

template< typename TInputIterator, typename TForwardIterator >
constexpr inline auto find_in(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1) -> TInputIterator {
	return find_in(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithms

} // namespace BR
