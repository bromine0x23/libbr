/**
 * @file
 * @brief allocator_destroy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/destroy_at.hpp>
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


namespace Detail {
namespace Memory {

BR_HAS_MEMBER_FUNCTION(destroy)

template< typename TAllocator, typename TValue >
inline void allocator_destroy(TAllocator & allocator, TValue * pointer, BooleanTrue) {
	allocator.destroy(pointer);
}

template< typename TAllocator, typename TValue >
inline void allocator_destroy(TAllocator & allocator, TValue * pointer, BooleanFalse) {
	using BR::destroy_at;
	destroy_at(pointer);
}

template< typename TAllocator, typename TValue >
inline void allocator_destroy(TAllocator & allocator, TValue * pointer) {
	allocator_destroy(allocator, pointer, HasMemberFunction_destroy< TAllocator, TValue * >{});
};

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TAllocator, typename TValue >
inline void allocator_destroy(TAllocator & allocator, TValue * pointer) {
	Detail::Memory::allocator_destroy(allocator, pointer);
}

} // namespace Memory

} // namespace BR