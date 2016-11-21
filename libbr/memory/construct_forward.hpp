#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/construct.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_const.hpp>
#include <libbr/type_traits/has_trivial_move_constructor.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

inline namespace Memory {

template< typename TAllocator, typename TInputIterator, typename TValue >
inline auto construct_forward(TAllocator & allocator, TInputIterator first, TInputIterator last, TValue * pointer) -> TValue *;

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TAllocator, typename TInputIterator, typename TValue >
auto construct_forward(TAllocator & allocator, TInputIterator first, TInputIterator last, TValue * pointer) -> TValue * {
	for (; first != last; ++first, (void) ++pointer) {
		construct(allocator, pointer, *first);
	}
	return pointer;
}

template< typename TAllocator, typename TInputIterator, typename TValue, typename = EnableIf< BooleanAnd< IsSame< RemoveConst<TInputValue>, TValue >, HasTrivialMoveConstructor<TValue> > > >
auto construct_forward(TAllocator & allocator, TInputValue * first, TInputValue * last, TValue * pointer) -> TValue * {
	auto n = static_cast<Size>(last - first);
	memory_copy(pointer, first, n * sizeof(TValue));
	return pointer + n;
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TAllocator, typename TInputIterator, typename TValue >
auto construct_forward(TAllocator & allocator, TInputIterator first, TInputIterator last, TValue * pointer) -> TValue * {
	Detail::Memory::construct_forward(allocator, first, last, pointer);
}

} // namespace Memory

} // namespace BR