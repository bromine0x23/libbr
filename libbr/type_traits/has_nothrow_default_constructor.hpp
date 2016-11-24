/**
 * @file
 * @brief 检查类型是否具有 \em nothrow 的默认构造函数
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有 \em nothrow 的默认构造函数
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsNothrowConstructible
 * @see HasDefaultConstructor
 * @see NoNothrowDefaultConstructor
 *
 * 如果 \em T 具有 \em nothrow 的默认构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowDefaultConstructor;

/**
 * @brief NoNothrowDefaultConstructor 的否定
 * @tparam T 待检查类型
 * @see HasNothrowDefaultConstructor
 */
template< typename T >
struct NoNothrowDefaultConstructor;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasNothrowDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasNothrowDefaultConstructor
 * @see no_nothrow_default_constructor
 */
template< typename T >
constexpr auto has_nothrow_default_constructor = boolean_constant< HasNothrowDefaultConstructor<T> >;

/**
 * @brief NoNothrowDefaultConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoNothrowDefaultConstructor
 * @see has_nothrow_default_constructor
 */
template< typename T >
constexpr auto no_nothrow_default_constructor = boolean_constant< NoNothrowDefaultConstructor<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowDefaultConstructor = IsNothrowConstructible<T>;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasNothrowDefaultConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasNothrowDefaultConstructor<T> > {};

template< typename T >
struct NoNothrowDefaultConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasNothrowDefaultConstructor<T> > {};

} // namespace TypeTraits

} // namespace BR