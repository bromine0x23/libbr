#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/use_allocator.hpp>

namespace BR {

struct NotUseAllocator {};

struct UseAllocatorWithTag {};

struct UseAllocatorWithoutTag {};

template< typename T, typename TAllocator, typename ... TArguments >
struct TypeAllocatorConstructorUsage : TypeWrapper<
	Conditional<
		UseAllocator< T, TAllocator >,
		Conditional<
			IsConstructible< T, AllocatorArgumentTag, TAllocator, TArguments ... >,
			UseAllocatorWithTag,
			UseAllocatorWithoutTag
		>,
		NotUseAllocator
	>
> {};

template< typename T, typename TAllocator, typename ... TArguments >
using AllocatorConstructorUsage = TypeUnwrap< TypeAllocatorConstructorUsage< T, TAllocator, TArguments ... > >;

} // namespace BR

