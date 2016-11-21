#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/has_member_function.hpp>

namespace BR {

inline namespace Memory {

/**
 *
 * @tparam TAllocator
 * @tparam TValue
 * @param allocator
 * @param pointer
 */
template< typename TAllocator, typename TValue >
inline void destroy(TAllocator & allocator, TValue * pointer);

} // namespace Memory


namespace Detail {
namespace Memory {

BR_HAS_MEMBER_FUNCTION(destroy)

template< typename TAllocator, typename TValue >
inline void destroy(TAllocator & allocator, TValue * pointer, BooleanTrue) {
	allocator.destroy(pointer);
}

template< typename TAllocator, typename TValue >
inline void destroy(TAllocator & allocator, TValue * pointer, BooleanFalse) {
	pointer->~TValue();
}

template< typename TAllocator, typename TValue >
inline void destroy(TAllocator & allocator, TValue * pointer) {
	destroy(allocator, pointer, HasMemberFunction_destroy< TAllocator, TValue * >{});
};

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TAllocator, typename TValue >
void destroy(TAllocator & allocator, TValue * pointer) {
	Detail::Memory::destroy(allocator, pointer);
}

} // namespace Memory

} // namespace BR