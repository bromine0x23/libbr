/**
 * @file
 * @brief 复合类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_fundamental.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsCompound = BooleanNot< IsFundamental<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是复合类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsFundamental
 * @see NotCompound
 *
 * 如果T是复合类型(非基本类型，包括数组、函数、对象指针、函数指针、成员对象指针、成员函数指针、引用、类、联合、枚举及其cv变种)，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsCompound : Boolean< Detail::TypeOperate::IsCompound<T> > {};

/**
 * @brief IsCompound 的否定
 * @tparam T 待检查类型
 * @see IsCompound
 */
template< typename T >
struct NotCompound : BooleanNot< Detail::TypeOperate::IsCompound<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsCompound 的模板变量版本
 * @tparam T 待检查类型
 * @see IsCompound
 * @see not_compound
 */
template< class T >
constexpr auto is_compound = IsCompound<T>::value;

/**
 * @brief NotCompound 的模板变量版本
 * @tparam T 待检查类型
 * @see NotCompound
 * @see is_compound
 */
template< class T >
constexpr auto not_compound = NotCompound<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR


