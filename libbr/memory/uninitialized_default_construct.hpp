/**
 * @file
 * @brief uninitialized_default_construct
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/default_construct_at.hpp>
#include <libbr/memory/destroy.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Constructs objects by default-initialization in an uninitialized area of memory, defined by a range.
 *
 * Constructs objects of type typename IteratorTraits<TForwardIterator>::Element in the uninitialized storage designated by the range \f$ [first, last) \f$ by default-initialization.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param[in,out] first,last The range of the elements to initialize.
 */
template< typename TForwardIterator >
void uninitialized_default_construct(
	TForwardIterator first, TForwardIterator last
);

} // namespace Memory



inline namespace Memory {

template< typename TForwardIterator >
inline void uninitialized_default_construct(TForwardIterator first, TForwardIterator last) {
	auto current = first;
	BR_TRY {
		for (; current != last; ++current) {
			default_construct_at(address_of(*current));
		}
	} BR_CATCH(...) {
		destroy(first, current);
		BR_RETHROW;
	}
}

} // namespace Memory

} // namespace BR