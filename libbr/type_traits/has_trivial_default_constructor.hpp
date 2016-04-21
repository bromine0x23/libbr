/**
 * @file
 * @brief 检查类型是否具有平凡的默认构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/is_trivially_constructible.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasTrivialDefaultConstructor = IsTriviallyConstructible<T>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有平凡的默认构造函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR::IsTrivially Constructible
 * @see BR::HasDefaultConstructor
 * @see BR::NoTrivialDefaultConstructor
 *
 * 如果 \em T 具有平凡的默认构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialDefaultConstructor : BooleanRewrapPositive< Detail::TypeTraits::HasTrivialDefaultConstructor<T> > {};

/**
 * @brief HasTrivialDefaultConstructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasTrivialDefaultConstructor
 */
template< typename T >
struct NoTrivialDefaultConstructor : BooleanRewrapNegative< Detail::TypeTraits::HasTrivialDefaultConstructor<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasTrivialDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasTrivialDefaultConstructor
 * @see BR::no_trivial_default_constructor
 */
template< typename T >
constexpr auto has_trivial_default_constructor = bool_constant< HasTrivialDefaultConstructor<T> >;

/**
 * @brief NoTrivialDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoTrivialDefaultConstructor
 * @see BR::has_trivial_default_constructor
 */
template< typename T >
constexpr auto no_trivial_default_constructor = bool_constant< NoTrivialDefaultConstructor<T> >;

#endif // defined(BR_CXX14)

} // namespace BR