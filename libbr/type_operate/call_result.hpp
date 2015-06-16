#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename TFunction, typename ... TArguments >
inline auto Call(TFunction && function, TArguments && ... arguments) -> decltype(
	forward< TFunction >(function)(forward< TArguments >(arguments) ...)
) {
	return forward< TFunction >(function)(forward< TArguments >(arguments) ...);
}

template< typename TBase, typename TMemberPointer, typename TDerived >
inline auto Call(TMemberPointer TBase::*member_pointer, TDerived && derived) ->  decltype(
	forward< TDerived >(derived).*member_pointer
) {
	return forward< TDerived >(derived).*member_pointer;
}

template< typename TMemberFunctionPointer, typename TPointer >
inline auto Call(TMemberFunctionPointer && member_function_pointer, TPointer && pointer) -> decltype(
	(*forward< TPointer >(pointer)).*forward< TMemberFunctionPointer >(member_function_pointer)
) {
	return (*forward< TPointer >(pointer)).*forward< TMemberFunctionPointer >(member_function_pointer);
}

template< typename TBase, typename TMemberPointer, typename TDerived, typename ... TArguments >
inline auto Call(TMemberPointer TBase::*member_pointer, TDerived && derived, TArguments && ... arguments) -> decltype(
	(forward< TDerived >(derived).*member_pointer)(forward< TArguments >(arguments) ...)
) {
	return (forward< TDerived >(derived).*member_pointer)(forward< TArguments >(arguments) ...);
}

template< typename TMemberFunctionPointer, typename TPointer, typename ... TArguments >
inline auto Call(TMemberFunctionPointer && member_function_pointer, TPointer && pointer, TArguments && ... arguments) -> decltype(
	((*forward< TPointer >(pointer)).*forward< TMemberFunctionPointer >(member_function_pointer))(forward<TArguments>(arguments) ...)
) {
	return ((*forward< TPointer >(pointer)).*forward< TMemberFunctionPointer >(member_function_pointer))(forward<TArguments>(arguments) ...);
}

template< typename T, typename = void >
struct TypeCallResult {
	static_assert((T(), false), "Type must be callable.");
};

template< typename TFunction, typename ... TArguments >
struct TypeCallResult<
	TFunction(TArguments ...), decltype(void(Detail::Call(make_rvalue< TFunction >(), make_rvalue< TArguments >() ...)))
> : TypeWrapper< decltype(Detail::Call(make_rvalue< TFunction >(), make_rvalue< TArguments >() ...)) > {};

} // namespace Detail

template< typename T >
struct TypeCallResult : TypeWrapper< TypeUnwrap< Detail::TypeCallResult< T > > > {};

template< typename T >
using CallResult = TypeUnwrap< TypeCallResult< T > >;

} // namespace TypeOperate
} // namespace BR