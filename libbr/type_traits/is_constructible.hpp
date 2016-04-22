/**
 * @file
 * @brief 构造函数重载检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_CONSTRUCTIBLE)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_operate/conditional.hpp>
#  include <libbr/type_operate/remove_all_extents.hpp>
#  include <libbr/type_operate/remove_reference.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_base_of.hpp>
#  include <libbr/type_traits/is_destructible.hpp>
#  include <libbr/type_traits/is_function.hpp>
#  include <libbr/type_traits/is_lvalue_reference.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_rvalue_reference.hpp>
#  include <libbr/type_traits/is_same.hpp>
#  include <libbr/type_traits/is_static_castable.hpp>
#  include <libbr/type_traits/is_void.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {

/**
 * @brief 检查 \em T 是否重载了特定参数的构造函数
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see IntegerConstant
 * @see BR_IS_CONSTRUCTIBLE
 * @see NotConstructible
 *
 * 如果表达式 <tt>T(BR::make_rvalue<TArgs>()...)</tt> 是合法的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename... TArgs >
struct IsConstructible;

/**
 * @brief IsConstructible 的否定
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see IsConstructible
 */
template< typename T, typename... TArgs >
struct NotConstructible;

#if defined(BR_CXX14)

/**
 * @brief IsConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see IsConstructible
 * @see not_constructible
 */
template< typename T, typename... TArgs >
constexpr auto is_constructible = bool_constant< IsConstructible< T, TArgs... > >

/**
 * @brief NotConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see NotConstructible
 * @see is_constructible
 */
template< typename T, typename... TArgs >
constexpr auto not_constructible = bool_constant< NotConstructible< T, TArgs... > >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_CONSTRUCTIBLE)

template< typename T, typename... TArgs >
using IsConstructible = BooleanConstant< BR_IS_CONSTRUCTIBLE(T, TArgs...) >;

#else

struct IsConstructibleZeroTest {
	template< typename T, typename = decltype(T()) >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T, bool = IsVoid<T>{}() >
struct IsConstructibleZeroBasic;

template< typename T >
struct IsConstructibleZeroBasic< T, true > : public BooleanFalse {};

template< typename T >
struct IsConstructibleZeroBasic< T, false > : public decltype(IsConstructibleZeroTest::test<T>(0)) {};

template< typename T >
using IsConstructibleZero = Conditional<
	IsArray<T>,
	BooleanAnd<
		IsArrayKnownBounds<T>,
		IsConstructibleZeroBasic< RemoveAllExtents<T> >
	>,
	IsConstructibleZeroBasic<T>
>;

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
	static auto test(int) -> BooleanTrue;

	template< typename T, typename TArg >
	static auto test(...) -> BooleanFalse;
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
	static auto test(int) -> BooleanTrue;

	template< typename T, typename TArg >
	static auto test(...) -> BooleanFalse;
};

template< typename T, typename... TArgs >
using IsConstructibleMany = decltype(IsConstructibleManyTest::test< T, TArgs... >(0));

template< typename T, typename... TArgs >
struct IsConstructible;

template< typename T >
struct IsConstructible<T> : IsConstructibleZero<T> {};

template< typename T, typename TArg >
struct IsConstructible< T, TArg > : IsConstructibleOne< T, TArg > {};

template< typename T, typename... TArgs >
struct IsConstructible : IsConstructibleMany< T, TArgs... > {
	static_assert(sizeof...(TArgs) > 1, "Only useful for > 1 arguments");
};

#endif // BR_IS_CONSTRUCTIBLE

} // namespace TypeTraits
} // namespace Detail

template< typename T, typename... TArgs >
struct IsConstructible : BooleanRewrapPositive< Detail::TypeTraits::IsConstructible< T, TArgs... > > {};

template< typename T, typename... TArgs >
struct NotConstructible : BooleanRewrapNegative< Detail::TypeTraits::IsConstructible< T, TArgs... > > {};

} // namespace BR