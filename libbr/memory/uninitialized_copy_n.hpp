/**
 * @file
 * @brief uninitialized_copy_n
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy_n.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/uninitialized_copy.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

inline namespace Memory {

/**
 * @tparam TInputIterator
 * @tparam TSize
 * @tparam TForwardIterator
 * @param[in] first
 * @param n
 * @param[out] result
 * @return
 */
template< typename TInputIterator, typename TSize, typename TForwardIterator >
inline auto uninitialized_copy_n(TInputIterator first, TSize n, TForwardIterator result) -> TForwardIterator;

} // namespace Memory


namespace Detail {
namespace Memory {


template< typename TInputIterator, typename TSize, typename TForwardIterator >
auto uninitialized_copy_n(TInputIterator first, TSize n, TForwardIterator result, SinglePassTraversalTag) -> TForwardIterator {
	using Element = typename IteratorTraits<TForwardIterator>::Element;
	auto start = result;
#if !defined(BR_NO_EXCEPTIONS)
	try {
#endif
		for (; n > 0; ++first, (void)++result, --n) {
			new(address_of(result)) Element(*first);
		}
#if !defined(BR_NO_EXCEPTIONS)
	} catch (...) {
		for (; start != result; ++start) {
			start->~Element();
		}
		throw;
	}
#endif
	return result;
};

template< typename TInputIterator, typename TSize, typename TForwardIterator >
auto uninitialized_copy_n(TInputIterator first, TSize n, TForwardIterator result, RandomAccessTraversalTag) -> TForwardIterator {
	return uninitialized_copy(first, first + n, result);
}

template< typename TInputIterator, typename TSize, typename TForwardIterator >
auto uninitialized_copy_n(TInputIterator first, TSize n, TForwardIterator result) -> TForwardIterator {
	return uninitialized_copy_n(first, n, result, typename IteratorTraits<TInputIterator>::Category {});
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TInputIterator, typename TSize, typename TForwardIterator >
auto uninitialized_copy_n(TInputIterator first, TSize n, TForwardIterator result) -> TForwardIterator {
	return Detail::Memory::uninitialized_copy_n(first, n, result);
}

} // namespace Memory

} // namespace BR