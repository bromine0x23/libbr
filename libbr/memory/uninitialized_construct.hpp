/**
 * @file
 * @brief uninitialized_construct
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
 * @brief Constructs objects in an uninitialized area of memory, defined by a range.
 *
 * Constructs objects of type typename IteratorTraits<TForwardIterator>::Element in the uninitialized storage designated by the range \f$ [first, last) \f$ using \p arguments.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param[in,out] first,last The range of the elements to initialize.
 * @param arguments The arguments used for construct.
 */
template< typename TForwardIterator, typename ... TArguments >
void uninitialized_construct(
	TForwardIterator first, TForwardIterator last,
	TArguments &&... arguments
);

} // namespace Memory



inline namespace Memory {

template< typename TForwardIterator, typename ... TArguments >
inline void uninitialized_construct(TForwardIterator first, TForwardIterator last, TArguments &&... arguments) {
	auto current = first;
	BR_TRY {
		for (; current != last; ++current) {
			construct_at(address_of(*current), forward<TArguments>(arguments)...);
		}
	} BR_CATCH(...) {
		destroy(first, current);
		BR_RETHROW;
	}
}

} // namespace Memory

} // namespace BR