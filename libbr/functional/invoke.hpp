/**
 * @file
 * @brief invoke
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/is_member_function_pointer.hpp>
#include <libbr/type_traits/is_member_object_pointer.hpp>
#include <libbr/type_traits/member_pointer_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

namespace Detail {
namespace Functional {

struct InvokerFunctor {
	template< typename TFunctor, typename ... TArgs >
	static auto invoke(TFunctor && functor, TArgs && ... args) -> decltype(forward<TFunctor>(functor)(forward<TArgs>(args)...)) {
		return forward<TFunctor>(functor)(forward<TArgs>(args)...);
	}
};

struct InvokerMemberObjectWithObject {
	template< typename TMemberPointer, typename TDerived >
	static auto invoke(TMemberPointer && pointer, TDerived && derived) -> decltype(forward<TDerived>(derived).*pointer) {
		return forward<TDerived>(derived).*pointer;
	}
};

struct InvokerMemberObjectWithPointer {
	template< typename TMemberPointer, typename TDerived >
	static auto invoke(TMemberPointer && pointer, TDerived && derived) -> decltype((*forward<TDerived>(derived)).*pointer) {
		return (*forward<TDerived>(derived)).*pointer;
	}
};

struct InvokerMemberFunctionWithObject {
	template< typename TMemberPointer, typename TDerived, typename ... TArgs >
	static auto invoke(TMemberPointer && pointer, TDerived && derived, TArgs && ... args) -> decltype((forward<TDerived>(derived).*pointer)(forward<TArgs>(args) ...)) {
		return (forward<TDerived>(derived).*pointer)(forward<TArgs>(args) ...);
	}
};

struct InvokerMemberFunctionWithPointer {
	template< typename TMemberPointer, typename TDerived, typename ... TArgs >
	static auto invoke(TMemberPointer && pointer, TDerived && derived, TArgs && ... args) -> decltype(((*forward<TDerived>(derived)).*pointer)(forward<TArgs>(args) ...)) {
		return ((*forward<TDerived>(derived)).*pointer)(forward<TArgs>(args) ...);
	}
};

template< typename TCallable, typename TArg, bool is_member_object_pointer = IsMemberObjectPointer<TCallable>{}(), bool is_member_function_pointer = IsMemberFunctionPointer<TCallable>{}() >
struct InvokerBasic;

template< typename TMemberObjectPointer, typename TDerived >
struct InvokerBasic< TMemberObjectPointer, TDerived, true, false > : public Conditional<
	IsBaseOf< typename MemberPointerTraits<TMemberObjectPointer>::Class, Decay<TDerived> >,
	InvokerMemberObjectWithObject,
	InvokerMemberObjectWithPointer
> {};

template< typename TMemberFunctionPointer, typename TDerived >
struct InvokerBasic< TMemberFunctionPointer, TDerived, false, true > : public Conditional<
	IsBaseOf< typename MemberPointerTraits<TMemberFunctionPointer>::Class, Decay<TDerived> >,
	InvokerMemberFunctionWithObject,
	InvokerMemberFunctionWithPointer
> {};

template< typename TCallable, typename TArg >
struct InvokerBasic< TCallable, TArg, false, false > : public InvokerFunctor {};

template< typename TCallable, typename ... TArgs >
struct Invoker;

template< typename TCallable >
struct Invoker<TCallable> : public InvokerFunctor {};

template< typename TCallable, typename TArg, typename ... TArgs >
struct Invoker< TCallable, TArg, TArgs ... > : public InvokerBasic< Decay<TCallable>, TArg > {};

} // namespace Functional
} // namespace Detail

template< typename TCallable, typename ... TArgs >
inline auto invoke(TCallable && callable, TArgs && ... args) -> decltype(Detail::Functional::Invoker< TCallable, TArgs ... >::invoke(forward<TCallable>(callable), forward<TArgs>(args)...)) {
	return Detail::Functional::Invoker< TCallable, TArgs ... >::invoke(forward<TCallable>(callable), forward<TArgs>(args)...);
}

}