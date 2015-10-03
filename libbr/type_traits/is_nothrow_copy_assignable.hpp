/**
 * @file
 * @brief 检查类型是否可被 \em nothrow 地拷贝赋值
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_traits/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using IsNothrowCopyAssignable = BooleanAnd<
	IsReferenceable< T >,
	IsNothrowAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地拷贝赋值
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsNothrowAssignable
 * @see NotNothrowCopyAssignable
 *
 * 如果 \em T 可被 \em nothrow 地拷贝赋值，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNothrowCopyAssignable : BooleanRewrapPositive< Detail::TypeTraits::IsNothrowCopyAssignable<T> > {};

/**
 * @brief IsNothrowCopyAssignable 的否定
 * @tparam T 待检查类型
 * @see IsNothrowCopyAssignable
 */
template< typename T >
struct NotNothrowCopyAssignable : BooleanRewrapNegative< Detail::TypeTraits::IsNothrowCopyAssignable<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsNothrowCopyAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @see IsNothrowCopyAssignable
 * @see not_nothrow_copy_assignable
 */
template< typename T >
constexpr auto is_nothrow_copy_assignable = bool_constant< IsNothrowCopyAssignable<T> >;

/**
 * @brief NotNothrowCopyAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNothrowCopyAssignable
 * @see is_nothrow_copy_assignable
 */
template< typename T >
constexpr auto not_nothrow_copy_assignable = bool_constant< NotNothrowCopyAssignable<T> >;

#endif // defined(BR_CXX14)

} // namespace BR