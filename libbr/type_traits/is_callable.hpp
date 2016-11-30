/**
 * @file
 * @brief IsCallable
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/functional/invoke.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief IsCallable
 * @tparam TCallable
 * @tparam TArgs
 * @see IntegerConstant
 * @see NotCallable
 *
 * 如果可以对 \em TCallable 以参数 \em TArgs 进行函数调用，那么封装的值为 \em true ；否则为 \em false
 */
template< typename TCallable, typename... TArgs >
struct IsCallable;

/**
 * @brief IsCallable 的否定
 * @tparam TCallable
 * @tparam TArgs
 * @see IsCallable
 */
template< typename TCallable, typename... TArgs >
struct NotCallable;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsCallable 的模板变量版本
 * @tparam TCallable
 * @tparam TArgs
 * @see IsCallable
 * @see not_callable
 */
template< typename TCallable, typename... TArgs >
constexpr auto is_callable = boolean_constant< IsCallable< TCallable, TArgs... > >;

/**
 * @brief NotCallable 的模板变量版本
 * @tparam TCallable
 * @tparam TArgs
 * @see NotCallable
 * @see is_callable
 */
template< typename TCallable, typename... TArgs >
constexpr auto not_callable = boolean_constant< NotCallable< TCallable, TArgs... > >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



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

inline namespace TypeTraits {

template< typename TCallable, typename... TArgs >
struct IsCallable : public BooleanRewrapPositive< Detail::TypeTraits::IsCallable< TCallable, TArgs... > > {};

template< typename TCallable, typename... TArgs >
struct NotCallable : public BooleanRewrapNegative< Detail::TypeTraits::IsCallable< TCallable, TArgs... > > {};

} // namespace TypeTraits

} // namespace BR
