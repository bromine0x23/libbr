/**
 * @file
 * @brief count_if
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Counts elements for which predicate \p predicate returns <code>true</code>.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param first,last The range of elements to examine.
 * @param predicate Unary predicate which returns ​<code>true</code> for the required elements.
 * @return Number of elements that predicate \p predicate returns <code>true</code>.
 */
template< typename TInputIterator, typename TUnaryPredicate >
constexpr auto count_if(
	TInputIterator first,
	TInputIterator last,
	TUnaryPredicate && predicate
) -> typename IteratorTraits<TInputIterator>::Difference;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TUnaryPredicate >
constexpr inline auto count_if(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> typename IteratorTraits<TInputIterator>::Difference {
	typename IteratorTraits<TInputIterator>::Difference result(0);
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			++result;
		}
	}
	return result;
}

} // namespace Algorithms

} // namespace BR
