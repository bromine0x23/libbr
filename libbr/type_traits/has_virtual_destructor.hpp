/**
 * @file
 * @brief 检查是否具有虚析构函数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有虚析构函数
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see BR_HAS_VIRTUAL_DESTRUCTOR
 * @see HasDestructor
 * @see NoVirtualDestructor
 *
 * 如果 \em T 具有虚析构函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasVirtualDestructor;

/**
 * @brief HasVirtualDestructor 的否定
 * @tparam T 待检查类型
 * @see HasVirtualDestructor
 */
template< typename T >
struct NoVirtualDestructor;

/**
 * @brief HasVirtualDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasVirtualDestructor
 * @see no_virtual_destructor
 */
template< typename T >
constexpr auto has_virtual_destructor = boolean_constant< HasVirtualDestructor<T> >;

/**
 * @brief NoVirtualDestructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoVirtualDestructor
 * @see has_virtual_destructor
 */
template< typename T >
constexpr auto no_virtual_destructor = boolean_constant< NoVirtualDestructor<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

#if defined(BR_HAS_VIRTUAL_DESTRUCTOR)

template< typename T >
using HasVirtualDestructor = BooleanConstant< BR_HAS_VIRTUAL_DESTRUCTOR(T) >;

#else

template< typename T >
using HasVirtualDestructor = BooleanFalse;

#endif // BR_HAS_VIRTUAL_DESTRUCTOR

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct HasVirtualDestructor : public BooleanRewrapPositive< _::TypeTraits::HasVirtualDestructor<T> > {};

template< typename T >
struct NoVirtualDestructor : public BooleanRewrapNegative< _::TypeTraits::HasVirtualDestructor<T> > {};

} // namespace TypeTraits

} // namespace BR
