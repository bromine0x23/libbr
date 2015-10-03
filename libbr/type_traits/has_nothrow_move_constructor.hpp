/**
 * @file
 * @brief 检查是否具有 \em nothrow 的移动构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowMoveConstructor = IsNothrowConstructible< T, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有 \em nothrow 的移动构造函数
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsNothrowConstructible
 * @see BR::HasMoveConstructor
 * @see BR::NoNothrowMoveConstructor
 *
 * 如果 \em T 具有 \em nothrow 的移动构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowMoveConstructor : BooleanRewrapPositive< Detail::TypeTraits::HasNothrowMoveConstructor<T> > {};

/**
 * @brief HasNothrowMoveConstructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasNothrowMoveConstructor
 */
template< typename T >
struct NoNothrowMoveConstructor : BooleanRewrapNegative< Detail::TypeTraits::HasNothrowMoveConstructor<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasNothrowMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasNothrowMoveConstructor
 * @see BR::no_nothrow_move_constructor
 */
template< typename T >
constexpr auto has_nothrow_move_constructor = bool_constant< HasNothrowMoveConstructor<T> >;

/**
 * @brief NoNothrowMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoNothrowMoveConstructor
 * @see BR::has_nothrow_move_constructor
 */
template< typename T >
constexpr auto no_nothrow_move_constructor = bool_constant< NoNothrowMoveConstructor<T> >;

#endif // defined(BR_CXX14)

} // namespace BR