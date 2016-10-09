/**
 * @file
 * @brief 检查是否具有平凡的拷贝构造函数
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_trivially_constructible.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否具有平凡的拷贝构造函数
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsTriviallyConstructible
 * @see BR::HasCopyConstructor
 * @see BR::NoTrivialCopyConstructor
 *
 * 如果 \em T 具有平凡的拷贝构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialCopyConstructor;

/**
 * @brief HasTrivialCopyConstructor 的否定
 * @tparam T 待检查类型
 * @see BR::HasTrivialCopyConstructor
 */
template< typename T >
struct NoTrivialCopyConstructor;

#if defined(BR_CXX14)

/**
 * @brief HasTrivialCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasTrivialCopyConstructor
 * @see BR::no_trivial_copy_constructor
 */
template< typename T >
constexpr auto has_trivial_copy_constructor = bool_constant< HasTrivialCopyConstructor<T> >;

/**
 * @brief NoTrivialCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoTrivialCopyConstructor
 * @see BR::has_trivial_copy_constructor
 */
template< typename T >
constexpr auto no_trivial_copy_constructor = bool_constant< NoTrivialCopyConstructor<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasTrivialCopyConstructor = IsTriviallyConstructible< T, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasTrivialCopyConstructor : public BooleanRewrapPositive< Detail::TypeTraits::HasTrivialCopyConstructor<T> > {};

template< typename T >
struct NoTrivialCopyConstructor : public BooleanRewrapNegative< Detail::TypeTraits::HasTrivialCopyConstructor<T> > {};

} // namespace BR