#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

template< typename TAllocator, typename TValue >
inline void destroy(TAllocator & allocator, TValue * pointer);



namespace Detail {
namespace Memory {

#define BR_TYPE_OPERATE_FUNCTION_NAME destroy
#include <libbr/type_traits/has_member_function.inc>

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

template< typename TAllocator, typename TValue >
void destroy(TAllocator & allocator, TValue * pointer) {
	Detail::Memory::destroy(allocator, pointer);
}

} // namespace BR