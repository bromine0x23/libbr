#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_use_allocator.hpp>

namespace BR {

enum class AllocatorConstructorUsageType {
	not_used, use_with_tag, use_without_tag
};

template< AllocatorConstructorUsageType type >
using AllocatorConstructorUsageConstant = IntegerConstant< AllocatorConstructorUsageType, type >;

template< typename T, typename TAllocator, typename ... TArguments >
struct TypeAllocatorConstructorUsage : TypeWrapper<
	Conditional<
		IsUseAllocator< T, TAllocator >,
		Conditional<
			IsConstructible< T, AllocatorArgumentTag, TAllocator, TArguments ... >,
			AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >,
			AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >
		>,
		AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >
	>
> {};

template< typename T, typename TAllocator, typename ... TArguments >
using AllocatorConstructorUsage = TypeUnwrap< TypeAllocatorConstructorUsage< T, TAllocator, TArguments ... > >;

} // namespace BR

