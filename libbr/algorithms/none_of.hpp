/**
 * @file
 * @brief none_of
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Checks if unary predicate \p predicate returns <code>true</code> for no elements in the range \f$ [first, last) \f$.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryPredicate Type of \p predicate
 * @param first,last The range of elements to examine.
 * @param predicate Unary predicate.
 * @retval true Unary predicate \p predicate returns <code>true</code> for no elements in the range.
 * @retval false Otherwise.
 */
template< typename TInputIterator, typename TUnaryPredicate >
constexpr auto none_of(
	TInputIterator first, TInputIterator last,
	TUnaryPredicate && predicate
) -> Boolean;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TUnaryPredicate >
constexpr inline auto none_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> Boolean {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			return false;
		}
	}
	return true;
}

} // namespace Algorithms

} // namespace BR
