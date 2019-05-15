/**
 * @file
 * @brief allocator_destroy
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/has_member_function.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Destructs an object stored in the allocated storage.
 * @tparam TAllocator Type of \p allocator.
 * @tparam TValue Type of element that \p pointer holds.
 * @param allocator Allocator to use for destruction.
 * @param pointer Pointer to the object being destroyed.
 */
template< typename TAllocator, typename TValue >
void allocator_destroy(
	TAllocator & allocator,
	TValue * pointer
);

} // namespace Memory



namespace _ {
namespace Memory {

BR_HAS_MEMBER_FUNCTION(destroy)

template< typename TAllocator, typename TValue >
inline void allocator_destroy(BooleanTrue, TAllocator & allocator, TValue * pointer) {
	allocator.destroy(pointer);
}

template< typename TAllocator, typename TValue >
inline void allocator_destroy(BooleanFalse, TAllocator & allocator, TValue * pointer) {
	pointer->~TValue();
}

template< typename TAllocator, typename TValue >
inline void allocator_destroy(TAllocator & allocator, TValue * pointer) {
	allocator_destroy(HasMemberFunction_destroy< TAllocator, TValue * >{}, allocator, pointer);
};

} // namespace Memory
} // namespace _

inline namespace Memory {

template< typename TAllocator, typename TValue >
inline void allocator_destroy(TAllocator & allocator, TValue * pointer) {
	_::Memory::allocator_destroy(allocator, pointer);
}

} // namespace Memory

} // namespace BR