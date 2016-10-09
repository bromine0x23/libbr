/**
 * @file
 * @brief 检查是否具有平凡的移动构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_trivially_constructible.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否具有平凡的移动构造函数
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsTriviallyConstructible
 * @see BR::HasMoveConstructor
 * @see BR::NoTrivialMoveConstructor
 *
 * 如果 \em T 具有平凡的移动构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialMoveConstructor;

/**
 * @brief HasTrivialMoveConstructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasTrivialMoveConstructor
 */
template< typename T >
struct NoTrivialMoveConstructor;

#if defined(BR_CXX14)

/**
 * @brief HasTrivialMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasTrivialMoveConstructor
 * @see BR::no_trivial_move_constructor
 */
template< typename T >
constexpr auto has_trivial_move_constructor = bool_constant< HasTrivialMoveConstructor<T> >;

/**
 * @brief NoTrivialMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoTrivialMoveConstructor
 * @see BR::has_trivial_move_constructor
 */
template< typename T >
constexpr auto no_trivial_move_constructor = bool_constant< NoTrivialMoveConstructor<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasTrivialMoveConstructor = IsTriviallyConstructible < T, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasTrivialMoveConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasTrivialMoveConstructor<T> > {};

template< typename T >
struct NoTrivialMoveConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasTrivialMoveConstructor<T> > {};

} // namespace BR