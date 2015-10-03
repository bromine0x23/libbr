/**
 * @file
 * @brief 移动构造函数检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using IsMoveConstructible = BooleanAnd<
	IsReferenceable< T >,
	IsConstructible< T, AddRValueReference<T> >
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有移动构造函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotMoveConstructible
 *
 * 如果 \em T 具有移动构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsMoveConstructible : BooleanRewrapPositive< Detail::TypeTraits::IsMoveConstructible<T> > {};

/**
 * @brief IsMoveConstructible 的否定
 * @tparam T 待检查类型
 * @see IsMoveConstructible
 */
template< typename T >
struct NotMoveConstructible : BooleanRewrapNegative< Detail::TypeTraits::IsMoveConstructible<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsMoveConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMoveConstructible
 * @see not_move_constructible
 */
template< typename T >
constexpr auto is_move_constructible = bool_constant< IsMoveAssignable<T> >;

/**
 * @brief NotMoveConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMoveConstructible
 * @see is_move_constructible
 */
template< typename T >
constexpr auto not_move_constructible = bool_constant< NotMoveConstructible<T> >;

#endif // defined(BR_CXX14)

} // namespace BR