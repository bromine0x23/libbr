/**
 * @file
 * @brief 检查是否具有 \em nothrow 的拷贝构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowCopyConstructor = IsNothrowConstructible< T, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地拷贝构造
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsNothrowConstructible
 * @see BR::HasCopyConstructor
 * @see BR::NoNothrowCopyConstructor
 *
 * 如果 \em T 可被 \em nothrow 地拷贝构造，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowCopyConstructor : BooleanRewrapPositive< Detail::TypeTraits::HasNothrowCopyConstructor<T> > {};

/**
 * @brief HasNothrowCopyConstructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasNothrowCopyConstructor
 */
template< typename T >
struct NoNothrowCopyConstructor : BooleanRewrapNegative< Detail::TypeTraits::HasNothrowCopyConstructor<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasNothrowCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasNothrowCopyConstructor
 * @see BR::no_nothrow_copy_constructor
 */
template< typename T >
constexpr auto has_nothrow_copy_constructor = bool_constant< HasNothrowCopyConstructor<T> >;

/**
 * @brief NoNothrowCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoNothrowCopyConstructor
 * @see BR::has_nothrow_copy_constructor
 */
template< typename T >
constexpr auto no_nothrow_copy_constructor = bool_constant< NoNothrowCopyConstructor<T> >;

#endif // defined(BR_CXX14)

} // namespace BR