/**
 * @file
 * @brief 检查类型是否可被 \em nothrow 地拷贝构造
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using IsNothrowCopyConstructible = BooleanAnd<
	IsReferenceable< T >,
	IsNothrowConstructible< T, AddLValueReference< AddConst<T> > >
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地拷贝构造
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsNothrowConstructible
 * @see NotNothrowCopyConstructible
 *
 * 如果 \em T 可被 \em nothrow 地拷贝构造，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNothrowCopyConstructible : BooleanRewrapPositive< Detail::TypeTraits::IsNothrowCopyConstructible<T> > {};

/**
 * @brief IsNothrowCopyConstructible 的否定
 * @tparam T 待检查类型
 * @see IsNothrowCopyConstructible
 */
template< typename T >
struct NotNothrowCopyConstructible : BooleanRewrapNegative< Detail::TypeTraits::IsNothrowCopyConstructible<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsNothrowCopyConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see IsNothrowCopyConstructible
 * @see not_nothrow_copy_constructible
 */
template< typename T >
constexpr auto is_nothrow_copy_constructible = bool_constant< IsNothrowCopyConstructible<T> >;

/**
 * @brief NotNothrowCopyConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNothrowCopyConstructible
 * @see is_nothrow_copy_constructible
 */
template< typename T >
constexpr auto not_nothrow_copy_constructible = bool_constant< NotNothrowCopyConstructible<T> >;

#endif // defined(BR_CXX14)

} // namespace BR