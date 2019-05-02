/**
 * @file
 * @brief 成员函数指针检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_function.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是成员函数指针
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see NotMemberFunctionPointer
 *
 * 如果 \em T 是指向非静态成员函数的指针类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsMemberFunctionPointer;

/**
 * @brief IsMemberFunctionPointer 的否定
 * @tparam T 待检查类型
 * @see IsMemberFunctionPointer
 */
template< typename T >
struct NotMemberFunctionPointer;

/**
 * @brief IsMemberFunctionPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMemberFunctionPointer
 * @see not_member_function_pointer
 */
template< typename T >
constexpr auto is_member_function_pointer = boolean_constant< IsMemberFunctionPointer<T> >;

/**
 * @brief NotMemberFunctionPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMemberFunctionPointer
 * @see is_member_function_pointer
 */
template< typename T >
constexpr auto not_member_function_pointer = boolean_constant< NotMemberFunctionPointer<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
struct IsMemberFunctionPointerBasic : public BooleanFalse {};

template< typename TClass, typename TMember >
struct IsMemberFunctionPointerBasic< MemberPointer<TClass, TMember> > : public IsFunction<TMember> {};

template< typename T >
using IsMemberFunctionPointer = IsMemberFunctionPointerBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsMemberFunctionPointer : public BooleanRewrapPositive< _::TypeTraits::IsMemberFunctionPointer<T> > {};

template< typename T >
struct NotMemberFunctionPointer : public BooleanRewrapNegative< _::TypeTraits::IsMemberFunctionPointer<T> > {};

} // namespace TypeTraits

} // namespace BR

