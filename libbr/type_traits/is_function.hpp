/**
 * @file
 * @brief 函数类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_reference.hpp>

namespace BR {

inline namespace TypeTraits {

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

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsFunction 的模板变量版本
 * @tparam T 待检查类型
 * @see IsFunction
 * @see not_function
 */
template< typename T >
constexpr auto is_function = boolean_constant< IsFunction<T> >;

/**
 * @brief NotFunction 的模板变量版本
 * @tparam T 待检查类型
 * @see NotFunction
 * @see is_function
 */
template< typename T >
constexpr auto not_function = boolean_constant< NotFunction<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsFunction : BooleanFalse {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)               > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const         > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)       volatile> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const volatile> : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)               > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const         > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)       volatile> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const volatile> : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)                &> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const          &> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)       volatile &> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const volatile &> : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)                &> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const          &> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)       volatile &> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const volatile &> : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)                &&> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const          &&> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...)       volatile &&> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs...) const volatile &&> : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)                &&> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const          &&> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...)       volatile &&> : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<TResult(TArgs..., ...) const volatile &&> : public BooleanTrue {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsFunction : public BooleanRewrapPositive< Detail::TypeTraits::IsFunction<T> > {};

template< typename T >
struct NotFunction : public BooleanRewrapNegative< Detail::TypeTraits::IsFunction<T> > {};

} // namespace TypeTraits

} // namespace BR