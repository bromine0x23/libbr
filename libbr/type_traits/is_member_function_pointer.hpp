/**
 * @file
 * @brief 成员函数指针检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否是成员函数指针
 * @tparam T 待检查类型
 * @see IntegerConstant
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

#if defined(BR_CXX14)

/**
 * @brief IsMemberFunctionPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMemberFunctionPointer
 * @see not_member_function_pointer
 */
template< typename T >
constexpr auto is_member_function_pointer = bool_constant< IsMemberFunctionPointer<T> >;

/**
 * @brief NotMemberFunctionPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMemberFunctionPointer
 * @see is_member_function_pointer
 */
template< typename T >
constexpr auto not_member_function_pointer = bool_constant< NotMemberFunctionPointer<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsMemberFunctionPointerBasic : public BooleanFalse {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs...)                > : public BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs...) const          > : public BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs...)       volatile > : public BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs...) const volatile > : public BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs..., ...)                > : public BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs..., ...) const          > : public BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs..., ...)       volatile > : public BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs..., ...) const volatile > : public BooleanTrue {};

template< typename T >
using IsMemberFunctionPointer = IsMemberFunctionPointerBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsMemberFunctionPointer : public BooleanRewrapPositive< Detail::TypeTraits::IsMemberFunctionPointer<T> > {};

template< typename T >
struct NotMemberFunctionPointer : public BooleanRewrapNegative< Detail::TypeTraits::IsMemberFunctionPointer<T> > {};

} // namespace BR

