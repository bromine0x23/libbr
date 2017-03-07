/**
 * @file
 * @brief construct_at
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Constructs an object at a given address.
 * @tparam TValue Type of element that \p pointer holds.
 * @param pointer A pointer to the object to be constructed.
 * @param arguments The arguments used for construct.
 */
template< typename TValue, typename... TArguments >
void construct_at(
	TValue * pointer,
	TArguments &&... arguments
);

} // namespace Memory



inline namespace Memory {

template< typename TValue, typename... TArguments >
inline void construct_at(TValue * pointer, TArguments &&... arguments) {
	::new(static_cast<void *>(pointer)) TValue(forward<TArguments>(arguments)...);
}

} // namespace Memory

} // namespace BR