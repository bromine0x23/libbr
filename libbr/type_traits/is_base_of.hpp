/**
 * @file
 * @brief 派生关系检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_BASE_OF)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_traits/is_class.hpp>
#  include <libbr/type_traits/is_lvalue_reference.hpp>
#  include <libbr/type_traits/is_same.hpp>
#endif

namespace BR {

/**
 * @brief 检查 \em TDerived 是否是 \em TBase 的基类(不考虑CV修饰符)
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see BR::IntegerConstant
 * @see BR_IS_BASE_OF
 * @see BR::NotAssignable
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
 * @see BR::IsBaseOf
 */
template< typename TBase, typename TDerived >
struct NotBaseOf;

#if defined(BR_CXX14)

/**
 * @brief IsBaseOf 的模板变量版本
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see BR::IsBaseOf
 * @see BR::not_base_of
 */
template< typename TBase, typename TDerived >
constexpr auto is_base_of = bool_constant< IsBaseOf< TBase, TDerived > >;

/**
 * @brief NotBaseOf 的模板变量版本
 * @tparam TBase 待检查类型，作为基类
 * @tparam TDerived 待检查类型，作为派生类
 * @see BR::NotBaseOf
 * @see BR::is_base_of
 */
template< typename TBase, typename TDerived >
constexpr auto not_base_of = bool_constant< NotBaseOf< TBase, TDerived > >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_BASE_OF)

template< typename TBase, typename TDerived >
using IsBaseOf = BooleanConstant < BR_IS_BASE_OF(TBase, TDerived) >;

#else

template< typename TBase, typename TDerived >
struct IsBaseOfTester {
	template< typename T >
	static BooleanTrue test(TDerived const volatile *, T);

	static BooleanFalse test(TBase const volatile *, int);
};

template< typename TBase, typename TDerived >
struct IsBaseOfHelper {
	operator TBase    const volatile *() const;
	operator TDerived const volatile *();
};

template< typename TBase, typename TDerived >
struct IsBaseOfBasic : public BooleanAnd<
	IsClass<TBase>,
	IsClass<TDerived>,
	decltype(IsBaseOfTester< TBase, TDerived >::test(IsBaseOfHelper< TBase, TDerived >(), 0))
> {
	static_assert(sizeof(TBase   ) != 0, "TBase must be complete."   );
	static_assert(sizeof(TDerived) != 0, "TDerived must be complete.");
};

template< typename TBase, typename TDerived >
using IsBaseOf = BooleanAnd<
	NotLValueReference<TBase>,
	NotLValueReference<TDerived>,
	IsBaseOfBasic< RemoveConstVolatile<TBase>, RemoveConstVolatile<TDerived> >
>;

#endif // BR_IS_BASE_OF

} // namespace TypeTraits
} // namespace Detail

template< typename TBase, typename TDerived >
struct IsBaseOf : public BooleanRewrapPositive< Detail::TypeTraits::IsBaseOf< TBase, TDerived > > {};

template< typename TBase, typename TDerived >
struct NotBaseOf : public BooleanRewrapNegative< Detail::TypeTraits::IsBaseOf< TBase, TDerived > > {};

} // namespace BR

