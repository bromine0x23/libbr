/**
 * @file
 * @brief 检查是否具有虚析构函数
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_VIRTUAL_DESTRUCTOR)

template< typename T >
using HasVirtualDestructor = BooleanConstant< BR_HAS_VIRTUAL_DESTRUCTOR(T) >;

#else

template< typename T >
using HasVirtualDestructor = BooleanFalse;

#endif // BR_HAS_VIRTUAL_DESTRUCTOR

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有虚析构函数
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_HAS_VIRTUAL_DESTRUCTOR
 * @see BR::HasDestructor
 * @see BR::NoVirtualDestructor
 *
 * 如果 \em T 具有虚析构函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasVirtualDestructor : BooleanRewrapPositive< Detail::TypeOperate::HasVirtualDestructor<T> > {};

/**
 * @brief HasVirtualDestructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasVirtualDestructor
 */
template< typename T >
struct NoVirtualDestructor : BooleanRewrapNegative< Detail::TypeOperate::HasVirtualDestructor<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasVirtualDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasVirtualDestructor
 * @see BR::no_virtual_destructor
 */
template< typename T >
constexpr auto has_virtual_destructor = bool_constant< HasVirtualDestructor<T> >;

/**
 * @brief NoVirtualDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoVirtualDestructor
 * @see BR::has_virtual_destructor
 */
template< typename T >
constexpr auto no_virtual_destructor = bool_constant< NoVirtualDestructor<T> >;

#endif // defined(BR_CXX14)

} // namespace BR
