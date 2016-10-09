/**
 * @file
 * @brief 检查赋值运算符重载
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否重载了特定参数的赋值运算符
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IntegerConstant
 * @see NotAssignable
 *
 * 如果表达式 <tt>BR::make_rvalue<T>() = BR::make_rvalue<TSrc>()</tt> 在非求值上下文中是合法的，
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

#if defined(BR_CXX14)

/**
 * @brief IsAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsAssignable
 * @see not_assignable
 */
template< typename T, typename TArg >
constexpr auto is_assignable = bool_constant< IsAssignable< T, TArg > >;

/**
 * @brief NotAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see NotAssignable
 * @see is_assignable
 */
template< typename T, typename TArg >
constexpr auto not_assignable = bool_constant< NotAssignable< T, TArg > >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

struct IsAssignableTest {
	template< typename T, typename TArg, typename = decltype(make_rvalue<T>() = make_rvalue<TArg>()) >
	static auto test(int) -> BooleanTrue;

	template< typename T, typename TArg >
	static auto test(...) -> BooleanFalse;
};

template< typename T, typename TArg >
using IsAssignable = decltype(IsAssignableTest::test< T, TArg >(0));

} // namespace TypeTraits
} // namespace Detail

template< typename T, typename TArg >
struct IsAssignable : public BooleanRewrapPositive< Detail::TypeTraits::IsAssignable< T, TArg > > {};

template< typename T, typename TArg >
struct NotAssignable : public BooleanRewrapNegative< Detail::TypeTraits::IsAssignable< T, TArg > > {};

} // namespace BR