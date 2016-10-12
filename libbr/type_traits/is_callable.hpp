/**
 * @file
 * @brief IsCallable
 * @author Bromine0x23
 * @since 2015/10/31
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/functional/invoke.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

/**
 * @brief IsCallable
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotCallable
 *
 * 如果 \em T 包含顶层 \em const 修饰，那么封装的值为 \em true ；否则为 \em false
 */
template< typename TCallable, typename... TArgs >
struct IsCallable;

/**
 * @brief IsCallable 的否定
 * @tparam T 待检查类型
 * @see IsCallable
 */
template< typename TCallable, typename... TArgs >
using NotCallable = BooleanNot< IsCallable< TCallable, TArgs... > >;

#if defined(BR_CXX14)

/**
 * @brief IsCallable 的模板变量版本
 * @tparam T 待检查类型
 * @see IsCallable
 * @see not_callable
 */
template< typename TCallable, typename... TArgs >
constexpr auto is_callable = bool_constant< IsCallable< TCallable, TArgs... > >;

/**
 * @brief NotCallable 的模板变量版本
 * @tparam T 待检查类型
 * @see NotCallable
 * @see is_callable
 */
template< typename TCallable, typename... TArgs >
constexpr auto not_callable = bool_constant< NotCallable< TCallable, TArgs... > >;

#endif // defined(BR_CXX14)

namespace Detail {
namespace TypeTraits {

struct IsCallableTest {
	template< typename TCallable, typename ... TArgs >
	static auto test(TCallable callable, TArgs && ... args) -> decltype(decltype(invoke(forward<TCallable>(callable), forward<TArgs>(args)...))(), BooleanTrue());

	static auto test(...) -> BooleanFalse;
};

template< typename TCallable, typename... TArgs >
struct IsCallableBasic : public decltype(IsCallableTest::test(make_rvalue<TCallable>(), make_rvalue<TArgs>() ...)) {};

template< typename TCallable, typename... TArgs >
struct IsCallable : public BooleanAnd< NotVoid<TCallable>, IsCallableBasic< TCallable, TArgs... > > {};

} // namespace TypeTraits
} // namespace Detail

template< typename TCallable, typename... TArgs >
struct IsCallable : public BooleanRewrap< Detail::TypeTraits::IsCallable< TCallable, TArgs... > > {
};

} // namespace BR
