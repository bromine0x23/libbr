/**
 * @file
 * @brief 对象类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_function.hpp>
#include <libbr/type_operate/is_reference.hpp>
#include <libbr/type_operate/is_void.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsObject = BooleanAnd< NotReference<T>, NotVoid<T>, NotFunction<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是对象类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsScalar
 * @see IsArray
 * @see IsClass
 * @see IsUnion
 * @see NotObject
 *
 * 如果 \em T 是对象类型(标量、数组、类、或联合)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsObject : Boolean< Detail::TypeOperate::IsObject<T> > {};

/**
 * @brief IsObject 的否定
 * @tparam T 待检查类型
 * @see IsObject
 */
template< typename T >
struct NotObject : BooleanNot< Detail::TypeOperate::IsObject<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsObject 的模板变量版本
 * @tparam T 待检查类型
 * @see IsObject
 * @see not_object
 */
template< typename T >
constexpr auto is_object = IsObject<T>::value;

/**
 * @brief NotObject 的模板变量版本
 * @tparam T 待检查类型
 * @see NotObject
 * @see is_object
 */
template< typename T >
constexpr auto not_object = NotObject<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR

