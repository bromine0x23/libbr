#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/tuple_forward.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/decay.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/map_qualifier.hpp>
#include <libbr/type_traits/make_integral_sequence.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>
#include <libbr/type_traits/remove_reference.hpp>
#include <libbr/utility/integral_sequence.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/utility/types.hpp>
#include <libbr/utility/wrapped_reference.hpp>

namespace BR {

template< typename T >
class WrappedReference;

namespace Detail {
namespace Container {
namespace Tuple {

template< typename T >
struct ToTypes;

template< typename... TTypes >
struct ToTypes< Types<TTypes...> > : public TypeWrapper< Types<TTypes...> > {};

template< typename... TTypes >
struct ToTypes< BR::Tuple<TTypes...> > : public TypeWrapper< Types<TTypes...> > {};

template< typename TFirst, typename TSecond >
struct ToTypes< BR::Pair< TFirst, TSecond > > : public TypeWrapper< Types< TFirst, TSecond > > {};



template< typename T >
struct IsTupleLike : public BooleanFalse {};

template< typename T >
struct IsTupleLike< T const > : public IsTupleLike<T> {};

template< typename T >
struct IsTupleLike< T volatile > : public IsTupleLike<T> {};

template< typename T >
struct IsTupleLike< T const volatile > : public IsTupleLike<T> {};

template< typename ... TTypes >
struct IsTupleLike< BR::Tuple< TTypes ... > > : public BooleanTrue {};

template< typename ... TTypes >
struct IsTupleLike< Types< TTypes ... > > : public BooleanTrue {};

template< typename T0, typename T1 >
struct IsTupleLike< BR::Pair< T0, T1 > > : public BooleanTrue {};


template< typename TFrom, typename TTo >
struct TypeMakeTupleType : TypeWrapper< RemoveReference<TTo> > {};

template< typename TFrom, typename TTo >
struct TypeMakeTupleType< TFrom &, TTo > : TypeWrapper< TypeUnwrap< TypeMakeTupleType< TFrom, TTo > > & > {};

template< typename TFrom, typename TTo >
struct TypeMakeTupleType< TFrom const, TTo > : TypeWrapper< TypeUnwrap< TypeMakeTupleType< TFrom, TTo > > const > {};

template< typename TFrom, typename TTo >
struct TypeMakeTupleType< TFrom volatile, TTo > : TypeWrapper< TypeUnwrap< TypeMakeTupleType< TFrom, TTo > > volatile > {};

template< typename TFrom, typename TTo >
struct TypeMakeTupleType< TFrom const volatile, TTo > : TypeWrapper< TypeUnwrap< TypeMakeTupleType< TFrom, TTo > > const volatile > {};

template< typename TFrom, typename TTo >
using MakeTupleType = TypeUnwrap< TypeMakeTupleType< TFrom, TTo > >;

template< typename TTuple, typename TIndices >
struct MakeTupleTypesFlat;

template< template<typename...> class TRawTuple, typename... TTypes, Size... Indices >
struct MakeTupleTypesFlat< TRawTuple<TTypes...>, IndexSequence<Indices...> > {
	template< typename TTuple >
	using Apply = TypeWrapper<
		Types< MakeTupleType< TTuple, typename Types<TTypes...>::template Get<Indices> >... >
	>;
};

template< typename TValue, Size N, Size... Indices >
struct MakeTupleTypesFlat< BR::FixedArray<TValue, N>, IndexSequence<Indices...> > {
	template< Size >
	using Value = TValue;
	template< typename TTuple >
	using Apply = TypeWrapper<
		Types< MakeTupleType< TTuple, Value<Indices> >... >
	>;
};

template< typename TTuple, Size from, Size to >
struct TypeMakeTupleTypes
	: public MakeTupleTypesFlat< RemoveConstVolatile< RemoveReference<TTuple> >, MakeIndexSequence<from, to> >::template Apply<TTuple> {
	static_assert(from <= to, "TypeMakeTupleTypes input error");
};

template< typename T, Size from = 0, Size to = TupleSize< RemoveReference<T> >{} >
using MakeTupleTypes = TypeUnwrap< TypeMakeTupleTypes< T, from, to > >;


struct SFINAE {
	template< template< typename, typename...> class TTrait, typename... TLArgs, typename...TRArgs >
	static auto test(Types<TLArgs...>, Types<TRArgs...>) -> EnableIf< BooleanAnd< TTrait<TLArgs, TRArgs>... >, BooleanTrue >;
	template< template<typename...> class >
	static auto test(...) -> BooleanFalse;

	template< template< typename, typename...> class TTrait, typename TLArgs, typename TRArgs >
	using Apply = decltype(test<TTrait>(TLArgs{}, TRArgs{}));

	template< typename TElement, typename TValue >
	using IsConstructible = Apply< BR::IsConstructible, TElement, TValue >;

	template< typename TElement, typename TValue >
	using IsConvertible = Apply< BR::IsConvertible, TValue, TElement >;

	template< typename TElement, typename TValue >
	using IsAssignable = Apply< BR::IsAssignable, TElement, TValue >;
};

template< typename TElement, typename TValue >
struct IsAllConstructible : BooleanFalse {};

template< typename... TElements, typename... TValues >
struct IsAllConstructible< Types<TElements...>, Types<TValues...> > : public SFINAE::IsConstructible< Types<TElements...>, Types<TValues...> > {};

template< typename TElement, typename TValue >
using NotAllConstructible = BooleanNot< IsAllConstructible< TElement, TValue > >;


template< typename TElement, typename TValue >
struct IsAllConvertible : BooleanFalse {};

template< typename... TElements, typename... TValues >
struct IsAllConvertible< Types<TElements...>, Types<TValues...> > : public SFINAE::IsConvertible< Types<TElements...>, Types<TValues...> > {};

template< typename TElement, typename TValue >
using NotAllConvertible = BooleanNot< IsAllConvertible< TElement, TValue > >;


template< typename TElement, typename TValue >
struct IsAllAssignable : BooleanFalse {};

template< typename... TElements, typename... TValues >
struct IsAllAssignable< Types<TElements...>, Types<TValues...> > : public SFINAE::IsAssignable< Types<TElements...>, Types<TValues...> > {};

template< typename TElement, typename TValue >
using NotAllAssignable = BooleanNot< IsAllAssignable< TElement, TValue > >;


template< typename T >
struct TypeMakeTupleReturnBasic : public TypeWrapper<T> {};

template< typename T >
struct TypeMakeTupleReturnBasic< WrappedReference<T> > : public TypeWrapper< T & > {};

template< typename T >
struct TypeMakeTupleReturn : public TypeMakeTupleReturnBasic< Decay<T> > {};

template< typename T >
using MakeTupleReturn = TypeUnwrap< TypeMakeTupleReturn<T> >;

} // namespace Tuple
} // namespace Container
} // namespace Detail

} // namespace BR
