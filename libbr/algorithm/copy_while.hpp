/**
 * @file
 * @brief copy_while
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Copies the elements until the predicate \p predicate returns <code>false</code>.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param[in] first,last The range of elements to copy.
 * @param[out] output The beginning of the destination range.
 * @param[in] predicate Unary predicate which returns ​<code>false</code> for ternimate copy.
 * @return Output iterator to the element in the destination range, one past the last element copied.
 */
template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
auto copy_while(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TUnaryPredicate && predicate
) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
inline auto copy_while(TInputIterator first, TInputIterator last, TOutputIterator output, TUnaryPredicate && predicate) -> TOutputIterator {
	for (; first != last && forward<TUnaryPredicate>(predicate)(*first); ++output, (void)++first) {
		*output = *first;
	}
	return output;
}

} // namespace Algorithm

} // namespace BR
