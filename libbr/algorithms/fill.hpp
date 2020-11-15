/**
 * @file
 * @brief fill
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/fill_n.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Copy-assigns the given value to every element in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value
 * @param[in,out] first,last The range of elements to modify.
 * @param[in] value the value to be assigned.
 */
template< typename TForwardIterator, typename TValue >
void fill(
	TForwardIterator first, TForwardIterator last,
	TValue const & value
);

} // namespace Algorithms



namespace _::Algorithms {

template< typename TForwardIterator, typename TValue >
inline void fill(TForwardIterator first, TForwardIterator last, TValue const & value, ForwardTraversalTag) {
	for (; first != last; ++first) {
		*first = value;
	}
}

template< typename TRandomAccessIterator, typename TValue >
inline void fill(TRandomAccessIterator first, TRandomAccessIterator last, TValue const & value, RandomAccessTraversalTag) {
	fill_n(first, last - first, value);
}

template< typename TForwardIterator, typename TValue >
inline void fill(TForwardIterator first, TForwardIterator last, TValue const & value) {
	fill(first, last, value, IteratorTraits<TForwardIterator>::iterator_category());
}

} // namespace _::Algorithms

inline namespace Algorithms {

template< typename TForwardIterator, typename TValue >
inline void fill(TForwardIterator first, TForwardIterator last, TValue const & value) {
	_::Algorithms::fill(first, last, value);
}

} // namespace Algorithms

} // namespace BR
