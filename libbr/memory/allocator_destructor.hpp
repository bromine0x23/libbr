#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/type_traits/allocator_traits.hpp>

namespace BR {
inline namespace Memory {

template< typename TAllocator >
struct AllocatorDestructor : public UnaryFunctor<typename AllocatorTraits<TAllocator>::Pointer> {

	using Allocator = TAllocator;

private:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
	using Pointer = typename AllocatorTraits::Pointer;

	using Size = typename AllocatorTraits::Size;

public:
	AllocatorDestructor(Allocator & allocator, Size size) noexcept : m_allocator(allocator), m_size(size) {}

	void operator()(Pointer pointer) noexcept {
		AllocatorTraits::deallocate(m_allocator, pointer, m_size);
	}

private:
	Allocator & m_allocator;
	Size m_size;
};

} // namespace Memory
} // namespace BR

