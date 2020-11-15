/**
 * @file
 * @brief 构造函数重载检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>
#if !defined(BR_IS_CONSTRUCTIBLE)
#  include <libbr/type_traits/has_destructor.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_base_of.hpp>
#  include <libbr/type_traits/is_function.hpp>
#  include <libbr/type_traits/is_lvalue_reference.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_rvalue_reference.hpp>
#  include <libbr/type_traits/is_same.hpp>
#  include <libbr/type_traits/is_static_castable.hpp>
#  include <libbr/type_traits/is_void.hpp>
#  include <libbr/type_transform/remove_all_extents.hpp>
#  include <libbr/type_transform/remove_reference.hpp>
#  include <libbr/utility/conditional.hpp>
#  include <libbr/utility/conjunction.hpp>
#  include <libbr/utility/converse_abjunction.hpp>
#  include <libbr/utility/declare_value.hpp>
#  include <libbr/utility/disjunction.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否重载了特定参数的构造函数
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see Utility::IntegralConstant
 * @see BR_IS_CONSTRUCTIBLE
 * @see NotConstructible
 *
 * 如果表达式 <tt>T(BR::declare_value<TArgs>()...)</tt> 是合法的，那么封装的值为 \em true ；否则为 \em false
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

/**
 * @brief IsConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see IsConstructible
 * @see not_constructible
 */
template< typename T, typename... TArgs >
constexpr auto is_constructible = boolean_constant< IsConstructible< T, TArgs... > >;

/**
 * @brief NotConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see NotConstructible
 * @see is_constructible
 */
template< typename T, typename... TArgs >
constexpr auto not_constructible = boolean_constant< NotConstructible< T, TArgs... > >;

} // namespace TypeTraits



namespace _::TypeTraits {

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

template< typename T, Boolean = IsVoid<T>{}() >
struct IsConstructibleZeroBasic;

template< typename T >
struct IsConstructibleZeroBasic< T, true > : public BooleanFalse {};

template< typename T >
struct IsConstructibleZeroBasic< T, false > : public decltype(IsConstructibleZeroTest::test<T>(0)) {};

template< typename T >
using IsConstructibleZero = Conditional<
	IsArray<T>,
	Conjunction<
		IsBoundedArray<T>,
		IsConstructibleZeroBasic< RemoveAllExtents<T> >
	>,
	IsConstructibleZeroBasic<T>
>;

template< typename T, typename TArg >
using IsConstructibleOneBaseToDerivedReference = ConverseAbjunction<
	IsSame< T, TArg >,
	IsBaseOf< TArg, T >
>;

template< typename T, typename TArg >
using IsConstructibleOneLValueToRValueReference = ConverseAbjunction<
	IsFunction<TArg>,
	Disjunction<
		IsSame< T, TArg >,
		IsBaseOf< TArg, T >
	>
>;

template< typename T, typename TArg >
using IsConstructibleReferenceCast = Abjunction<
	IsStaticCastable< TArg, T >,
	Disjunction<
		IsConstructibleOneBaseToDerivedReference< RemoveReference<T>, RemoveReference<TArg> >,
		Conjunction<
			IsRValueReference<T>,
			IsLValueReference<TArg>,
			IsConstructibleOneLValueToRValueReference< RemoveReference<T>, RemoveReference<TArg> >
		>
	>
>;

struct IsConstructibleOneTest {
	template< typename T, typename TArg, typename = decltype(::new T(declare_value<TArg>())) >
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
	Conjunction<
		HasDestructor< T >,
		IsConstructibleOneBasic< T, TArg >
	>
>;

struct IsConstructibleManyTest {
	template< typename T, typename... TArgs, typename = decltype(T(declare_value<TArgs>()...)) >
	static auto test(int) -> BooleanTrue;

	template< typename T, typename... TArg >
	static auto test(...) -> BooleanFalse;
};

template< typename T, typename... TArgs >
using IsConstructibleMany = decltype(IsConstructibleManyTest::test< T, TArgs... >(0));

template< typename T, typename... TArgs >
struct IsConstructible;

template< typename T >
struct IsConstructible<T> : public IsConstructibleZero<T> {};

template< typename T, typename TArg >
struct IsConstructible< T, TArg > : public IsConstructibleOne< T, TArg > {};

template< typename T, typename... TArgs >
struct IsConstructible : public IsConstructibleMany< T, TArgs... > {
	static_assert(sizeof...(TArgs) > 1, "Only useful for > 1 arguments");
};

#endif // BR_IS_CONSTRUCTIBLE

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T, typename... TArgs >
struct IsConstructible : public BooleanRewrapPositive< _::TypeTraits::IsConstructible< T, TArgs... > > {};

template< typename T, typename... TArgs >
struct NotConstructible : public BooleanRewrapNegative< _::TypeTraits::IsConstructible< T, TArgs... > > {};

} // namespace TypeTraits

} // namespace BR