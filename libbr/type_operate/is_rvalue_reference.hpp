/**
 * @file
 * @brief 右值引用类型检查
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
struct IsRValueReference : BooleanFalse {};

template< typename T >
struct IsRValueReference< T && > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是右值引用类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsLValueReference
 * @see NotRValueReference
 *
 * 如果 \em T 是右值引用类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsRValueReference : Boolean< Detail::TypeOperate::IsRValueReference<T> > {};

/**
 * @brief IsRValueReference 的否定
 * @tparam T 待检查类型
 * @see IsRValueReference
 */
template< typename T >
struct NotRValueReference : BooleanNot< Detail::TypeOperate::IsRValueReference<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsRValueReference 的模板变量版本
 * @tparam T 待检查类型
 * @see IsRValueReference
 * @see not_rvalue_reference
 */
template< typename T >
constexpr auto is_rvalue_reference = IsRValueReference<T>::value;

/**
 * @brief NotRValueReference 的模板变量版本
 * @tparam T 待检查类型
 * @see NotRValueReference
 * @see is_rvalue_reference
 */
template< typename T >
constexpr auto not_rvalue_reference = NotRValueReference<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR