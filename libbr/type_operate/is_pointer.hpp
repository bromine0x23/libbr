/**
 * @file
 * @brief 指针类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_member_pointer.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsPointerBasic : BooleanFalse {};

template< typename T >
struct IsPointerBasic< T * > : BooleanTrue {};

template< typename T >
using IsPointer = BooleanAnd< IsPointerBasic< RemoveConstVolatile<T> >, NotMemberPointer<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是指针类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotPointer
 *
 * 如果 \em T 是对象指针类型或函数指针类型(但不是空指针或非静态成员对象或成员函数指针)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsPointer : Boolean< Detail::TypeOperate::IsPointer<T> > {};

/**
 * @brief IsPointer 的否定
 * @tparam T 待检查类型
 * @see IsPointer
 */
template< typename T >
struct NotPointer : BooleanNot< Detail::TypeOperate::IsPointer<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsPointer
 * @see not_pointer
 */
template< typename T >
constexpr auto is_pointer = IsPointer<T>::value;

/**
 * @brief NotPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotPointer
 * @see is_pointer
 */
template< typename T >
constexpr auto not_pointer = NotPointer<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR