/**
 * @file
 * @brief \em nothrow 移动赋值运算符检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_traits/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using IsNothrowMoveAssignable = BooleanAnd<
	IsReferenceable<T>,
	IsNothrowAssignable< AddLValueReference<T>, AddRValueReference<T> >
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否重载了 \em nothrow 的移动赋值运算符
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsMoveAssignable
 * @see NotNothrowMoveAssignable
 *
 * 如果 \em T 重载了 \em nothrow 的移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNothrowMoveAssignable : BooleanRewrapPositive< Detail::TypeTraits::IsNothrowMoveAssignable<T> > {};

/**
 * @brief IsNothrowMoveAssignable 的否定
 * @tparam T 待检查类型
 * @see IsNothrowMoveAssignable
 */
template< typename T >
struct NotNothrowMoveAssignable : BooleanRewrapNegative< Detail::TypeTraits::IsNothrowMoveAssignable<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsNothrowMoveAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @see IsNothrowMoveAssignable
 * @see not_nothrow_move_assignable
 */
template< typename T >
constexpr auto is_nothrow_move_assignable = bool_constant< IsNothrowMoveAssignable<T> >;

/**
 * @brief NotNothrowMoveAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNothrowMoveAssignable
 * @see is_nothrow_move_assignable
 */
template< typename T >
constexpr auto not_nothrow_move_assignable = bool_constant< NotNothrowMoveAssignable<T> >;

#endif // defined(BR_CXX14)

} // namespace BR