/**
 * @file
 * @brief 函数调用结果
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/is_callable.hpp>
#include <libbr/type_traits/member_pointer_traits.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct CallResultTest {
	template< typename TFunc, typename... TArgs >
	static auto test(TFunc && func, TArgs && ... args) -> decltype(forward<TFunc>(func)(forward<TArgs>(args) ...));

	template<
		typename TMemberPtr,
		typename TDerived,
		typename _TDummy = EnableIf<
			BooleanAnd<
				typename MemberPointerTraits< RemoveReference<TMemberPtr> >::IsObjectPointer,
				IsBaseOf< typename MemberPointerTraits< RemoveReference<TMemberPtr> >::Class, RemoveReference<TDerived> >
			>
		>
	>
	static auto test(TMemberPtr && mem_ptr, TDerived && derived) -> decltype(forward<TDerived>(derived).*mem_ptr);

	template<
		typename TMemberPtr,
		typename TDerived,
		typename _TDummy = EnableIf<
			BooleanAnd<
				typename MemberPointerTraits< RemoveReference<TMemberPtr> >::IsObjectPointer,
				NotBaseOf< typename MemberPointerTraits< RemoveReference<TMemberPtr> >::Class, RemoveReference<TDerived> >
			>
		>
	>
	static auto test(TMemberPtr && mem_ptr, TDerived && derived) -> decltype((*forward<TDerived>(derived)).*mem_ptr);

	template<
		typename TMemberPtr,
		typename TDerived,
		typename ... TArgs,
		typename _TDummy = EnableIf<
			BooleanAnd<
				typename MemberPointerTraits< RemoveReference<TMemberPtr> >::IsFunctionPointer,
				IsBaseOf< typename MemberPointerTraits< RemoveReference<TMemberPtr> >::Class, RemoveReference<TDerived> >
			>
		>
	>
	static auto test(TMemberPtr && mem_ptr, TDerived && derived, TArgs && ... args) -> decltype((forward<TDerived>(derived).*mem_ptr)(forward<TArgs>(args) ...));

	template<
		typename TMemberPtr,
		typename TDerived,
		typename ... TArgs,
		typename _TDummy = EnableIf<
			BooleanAnd<
				typename MemberPointerTraits< RemoveReference<TMemberPtr> >::IsFunctionPointer,
				NotBaseOf< typename MemberPointerTraits< RemoveReference<TMemberPtr> >::Class, RemoveReference<TDerived> >
			>
		>
	>
	static auto test(TMemberPtr && mem_ptr, TDerived && derived, TArgs && ... args) -> decltype(((*forward<TDerived>(derived)).*mem_ptr)(forward<TArgs>(args) ...));
};

template< typename TCallable, typename... TArgs >
using CallResultBasic = decltype(CallResultTest::test(make_rvalue<TCallable>(), make_rvalue<TArgs>() ...));

template< typename T, bool is_callable = IsCallable<T>::value >
struct TypeCallResult;

template< typename TCallable >
struct TypeCallResult< TCallable, true > : TypeWrapper< CallResultBasic< TCallable > > {};

template< typename T >
struct TypeCallResult< T, false > {
};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 获取调用结果类型
 * @tparam T 可调用对象
 * @tparam TArgs 调用参数
 * @see TypeWrapper
 *
 * 包装调用 \em T 类型变量的的返回值类型
 */
template< typename TCallable, typename... TArgs >
struct TypeCallResult : TypeRewrap< Detail::TypeOperate::TypeCallResult< TCallable, TArgs... > > {
};

/**
 * @brief TypeCallResult 的简写版本
 * @tparam T 可调用对象
 * @tparam TArgs 调用参数
 * @see TypeCallResult
 */
template< typename TCallable, typename... TArgs >
using CallResult = TypeUnwrap< TypeCallResult< TCallable, TArgs... > >;

} // namespace BR