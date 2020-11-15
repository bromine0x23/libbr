/**
 * @file
 * @brief replace_copy_if
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Copies a range, replacing elements satisfying specific criteria with another value.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of output which satisfies \em OutputIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @tparam TValue Type of \p new_value.
 * @param[in] first,last The range of elements to copy.
 * @param[out] output The beginning of the destination range.
 * @param[in] predicate Unary predicate which returns <code>true</code> if the element value should be replaced.
 * @param[in] new_value The value to use as replacement.
 * @return Iterator to the element past the last element copied.
 */
template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate, typename TValue >
constexpr auto replace_copy_if(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TUnaryPredicate && predicate,
	TValue const & new_value
) -> TOutputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate, typename TValue >
constexpr inline auto replace_copy_if(TInputIterator first, TInputIterator last, TOutputIterator output, TUnaryPredicate && predicate, TValue const & new_value) -> TOutputIterator {
	for (; first != last; ++first, (void) ++output) {
		*output = forward<TUnaryPredicate>(predicate)(*first) ? new_value : *first;
	}
	return output;
}

} // namespace Algorithms

} // namespace BR
