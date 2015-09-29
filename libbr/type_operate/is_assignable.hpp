/**
 * @file
 * @brief 赋值运算符重载检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct IsAssignableTest {
	template< typename T, typename TSrc, typename = decltype(make_rvalue<T>() = make_rvalue<TSrc>()) >
	static BooleanTrue test(int);

	template< typename T, typename TSrc >
	static BooleanFalse test(...);
};

template< typename T, typename TSrc >
using IsAssignable = decltype(IsAssignableTest::test< T, TSrc >(0));

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否重载了特定参数的赋值运算符
 * @tparam T 待检查类型
 * @tparam TSrc 赋值参数
 * @see IntegerConstant
 * @see NotAssignable
 *
 * 如果表达式 <tt>BR::make_rvalue<T>() = BR::make_rvalue<TSrc>()</tt> 在非求值上下文中是合法的，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename TSrc >
struct IsAssignable : Boolean< Detail::TypeOperate::IsAssignable< T, TSrc > > {};

/**
 * @brief IsAssignable 的否定
 * @tparam T 待检查类型
 * @tparam TSrc 赋值参数
 * @see IsAssignable
 */
template< typename T, typename TSrc >
struct NotAssignable : BooleanNot< Detail::TypeOperate::IsAssignable< T, TSrc > > {};

#if defined(BR_CXX14)

/**
 * @brief IsAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TSrc 赋值参数
 * @see IsAssignable
 * @see not_assignable
 */
template< class T, typename TSrc >
constexpr auto is_assignable = IsAssignable< T, TSrc >::value;

/**
 * @brief NotAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TSrc 赋值参数
 * @see NotAssignable
 * @see is_assignable
 */
template< class T, typename TSrc >
constexpr auto not_assignable = NotAssignable< T, TSrc >::value;

#endif // defined(BR_CXX14)

} // namespace BR