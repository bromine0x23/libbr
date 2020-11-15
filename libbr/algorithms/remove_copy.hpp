/**
 * @file
 * @brief remove_copy
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithms {

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
constexpr auto remove_copy(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TValue const & value
) -> TOutputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TOutputIterator, typename TValue >
constexpr auto remove_copy(TInputIterator first, TInputIterator last, TOutputIterator output, TValue const & value) -> TOutputIterator {
	for (; first != last; ++first) {
		if (!(*first == value)) {
			*output = *first;
			++output;
		}
	}
	return output;
}

} // namespace Algorithms

} // namespace BR
