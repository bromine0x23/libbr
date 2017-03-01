#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/has_member_function.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Memory {

/**
 *
 * @tparam TAllocator
 * @tparam TValue
 * @tparam TArguments
 * @param allocator
 * @param pointer
 * @param arguments
 */
template<typename TAllocator, typename TValue, typename ... TArguments>
void construct(TAllocator &allocator, TValue *pointer, TArguments &&... arguments);

} // namespace Memory

namespace Detail {
namespace Memory {

BR_HAS_MEMBER_FUNCTION(construct)

template< typename TAllocator, typename TValue, typename ... TArguments >
inline void construct_detail(BooleanTrue, TAllocator & allocator, TValue * pointer, TArguments && ... arguments) {
	allocator.construct(pointer, forward<TArguments>(arguments) ...);
}

template< typename TAllocator, typename TValue, typename ... TArguments >
inline void construct_detail(BooleanFalse, TAllocator & allocator, TValue * pointer, TArguments && ... arguments) {
	::new (reinterpret_cast< void * >(pointer)) TValue(forward<TArguments>(arguments) ...);
}

template< typename TAllocator, typename TValue, typename ... TArguments >
inline void construct(TAllocator & allocator, TValue * pointer, TArguments && ... arguments) {
	construct_detail(HasMemberFunction_construct< TAllocator, TValue *, TArguments ... >{}, allocator, pointer, forward<TArguments>(arguments) ...);
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TAllocator, typename TValue, typename ... TArguments >
inline void construct(TAllocator & allocator, TValue * pointer, TArguments && ... arguments) {
	Detail::Memory::construct(allocator, pointer, forward<TArguments>(arguments) ...);
}

} // namespace Memory

} // namespace BR