#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/allocator_traits.hpp>

namespace BR {

template< typename Allocator >
class AllocatorDestructor {

	using Traits = BR::AllocatorTraits<Allocator>;

public:

	using Pointer = typename Traits::Pointer;
	using Size    = typename Traits::Size;

public:
	AllocatorDestructor(Allocator & allocator, Size size) noexcept : m_allocator(allocator), m_size(size) {}

	void operator()(Pointer pointer) noexcept {
		Traits::deallocate(m_allocator, pointer, m_size);
	}

private:
	Allocator & m_allocator;
	Size m_size;
};

} // namespace BR

