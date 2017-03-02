/**
 * @file
 * @brief count_if
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Counts elements for which predicate \p predicate returns <code>true</code>.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param first,last The range of elements to examine.
 * @param predicate Unary predicate which returns ​<code>true</code> for the required elements.
 * @return Number of elements that predicate \p predicate returns <code>true</code>.
 */
template< typename TInputIterator, typename TUnaryPredicate >
auto count_if(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> typename IteratorTraits<TInputIterator>::Difference;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryPredicate >
inline auto count_if(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> typename IteratorTraits<TInputIterator>::Difference {
	typename IteratorTraits<TInputIterator>::Difference result(0);
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			++result;
		}
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
