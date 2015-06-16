#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_constructible.hpp>
#include <libbr/type_traits/use_allocator.hpp>

namespace BR {
namespace TypeTraits {

struct NotUseAllocator {};

struct UseAllocatorWithTag {};

struct UseAllocatorWithoutTag {};

template< typename T, typename TAllocator, typename ... TArguments >
struct TypeAllocatorConstructorUsage : TypeOperate::TypeWrapper<
	TypeOperate::Conditional<
		UseAllocator< T, TAllocator >,
		TypeOperate::Conditional<
			TypeOperate::IsConstructible< T, Memory::AllocatorArgumentTag, TAllocator, TArguments ... >,
			UseAllocatorWithTag,
			UseAllocatorWithoutTag
		>,
		NotUseAllocator
	>
> {};

template< typename T, typename TAllocator, typename ... TArguments >
using AllocatorConstructorUsage = TypeOperate::TypeUnwrap< TypeAllocatorConstructorUsage< T, TAllocator, TArguments ... > >;

} // namespace TypeTraits
} // namespace BR

