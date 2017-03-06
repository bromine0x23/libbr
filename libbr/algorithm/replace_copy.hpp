/**
 * @file
 * @brief replace_copy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Copies a range, replacing elements that equal to specific value with another value.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of output which satisfies \em OutputIterator.
 * @tparam TValue Type of \p old_value & \p new_value.
 * @param[in] first,last The range of elements to copy.
 * @param[out] output The beginning of the destination range.
 * @param[in] old_value The value of elements to replace.
 * @param[in] new_value The value to use as replacement.
 * @return Iterator to the element past the last element copied.
 */
template< typename TInputIterator, typename TOutputIterator, typename TValue >
auto replace_copy(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TValue const & old_value,
	TValue const & new_value
) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TValue >
inline auto replace_copy(TInputIterator first, TInputIterator last, TOutputIterator output, TValue const & old_value, TValue const & new_value) -> TOutputIterator {
	for (; first != last; ++first, (void) ++output) {
		*output = (*first == old_value) ? new_value : *first;
	}
	return output;
}

} // namespace Algorithm

} // namespace BR
