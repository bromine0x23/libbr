/**
 * @file
 * @brief 检查是否具有移动构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_constructible.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否具有移动构造函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsConstructible
 * @see NotMovConstructible
 *
 * 如果 \em T 具有移动构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasMoveConstructor;

/**
 * @brief HasMoveConstructor 的否定
 * @tparam T 待检查类型
 * @see HasMoveConstructor
 */
template< typename T >
struct NoMoveConstructor;

#if defined(BR_CXX14)

/**
 * @brief HasMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasMoveConstructor
 * @see no_move_constructor
 */
template< typename T >
constexpr auto has_move_constructor = bool_constant< HasMoveConstructor<T> >;

/**
 * @brief NoMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoMoveConstructor
 * @see has_move_constructor
 */
template< typename T >
constexpr auto no_move_constructor = bool_constant< NoMoveConstructor<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasMoveConstructor = IsConstructible< T, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasMoveConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasMoveConstructor<T> > {};

template< typename T >
struct NoMoveConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasMoveConstructor<T> > {};

} // namespace BR