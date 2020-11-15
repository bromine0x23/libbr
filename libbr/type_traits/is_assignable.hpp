/**
 * @file
 * @brief 检查赋值运算符重载
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#if !defined(BR_IS_ASSIGNABLE)
#  include <libbr/utility/declare_value.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否重载了特定参数的赋值运算符
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see Utility::IntegralConstant
 * @see NotAssignable
 *
 * 如果表达式 <tt>BR::declare_value<T>() = BR::declare_value<TSrc>()</tt> 在非求值上下文中是合法的，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename TArg >
struct IsAssignable;

/**
 * @brief IsAssignable 的否定
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsAssignable
 */
template< typename T, typename TArg >
struct NotAssignable;

/**
 * @brief IsAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsAssignable
 * @see not_assignable
 */
template< typename T, typename TArg >
constexpr auto is_assignable = boolean_constant< IsAssignable< T, TArg > >;

/**
 * @brief NotAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see NotAssignable
 * @see is_assignable
 */
template< typename T, typename TArg >
constexpr auto not_assignable = boolean_constant< NotAssignable< T, TArg > >;

} // namespace TypeTraits



namespace _::TypeTraits {

#if defined(BR_IS_ASSIGNABLE)

template< typename T, typename TArg >
using IsAssignable = BooleanConstant< BR_IS_ASSIGNABLE(T, TArg) >;

#else

struct IsAssignableTest {
	template< typename T, typename TArg, typename = decltype(declare_value<T>() = declare_value<TArg>()) >
	static auto test(int) -> BooleanTrue;

	template< typename T, typename TArg >
	static auto test(...) -> BooleanFalse;
};

template< typename T, typename TArg >
using IsAssignable = decltype(IsAssignableTest::test< T, TArg >(0));

#endif // defined(BR_IS_ASSIGNABLE)

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T, typename TArg >
struct IsAssignable : public BooleanRewrapPositive< _::TypeTraits::IsAssignable< T, TArg > > {};

template< typename T, typename TArg >
struct NotAssignable : public BooleanRewrapNegative< _::TypeTraits::IsAssignable< T, TArg > > {};

} // namespace TypeTraits

} // namespace BR