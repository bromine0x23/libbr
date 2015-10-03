/**
 * @file
 * @brief \em nothrow 移动构造函数检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using IsNothrowMoveConstructible = BooleanAnd<
	IsReferenceable<T>,
	IsNothrowConstructible< AddRValueReference<T> >
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有 \em nothrow 的移动构造函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsNothrowConstructible
 * @see NotNothrowMoveConstructible
 *
 * 如果 \em T 具有 \em nothrow 的移动构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNothrowMoveConstructible : BooleanRewrapPositive< Detail::TypeTraits::IsNothrowMoveConstructible<T> > {};

/**
 * @brief IsNothrowMoveConstructible 的否定
 * @tparam T 待检查类型
 * @see IsNothrowMoveConstructible
 */
template< typename T >
struct NotNothrowMoveConstructible : BooleanRewrapNegative< Detail::TypeTraits::IsNothrowMoveConstructible<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsNothrowMoveConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNothrowMoveConstructible
 * @see not_nothrow_move_constructible
 */
template< typename T >
constexpr auto is_nothrow_move_constructible = bool_constant< IsNothrowMoveConstructible<T> >;

/**
 * @brief NotMoveConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNothrowMoveConstructible
 * @see is_nothrow_move_constructible
 */
template< typename T >
constexpr auto not_nothrow_move_constructible = bool_constant< NotNothrowMoveConstructible<T> >;

#endif // defined(BR_CXX14)

} // namespace BR