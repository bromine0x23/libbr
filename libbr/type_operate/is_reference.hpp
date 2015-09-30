/**
 * @file
 * @brief 引用类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_lvalue_reference.hpp>
#include <libbr/type_operate/is_rvalue_reference.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsReference = BooleanOr< IsLValueReference<T>, IsRValueReference<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是引用类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsLValueReference
 * @see IsRValueReference
 * @see NotLValueReference
 *
 * 如果\em T 是引用类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsReference : Boolean< Detail::TypeOperate::IsReference<T> > {};

/**
 * @brief IsReference 的否定
 * @tparam T 待检查类型
 * @see IsReference
 */
template< typename T >
struct NotReference : BooleanNot< Detail::TypeOperate::IsReference<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsReference 的模板变量版本
 * @tparam T 待检查类型
 * @see IsReference
 * @see not_reference
 */
template< typename T >
constexpr auto is_reference = IsReference<T>::value;

/**
 * @brief NotReference 的模板变量版本
 * @tparam T 待检查类型
 * @see NotReference
 * @see is_reference
 */
template< typename T >
constexpr auto not_reference = NotReference<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
