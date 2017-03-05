/**
 * @file
 * @brief shuffle
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/random/uniform_int_distribution.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>
#include <random>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Randomly re-orders elements in a range.
 * @tparam TRandomAccessIterator Type of \p first & \p last which satisfies \em RandomAccessIterator.
 * @tparam TUniformRandomBitGenerator Type of \p generator
 * @param[in,out] first,last The range of elements to shuffle randomly.
 * @param[in] generator a UniformRandomBitGenerator whose result type is convertible to IteratorTraits<TRandomAccessIterator>::Difference.
 */
template< typename TRandomAccessIterator, typename TUniformRandomBitGenerator >
void shuffle(
	TRandomAccessIterator first, TRandomAccessIterator last,
	TUniformRandomBitGenerator && generator
);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TUniformRandomBitGenerator >
void shuffle(TRandomAccessIterator first, TRandomAccessIterator last, TUniformRandomBitGenerator && generator) {
	using Difference = typename IteratorTraits<TRandomAccessIterator>::Difference;
	using Distribution = UniformIntDistribution<PointerDifference>;
	using Parameter = Distribution::Parameter;
	auto length = last - first;
	if (length > 1) {
		Distribution distribution;
		for (--last, --length; first < last; ++first, --length) {
			Difference index = distribution(forward<TUniformRandomBitGenerator>(generator), Parameter(0, length));
			if (index != Difference(0)) {
				swap(*first, *(first + index));
			}
		}
	}
}

} // namespace Algorithm


} // namespace BR
