/**
 * @file
 * @brief find_if
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Searches for an element for which predicate \p predicate returns <code>true</code>.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryPredicate Type of \p predicate
 * @param first,last The range of elements to examine.
 * @param predicate Unary predicate which returns <code>true</code> for the required element.
 * @return Iterator to the first element that predicate \p predicate returns <code>true</code>
 *         or \p last if no such element is found.
 */
template< typename TInputIterator, typename TUnaryPredicate >
constexpr auto find_if(
	TInputIterator first, TInputIterator last,
	TUnaryPredicate && predicate
) -> TInputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TUnaryPredicate >
constexpr inline auto find_if(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> TInputIterator {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			break;
		}
	}
	return first;
}

} // namespace Algorithms

} // namespace BR
