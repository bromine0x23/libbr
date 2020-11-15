/**
 * @file
 * @brief allocator_construct
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/has_member_function.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Constructs an object in the allocated storage.
 * @tparam TAllocator Type of \p allocator.
 * @tparam TValue Type of element that \p pointer holds.
 * @tparam TArguments Type of \p arguments.
 * @param allocator Allocator to use for construction.
 * @param pointer Pointer to allocated uninitialized storage.
 * @param arguments The constructor arguments to use
 */
template<typename TAllocator, typename TValue, typename ... TArguments>
void allocator_construct(
	TAllocator & allocator,
	TValue * pointer,
	TArguments && ... arguments
);

} // namespace Memory



namespace _::Memory {

BR_HAS_MEMBER_FUNCTION(construct)

template<typename TAllocator, typename TValue, typename... TArguments>
inline void allocator_construct(BooleanTrue, TAllocator & allocator, TValue * pointer, TArguments &&... arguments) {
	allocator.construct(pointer, forward<TArguments>(arguments)...);
}

template<typename TAllocator, typename TValue, typename... TArguments>
inline void allocator_construct(BooleanFalse, TAllocator & allocator, TValue * pointer, TArguments &&... arguments) {
	::new(static_cast<void *>(pointer)) TValue(forward<TArguments>(arguments)...);
}

template<typename TAllocator, typename TValue, typename... TArguments>
inline void allocator_construct(TAllocator & allocator, TValue * pointer, TArguments &&... arguments) {
	allocator_construct(HasMemberFunction_construct<TAllocator, TValue *, TArguments...>{}, allocator, pointer, forward<TArguments>(arguments)...);
}

} // namespace _::Memory

inline namespace Memory {

template<typename TAllocator, typename TValue, typename... TArguments>
inline void allocator_construct(TAllocator & allocator, TValue * pointer, TArguments &&... arguments) {
	_::Memory::allocator_construct(allocator, pointer, forward<TArguments>(arguments)...);
}

} // namespace Memory

} // namespace BR