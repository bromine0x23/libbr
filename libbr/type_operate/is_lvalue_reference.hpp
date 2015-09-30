/**
 * @file
 * @brief 左值引用类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsLValueReference : BooleanFalse {};

template< typename T >
struct IsLValueReference< T & > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是左值引用类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotLValueReference
 *
 * 如果\em T 是左值引用类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsLValueReference : Boolean< Detail::TypeOperate::IsLValueReference<T> > {};

/**
 * @brief IsLValueReference 的否定
 * @tparam T 待检查类型
 * @see IsLValueReference
 */
template< typename T >
struct NotLValueReference : BooleanNot< Detail::TypeOperate::IsLValueReference<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsLValueReference 的模板变量版本
 * @tparam T 待检查类型
 * @see IsLValueReference
 * @see not_lvalue_reference
 */
template< typename T >
constexpr auto is_lvalue_reference = IsLValueReference<T>::value;

/**
 * @brief NotLValueReference 的模板变量版本
 * @tparam T 待检查类型
 * @see NotLValueReference
 * @see is_lvalue_reference
 */
template< typename T >
constexpr auto not_lvalue_reference = NotLValueReference<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR