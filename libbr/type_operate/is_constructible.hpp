/**
 * @file
 * @brief 构造函数重载检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_CONSTRUCTIBLE)
#  include <libbr/type_operate/is_base_of.hpp>
#  include <libbr/type_operate/is_default_constructible.hpp>
#  include <libbr/type_operate/is_destructible.hpp>
#  include <libbr/type_operate/is_static_castable.hpp>
#  include <libbr/type_operate/is_lvalue_reference.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_rvalue_reference.hpp>
#  include <libbr/type_operate/is_same.hpp>
#  include <libbr/type_operate/remove_reference.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_CONSTRUCTIBLE)

template< typename T, typename... TArgs >
using IsConstructible = BooleanConstant< BR_IS_CONSTRUCTIBLE(T, TArgs...) >;

#else

template< typename T, typename TArg >
using IsConstructibleOneBaseToDerivedReference = BooleanAnd<
	NotSame< T, TArg >,
	IsBaseOf< TArg, T >
>;

template< typename T, typename TArg >
using IsConstructibleOneLValueToRValueReference = BooleanAnd<
	NotFunction<TArg>,
	BooleanOr<
		NotSame< T, TArg >,
		IsBaseOf< TArg, T >
	>
>;

template< typename T, typename TArg >
using IsConstructibleReferenceCast = BooleanAnd<
	IsStaticCastable< TArg, T >,
	BooleanNot<
		BooleanOr<
			IsConstructibleOneBaseToDerivedReference< RemoveReference<T>, RemoveReference<TArg> >,
			BooleanAnd<
				IsRValueReference<T>,
				IsLValueReference<TArg>,
				IsConstructibleOneLValueToRValueReference< RemoveReference<T>, RemoveReference<TArg> >
			>
		>
	>
>;

struct IsConstructibleOneTest {
	template< typename T, typename TArg, typename = decltype(::new T(make_rvalue<TArg>())) >
	static BooleanTrue test(int);

	template< typename T, typename TArg >
	static BooleanFalse test(...);
};

template< typename T, typename TArg >
using IsConstructibleOneBasic = decltype(IsConstructibleOneTest::test< T, TArg >(0));

template< typename T, typename TArg >
using IsConstructibleOne = Conditional<
	IsReference<T>,
	IsConstructibleReferenceCast< T, TArg >,
	BooleanAnd<
		IsDestructible< T >,
		IsConstructibleOneBasic< T, TArg >
	>
>;

struct IsConstructibleManyTest {
	template< typename T, typename... TArgs, typename = decltype(T(make_rvalue<TArgs>()...)) >
	static BooleanTrue test(int);

	template< typename T, typename TArg >
	static BooleanFalse test(...);
};

template< typename T, typename... TArgs >
using IsConstructibleMany = decltype(IsConstructibleManyTest::test< T, TArgs... >(0));

template< typename T, typename... TArgs >
struct IsConstructible;

template< typename T >
struct IsConstructible<T> : IsDefaultConstructible<T> {};

template< typename T, typename TArg >
struct IsConstructible< T, TArg > : IsConstructibleOne< T, TArg > {};

template< typename T, typename... TArgs >
struct IsConstructible : IsConstructibleMany< T, TArgs... > {
	static_assert(sizeof...(TArgs) > 1, "Only useful for > 1 arguments");
};

#endif // BR_IS_CONSTRUCTIBLE

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否重载了特定参数的构造函数
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see IntegerConstant
 * @see NotConstructible
 *
 * 如果表达式 <tt>T(BR::make_rvalue<TArgs>()...)</tt> 是合法的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename... TArgs >
struct IsConstructible : Boolean< Detail::TypeOperate::IsConstructible< T, TArgs... > > {};

/**
 * @brief IsConstructible 的否定
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see IsConstructible
 */
template< typename T, typename... TArgs >
struct NotConstructible : BooleanNot< Detail::TypeOperate::IsConstructible< T, TArgs... > > {};

#if defined(BR_CXX14)

/**
 * @brief IsConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see IsConstructible
 * @see not_constructible
 */
template< typename T, typename... TArgs >
constexpr auto is_constructible = IsConstructible< T, TArgs... >::value;

/**
 * @brief NotConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see NotConstructible
 * @see is_constructible
 */
template< typename T, typename... TArgs >
constexpr auto not_constructible = NotConstructible< T, TArgs... >::value;

#endif // defined(BR_CXX14)

} // namespace BR