/**
 * @file
 * @brief remove_copy_if
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Copies a range of elements omitting those that satisfy specific criteria.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of\p output which satisfies \em OutputIterator.
 * @tparam TUnaryPredicate Type of \p predicate
 * @param[in] first,last The range of elements to copy.
 * @param[out] output The beginning of the destination range.
 * @param[in] predicate Unary predicate which returns ​<code>true</code> for the omitted elements.
 * @return Iterator to the element past the last element copied.
 */
template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
constexpr auto remove_copy_if(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TUnaryPredicate && predicate
) -> TOutputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
constexpr auto remove_copy_if(TInputIterator first, TInputIterator last, TOutputIterator output, TUnaryPredicate && predicate) -> TOutputIterator {
	for (; first != last; ++first) {
		if (!forward<TUnaryPredicate>(predicate)(*first)) {
			*output = *first;
			++output;
		}
	}
	return output;
}

} // namespace Algorithms

} // namespace BR
