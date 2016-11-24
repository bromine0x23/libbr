/**
 * @file
 * @brief fill
 * @author Bromine0x23
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
 * @brief like std::fill
 * @tparam TForwardIterator
 * @tparam TValue
 * @param[in,out] first,last
 * @param[in] value
 */
template< typename TForwardIterator, typename TValue >
void fill(TForwardIterator first, TForwardIterator last, TValue const & value);

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
