/**
 * @file
 * @brief 派生关系检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/boolean_constant.hpp>
#if !defined(BR_IS_BASE_OF)
#  include <libbr/type_traits/is_class.hpp>
#  include <libbr/type_traits/is_lvalue_reference.hpp>
#  include <libbr/type_traits/is_same.hpp>
#  include <libbr/utility/conjunction.hpp>
#  include <libbr/utility/disjunction.hpp>
#  include <libbr/utility/non_disjunction.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em TDerived 是否是 \em TBase 的基类(不考虑CV修饰符)
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see Utility::IntegralConstant
 * @see BR_IS_BASE_OF
 * @see NotBaseOf
 *
 * 如果 \em TDerived 是否是 \em TBase 或派生自 \em TBase ，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename TBase, typename TDerived >
struct IsBaseOf;

/**
 * @brief IsBaseOf 的否定
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see IsBaseOf
 */
template< typename TBase, typename TDerived >
struct NotBaseOf;

/**
 * @brief IsBaseOf 的模板变量版本
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see IsBaseOf
 * @see not_base_of
 */
template< typename TBase, typename TDerived >
constexpr auto is_base_of = boolean_constant< IsBaseOf< TBase, TDerived > >;

/**
 * @brief NotBaseOf 的模板变量版本
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see NotBaseOf
 * @see is_base_of
 */
template< typename TBase, typename TDerived >
constexpr auto not_base_of = boolean_constant< NotBaseOf< TBase, TDerived > >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

#if defined(BR_IS_BASE_OF)

template< typename TBase, typename TDerived >
using IsBaseOf = BooleanConstant< BR_IS_BASE_OF(TBase, TDerived) >;

#else

template< typename TBase, typename TDerived >
struct IsBaseOfTester {
	template< typename T >
	static auto test(TDerived const volatile *, T) -> BooleanTrue;

	static auto test(TBase const volatile *, int) -> BooleanFalse;
};

template< typename TBase, typename TDerived >
struct IsBaseOfHelper {
	operator TBase    const volatile *() const;
	operator TDerived const volatile *();
};

template< typename TBase, typename TDerived >
struct IsBaseOfBasic : public Conjunction<
	IsClass<TBase>,
	IsClass<TDerived>,
	Disjunction< IsSame<TBase, TDerived>, decltype(IsBaseOfTester< TBase, TDerived >::test(IsBaseOfHelper< TBase, TDerived >(), 0)) >
> {
	static_assert(sizeof(TBase   ) != 0, "TBase must be complete."   );
	static_assert(sizeof(TDerived) != 0, "TDerived must be complete.");
};

template< typename TBase, typename TDerived >
using IsBaseOf = Conjunction<
	NonDisjunction< IsLValueReference<TBase>, IsLValueReference<TDerived> >,
	IsBaseOfBasic< RemoveConstVolatile<TBase>, RemoveConstVolatile<TDerived> >
>;

#endif // BR_IS_BASE_OF

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename TBase, typename TDerived >
struct IsBaseOf : public BooleanRewrapPositive< _::TypeTraits::IsBaseOf< TBase, TDerived > > {};

template< typename TBase, typename TDerived >
struct NotBaseOf : public BooleanRewrapNegative< _::TypeTraits::IsBaseOf< TBase, TDerived > > {};

} // namespace TypeTraits

} // namespace BR

