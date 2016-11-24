/**
 * @file
 * @brief 检查是否具有 \em nothrow 的(复制)赋值运算符
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/add_const.hpp>
#include <libbr/type_traits/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地拷贝赋值
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsNothrowAssignable
 * @see HasCopyAssignment
 * @see NoNothrowCopyAssignment
 *
 * 如果 \em T 可被 \em nothrow 地拷贝赋值，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowCopyAssignment;

/**
 * @brief HasNothrowCopyAssignment 的否定
 * @tparam T 待检查类型
 * @see HasNothrowCopyAssignment
 */
template< typename T >
struct NoNothrowCopyAssignment;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasNothrowCopyAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see HasNothrowCopyAssignment
 * @see no_nothrow_copy_assignment
 */
template< typename T >
constexpr auto has_nothrow_copy_assignment = boolean_constant< HasNothrowCopyAssignment<T> >;

/**
 * @brief NoNothrowCopyAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see NoNothrowCopyAssignment
 * @see has_nothrow_copy_assignment
 */
template< typename T >
constexpr auto no_nothrow_copy_assignment = boolean_constant< NoNothrowCopyAssignment<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits


namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowCopyAssignment = IsNothrowAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasNothrowCopyAssignment : BooleanRewrapPositive< Detail::TypeTraits::HasNothrowCopyAssignment<T> > {};

template< typename T >
struct NoNothrowCopyAssignment : BooleanRewrapNegative< Detail::TypeTraits::HasNothrowCopyAssignment<T> > {};

} // namespace TypeTraits

} // namespace BR