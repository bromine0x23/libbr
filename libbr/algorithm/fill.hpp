/**
 * @file
 * @brief fill
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

inline namespace Algorithm {

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

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

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

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TForwardIterator, typename TValue >
inline void fill(TForwardIterator first, TForwardIterator last, TValue const & value) {
	Detail::Algorithm::fill(first, last, value, typename IteratorTraits<TForwardIterator>::Category{});
}

} // namespace Algorithm

} // namespace BR
