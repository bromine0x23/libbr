/**
 * @file
 * @brief 空指针类型检查
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

template< typename T >
struct IsNullPointerBasic : BooleanFalse {};

template<>
struct IsNullPointerBasic<NullPointer> : BooleanTrue {};

template< typename T >
struct IsNullPointer : IsNullPointerBasic< RemoveConstVolatile<T> > {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是空指针类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotNullPointer
 *
 * 如果 \em T 是空指针类型(\em nullptr 的类型)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNullPointer : Boolean< Detail::TypeOperate::IsNullPointer<T> > {};

/**
 * @brief IsNullPointer 的否定
 * @tparam T 待检查类型
 * @see IsNullPointer
 */
template< typename T >
struct NotNullPointer: BooleanNot< Detail::TypeOperate::IsNullPointer<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsNullPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsNullPointer
 * @see not_null_pointer
 */
template< typename T >
constexpr auto is_null_pointer = IsNullPointer<T>::value;

/**
 * @brief NotNullPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNullPointer
 * @see is_null_pointer
 */
template< typename T >
constexpr auto not_null_pointer = NotNullPointer<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
