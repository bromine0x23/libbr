/**
 * @file
 * @brief 检查是否具有默认构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/is_constructible.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否可被默认构造
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsConstructible
 * @see BR::NoDefaultConstructor
 *
 * 如果 \em T 可被默认构造，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasDefaultConstructor;

/**
 * @brief HasDefaultConstructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasDefaultConstructor
 */
template< typename T >
struct NoDefaultConstructor;

#if defined(BR_CXX14)

/**
 * @brief HasDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasDefaultConstructor
 * @see BR::no_default_constructor
 */
template< typename T >
constexpr auto has_default_constructor = bool_constant< HasDefaultConstructor<T> >;

/**
 * @brief NoDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoDefaultConstructor
 * @see BR::has_default_constructor
 */
template< typename T >
constexpr auto no_default_constructor = bool_constant< NoDefaultConstructor<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasDefaultConstructor = IsConstructible<T>;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasDefaultConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasDefaultConstructor<T> > {};

template< typename T >
struct NoDefaultConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasDefaultConstructor<T> > {};

} // namespace BR