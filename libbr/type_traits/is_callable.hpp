/**
 * @file
 * @brief IsCallable
 * @author Bromine0x23
 * @since 2015/10/31
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/is_member_function_pointer.hpp>
#include <libbr/type_traits/is_member_object_pointer.hpp>
#include <libbr/type_traits/member_pointer_traits.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

struct IsCallableTest {
	template< typename TFunc, typename... TArgs >
	static auto test(TFunc && func, TArgs && ... args) -> decltype((forward<TFunc>(func)(forward<TArgs>(args) ...)), BooleanTrue());

	template<
		typename TMemberPtr,
		typename TDerived,
		typename _TDummy = EnableIf<
			BooleanAnd<
				IsMemberObjectPointer< RemoveReference<TMemberPtr> >,
				IsBaseOf< typename MemberPointerTraits< RemoveReference<TMemberPtr> >::Class, RemoveReference<TDerived> >
			>
		>
	>
	static auto test(TMemberPtr && mem_ptr, TDerived && derived) -> decltype((forward<TDerived>(derived).*mem_ptr), BooleanTrue());

	template<
		typename TMemberPtr,
		typename TDerived,
		typename _TDummy = EnableIf<
			BooleanAnd<
				IsMemberObjectPointer< RemoveReference<TMemberPtr> >,
				NotBaseOf< typename MemberPointerTraits< RemoveReference<TMemberPtr> >::Class, RemoveReference<TDerived> >
			>
		>
	>
	static auto test(TMemberPtr && mem_ptr, TDerived && derived) -> decltype(((*forward<TDerived>(derived)).*mem_ptr), BooleanTrue());

	template<
		typename TMemberPtr,
		typename TDerived,
		typename ... TArgs,
		typename _TDummy = EnableIf<
			BooleanAnd<
				IsMemberFunctionPointer< RemoveReference<TMemberPtr> >,
				IsBaseOf< typename MemberPointerTraits< RemoveReference<TMemberPtr> >::Class, RemoveReference<TDerived> >
			>
		>
	>
	static auto test(TMemberPtr && mem_ptr, TDerived && derived, TArgs && ... args) -> decltype(((forward<TDerived>(derived).*mem_ptr)(forward<TArgs>(args) ...)), BooleanTrue());

	template<
		typename TMemberPtr,
		typename TDerived,
		typename ... TArgs,
		typename _TDummy = EnableIf<
			BooleanAnd<
				IsMemberFunctionPointer< RemoveReference<TMemberPtr> >,
				NotBaseOf< typename MemberPointerTraits< RemoveReference<TMemberPtr> >::Class, RemoveReference<TDerived> >
			>
		>
	>
	static auto test(TMemberPtr && mem_ptr, TDerived && derived, TArgs && ... args) -> decltype((((*forward<TDerived>(derived)).*mem_ptr)(forward<TArgs>(args) ...)), BooleanTrue());

	template< typename ... TArgs >
	static auto test(TArgs && ... args) -> BooleanFalse;
};

template< typename TCallable, typename... TArgs >
using IsCallable = decltype(IsCallableTest::test(make_rvalue<TCallable>(), make_rvalue<TArgs>() ...));

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief IsCallable
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotCallable
 *
 * 如果 \em T 包含顶层 \em const 修饰，那么封装的值为 \em true ；否则为 \em false
 */
template< typename TCallable, typename... TArgs >
struct IsCallable : BooleanRewrapPositive< Detail::TypeTraits::IsCallable< TCallable, TArgs... > > {
};

/**
 * @brief IsCallable 的否定
 * @tparam T 待检查类型
 * @see IsCallable
 */
template< typename TCallable, typename... TArgs >
struct NotCallable : BooleanRewrapNegative< Detail::TypeTraits::IsCallable< TCallable, TArgs... > > {
};

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

} // namespace BR
