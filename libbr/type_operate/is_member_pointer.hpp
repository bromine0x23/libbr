/**
 * @file
 * @brief 成员指针检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_member_function_pointer.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsMemberPointer : IsMemberFunctionPointer<T> {};

template< typename TClass, typename TMember >
struct IsMemberPointer< TMember TClass::* > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是成员指针
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsMemberFunctionPointer
 * @see IsMemberObjectPointer
 * @see NotMemberPointer
 *
 * 如果 \em T 是指向非静态成员的指针类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsMemberPointer : Boolean< Detail::TypeOperate::IsMemberPointer<T> > {};

/**
 * @brief IsMemberPointer 的否定
 * @tparam T 待检查类型
 * @see IsMemberPointer
 */
template< typename T >
struct NotMemberPointer : BooleanNot< Detail::TypeOperate::IsMemberPointer<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsMemberPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMemberPointer
 * @see not_member_pointer
 */
template< typename T >
constexpr auto is_member_pointer = IsMemberPointer<T>::value;

/**
 * @brief NotMemberPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMemberPointer
 * @see is_member_pointer
 */
template< typename T >
constexpr auto not_member_pointer = NotMemberPointer<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
