#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Container {

template< typename TAllocator >
inline void copy_allocator(TAllocator & l, TAllocator const & r, BooleanTrue) {
	l = r;
}

template< typename TAllocator >
inline void copy_allocator(TAllocator &, TAllocator const &, BooleanFalse) noexcept {
}

template< typename TAllocator >
inline void copy_allocator(TAllocator & l, TAllocator const & r) {
	copy_allocator(l, r, typename AllocatorTraits<TAllocator>::IsPropagateOnContainerCopyAssignment{});
}

template< typename TAllocator >
inline void move_allocator(TAllocator & l, TAllocator & r, BooleanTrue) {
	l = BR::move(r);
}

template< typename TAllocator >
inline void move_allocator(TAllocator &, TAllocator &, BooleanFalse) noexcept {
}

template< typename TAllocator >
inline void move_allocator(TAllocator & l, TAllocator & r) {
	move_allocator(l, r, typename AllocatorTraits<TAllocator>::IsPropagateOnContainerMoveAssignment{});
}

template< typename TAllocator >
inline void swap_allocator(TAllocator & l, TAllocator & r, BooleanTrue) {
	using BR::swap;
	swap(l, r);
}

template< typename TAllocator >
inline void swap_allocator(TAllocator &, TAllocator &, BooleanFalse) noexcept {
}

template< typename TAllocator >
inline void swap_allocator(TAllocator & l, TAllocator & r) {
	swap_allocator(l, r, typename AllocatorTraits<TAllocator>::IsPropagateOnContainerSwap{});
}

} // namespace Container
} // namespace Detail
} // namespace BR