#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct CallResultTest {
	template< typename TFunc, typename... TArgs >
	constexpr static auto test(
		TFunc && func,
		TArgs && ... args
	) -> decltype(forward<TFunc>(func)(forward<TArgs>(args) ...));

	template< typename TBase, typename TMemPtr, typename TDerived >
	constexpr static auto test(
		TMemPtr TBase::*mem_ptr,
		TDerived && derived
	) -> decltype(forward<TDerived>(derived).*mem_ptr);

	template< typename TMemFuncPtr, typename TPtr >
	constexpr static auto test(
		TMemFuncPtr && mem_func_ptr,
		TPtr && ptr
	) -> decltype((*forward<TPtr>(ptr)).*forward<TMemFuncPtr>(mem_func_ptr));

	template< typename TBase, typename TMemPtr, typename TDerived, typename... TArgs >
	constexpr static auto test(
		TMemPtr TBase::*mem_ptr,
		TDerived && derived,
		TArgs && ... args
	) -> decltype((forward<TDerived>(derived).*mem_ptr)(forward<TArgs>(args) ...));

	template< typename TMemFuncPtr, typename TPtr, typename... TArgs >
	constexpr static auto test(
		TMemFuncPtr && mem_func_ptr,
		TPtr && ptr,
		TArgs && ... args
	) -> decltype(((*forward<TPtr>(ptr)).*forward<TMemFuncPtr>(mem_func_ptr))(forward<TArgs>(args) ...));
};

template< typename TFunc, typename... TArgs >
using CallResultBasic = decltype(CallResultTest::test(make_rvalue<TFunc>(), make_rvalue<TArgs>() ...));

template< typename T >
struct TypeCallResult {
	static_assert(sizeof(T *) == sizeof(nullptr), "Type T must be callable.");

};

template< typename TResult, typename ... TArgs >
struct TypeCallResult<TResult(TArgs ...)> : TypeWrapper< CallResultBasic< TResult(TArgs ...), TArgs ... > > {};

template< typename TResult, typename ... TArgs >
struct TypeCallResult<TResult(TArgs ..., ...)> : TypeWrapper< CallResultBasic< TResult(TArgs ...), TArgs ... > > {};

template< typename TResult, typename ... TArgs >
struct TypeCallResult<TResult(*)(TArgs ...)> : TypeWrapper< CallResultBasic< TResult(TArgs ...), TArgs ... > > {};

template< typename TResult, typename ... TArgs >
struct TypeCallResult<TResult(*)(TArgs ..., ...)> : TypeWrapper< CallResultBasic< TResult(TArgs ...), TArgs ... > > {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeCallResult : TypeRewrap< Detail::TypeOperate::TypeCallResult<T> > {};

template< typename T >
using CallResult = TypeUnwrap< TypeCallResult<T> >;

} // namespace BR