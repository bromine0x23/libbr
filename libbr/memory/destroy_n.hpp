/**
 * @file
 * @brief destroy_n
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/memory/destroy_at.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Destroys a number of objects in a range.
 * @tparam TForwardIterator Type of \p first which satisfies \em ForwardIterator.
 * @tparam TSize Type of \p count.
 * @param first The beginning of the range of elements to destroy.
 * @param count The number of elements to destroy.
 */
template< typename TForwardIterator, typename TSize >
void destroy_n(
	TForwardIterator first,
	TSize count
);

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TForwardIterator, typename TSize >
inline void destroy_n(TForwardIterator first, TSize count, SinglePassTraversalTag) {
	for (; count > 0; ++first, (void)--count) {
		destroy_at(address_of(*first));
	}
}

template< typename TForwardIterator, typename TSize >
inline void destroy_n(TForwardIterator first, TSize count, RandomAccessTraversalTag) {
	using BR::destroy;
	destroy(first, first + count);
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TForwardIterator, typename TSize >
inline void destroy_n(TForwardIterator first, TSize count) {
	return Detail::Memory::destroy_n(first, count, typename IteratorTraits<TForwardIterator>::Category{});
}

} // namespace Memory

} // namespace BR