/**
 * @file
 * @brief \em IsUseAllocator
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_convertible.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

struct IsUseAllocatorTest {
	template < typename T >
	static auto test(typename T::Allocator * = nullptr) -> BooleanTrue;

	template < typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T, typename TAllocator, typename = decltype(IsUseAllocatorTest::test<T>()) >
struct IsUseAllocator;

template< typename T, typename TAllocator >
struct IsUseAllocator< T, TAllocator, BooleanTrue > : IsConstructible< TAllocator, typename T::Allocator > {
};

template< typename T, typename TAllocator >
struct IsUseAllocator< T, TAllocator, BooleanFalse > : BooleanFalse {};

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief IsUseAllocator
 * @tparam T 待检查类型
 * @tparam TAllocator 分配器类型
 * @see IntegerConstant
 * @see NotUseAllocator
 */
template< typename T, typename TAllocator >
struct IsUseAllocator : BooleanRewrapPositive< Detail::TypeTraits::IsUseAllocator< T, TAllocator > > {
};

/**
 * @brief IsUseAllocator 的否定
 * @tparam T 待检查类型
 * @tparam TAllocator 分配器类型
 * @see IsUseAllocator
 */
template< typename T, typename TAllocator >
struct NotUseAllocator : BooleanRewrapNegative< Detail::TypeTraits::IsUseAllocator< T, TAllocator > > {
};

#if defined(BR_CXX14)

/**
 * @brief IsUseAllocator 的模板变量版本
 * @tparam T 待检查类型
 * @see IsUseAllocator
 * @see not_use_allocator
 */
template< typename T, typename TAllocator >
constexpr auto is_use_allocator = bool_constant< IsUseAllocator< T, TAllocator> >;

/**
 * @brief NotUseAllocator 的模板变量版本
 * @tparam T 待检查类型
 * @see NotUseAllocator
 * @see is_use_allocator
 */
template< typename T, typename TAllocator >
constexpr auto not_use_allocator = bool_constant< NotUseAllocator< T, TAllocator> >;

#endif // defined(BR_CXX14)

} // namespace BR