/**
 * @file
 * @brief 检查是否具有平凡的移动构造函数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_trivially_constructible.hpp>
#include <libbr/type_transform/add_rvalue_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有平凡的移动构造函数
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsTriviallyConstructible
 * @see HasMoveConstructor
 * @see NoTrivialMoveConstructor
 *
 * 如果 \em T 具有平凡的移动构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialMoveConstructor;

/**
 * @brief HasTrivialMoveConstructor 的否定
 * @tparam T 待检查类型
 * @see HasTrivialMoveConstructor
 */
template< typename T >
struct NoTrivialMoveConstructor;

/**
 * @brief HasTrivialMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasTrivialMoveConstructor
 * @see no_trivial_move_constructor
 */
template< typename T >
constexpr auto has_trivial_move_constructor = boolean_constant< HasTrivialMoveConstructor<T> >;

/**
 * @brief NoTrivialMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoTrivialMoveConstructor
 * @see has_trivial_move_constructor
 */
template< typename T >
constexpr auto no_trivial_move_constructor = boolean_constant< NoTrivialMoveConstructor<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
using HasTrivialMoveConstructor = IsTriviallyConstructible < T, AddRValueReference<T> >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct HasTrivialMoveConstructor : public BooleanRewrapPositive< _::TypeTraits::HasTrivialMoveConstructor<T> > {};

template< typename T >
struct NoTrivialMoveConstructor : public BooleanRewrapNegative< _::TypeTraits::HasTrivialMoveConstructor<T> > {};

} // namespace TypeTraits

} // namespace BR