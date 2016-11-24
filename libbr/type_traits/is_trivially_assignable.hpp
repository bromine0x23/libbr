/**
 * @file
 * @brief 检查是否具有 \em trivially 的赋值运算符
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_TRIVIALLY_ASSIGNABLE)
#  include <libbr/type_traits/is_lvalue_reference.hpp>
#  include <libbr/type_traits/is_same.hpp>
#  include <libbr/type_traits/is_scalar.hpp>
#  include <libbr/type_traits/remove_const.hpp>
#  include <libbr/type_traits/remove_reference.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有 \em trivially 的赋值运算符
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IntegerConstant
 * @see BR_IS_TRIVIALLY_ASSIGNABLE
 * @see IsAssignable
 * @see NotTriviallyAssignable
 *
 * 如果 \em T 是否具有 \em trivially 的赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename TArg >
struct IsTriviallyAssignable;

/**
 * @brief IsTriviallyAssignable 的否定
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsTriviallyAssignable
 */
template< typename T, typename TArg >
struct NotTriviallyAssignable;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsTriviallyAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsTriviallyAssignable
 * @see not_trivially_assignable
 */
template< typename T, typename TArg >
constexpr auto is_trivially_assignable = boolean_constant< IsTriviallyAssignable< T, TArg > >;

/**
 * @brief NotTriviallyAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see NotTriviallyAssignable
 * @see is_trivially_assignable
 */
template< typename T, typename TArg >
constexpr auto not_trivially_assignable = boolean_constant< NotTriviallyAssignable< T, TArg > >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_TRIVIALLY_ASSIGNABLE)

template< typename T, typename TArg >
using IsTriviallyAssignable = BooleanConstant< BR_IS_TRIVIALLY_ASSIGNABLE(T, TArg) >;

#else

template< typename T, typename TArg >
using IsTriviallyAssignableBasic = BooleanAnd< IsSame< T, TArg >, IsScalar<T> >;

template< typename T, typename TArg >
using IsTriviallyAssignable = BooleanAnd<
	IsLValueReference<T>,
	IsTriviallyAssignableBasic< RemoveReference<T>, RemoveConst< RemoveReference<TArg> > >
>;

#endif // defined(BR_IS_TRIVIALLY_ASSIGNABLE)

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T, typename TArg >
struct IsTriviallyAssignable : BooleanRewrapPositive< Detail::TypeTraits::IsTriviallyAssignable< T, TArg > > {};

template< typename T, typename TArg >
struct NotTriviallyAssignable : BooleanRewrapNegative< Detail::TypeTraits::IsTriviallyAssignable< T, TArg > > {};

} // namespace TypeTraits

} // namespace BR