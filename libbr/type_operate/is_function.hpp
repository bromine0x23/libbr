#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_pointer.hpp>
#include <libbr/type_operate/is_reference.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_MSVC) || defined(BR_WIN32)

template< typename TResult, typename ... TArguments >
BooleanTrue is_function_pointer_tester(TResult(*)(TArguments ...));

template< typename TResult, typename ... TArguments >
BooleanTrue is_function_pointer_tester(TResult(__stdcall *)(TArguments ...));

template< typename TResult, typename ... TArguments >
BooleanTrue is_function_pointer_tester(TResult(__fastcall *)(TArguments ...));

template< typename TResult, typename ... TArguments >
BooleanTrue is_function_pointer_tester(TResult(__cdecl *)(TArguments ...));

BooleanFalse is_function_pointer_tester(...);

template< typename T >
using IsFunctionBasic = decltype(is_function_pointer_tester(static_cast< T * >(nullptr)));

#else

template< typename T >
struct IsFunctionPointer : BooleanFalse {};

template< typename TResult, typename ... TArguments >
struct IsFunctionPointer< TResult(*)(TArguments ...) > : BooleanTrue {};

template< typename T >
using IsFunctionBasic = IsFunctionPointer< AddPointer< T > >;

#endif // BR_MSVC

template< typename T >
using IsFunction = BooleanAnd< NotReference< T >, IsFunctionBasic< T > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsFunction : Boolean< Detail::TypeOperate::IsFunction< T > > {};

template< typename T >
struct NotFunction : BooleanNot< Detail::TypeOperate::IsFunction< T > > {};

} // namespace BR