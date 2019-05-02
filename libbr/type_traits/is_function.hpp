/**
 * @file
 * @brief 函数类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

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

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
struct IsFunction : BooleanFalse {};

template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...)                -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...) const          -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...)       volatile -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...) const volatile -> TResult > : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...)                & -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...) const          & -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...)       volatile & -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...) const volatile & -> TResult > : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...)                && -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...) const          && -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...)       volatile && -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs...) const volatile && -> TResult > : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...)                -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...) const          -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...)       volatile -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...) const volatile -> TResult > : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...)                & -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...) const          & -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...)       volatile & -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...) const volatile & -> TResult > : public BooleanTrue {};

template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...)                && -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...) const          && -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...)       volatile && -> TResult > : public BooleanTrue {};
template< typename TResult, typename... TArgs > struct IsFunction<auto (TArgs..., ...) const volatile && -> TResult > : public BooleanTrue {};

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsFunction : public BooleanRewrapPositive< _::TypeTraits::IsFunction<T> > {};

template< typename T >
struct NotFunction : public BooleanRewrapNegative< _::TypeTraits::IsFunction<T> > {};

} // namespace TypeTraits

} // namespace BR