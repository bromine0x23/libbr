#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/integer.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_const_volatile.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_volatile.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/is_assignable.hpp>
#include <libbr/type_operate/is_constructible.hpp>
#include <libbr/type_operate/is_convertible.hpp>
#include <libbr/type_operate/is_empty.hpp>
#include <libbr/type_operate/is_final.hpp>
#include <libbr/type_operate/is_lvalue_reference.hpp>
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/is_nothrow_assignable.hpp>
#include <libbr/type_operate/is_nothrow_default_constructible.hpp>
#include <libbr/type_operate/is_nothrow_constructible.hpp>
#include <libbr/type_operate/is_nothrow_copy_assignable.hpp>
#include <libbr/type_operate/is_nothrow_copy_constructible.hpp>
#include <libbr/type_operate/is_nothrow_move_assignable.hpp>
#include <libbr/type_operate/map_qualifier.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/allocator_constructor_usage.hpp>
#include <libbr/utility/forward.hpp>
// #include <libbr/utility/reference.hpp>

#if defined(BR_CPP14)
#  define BR_TUPLE_CONSTEXPR constexpr
#else
#  define BR_TUPLE_CONSTEXPR
#endif // defined

namespace BR {

namespace Detail {

using namespace Memory;
using namespace TypeOperate;
using namespace TypeTraits;

template< typename T >
struct TupleSize;

template< Size I, typename T >
struct TypeTupleElement;

template< Size I, typename T >
using TupleElement = TypeUnwrap< TypeTupleElement< I, T > >;

template< Size ... In >
struct TupleIndices : Integers< Size, In ... > {};

template< typename ... Tn >
struct TupleTypes : Types< Tn ... > {};

} // namespace Detail

template< typename T >
class ReferenceWrapper;

template< typename ... types >
class Tuple;

template< typename T0, typename T1 >
struct Pair;

template< typename T, Size S >
struct Array;

template< typename T >
struct TupleSize : TypeOperate::IntegerConstant< Size, Detail::TupleSize< T >::value > {};

template< Size I, typename T >
struct TypeTupleElement : TypeOperate::TypeRewrap< Detail::TypeTupleElement< I, T > > {};

template< Size I, typename T >
using TupleElement = Detail::TupleElement< I, T >;

template< Size I, typename T, Size S > BR_TUPLE_CONSTEXPR T       & get(Array< T, S >       &) noexcept;
template< Size I, typename T, Size S > BR_TUPLE_CONSTEXPR T const & get(Array< T, S > const &) noexcept;
template< Size I, typename T, Size S > BR_TUPLE_CONSTEXPR T      && get(Array< T, S >      &&) noexcept;

template< Size I, typename ... Tn > BR_TUPLE_CONSTEXPR Detail::TupleElement< I, Tuple< Tn ... > >       & get(Tuple< Tn ... >       &) noexcept;
template< Size I, typename ... Tn > BR_TUPLE_CONSTEXPR Detail::TupleElement< I, Tuple< Tn ... > > const & get(Tuple< Tn ... > const &) noexcept;
template< Size I, typename ... Tn > BR_TUPLE_CONSTEXPR Detail::TupleElement< I, Tuple< Tn ... > >      && get(Tuple< Tn ... >      &&) noexcept;

template< Size I, typename T0, typename T1 > BR_TUPLE_CONSTEXPR Detail::TupleElement< I, Pair< T0, T1 > >       & get(Pair< T0, T1 >       &) noexcept;
template< Size I, typename T0, typename T1 > BR_TUPLE_CONSTEXPR Detail::TupleElement< I, Pair< T0, T1 > > const & get(Pair< T0, T1 > const &) noexcept;
template< Size I, typename T0, typename T1 > BR_TUPLE_CONSTEXPR Detail::TupleElement< I, Pair< T0, T1 > >      && get(Pair< T0, T1 >      &&) noexcept;

namespace Detail {

////////////////////////////////
//
// TupleSize
//
template< typename ... Tn >
struct TupleSize< Tuple< Tn ... > > : IntegerConstant< Size, sizeof...(Tn) > {};

template< typename T > class TupleSize< T const          > : TupleSize< T > {};
template< typename T > class TupleSize< T       volatile > : TupleSize< T > {};
template< typename T > class TupleSize< T const volatile > : TupleSize< T > {};

template< typename ... Tn >
struct TupleSize< TupleTypes< Tn ... > > : IntegerConstant< Size, sizeof...(Tn) > {};

////////////////////////////////
//
// TupleElement
//
template< Size I, typename ... Tn >
struct TypeTupleElement< I, Tuple< Tn ... > > : TypeTupleElement< I, TupleTypes< Tn ... > > {};

template< Size I, typename T > struct TypeTupleElement< I, T const          > : TypeOperate::TypeAddConst        < TupleElement< I, T > > {};
template< Size I, typename T > struct TypeTupleElement< I, T       volatile > : TypeOperate::TypeAddVolatile     < TupleElement< I, T > > {};
template< Size I, typename T > struct TypeTupleElement< I, T const volatile > : TypeOperate::TypeAddConstVolatile< TupleElement< I, T > > {};

template< Size I >
struct TypeTupleElement< I, TupleTypes<> > {
	static_assert(I == 0, "tuple_element index out of range");
	static_assert(I != 0, "tuple_element index out of range");
};

template< typename THead, typename ... TTail >
struct TypeTupleElement< 0, TupleTypes< THead, TTail ... > > :TypeWrapper< THead > {};

template< Size I, typename THead, typename ... TTail >
struct TypeTupleElement< I, TupleTypes< THead, TTail ... > > : TypeTupleElement< I - 1, TupleTypes< TTail ... > > {};

////////////////////////////////
//
// IsTupleLike
//
template< typename T >
struct IsTupleLike : BooleanFalse {};

template< typename T > struct IsTupleLike< T const          > : IsTupleLike< T > {};
template< typename T > struct IsTupleLike< T       volatile > : IsTupleLike< T > {};
template< typename T > struct IsTupleLike< T const volatile > : IsTupleLike< T > {};

template< typename ... Tn >
struct IsTupleLike< Tuple< Tn ... > > :BooleanTrue {};

template< typename T0, typename T1 >
struct IsTupleLike< Pair< T0, T1 > > : BooleanTrue {};

template< typename T, Size S >
struct IsTupleLike< Array< T, S > > : BooleanTrue {};

template< typename ... Tn >
struct IsTupleLike< TupleTypes< Tn ... > > : BooleanTrue {};

////////////////////////////////
//
// MakeTupleIndices
//
template< Size From, Size To, Size ... In >
struct TypeMakeTupleIndices : TypeMakeTupleIndices< From + 1, To, In ..., From > {};

template< Size To, Size ... In >
struct TypeMakeTupleIndices< To, To, In ... > : TypeWrapper< TupleIndices< In ... > > {};

template< Size From, Size To >
using MakeTupleIndices = TypeUnwrap< TypeMakeTupleIndices< From, To > >;

////////////////////////////////
//
// MakeTupleTypes
//
template< typename T, Size From, Size To, typename ... Tn >
struct TypeMakeTupleTypes;

template< Size I, typename T >
using MakeTupleType = Conditional<
	IsLValueReference< T >,
	TupleElement< I, T > &,
	TupleElement< I, T >
>;

template< typename T, Size From, Size To, typename ... Tn >
struct TypeMakeTupleTypes : TypeMakeTupleTypes< T, From + 1, To, Tn ..., MakeTupleType< From, RemoveReference< T > > > {
	static_assert(From <= To, "MakeTupleTypes input error");
};

template< typename T, Size To, typename ... Tn >
struct TypeMakeTupleTypes< T, To, To, Tn ... > : TypeWrapper< TupleTypes< Tn ... > > {};

template< typename T, Size From = 0, Size To = TupleSize< RemoveReference < T > >::value >
using MakeTupleTypes = TypeUnwrap< TypeMakeTupleTypes< T, From, To > >;

////////////////////////////////
//
// IsTupleConvertible
//
template< typename TFrom, typename TTo >
struct IsTupleConvertibleBasic : BooleanFalse {};

template< typename ... TFrom, typename ... TTo >
struct IsTupleConvertibleBasic< TupleTypes< TFrom ... >, TupleTypes< TTo ... > > : BooleanAnd<
	IsConvertible< TFrom, TTo > ...
> {};

template< typename TFrom, typename TTo >
struct IsTupleConvertibleApply : BooleanAnd<
	BooleanConstant< TupleSize< RemoveReference< TFrom > >::value == TupleSize< TTo >::value >,
	IsTupleConvertibleBasic<
		MakeTupleTypes< TFrom >,
		MakeTupleTypes< TTo >
	>
> {};

template< typename TFrom, typename TTo >
using IsTupleConvertible = BooleanAnd<
	IsTupleLike< RemoveReference< TFrom > >,
	IsTupleLike< TTo >,
	IsTupleConvertibleApply< TFrom, TTo >
>;

template< typename TFrom, typename TTo >
using NotTupleConvertible = BooleanNot< IsTupleConvertible< TFrom, TTo > >;

////////////////////////////////
//
// IsTupleConstructible
//
template< typename T0, typename T1 >
struct IsTupleConstructibleBasic : BooleanFalse {};

template< typename ... TElement, typename ... TValue >
struct IsTupleConstructibleBasic< TupleTypes< TElement ... >, TupleTypes< TValue ... > > : BooleanAnd<
	IsConstructible< TElement, TValue > ...
> {};

template< typename TTuple, typename TArgument >
struct IsTupleConstructibleApply : BooleanAnd<
	BooleanConstant< TupleSize< TTuple >::value == TupleSize< RemoveReference< TArgument > >::value >,
	IsTupleConstructibleBasic<
		MakeTupleTypes< TTuple >,
		MakeTupleTypes< TArgument >
	>
> {};

template< typename TTuple, typename TArgument >
using IsTupleConstructible = BooleanAnd<
	IsTupleLike< TTuple >,
	IsTupleLike< RemoveReference< TArgument > >,
	IsTupleConstructibleApply< TTuple, TArgument >
>;

template< typename TFrom, typename TTo >
using NotTupleConstructible = BooleanNot< IsTupleConstructible< TFrom, TTo > >;

////////////////////////////////
//
// IsTupleAssignable
//
template< typename T0, typename T1 >
struct IsTupleAssignableBasic : BooleanFalse {};

template< typename ... TElement, typename ... TValue >
struct IsTupleAssignableBasic< TupleTypes< TElement ... >, TupleTypes< TValue ... > > : BooleanAnd<
	IsAssignable< TElement &, TValue > ...
> {};

template< typename TTuple, typename TArgument >
struct IsTupleAssignableApply : BooleanAnd<
	BooleanConstant< TupleSize< TTuple >::value == TupleSize< RemoveReference< TArgument > >::value >,
	IsTupleAssignableBasic<
		MakeTupleTypes< TTuple >,
		MakeTupleTypes< TArgument >
	>
> {};

template< typename TTuple, typename TArgument >
using IsTupleAssignable = BooleanAnd<
	IsTupleLike< TTuple >,
	IsTupleLike< RemoveReference< TArgument > >,
	IsTupleAssignableApply< TTuple, TArgument >
>;

template< typename TFrom, typename TTo >
using NotTupleAssignable = BooleanNot< IsTupleAssignable< TFrom, TTo > >;

template< Size I, typename T, bool = BooleanAnd< IsEmpty< T >, NotFinal< T > >::value >
class TupleLeaf;

template< Size I, typename T, bool B >
inline void swap(
	TupleLeaf< I, T, B > & x,
	TupleLeaf< I, T, B > & y
) noexcept(
	noexcept(swap(x.get(), y.get()))
) {
	swap(x.get(), y.get());
}

template< Size I, typename TElement, bool >
class TupleLeaf {
public:
	BR_TUPLE_CONSTEXPR TupleLeaf() noexcept(IsNothrowDefaultConstructible< TElement >::value) : m_element() {
		assert();
	}

	TupleLeaf(TupleLeaf const &) = default;

	TupleLeaf(TupleLeaf &&) = default;

	template< typename TAllocator >
	TupleLeaf(NotUseAllocator, TAllocator const &) : m_element() {
		assert();
	}

	template< typename TAllocator >
	TupleLeaf(UseAllocatorWithTag, TAllocator const & allocator) : m_element(AllocatorArgumentTag(), allocator) {
		assert();
	}

	template< typename TAllocator >
	TupleLeaf(UseAllocatorWithoutTag, TAllocator const & allocator) : m_element(allocator) {
		assert();
	}

	template<
		typename TValue,
		typename = EnableIf<
			BooleanAnd<
				NotSame< Decay< TValue >, TupleLeaf >,
				IsConstructible< TElement, TValue >
			>
		>
	>
	explicit BR_TUPLE_CONSTEXPR TupleLeaf(TValue && value) noexcept(
		IsNothrowConstructible< TElement, TValue >::value
	) : m_element(forward< TValue >(value)) {
		static_assert(
			BooleanOr<
				NotReference< TElement >,
				BooleanAnd<
					IsLValueReference< TElement >,
					BooleanOr<
						IsLValueReference< TValue >,
						IsSame<
							RemoveReference< TValue >,
							ReferenceWrapper< RemoveReference< TElement > >
						>
					>
				>,
				BooleanAnd<
					IsRValueReference< TElement >,
					NotLValueReference< TValue >
				>
			>::value,
			"Attempted to construct a reference element in a tuple with an rvalue"
		);
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(
		NotUseAllocator,
		TAllocator const &,
		TValue && value
	) : m_element(forward< TValue >(value)) {
		assert< TValue >();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(
		UseAllocatorWithTag,
		TAllocator const & allocator,
		TValue && value
	) : m_element(AllocatorArgumentTag(), allocator, forward< TValue >(value)) {
		assert< TValue >();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(
		UseAllocatorWithoutTag,
		TAllocator const & allocator,
		TValue && value
	) : m_element(forward< TValue >(value), allocator) {
		assert< TValue >();
	}

	template< typename TValue >
	TupleLeaf & operator=(TValue && value) noexcept(
		IsNothrowAssignable< AddLValueReference< TElement >, TValue >::value
	) {
		m_element = forward< TValue >(value);
		return *this;
	}

	int swap(TupleLeaf & tuple_leaf) noexcept(
		noexcept(swap(make_reference< TupleLeaf >(), make_reference< TupleLeaf >()))
	) {
		swap(*this, tuple_leaf);
		return 0;
	}

	BR_TUPLE_CONSTEXPR TElement       & get()       noexcept { return m_element; }
	BR_TUPLE_CONSTEXPR TElement const & get() const noexcept { return m_element; }

private:
	TupleLeaf & operator=(TupleLeaf const &) = delete;

	void assert() {
		static_assert(NotReference< TElement >::value, "Attempted to default construct a reference element in a tuple");
	}

	template< typename TValue >
	void assert() {
		static_assert(
			BooleanOr<
				NotReference< TElement >,
				BooleanAnd<
					IsLValueReference< TElement >,
					BooleanOr<
						IsLValueReference< TValue >,
						IsSame<
							RemoveReference< TValue >,
							ReferenceWrapper< RemoveReference< TElement > >
						>
					>
				>
			>::value,
			"Attempted to construct a reference element in a tuple with an rvalue"
		);
	}

private:
	TElement m_element;
}; // class TupleLeaf

template< Size I, typename TElement >
class TupleLeaf< I, TElement, true > : TElement {
public:
	BR_TUPLE_CONSTEXPR TupleLeaf() noexcept(IsNothrowDefaultConstructible< TElement >::value) {}

	template< typename TAllocator >
	TupleLeaf(NotUseAllocator, TAllocator const &) {}

	template< typename TAllocator >
	TupleLeaf(UseAllocatorWithTag, TAllocator const & allocator)
		: TElement(AllocatorArgumentTag(), allocator) {}

	template< typename TAllocator >
	TupleLeaf(UseAllocatorWithoutTag, TAllocator const & allocator)
		: TElement(allocator) {}

	template<
		typename TValue,
		typename = EnableIf<
			BooleanAnd<
				NotSame< Decay< TValue >, TupleLeaf >,
				IsConstructible< TElement, TValue >
			>
		>
	>
	explicit BR_TUPLE_CONSTEXPR TupleLeaf(TValue && value) noexcept(
		IsNothrowConstructible< TElement, TValue >::value
	) : TElement(forward< TValue >(value)) {}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(NotUseAllocator, TAllocator const &, TValue && value)
		: TElement(forward< TValue >(value)) {}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(UseAllocatorWithTag, TAllocator const & allocator, TValue && value)
		: TElement(AllocatorArgumentTag(), allocator, forward< TValue >(value)) {}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(UseAllocatorWithoutTag, TAllocator const & allocator, TValue && value)
		: TElement(forward< TValue >(value), allocator) {}

    TupleLeaf(TupleLeaf const &) = default;

    TupleLeaf(TupleLeaf &&) = default;

	template< typename TValue >
	TupleLeaf & operator=(TValue && value) noexcept(
		IsNothrowAssignable< AddLValueReference< TElement >, TValue >::value
	) {
		TElement::operator=(forward< TValue >(value));
		return *this;
	}

	int swap(TupleLeaf & tuple_leaf) noexcept(
		noexcept(swap(make_reference< TupleLeaf >(), make_reference< TupleLeaf >()))
	) {
		swap(*this, tuple_leaf);
		return 0;
	}

	BR_TUPLE_CONSTEXPR TElement       & get()       noexcept { return static_cast< TElement       & >(*this); }
	BR_TUPLE_CONSTEXPR TElement const & get() const noexcept { return static_cast< TElement const & >(*this); }

private:
	TupleLeaf & operator=(TupleLeaf const &) = delete;
}; // class TupleLeaf< I, TElement, true >

template< typename ... Tn >
void swallow(Tn &&...) noexcept {}

template< typename I, typename ... T >
struct TupleImp;

template< Size ... I, typename ... T >
class TupleImp< TupleIndices< I ... >, T ... > : public TupleLeaf< I, T > ... {
public:
	BR_TUPLE_CONSTEXPR TupleImp() noexcept(BooleanAnd< IsNothrowDefaultConstructible< T > ...>::value) {}

	TupleImp(TupleImp const &) = default;

    TupleImp(TupleImp &&) = default;

	template<
		Size ... IHead, typename ... THead,
		Size ... ITail, typename ... TTail,
		typename ... TValue
	>
	explicit BR_TUPLE_CONSTEXPR TupleImp(
		TupleIndices< IHead ... >, TupleTypes< THead ... >,
		TupleIndices< ITail ... >, TupleTypes< TTail ... >,
		TValue && ... value
	) noexcept(
		BooleanAnd<
			IsNothrowConstructible< THead, TValue > ...,
			IsNothrowDefaultConstructible< TTail > ...
		>::value
	) :
		TupleLeaf< IHead, THead >(forward< TValue >(value)) ...,
		TupleLeaf< ITail, TTail >() ...
	{}

	template<
		typename TAllocator,
		Size ... IHead, typename ... THead,
		Size ... ITail, typename ... TTail,
		typename ... TValue
	>
	explicit TupleImp(
		AllocatorArgumentTag,
		TAllocator const & allocator,
		TupleIndices< IHead ... >, TupleTypes< THead ... >,
		TupleIndices< ITail ... >, TupleTypes< TTail ... >,
		TValue && ... value
	) :
		TupleLeaf< IHead, THead >(AllocatorConstructorUsage< THead, TAllocator, TValue >(), allocator, forward< TValue >(value)) ...,
		TupleLeaf< ITail, TTail >(AllocatorConstructorUsage< TTail, TAllocator >(), allocator) ...
	{}

	template<
		typename TTuple,
		typename = EnableIf< IsTupleConstructible< Tuple< T ... >, TTuple > >
	>
	BR_TUPLE_CONSTEXPR TupleImp(TTuple && tuple) noexcept(
		BooleanAnd<
			IsNothrowConstructible< T, TupleElement< I, MakeTupleTypes< TTuple > > > ...
		>::value
	) : TupleLeaf< I, T >(forward< TupleElement< I, MakeTupleTypes< TTuple > > >(get< I >(tuple))) ... {}

	template<
		typename TAllocator,
		typename TTuple,
		typename = EnableIf< IsTupleConstructible< Tuple< T ... >, TTuple > >
	>
	TupleImp(
		AllocatorArgumentTag,
		TAllocator const & allocator,
		TTuple && tuple
	) : TupleLeaf< I, T >(
			AllocatorConstructorUsage< T, TAllocator, TupleElement< I, MakeTupleTypes< TTuple > > >(),
			allocator,
			forward< TupleElement< I, MakeTupleTypes< TTuple > > >(get< I >(tuple))
		) ...
	{}

	template< typename TTuple >
	EnableIf<
		IsTupleAssignable< Tuple< T ... >, TTuple >,
		TupleImp &
	> operator=(TTuple && tuple) noexcept(
		BooleanAnd<
			IsNothrowAssignable< T &, TupleElement< I, MakeTupleTypes< TTuple > > > ...
		>::value
	) {
		swallow(
			TupleLeaf< I, T >::operator=(
				forward< TupleElement< I, MakeTupleTypes< TTuple > > >(get< I >(tuple))
			) ...
		);
		return *this;
	}

	TupleImp & operator=(TupleImp const & tuple) noexcept(
		BooleanAnd< IsNothrowCopyAssignable< T > ... >::value
	) {
		swallow(TupleLeaf< I, T >::operator=(static_cast< TupleLeaf< I, T > const & >(tuple).get()) ...);
		return *this;
	}

	TupleImp & operator=(TupleImp && tuple) noexcept(
		BooleanAnd< IsNothrowMoveAssignable< T > ... >::value
	) {
		swallow(TupleLeaf< I, T >::operator=(forward< T >(static_cast< TupleLeaf< I, T > & >(tuple).get())) ...);
		return *this;
	}

	void swap(TupleImp & tuple) noexcept(
		BooleanAnd< BooleanConstant< noexcept(make_reference< T >(), make_reference< T >()) > ... >::value
	) {
		swallow(TupleLeaf< I, T >::swap(static_cast< TupleLeaf< I, T > & >(tuple)) ...);
	}

	template< Size P >
	BR_TUPLE_CONSTEXPR TupleElement< P, TupleTypes< T ... > > & get() noexcept {
		return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > > & >(*this).get();
	}

	template< Size P >
	BR_TUPLE_CONSTEXPR TupleElement< P, TupleTypes< T ... > > const & get() const noexcept {
		return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > > const & >(*this).get();
	}

}; // class TupleImp< TupleIndices< I ... >, T ... >

template< typename ... T >
struct IsAllDefaultConstructible;

template< typename ... T >
struct IsAllDefaultConstructible< TupleTypes< T ... > > : BooleanAnd<
	IsDefaultConstructible< T > ...
> {};

} // namespace Detail

/// @brief Tuple
template < typename ... TElement >
class Tuple {
private:
	using Imp = Detail::TupleImp< Detail::MakeTupleIndices< 0, sizeof...(TElement) >, TElement ... >;

public:
	/**
	 *	@brief default constructor
	 */
	template<
		typename TDummy = TypeOperate::BooleanTrue,
		typename =  TypeOperate::EnableIf<
			TypeOperate::BooleanAnd< TDummy, TypeOperate::IsDefaultConstructible< TElement > ... >
		>
	>
	BR_TUPLE_CONSTEXPR Tuple() noexcept(
		TypeOperate::BooleanAnd< TypeOperate::IsNothrowDefaultConstructible< TElement > ... >::value
	) {}

	/**
	 *	@brief initialization conversion constructor
	 */
	explicit BR_TUPLE_CONSTEXPR Tuple(TElement const & ... element) noexcept(
		TypeOperate::BooleanAnd< TypeOperate::IsNothrowCopyConstructible< TElement > ... >::value
	) : m_imp(
		Detail::MakeTupleIndices< 0, sizeof...(TElement) >(),
		Detail::MakeTupleTypes< Tuple, 0, sizeof...(TElement) >(),
		Detail::MakeTupleIndices< 0, 0 >(),
		Detail::MakeTupleTypes< Tuple, 0, 0 >(),
		element ...
	) {}

	/**
	 *	@brief implicit initialization conversion constructor
	 */
    template<
		typename ... TValue,
		TypeOperate::EnableIf<
			TypeOperate::BooleanAnd<
				TypeOperate::BooleanConstant< sizeof...(TValue) <= sizeof...(TElement) >,
				Detail::IsTupleConvertible<
					Tuple< TValue ... >, Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >
				>,
				Detail::IsAllDefaultConstructible<
					Detail::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >
				>
			>,
			bool
		> = false
	>
	BR_TUPLE_CONSTEXPR Tuple(
		TValue && ... value
	) noexcept(
		TypeOperate::IsNothrowConstructible<
			Imp,
			Detail::MakeTupleIndices< 0, sizeof...(TValue) >,
			Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >,
			Detail::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >,
			Detail::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >,
			TValue ...
		>::value
	) : m_imp(
		Detail::MakeTupleIndices< 0, sizeof...(TValue) >(),
		Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward< TValue >(value) ...
	) {}

    template<
		typename ... TValue,
		TypeOperate::EnableIf<
			TypeOperate::BooleanAnd<
				TypeOperate::BooleanConstant< sizeof...(TValue) <= sizeof...(TElement) >,
				Detail::IsTupleConstructible<
					Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >, Tuple< TValue ... >
				>,
				Detail::NotTupleConvertible<
					Tuple< TValue ... >, Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >
				>,
				Detail::IsAllDefaultConstructible<
					Detail::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >
				>
			>,
			bool
		> = false
	>
	explicit BR_TUPLE_CONSTEXPR Tuple(
		TValue && ... value
	) noexcept(
		TypeOperate::IsNothrowConstructible<
			Imp,
			Detail::MakeTupleIndices< 0, sizeof...(TValue) >,
			Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >,
			Detail::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >,
			Detail::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >,
			TValue ...
		>::value
	) : m_imp(
		Detail::MakeTupleIndices< 0, sizeof...(TValue) >(),
		Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward< TValue >(value) ...
	) {}

	/**
	 *	@brief copy constructor
	 */
	Tuple(Tuple const &) = default;

	/**
	 *	@brief move constructor
	 */
	Tuple(Tuple &&) = default;

	/**
	 *	@brief implicit move conversion constructor
	 */
	template<
		typename TTuple,
		TypeOperate::EnableIf<
			Detail::IsTupleConvertible< TTuple, Tuple >,
			bool
		> = false
	>
	BR_TUPLE_CONSTEXPR Tuple(TTuple && tuple) noexcept(
		Detail::IsNothrowConstructible< Imp, TTuple >::value
	) : m_imp(
		forward< TTuple >(tuple)
	) {}

	template<
		typename TTuple,
		TypeOperate::EnableIf<
			TypeOperate::BooleanAnd<
				Detail::IsTupleConstructible< Tuple, TTuple >,
				Detail::NotTupleConvertible< TTuple, Tuple >
			>,
			bool
		> = false
	>
	explicit BR_TUPLE_CONSTEXPR Tuple(TTuple && tuple) noexcept(
		Detail::IsNothrowConstructible< Imp, TTuple >::value
	) : m_imp(
		forward< TTuple >(tuple)
	) {}

	/**
	 *	@brief allocator version initialization constructor
	 */
	template< typename TAllocator >
	Tuple(Memory::AllocatorArgumentTag, TAllocator const & allocator, TElement const & ... element) : m_imp(
		Memory::AllocatorArgumentTag(),
		allocator,
		Detail::MakeTupleIndices< 0, sizeof...(TElement) >(),
		Detail::MakeTupleTypes< Tuple, 0, sizeof...(TElement) >(),
		Detail::MakeTupleIndices< 0, 0 >(),
		Detail::MakeTupleTypes< Tuple, 0, 0 >(),
		element ...
	) {}

	/**
	 *	@brief allocator version implicit initialization conversion constructor
	 */
    template<
		typename TAllocator,
		typename ... TValue,
		typename = TypeOperate::EnableIf<
			TypeOperate::BooleanAnd<
				TypeOperate::BooleanConstant< sizeof...(TValue) <= sizeof...(TElement) >,
				Detail::IsTupleConstructible<
					Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >, Tuple< TValue ... >
				>,
				Detail::IsAllDefaultConstructible<
					Detail::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >
				>
			>
		>
	>
	Tuple(Memory::AllocatorArgumentTag, TAllocator const & allocator, TValue && ... value) : m_imp(
		Memory::AllocatorArgumentTag(),
		allocator,
		Detail::MakeTupleIndices<  0, sizeof...(TValue) >(),
		Detail::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward< TValue >(value) ...
	) {}

	/**
	 *	@brief allocator version move conversion constructor
	 */
	template<
		typename TAllocator, typename TTuple,
		typename = TypeOperate::EnableIf< Detail::IsTupleConvertible< TTuple, Tuple > >
	>
	Tuple(Memory::AllocatorArgumentTag, TAllocator const & allocator, TTuple && tuple) : m_imp(
		Memory::AllocatorArgumentTag(), allocator, forward< TTuple >(tuple)
	) {}

	/**
	 * @brief implicit move conversion assignment
	 */
	template<
		typename TTuple,
	 	typename = TypeOperate::EnableIf< Detail::IsTupleAssignable< Tuple, TTuple > >
	>
	Tuple & operator=(TTuple && tuple) noexcept(
		TypeOperate::IsNothrowAssignable< Imp &, TTuple >::value
	) {
		m_imp.operator=(forward< TTuple >(tuple));
		return *this;
	}

	/// @brief swap
	void swap(Tuple & tuple) noexcept(
		TypeOperate::BooleanAnd<
			TypeOperate::BooleanConstant< noexcept(swap(make_value< TElement >(), make_value< TElement >())) > ...
		>::value
	) {
		m_imp.swap(tuple.m_imp);
	}

	/// @brief get element at <b>I</b>
	template< Size I >
	BR_TUPLE_CONSTEXPR TupleElement< I, Tuple > & get() noexcept {
		return m_imp.get< I >();
	}

	/// @brief get element at <b>I</b>
	template< Size I >
	BR_TUPLE_CONSTEXPR TupleElement< I, Tuple > const & get() const noexcept {
		return m_imp.get< I >();
	}

private:
	Imp m_imp;

}; // class Tuple< TElement ... >

template <>
class Tuple<> {
public:
	BR_TUPLE_CONSTEXPR Tuple() noexcept {}

	template< typename TAllocator >
	Tuple(Memory::AllocatorArgumentTag, TAllocator const &) noexcept {}

	template< typename TAllocator >
	Tuple(Memory::AllocatorArgumentTag, TAllocator const &, Tuple const &) noexcept {}

	template< typename TValue >
	Tuple(Array< TValue, 0 >) noexcept {}

	template< typename TAllocator, typename TValue >
	Tuple(Memory::AllocatorArgumentTag, TAllocator const &, Array< TValue, 0 >) noexcept {}

	void swap(Tuple &) noexcept {}
}; // class Tuple<>

template< typename ... TElement >
void swap(Tuple< TElement ... > & lhs, Tuple< TElement ... > & rhs) noexcept(
	TypeOperate::BooleanAnd<
		TypeOperate::BooleanConstant< noexcept(swap(make_value< TElement >(), make_value< TElement >())) > ...
	>::value
) {
	lhs.swap(rhs);
}

template< Size I, typename ... TElement >
inline BR_TUPLE_CONSTEXPR TupleElement< I, Tuple< TElement ... > > & get(
	Tuple< TElement ... > & tuple
) noexcept {
	return tuple.get< I >();
}

template< Size I, typename ... TElement >
inline BR_TUPLE_CONSTEXPR TupleElement< I, Tuple< TElement ... > > const & get(
	Tuple< TElement ... > const & tuple
) noexcept {
	return tuple.get< I >();
}

template< Size I, typename ... TElement >
inline BR_TUPLE_CONSTEXPR TupleElement< I, Tuple< TElement ... > > && get(
	Tuple< TElement ... > && tuple
) noexcept {
	return static_cast< TupleElement< I, Tuple< TElement ... > > && >(tuple.get< I >());
}

template< typename ... T >
inline BR_TUPLE_CONSTEXPR Tuple< T & ... > tie(T & ... t) noexcept {
	return Tuple< T & ... >(t ...);
}

namespace Detail {

template< typename T >
struct IgnoreTag {
	template< typename TT >
	IgnoreTag const & operator=(TT &&) const { return *this; }
};

} // namespace Detail

constexpr static auto ignore = Detail::IgnoreTag< unsigned char >();

namespace Detail {

template< typename T >
struct make_tuple_return_imp {
	using Type = T;
};

template< typename T >
struct TypeMakeTupleReturnBasic : TypeWrapper< T > {};

template< typename T >
struct TypeMakeTupleReturnBasic< ReferenceWrapper< T > > : TypeAddLValueReference< T > {};

template< typename T >
struct TypeMakeTupleReturn : TypeMakeTupleReturnBasic< Decay< T > > {};

template< typename T >
using MakeTupleReturn = TypeUnwrap< TypeMakeTupleReturn< T > >;

} // namespace Detail

template< typename ... T >
inline BR_TUPLE_CONSTEXPR Tuple< Detail::MakeTupleReturn< T > ... > make_tuple(T && ... t) {
	return Tuple< Detail::MakeTupleReturn< T > ... >(forward< T >(t) ...);
}

template< typename ... T >
inline BR_TUPLE_CONSTEXPR Tuple< T && ... > forward_as_tuple(T && ... t) noexcept {
	return Tuple< T && ... >(forward< T >(t) ...);
}

namespace Detail {

template< Size I >
struct TupleCompare {
	template< typename T0, typename T1 >
	static BR_TUPLE_CONSTEXPR bool equal(T0 const & t0, T1 const & t1) {
		return TupleCompare< I-1 >::equal(t0, t1) && get< I-1 >(t0) == get< I-1 >(t1);
	}

	template< typename T0, typename T1 >
	static BR_TUPLE_CONSTEXPR bool less(T0 const & t0, T1 const & t1) {
		return TupleCompare< I-1 >::less(t0, t1) || (!TupleCompare< I-1 >::less(t1, t0) && get< I-1 >(t0) < get< I-1 >(t1));
	}
};

template<>
struct TupleCompare< 0 > {
	template< typename T0, typename T1 >
	static BR_TUPLE_CONSTEXPR bool equal(T0 const &, T1 const &) {
		return true;
	}

	template< typename T0, typename T1 >
	static BR_TUPLE_CONSTEXPR bool less(T0 const &, T1 const &) {
		return false;
	}
};

} // namespace Detail

template< typename ... T0, typename ... T1 >
BR_TUPLE_CONSTEXPR bool operator==(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return Detail::TupleCompare< sizeof...(T0) >::equal(t0, t1);
}

template< typename ... T0, typename ... T1 >
BR_TUPLE_CONSTEXPR bool operator!=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return !(t0 == t1);
}

template< typename ... T0, typename ... T1 >
BR_TUPLE_CONSTEXPR bool operator<(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return Detail::TupleCompare< sizeof...(T0) >::less(t0, t1);
}

template< typename ... T0, typename ... T1 >
BR_TUPLE_CONSTEXPR bool operator>(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return t1 < t0;
}

template< typename ... T0, typename ... T1 >
BR_TUPLE_CONSTEXPR bool operator<=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return !(t1 < t0);
}

template< typename ... T0, typename ... T1 >
BR_TUPLE_CONSTEXPR bool operator>=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return !(t0 < t1);
}

namespace Detail {

template< typename T0, typename T1 >
struct TypeTupleCatType;

template< typename T0, typename T1 >
using TupleCatType = TypeUnwrap< TypeTupleCatType< T0, T1 > >;

template< typename ... T0, typename ... T1 >
struct TypeTupleCatType< Tuple< T0 ... >, TupleTypes< T1 ... > > : TypeWrapper< Tuple< T0 ..., T1 ...  > > {};

template< typename TResult, bool is_tuple_like, typename ... TTuple >
struct TypeTupleCatResultBasic {};

template< typename ... T, typename TTuple >
struct TypeTupleCatResultBasic< Tuple< T ... >, true, TTuple > : TypeTupleCatType<
	Tuple< T ... >, MakeTupleTypes< RemoveReference< TTuple > >
> {};

template< typename ... T, typename TTuple0, typename TTuple1, typename ... TTuple >
struct TypeTupleCatResultBasic< Tuple< T ... >, true, TTuple0, TTuple1, TTuple ... > : TypeTupleCatResultBasic<
	TupleCatType< Tuple< T ... >, MakeTupleTypes< RemoveReference< TTuple0 > > >,
	IsTupleLike< RemoveReference< TTuple1 > >::value,
	TTuple1,
	TTuple ...
> {};

template< typename ... TTuple >
struct TypeTupleCatResult;

template< typename TTuple0, typename ... TTuple >
struct TypeTupleCatResult< TTuple0, TTuple ... > : TypeTupleCatResultBasic<
	Tuple<>,
	IsTupleLike< RemoveReference< TTuple0 > >::value,
	TTuple0, TTuple ...
> {};

template<>
struct TypeTupleCatResult<> : TypeWrapper< Tuple<> > {};

template< typename ... TTuple >
using TupleCatResult = TypeUnwrap< TypeTupleCatResult< TTuple ... > >;

template< typename TResult, typename TIndices, typename TTuple0, typename ... TTuple >
struct TypeTupleCatResultReferenceBasic;

template< typename ... T, Size ... I, typename TTuple >
struct TypeTupleCatResultReferenceBasic<
	Tuple< T ... >, TupleIndices< I ... >, TTuple
> : TypeWrapper<
	Tuple< T ..., MapQualifier< TTuple, TupleElement< I, RemoveReference< TTuple > > > && ... >
> {};

template< typename ... T, Size ... I, typename TTuple0, typename TTuple1, typename ... TTuple >
struct TypeTupleCatResultReferenceBasic<
	Tuple< T ... >, TupleIndices< I ... >, TTuple0, TTuple1, TTuple ...
> : TypeTupleCatResultReferenceBasic<
	Tuple< T ..., MapQualifier< TTuple0, TupleElement< I, RemoveReference< TTuple0 > > > && ... >,
	MakeTupleIndices< 0, TupleSize< RemoveReference< TTuple1 > >::value >,
	TTuple1,
	TTuple ...
> {};

template< typename TTuple0, typename ... TTuple >
struct TypeTupleCatResultReference : TypeTupleCatResultReferenceBasic<
	Tuple<>,
	MakeTupleIndices< 0, TupleSize< RemoveReference< TTuple0 > >::value >,
	TTuple0,
	TTuple ...
> {};

template< typename ... TTuple >
using TupleCatResultReference = TypeUnwrap< TypeTupleCatResultReference< TTuple ... > >;

template< typename TResult, typename TIHead, typename TITail >
struct TupleCat;

template< typename ... T, Size ... IHead, Size ... ITail >
struct TupleCat< Tuple<  T ... >, TupleIndices< IHead ... >, TupleIndices< ITail ... > > {
	template< typename TTuple >
	BR_TUPLE_CONSTEXPR TupleCatResultReference<
		Tuple< T ... > &&, TTuple &&
	> operator()(
		Tuple< T ... > head, TTuple && tail
	) {
		return forward_as_tuple(forward< T >(get< IHead >(head)) ..., get< ITail >(forward< TTuple >(tail)) ...);
	}

	template< typename TTuple0, typename TTuple1, typename ... TTuples >
	BR_TUPLE_CONSTEXPR TupleCatResultReference<
		Tuple< T ... > &&, TTuple0 &&, TTuple1 &&, TTuples && ...
	> operator()(
		Tuple< T ... > head, TTuple0 && tail0, TTuple1 && tail1, TTuples && ... tails
	) {
		using NoRefTuple0 = RemoveReference< TTuple0 >;
		return TupleCat<
			Tuple< T ..., MapQualifier< TTuple0, TupleElement< ITail, NoRefTuple0 > > && ... >,
			MakeTupleIndices< 0, sizeof...(T) + TupleSize< NoRefTuple0 >::value >,
			MakeTupleIndices< 0, TupleSize< RemoveReference< TTuple1 > >::value >
		>()(
			forward_as_tuple(forward< T >(get< IHead >(head)) ..., get< ITail >(forward< TTuple0 >(tail0)) ...),
			forward< TTuple1 >(tail1),
			forward< TTuples >(tails) ...
		);
	}
};

} // namespace Detail

inline BR_TUPLE_CONSTEXPR Tuple<> tuple_cat() {
	return Tuple<>();
}

template< typename TTuple0, typename ... TTuples >
inline BR_TUPLE_CONSTEXPR Detail::TupleCatResult< TTuple0, TTuples ... > tuple_cat(TTuple0 && tuple0, TTuples ... tuples) {
	return Detail::TupleCat<
		Tuple<>,
		Detail::TupleIndices<>,
		Detail::MakeTupleIndices< 0, TupleSize< TypeOperate::RemoveReference< TTuple0 > >::value >
	>()(
		Tuple<>(), forward< TTuple0 >(tuple0), forward< TTuples >(tuples) ...
	);
}

// template< typename ... T, typename TAllocator >
// struct IsUseAllocator< Tuple< T ... >, TAllocator > : TypeOperate::BooleanTrue {};

} // namespace BR

#undef BR_TUPLE_CONSTEXPR