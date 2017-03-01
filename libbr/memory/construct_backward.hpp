#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/construct.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_trivial_move_constructor.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/remove_const.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Memory {

template< typename TAllocator, typename TInputIterator, typename TValue >
auto construct_backward(TAllocator & allocator, TInputIterator first, TInputIterator last, TValue * pointer) -> TValue *;

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TAllocator, typename TInputIterator, typename TValue >
auto construct_backward(TAllocator & allocator, TInputIterator first, TInputIterator last, TValue * pointer) -> TValue * {
	for (; first != last;) {
		BR::construct(allocator, --pointer, move_if_noexcept(*--last));
	}
	return pointer;
}

template< typename TAllocator, typename TInputValue, typename TValue, typename = EnableIf< BooleanAnd< IsSame< RemoveConst<TInputValue>, TValue >, HasTrivialMoveConstructor<TValue> > > >
auto construct_backward(TAllocator & allocator, TInputValue * first, TInputValue * last, TValue * pointer) -> TValue * {
	auto n = static_cast<Size>(last - first);
	pointer -= n;
	if (n > 0) {
		memory_copy(pointer, first, n * sizeof(TValue));
	}
	return pointer;
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TAllocator, typename TInputIterator, typename TValue >
inline auto construct_backward(TAllocator & allocator, TInputIterator first, TInputIterator last, TValue * pointer) -> TValue * {
	Detail::Memory::construct_backward(allocator, first, last, pointer);
}

} // namespace Memory

} // namespace BR