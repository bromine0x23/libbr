/**
 * @file
 * @brief 函数类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_reference.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否是函数类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotFunction
 *
 * 如果\em T 是函数类型(不包括lambda等可调用对象)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsFunction;

/**
 * @brief IsFunction 的否定
 * @tparam T 待检查类型
 * @see IsFunction
 */
template< typename T >
struct NotFunction;

#if defined(BR_CXX14)

/**
 * @brief IsFunction 的模板变量版本
 * @tparam T 待检查类型
 * @see IsFunction
 * @see not_function
 */
template< typename T >
constexpr auto is_function = bool_constant< IsFunction<T> >;

/**
 * @brief NotFunction 的模板变量版本
 * @tparam T 待检查类型
 * @see NotFunction
 * @see is_function
 */
template< typename T >
constexpr auto not_function = bool_constant< NotFunction<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsFunction : BooleanFalse {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)               > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const         > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)       volatile> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const volatile> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)               > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const         > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)       volatile> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const volatile> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)                &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const          &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)       volatile &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const volatile &> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)                &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const          &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)       volatile &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const volatile &> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)                &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const          &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)       volatile &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const volatile &&> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)                &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const          &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)       volatile &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const volatile &&> : BooleanTrue {};

#if defined(BR_MSVC)

template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...)               > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...) const         > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...)       volatile> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...) const volatile> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...)               > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...) const         > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...)       volatile> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...) const volatile> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...)                &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...) const          &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...)       volatile &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...) const volatile &> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...)                &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...) const          &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...)       volatile &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...) const volatile &> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...)                &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...) const          &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...)       volatile &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs...) const volatile &&> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...)                &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...) const          &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...)       volatile &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __stdcall (TArgs..., ...) const volatile &&> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...)               > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...) const         > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...)       volatile> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...) const volatile> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...)               > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...) const         > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...)       volatile> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...) const volatile> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...)                &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...) const          &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...)       volatile &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...) const volatile &> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...)                &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...) const          &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...)       volatile &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...) const volatile &> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...)                &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...) const          &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...)       volatile &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...) const volatile &&> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...)                &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...) const          &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...)       volatile &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs..., ...) const volatile &&> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...)               > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...) const         > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...)       volatile> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __fastcall (TArgs...) const volatile> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...)               > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...) const         > : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...)       volatile> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...) const volatile> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs...)                &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs...) const          &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs...)       volatile &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs...) const volatile &> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...)                &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...) const          &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...)       volatile &> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...) const volatile &> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs...)                &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs...) const          &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs...)       volatile &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs...) const volatile &&> : BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...)                &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...) const          &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...)       volatile &&> : BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult __cdecl (TArgs..., ...) const volatile &&> : BooleanTrue {};

#endif

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsFunction : BooleanRewrapPositive< Detail::TypeTraits::IsFunction<T> > {};

template< typename T >
struct NotFunction : BooleanRewrapNegative< Detail::TypeTraits::IsFunction<T> > {};

} // namespace BR