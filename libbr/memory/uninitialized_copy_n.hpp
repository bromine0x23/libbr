/**
 * @file
 * @brief uninitialized_copy_n
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy_n.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/construct_at.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/memory/uninitialized_copy.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Copies a number of objects to an uninitialized area of memory.
 *
 * Copies count elements from a range beginning at \p first to an uninitialized memory area beginning at \p output.
 * @tparam TInputIterator Type of \p first which satisfies \em InputIterator.
 * @tparam TSize Type of \p count.
 * @tparam TForwardIterator Type of \p output which satisfies \em ForwardIterator.
 * @param[in] first The beginning of the range of the elements to copy.
 * @param count Number of the elements to copy.
 * @param[out] result The beginning of the destination range.
 * @return Iterator to the element past the last element copied.
 */
template< typename TInputIterator, typename TSize, typename TForwardIterator >
inline auto uninitialized_copy_n(
	TInputIterator first,
	TSize count,
	TForwardIterator result
) -> TForwardIterator;

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TInputIterator, typename TSize, typename TForwardIterator >
auto uninitialized_copy_n(TInputIterator first, TSize count, TForwardIterator output, SinglePassTraversalTag) -> TForwardIterator {
	using BR::destroy;
	auto start = output;
	BR_TRY {
		for (; count > 0; ++first, (void)++output, --count) {
			construct_at(address_of(*output), *first);
		}
	} BR_CATCH(...) {
		destroy(start, output);
		BR_RETHROW;
	}
	return output;
}

template< typename TRandomAccessIterator, typename TSize, typename TForwardIterator >
inline auto uninitialized_copy_n(TRandomAccessIterator first, TSize count, TForwardIterator output, RandomAccessTraversalTag) -> TForwardIterator {
	using BR::uninitialized_copy;
	return uninitialized_copy(first, first + count, output);
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TInputIterator, typename TSize, typename TForwardIterator >
inline auto uninitialized_copy_n(TInputIterator first, TSize count, TForwardIterator output) -> TForwardIterator {
	return Detail::Memory::uninitialized_copy_n(first, count, output, typename IteratorTraits<TInputIterator>::Category {});
}

} // namespace Memory

} // namespace BR