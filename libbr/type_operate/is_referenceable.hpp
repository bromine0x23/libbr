/**
 * @file
 * @brief 可引用性检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_function.hpp>
#include <libbr/type_operate/is_object.hpp>
#include <libbr/type_operate/is_reference.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsReferenceable = BooleanOr< IsObject<T>, IsReference<T>, IsFunction<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否可引用
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsFunction
 * @see IsObject
 * @see IsReference
 * @see NotReferenceable
 *
 * 如果\em T 可引用(对象类型、引用类型、函数类型)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsReferenceable : Boolean< Detail::TypeOperate::IsReferenceable<T> > {};

/**
 * @brief IsReferenceable 的否定
 * @tparam T 待检查类型
 * @see IsReferenceable
 */
template< typename T >
struct NotReferenceable : BooleanNot< Detail::TypeOperate::IsReferenceable<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsReferenceable 的模板变量版本
 * @tparam T 待检查类型
 * @see IsReferenceable
 * @see not_referenceable
 */
template< typename T >
constexpr auto is_referenceable = IsReferenceable<T>::value;

/**
 * @brief NotReferenceable 的模板变量版本
 * @tparam T 待检查类型
 * @see NotReferenceable
 * @see is_referenceable
 */
template< typename T >
constexpr auto not_referenceable = NotReferenceable<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
