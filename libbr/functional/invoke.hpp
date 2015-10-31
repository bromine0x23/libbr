/**
 * @file
 * @brief invoke
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/member_pointer_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename TFunc, typename ... TArgs >
inline auto invoke(TFunc && func, TArgs && ... args) -> decltype(forward<TFunc>(func)(forward<TArgs>(args)...)) {
	return forward<TFunc>(func)(forward<TArgs>(args)...);
}

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
inline auto invoke(TMemberPtr && mem_ptr, TDerived && derived) -> decltype(forward<TDerived>(derived).*mem_ptr) {
	return forward<TDerived>(derived).*mem_ptr;
};

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
inline auto invoke(TMemberPtr && mem_ptr, TDerived && derived) -> decltype((*forward<TDerived>(derived)).*mem_ptr) {
	return (*forward<TDerived>(derived)).*mem_ptr;
};

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
inline auto invoke(TMemberPtr && mem_ptr, TDerived && derived, TArgs && ... args) -> decltype((forward<TDerived>(derived).*mem_ptr)(forward<TArgs>(args) ...)) {
	return (forward<TDerived>(derived).*mem_ptr)(forward<TArgs>(args) ...);
};

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
inline auto invoke(TMemberPtr && mem_ptr, TDerived && derived, TArgs && ... args) -> decltype(((*forward<TDerived>(derived)).*mem_ptr)(forward<TArgs>(args) ...)) {
	return ((*forward<TDerived>(derived)).*mem_ptr)(forward<TArgs>(args) ...);
};

}