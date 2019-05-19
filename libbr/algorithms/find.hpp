/**
 * @file
 * @brief find
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Searches for an element equal to \p value.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TValue Type of \p value
 * @param first,last The range of elements to examine.
 * @param value Value to compare the elements to.
 * @return Iterator to the first element equal to \p value
 *         or last if no such element is found.
 */
template< typename TInputIterator, typename TValue >
constexpr auto find(
	TInputIterator first, TInputIterator last,
	TValue const & value
) -> TInputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TValue >
constexpr inline auto find(TInputIterator first, TInputIterator last, TValue const & value) -> TInputIterator {
	for (; first != last; ++first) {
		if (*first == value) {
			break;
		}
	}
	return first;
}

} // namespace Algorithms

} // namespace BR
