/**
 * @file
 * @brief 检查类型是否具有 \em nothrow 的默认构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowDefaultConstructor = IsNothrowConstructible<T>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有 \em nothrow 的默认构造函数
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsNothrowConstructible
 * @see BR::HasDefaultConstructor
 * @see BR::NoNothrowDefaultConstructor
 *
 * 如果 \em T 具有 \em nothrow 的默认构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowDefaultConstructor : BooleanRewrapPositive< Detail::TypeTraits::HasNothrowDefaultConstructor<T> > {};

/**
 * @brief HasNothrowDefaultConstructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasNothrowDefaultConstructor
 */
template< typename T >
struct NoNothrowDefaultConstructor : BooleanRewrapNegative< Detail::TypeTraits::HasNothrowDefaultConstructor<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasNothrowDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasNothrowDefaultConstructor
 * @see BR::no_nothrow_default_constructor
 */
template< typename T >
constexpr auto has_nothrow_default_constructor = bool_constant< HasNothrowDefaultConstructor<T> >;

/**
 * @brief NoNothrowDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoNothrowDefaultConstructor
 * @see BR::has_nothrow_default_constructor
 */
template< typename T >
constexpr auto no_nothrow_default_constructor = bool_constant< NoNothrowDefaultConstructor<T> >;

#endif // defined(BR_CXX14)

} // namespace BR