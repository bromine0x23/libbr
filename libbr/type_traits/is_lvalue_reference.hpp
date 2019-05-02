/**
 * @file
 * @brief 左值引用类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是左值引用类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsRValueReference
 * @see NotLValueReference
 *
 * 如果 \em T 是左值引用类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsLValueReference;

/**
 * @brief IsLValueReference 的否定
 * @tparam T 待检查类型
 * @see IsLValueReference
 */
template< typename T >
struct NotLValueReference;

/**
 * @brief IsLValueReference 的模板变量版本
 * @tparam T 待检查类型
 * @see IsLValueReference
 * @see not_lvalue_reference
 */
template< typename T >
constexpr auto is_lvalue_reference = boolean_constant< IsLValueReference<T> >;

/**
 * @brief NotLValueReference 的模板变量版本
 * @tparam T 待检查类型
 * @see NotLValueReference
 * @see is_lvalue_reference
 */
template< typename T >
constexpr auto not_lvalue_reference = boolean_constant< NotLValueReference<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
struct IsLValueReference : public BooleanFalse {};

template< typename T >
struct IsLValueReference< T & > : public BooleanTrue {};

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsLValueReference : public BooleanRewrapPositive< _::TypeTraits::IsLValueReference<T> > {};

template< typename T >
struct NotLValueReference : public BooleanRewrapNegative< _::TypeTraits::IsLValueReference<T> > {};

} // namespace TypeTraits

} // namespace BR