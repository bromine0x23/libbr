#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

template< typename TAllocator, typename TValue, typename ... TArguments >
inline void construct(TAllocator & allocator, TValue * pointer, TArguments && ... arguments);



namespace Detail {
namespace Memory {

#define BR_TYPE_OPERATE_FUNCTION_NAME construct
#include <libbr/type_traits/has_member_function.inc>

template< typename TAllocator, typename TValue, typename ... TArguments >
inline void construct(BooleanTrue, TAllocator & allocator, TValue * pointer, TArguments && ... arguments) {
	allocator.construct(pointer, forward<TArguments>(arguments) ...);
}

template< typename TAllocator, typename TValue, typename ... TArguments >
inline void construct(BooleanFalse, TAllocator & allocator, TValue * pointer, TArguments && ... arguments) {
	::new (reinterpret_cast< void * >(pointer)) TValue(forward<TArguments>(arguments) ...);
}

template< typename TAllocator, typename TValue, typename ... TArguments >
inline void construct(TAllocator & allocator, TValue * pointer, TArguments && ... arguments) {
	construct(HasMemberFunction_construct< TAllocator, TValue *, TArguments ... >{}, allocator, pointer, forward<TArguments>(arguments) ...);
};

} // namespace Memory
} // namespace Detail

template< typename TAllocator, typename TValue, typename ... TArguments >
void construct(TAllocator & allocator, TValue * pointer, TArguments && ... arguments) {
	Detail::Memory::construct(allocator, pointer, forward<TArguments>(arguments) ...);
}

} // namespace BR