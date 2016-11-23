/**
 * @file
 * @brief 指针类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是指针类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotPointer
 *
 * 如果 \em T 是对象指针类型或函数指针类型(但不是空指针或非静态成员对象或成员函数指针)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsPointer;

/**
 * @brief IsPointer 的否定
 * @tparam T 待检查类型
 * @see IsPointer
 */
template< typename T >
struct NotPointer;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsPointer
 * @see not_pointer
 */
template< typename T >
constexpr auto is_pointer = boolean_constant< IsPointer<T> >;

/**
 * @brief NotPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotPointer
 * @see is_pointer
 */
template< typename T >
constexpr auto not_pointer = boolean_constant< NotPointer<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsPointerBasic : public BooleanFalse {};

template< typename T >
struct IsPointerBasic< T * > : public BooleanTrue {};

template< typename T >
using IsPointer = BooleanAnd< IsPointerBasic< RemoveConstVolatile<T> >, NotMemberPointer<T> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsPointer : public BooleanRewrapPositive< Detail::TypeTraits::IsPointer<T> > {};

template< typename T >
struct NotPointer : public BooleanRewrapNegative< Detail::TypeTraits::IsPointer<T> > {};

} // namespace TypeTraits

} // namespace BR