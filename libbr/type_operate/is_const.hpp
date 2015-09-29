/**
 * @file
 * @brief \em const 修饰符检查
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
struct IsConst : BooleanFalse {};

template< typename T >
struct IsConst< T const > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否包含 \em const 修饰符
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotConst
 *
 * 如果T包含 \em const 修饰符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsConst : Boolean< Detail::TypeOperate::IsConst<T> > {};

/**
 * @brief IsConst 的否定
 * @tparam T 待检查类型
 * @see IsConst
 */
template< typename T >
struct NotConst : BooleanNot< Detail::TypeOperate::IsConst<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsConst 的模板变量版本
 * @tparam T 待检查类型
 * @see IsConst
 * @see not_const
 */
template< class T >
constexpr auto is_const = IsConst<T>::value;

/**
 * @brief NotConst 的模板变量版本
 * @tparam T 待检查类型
 * @see NotConst
 * @see is_const
 */
template< class T >
constexpr auto not_const = NotConst<T>::value;

#endif // defined(BR_CXX14)


} // namespace BR
