/**
 * @file
 * @brief count
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/iterator_traits.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Counts the elements that are equal to \p value.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TValue Type of \p value.
 * @param first,last The range of elements to examine.
 * @param value The value to count for.
 * @return Number of elements that are equal to \p value.
 */
template< typename TInputIterator, typename TValue >
constexpr auto count(
	TInputIterator first, TInputIterator last,
	TValue const & value
) -> typename IteratorTraits<TInputIterator>::Difference;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TValue >
constexpr inline auto count(TInputIterator first, TInputIterator last, TValue const & value) -> typename IteratorTraits<TInputIterator>::Difference {
	auto result = typename IteratorTraits<TInputIterator>::Difference(0);
	for (; first != last; ++first) {
		if (*first == value) {
			++result;
		}
	}
	return result;
}

} // namespace Algorithms

} // namespace BR
