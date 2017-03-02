/**
 * @file
 * @brief copy_n
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

inline namespace Algorithm {

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
inline auto copy_n(
	TInputIterator first, TSize count,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TSinglePassIterator, typename TSize, typename TOutputIterator >
auto copy_n(TSinglePassIterator first, TSize count, TOutputIterator output, SinglePassTraversalTag) -> TOutputIterator {
	if (count > 0) {
		*output = *first;
		++output;
		for (--count; count > 0; --count) {
			*output = *++first;
			++output;
		}
	}
	return output;
}

template< typename TRandomAccessIterator, typename TSize, typename TOutputIterator >
inline auto copy_n(TRandomAccessIterator first, TSize count, TOutputIterator output, RandomAccessTraversalTag) -> TOutputIterator {
	using BR::copy;
	return copy(first, first + count, output);
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TInputIterator, typename TSize, typename TOutputIterator >
auto copy_n(TInputIterator first, TSize count, TOutputIterator output) -> TOutputIterator {
	return Detail::Algorithm::copy_n(first, count, output, typename IteratorTraits<TInputIterator>::Category{});
}

} // namespace Algorithm

} // namespace BR
