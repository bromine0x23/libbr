#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsMemberFunctionPointerBasic : BooleanFalse {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArguments ...) > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArguments ...) const > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArguments ...) volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(TClass::*)(TArguments ...) const volatile > : BooleanTrue {};

#if defined(BR_MSVC)

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__stdcall TClass::*)(TArguments ...) > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__stdcall TClass::*)(TArguments ...) const > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__stdcall TClass::*)(TArguments ...) volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__stdcall TClass::*)(TArguments ...) const volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__fastcall TClass::*)(TArguments ...) > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__fastcall TClass::*)(TArguments ...) const > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__fastcall TClass::*)(TArguments ...) volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__fastcall TClass::*)(TArguments ...) const volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__cdecl TClass::*)(TArguments ...) > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__cdecl TClass::*)(TArguments ...) const > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__cdecl TClass::*)(TArguments ...) volatile > : BooleanTrue {};

template< typename TResult, typename TClass, typename ... TArguments >
struct IsMemberFunctionPointerBasic< TResult(__cdecl TClass::*)(TArguments ...) const volatile > : BooleanTrue {};

#endif

template< typename T >
using IsMemberFunctionPointer = IsMemberFunctionPointerBasic< RemoveConstVolatile< T > >;

} // namespace Detail

template< typename T >
struct IsMemberFunctionPointer : Boolean< Detail::IsMemberFunctionPointer< T > > {};

template< typename T >
struct NotMemberFunctionPointer : BooleanNot< Detail::IsMemberFunctionPointer< T > > {};

} // namespace TypeOperate
} // namespace BR

