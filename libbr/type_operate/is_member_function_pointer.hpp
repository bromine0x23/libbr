/**
 * @file
 * @brief 成员函数指针检查
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
struct IsMemberFunctionPointerBasic : BooleanFalse {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs...) > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs...) const > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs...) volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArgs...) const volatile > : BooleanTrue {};

#if defined(BR_MSVC)

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__stdcall TClass::*)(TArgs...) > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__stdcall TClass::*)(TArgs...) const > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__stdcall TClass::*)(TArgs...) volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__stdcall TClass::*)(TArgs...) const volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__fastcall TClass::*)(TArgs...) > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__fastcall TClass::*)(TArgs...) const > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__fastcall TClass::*)(TArgs...) volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__fastcall TClass::*)(TArgs...) const volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__cdecl TClass::*)(TArgs...) > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__cdecl TClass::*)(TArgs...) const > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__cdecl TClass::*)(TArgs...) volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename... TArgs >
struct IsMemberFunctionPointerBasic< TResult(__cdecl TClass::*)(TArgs...) const volatile > : BooleanTrue {};

#endif

template< typename T >
using IsMemberFunctionPointer = IsMemberFunctionPointerBasic< RemoveConstVolatile<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是成员函数指针
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotMemberFunctionPointer
 *
 * 如果 \em T 是指向非静态成员函数的指针类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsMemberFunctionPointer : Boolean< Detail::TypeOperate::IsMemberFunctionPointer<T> > {};

/**
 * @brief IsMemberFunctionPointer 的否定
 * @tparam T 待检查类型
 * @see IsMemberFunctionPointer
 */
template< typename T >
struct NotMemberFunctionPointer : BooleanNot< Detail::TypeOperate::IsMemberFunctionPointer<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsMemberFunctionPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see IsMemberFunctionPointer
 * @see not_member_function_pointer
 */
template< typename T >
constexpr auto is_member_function_pointer = IsMemberFunctionPointer<T>::value;

/**
 * @brief NotMemberFunctionPointer 的模板变量版本
 * @tparam T 待检查类型
 * @see NotMemberFunctionPointer
 * @see is_member_function_pointer
 */
template< typename T >
constexpr auto not_member_function_pointer = NotMemberFunctionPointer<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR

