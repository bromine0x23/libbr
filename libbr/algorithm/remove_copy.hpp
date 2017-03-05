/**
 * @file
 * @brief remove_copy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Copies a range of elements omitting those that equal to specific value.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of\p output which satisfies \em OutputIterator.
 * @tparam TValue Type of \p value.
 * @param[in] first,last The range of elements to copy.
 * @param[out] output The beginning of the destination range.
 * @param[in] value The value of the elements not to copy.
 * @return Iterator to the element past the last element copied.
 */
template< typename TInputIterator, typename TOutputIterator, typename TValue >
auto remove_copy(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TValue const & value
) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TValue >
auto remove_copy(TInputIterator first, TInputIterator last, TOutputIterator output, TValue const & value) -> TOutputIterator {
	for (; first != last; ++first) {
		if (!(*first == value)) {
			*output = *first;
			++output;
		}
	}
	return output;
}

} // namespace Algorithm

} // namespace BR
