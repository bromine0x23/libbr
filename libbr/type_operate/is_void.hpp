/**
 * @file
 * @brief \em void 类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

using BR::RemoveConstVolatile;

template< typename T >
struct IsVoidBasic : BooleanFalse {};

template<>
struct IsVoidBasic< void > : BooleanTrue {};

template< typename T >
using IsVoid = IsVoidBasic< RemoveConstVolatile<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是 \em void 类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotVoid
 *
 * 如果 \em T 是 \em void 类型(包括带CV修饰的版本)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsVoid : Boolean< Detail::TypeOperate::IsVoid<T> > {};

/**
 * @brief IsVoid 的否定
 * @tparam T 待检查类型
 * @see IsVoid
 */
template< typename T >
struct NotVoid : BooleanNot< Detail::TypeOperate::IsVoid<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsVoid 的模板变量版本
 * @tparam T 待检查类型
 * @see IsVoid
 * @see not_void
 */
template< typename T >
constexpr auto is_void = IsVoid<T>::value;

/**
 * @brief NotVoid 的模板变量版本
 * @tparam T 待检查类型
 * @see NotVoid
 * @see is_void
 */
template< typename T >
constexpr auto not_void = NotVoid<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
