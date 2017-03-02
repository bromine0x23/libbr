/**
 * @file
 * @brief find_if_not
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Searches for an element for which predicate \p predicate returns <code>false</code>.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryPredicate Type of \p predicate
 * @param first,last The range of elements to examine.
 * @param predicate Unary predicate which returns <code>false</code> for the required element.
 * @return Iterator to the first element that predicate \p predicate returns <code>false</code>
 *         or \p last if no such element is found.
 */
template< typename TInputIterator, typename TUnaryPredicate >
auto find_if_not(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> TInputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryPredicate >
inline auto find_if_not(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> TInputIterator {
	for (; first != last; ++first) {
		if (!forward<TUnaryPredicate>(predicate)(*first)) {
			break;
		}
	}
	return first;
}

} // namespace Algorithm

} // namespace BR
