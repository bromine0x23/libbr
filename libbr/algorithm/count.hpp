/**
 * @file
 * @brief count
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Counts the elements that are equal to \p value.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TValue Type of \p value.
 * @param first,last The range of elements to examine.
 * @param value The value to count for.
 * @return Number of elements that are equal to \p value.
 */
template< typename TInputIterator, typename TValue >
auto count(TInputIterator first, TInputIterator last, TValue const & value) -> typename IteratorTraits<TInputIterator>::Difference;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TValue >
inline auto count(TInputIterator first, TInputIterator last, TValue const & value) -> typename IteratorTraits<TInputIterator>::Difference {
	typename IteratorTraits<TInputIterator>::Difference result(0);
	for (; first != last; ++first) {
		if (*first == value) {
			++result;
		}
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
