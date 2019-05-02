/**
 * @file
 * @brief 成员指针检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是成员指针
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsMemberFunctionPointer
 * @see IsMemberObjectPointer
 * @see NotMemberPointer
 *
 * 如果 \em T 是指向非静态成员的指针类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsMemberPointer;

/**
 * @brief IsMemberPointer 的否定
 * @tparam T 待检查类型
 * @see IsMemberPointer
 */
template< typename T >
struct NotMemberPointer;

/**
 * @brief IsMemberPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMemberPointer
 * @see not_member_pointer
 */
template< typename T >
constexpr auto is_member_pointer = boolean_constant< IsMemberPointer<T> >;

/**
 * @brief NotMemberPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMemberPointer
 * @see is_member_pointer
 */
template< typename T >
constexpr auto not_member_pointer = boolean_constant< NotMemberPointer<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
struct IsMemberPointerBasic : public BooleanFalse {};

template< typename TClass, typename TMember >
struct IsMemberPointerBasic< TMember TClass::* > : public BooleanTrue {};

template< typename T >
using IsMemberPointer = IsMemberPointerBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsMemberPointer : public BooleanRewrapPositive< _::TypeTraits::IsMemberPointer<T> > {};

template< typename T >
struct NotMemberPointer : public BooleanRewrapNegative< _::TypeTraits::IsMemberPointer<T> > {};

} // namespace TypeTraits

} // namespace BR
