/**
 * @file
 * @brief 检查是否具有 \em nothrow 的移动构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有 \em nothrow 的移动构造函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsNothrowConstructible
 * @see IsMoveConstructible
 * @see NoNothrowMoveConstructor
 *
 * 如果 \em T 具有 \em nothrow 的移动构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowMoveConstructor;

/**
 * @brief HasNothrowMoveConstructor 的否定
 * @tparam T 待检查类型
 * @see HasNothrowMoveConstructor
 */
template< typename T >
struct NoNothrowMoveConstructor;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasNothrowMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasNothrowMoveConstructor
 * @see no_nothrow_move_constructor
 */
template< typename T >
constexpr auto has_nothrow_move_constructor = boolean_constant< HasNothrowMoveConstructor<T> >;

/**
 * @brief NoNothrowMoveConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoNothrowMoveConstructor
 * @see has_nothrow_move_constructor
 */
template< typename T >
constexpr auto no_nothrow_move_constructor = boolean_constant< NoNothrowMoveConstructor<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowMoveConstructor = IsNothrowConstructible< T, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasNothrowMoveConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasNothrowMoveConstructor<T> > {};

template< typename T >
struct NoNothrowMoveConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasNothrowMoveConstructor<T> > {};

} // namespace TypeTraits

} // namespace BR