/**
 * @file
 * @brief 检查是否具有拷贝构造函数
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_constructible.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否具有拷贝构造函数
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsConstructible
 * @see BR::NoCopyConstructor
 *
 * 如果 \em T 具有拷贝构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasCopyConstructor;

/**
 * @brief HasCopyConstructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasCopyConstructor
 */
template< typename T >
struct NoCopyConstructor;

#if defined(BR_CXX14)

/**
 * @brief HasCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasCopyConstructor
 * @see BR::no_copy_constructor
 */
template< typename T >
constexpr auto has_copy_constructor = bool_constant< HasCopyConstructor<T> >;

/**
 * @brief NoCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoCopyConstructor
 * @see BR::has_copy_constructor
 */
template< typename T >
constexpr auto no_copy_constructor = bool_constant< NoCopyConstructor<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasCopyConstructor = IsConstructible< T, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasCopyConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasCopyConstructor<T> > {};

template< typename T >
struct NoCopyConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasCopyConstructor<T> > {};

} // namespace BR