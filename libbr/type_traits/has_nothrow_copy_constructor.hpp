/**
 * @file
 * @brief 检查是否具有 \em nothrow 的拷贝构造函数
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/add_const.hpp>
#include <libbr/type_traits/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地拷贝构造
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsNothrowConstructible
 * @see HasCopyConstructor
 * @see NoNothrowCopyConstructor
 *
 * 如果 \em T 可被 \em nothrow 地拷贝构造，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowCopyConstructor;

/**
 * @brief HasNothrowCopyConstructor 的否定
 * @tparam T 待检查类型
 * @see HasNothrowCopyConstructor
 */
template< typename T >
struct NoNothrowCopyConstructor;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasNothrowCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasNothrowCopyConstructor
 * @see no_nothrow_copy_constructor
 */
template< typename T >
constexpr auto has_nothrow_copy_constructor = boolean_constant< HasNothrowCopyConstructor<T> >;

/**
 * @brief NoNothrowCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoNothrowCopyConstructor
 * @see has_nothrow_copy_constructor
 */
template< typename T >
constexpr auto no_nothrow_copy_constructor = boolean_constant< NoNothrowCopyConstructor<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowCopyConstructor = IsNothrowConstructible< T, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasNothrowCopyConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasNothrowCopyConstructor<T> > {};

template< typename T >
struct NoNothrowCopyConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasNothrowCopyConstructor<T> > {};

} // namespace TypeTraits

} // namespace BR