/**
 * @file
 * @brief uninitialized_construct_n
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/construct_at.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Constructs objects in an uninitialized area of memory, defined by a start and a count.
 *
 * Constructs n objects of type typename IteratorTraits<TForwardIterator>::Element in the uninitialized storage starting at \p first using \p arguments.
 * @tparam TForwardIterator Type of \p first which satisfies \em ForwardIterator.
 * @param[in,out] first The range of the elements to initialize.
 * @param count The number of elements to initialize.
 * @param arguments The arguments used for construct.
 */
template< typename TForwardIterator, typename TSize, typename ... TArguments >
auto uninitialized_construct_n(
	TForwardIterator first,
	TSize count,
	TArguments &&... arguments
) -> TForwardIterator;

} // namespace Memory



inline namespace Memory {

template< typename TForwardIterator, typename TSize, typename ... TArguments >
inline auto uninitialized_construct_n(TForwardIterator first, TSize count, TArguments &&... arguments) -> TForwardIterator {
	auto current = first;
	BR_TRY {
		for (; count > 0; ++current, (void)--count) {
			construct_at(address_of(*current), forward<TArguments>(arguments)...);
		}
	} BR_CATCH(...) {
		destroy(first, current);
		BR_RETHROW;
	}
	return current;
}

} // namespace Memory

} // namespace BR