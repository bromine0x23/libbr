/**
 * @file
 * @brief allocator_construct_backward
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_construct.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_trivial_move_constructor.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Memory {

/**
 *
 * @tparam TAllocator Type of \p allocator.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TPointer Type of \p output.
 * @param allocator
 * @param first
 * @param last
 * @param output
 * @return
 */
template< typename TAllocator, typename TInputIterator, typename TPointer >
auto allocator_construct_backward(
	TAllocator & allocator,
	TInputIterator first, TInputIterator last,
	TPointer output
) -> TPointer;

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TAllocator, typename TInputIterator, typename TPointer >
auto allocator_construct_backward(TAllocator & allocator, TInputIterator first, TInputIterator last, TPointer output) -> TPointer {
	using BR::allocator_construct;
	for (; first != last; --output) {
		allocator_construct(allocator, PointerTraits<TPointer>::to_raw(output - 1), move_if_noexcept(*--last));
	}
	return output;
}

template< typename TAllocator, typename TInputValue, typename TValue, typename = EnableIf< BooleanAnd< IsSame< TAllocator, Allocator<TValue> >, HasTrivialMoveConstructor<TValue> > > >
auto allocator_construct_backward(TAllocator & allocator, TInputValue * first, TInputValue * last, TValue * output) -> TValue * {
	auto n = static_cast<Size>(last - first);
	output -= n;
	if (n > 0) {
		memory_copy(output, first, n * sizeof(TValue));
	}
	return output;
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TAllocator, typename TInputIterator, typename TPointer >
inline auto allocator_construct_backward(TAllocator & allocator, TInputIterator first, TInputIterator last, TPointer output) -> TPointer {
	return Detail::Memory::allocator_construct_backward(allocator, first, last, output);
}

} // namespace Memory

} // namespace BR