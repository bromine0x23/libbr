/**
 * @file
 * @brief 函数类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_reference.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename TResult, typename... TArgs >
auto is_function_pointer_tester(TResult(* pointer)(TArgs...)) -> BooleanTrue;

template< typename TResult, typename... TArgs >
auto is_function_pointer_tester(TResult(* pointer)(TArgs..., ...)) -> BooleanTrue;

#if defined(BR_MSVC) || defined(BR_WIN32)

template< typename TResult, typename... TArgs >
auto is_function_pointer_tester(TResult(__stdcall * pointer)(TArgs...)) -> BooleanTrue;

template< typename TResult, typename... TArgs >
auto is_function_pointer_tester(TResult(__stdcall * pointer)(TArgs..., ...)) -> BooleanTrue;

template< typename TResult, typename... TArgs >
auto is_function_pointer_tester(TResult(__fastcall * pointer)(TArgs...)) -> BooleanTrue;

template< typename TResult, typename... TArgs >
auto is_function_pointer_tester(TResult(__fastcall * pointer)(TArgs..., ...)) -> BooleanTrue;

template< typename TResult, typename... TArgs >
auto is_function_pointer_tester(TResult(__cdecl * pointer)(TArgs...)) -> BooleanTrue;

template< typename TResult, typename... TArgs >
auto is_function_pointer_tester(TResult(__cdecl * pointer)(TArgs..., ...)) -> BooleanTrue;

#endif // defined(BR_MSVC) || defined(BR_WIN32)

auto is_function_pointer_tester(...) -> BooleanFalse;

template< typename T >
struct IsFunctionBasic : decltype(is_function_pointer_tester(static_cast< T * >(nullptr))) {
};

template< typename T >
using IsFunction = BooleanAnd< NotReference<T>, IsFunctionBasic<T> >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是函数类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotFunction
 *
 * 如果\em T 是函数类型(不包括lambda等可调用对象)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsFunction : BooleanRewrapPositive< Detail::TypeTraits::IsFunction<T> > {};

/**
 * @brief IsFunction 的否定
 * @tparam T 待检查类型
 * @see IsFunction
 */
template< typename T >
struct NotFunction : BooleanRewrapNegative< Detail::TypeTraits::IsFunction<T> > {};

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

} // namespace BR