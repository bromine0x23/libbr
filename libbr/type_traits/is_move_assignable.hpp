/**
 * @file
 * @brief 移动赋值运算符检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using IsMoveAssignable = BooleanAnd<
	IsReferenceable<T>,
	IsAssignable< AddLValueReference<T>, AddRValueReference<T> >
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否重载了移动赋值运算符
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotMoveAssignable
 *
 * 如果 \em T 重载了移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsMoveAssignable : BooleanRewrapPositive< Detail::TypeTraits::IsMoveAssignable<T> > {};

/**
 * @brief IsMoveAssignable 的否定
 * @tparam T 待检查类型
 * @see IsMoveAssignable
 */
template< typename T >
struct NotMoveAssignable : BooleanRewrapNegative< Detail::TypeTraits::IsMoveAssignable<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsMoveAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMoveAssignable
 * @see not_move_assignable
 */
template< typename T >
constexpr auto is_move_assignable = bool_constant< IsMoveAssignable<T> >;

/**
 * @brief NotMoveAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMoveAssignable
 * @see is_move_assignable
 */
template< typename T >
constexpr auto not_move_assignable = bool_constant< NotMoveAssignable<T> >;

#endif // defined(BR_CXX14)

} // namespace BR