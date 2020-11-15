/**
 * @file
 * @brief copy_n
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/copy.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Copies a number of elements to a new location.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TSize Type of \p count.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @param[in] first The beginning of the range of elements to copy from.
 * @param[in] count Number of the elements to copy.
 * @param[out] output The beginning of the destination range.
 * @return Iterator in the destination range, pointing past the last element copied if \f$ count > 0 \f$ or \p output otherwise.
 */
template< typename TInputIterator, typename TSize, typename TOutputIterator >
constexpr inline auto copy_n(
	TInputIterator first, TSize count,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithms



namespace _::Algorithms {

template< typename TSinglePassIterator, typename TSize, typename TOutputIterator >
constexpr inline auto copy_n(TSinglePassIterator first, TSize count, TOutputIterator output, SinglePassTraversalTag) -> TOutputIterator {
	if (count > 0) {
		*output = *first;
		++output;
		for (--count; count > 0; --count) {
			++first;
			*output = *first;
			++output;
		}
	}
	return output;
}

template< typename TRandomAccessIterator, typename TSize, typename TOutputIterator >
constexpr inline auto copy_n(TRandomAccessIterator first, TSize count, TOutputIterator output, RandomAccessTraversalTag) -> TOutputIterator {
	return copy(first, first + count, output);
}

template< typename TInputIterator, typename TSize, typename TOutputIterator >
constexpr inline auto copy_n(TInputIterator first, TSize count, TOutputIterator output) -> TOutputIterator {
	return copy_n(first, count, output, IteratorTraits<TInputIterator>::iterator_category());
}

} // namespace _::Algorithms

inline namespace Algorithms {

template< typename TInputIterator, typename TSize, typename TOutputIterator >
constexpr inline auto copy_n(TInputIterator first, TSize count, TOutputIterator output) -> TOutputIterator {
	return _::Algorithms::copy_n(first, count, output);
}

} // namespace Algorithms

} // namespace BR
