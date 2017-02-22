#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator_traits.hpp>

namespace BR {
namespace Detail {
namespace Container {

template< typename TAllocator >
struct NodeDestructor : public UnaryFunctor<typename AllocatorTraits<TAllocator>::Pointer> {
	using Allocator = TAllocator;

private:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
	using Pointer = typename AllocatorTraits::Pointer;

	explicit NodeDestructor(Allocator & allocator, bool constructed = false) noexcept : m_allocator(allocator), constructed(constructed) {
	}

	void operator()(Pointer pointer) noexcept {
		if (constructed) {
			AllocatorTraits::destroy(m_allocator, address_of(pointer->element));
		}
		if (pointer != nullptr) {
			AllocatorTraits::deallocate(m_allocator, pointer, 1);
		}
	}

public:
	bool constructed;

private:
	Allocator & m_allocator;
}; // struct NodeDestructor<TAllocator>

template< typename TNodeAllocator, typename TNodePointer >
void destroy_node(TNodeAllocator & allocator, TNodePointer node) {
	AllocatorTraits<TNodeAllocator>::destroy(allocator, address_of(node->element));
	AllocatorTraits<TNodeAllocator>::deallocate(allocator, node, 1);
}

} // namespace Container
} // namespace Detail
} // namespace BR