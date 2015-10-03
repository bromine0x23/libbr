#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_const_volatile.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_volatile.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/map_qualifier.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_assign.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assign.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/integer_constant.hpp>
#include <libbr/utility/wrapped_reference.hpp>

namespace BR {

namespace Detail {
namespace Utility {

template< typename T >
struct TupleSize;

template< Size I, typename T >
struct TypeTupleElement;

template< Size ... In >
struct TupleIndices : Integers< Size, In ... > {};

template< typename ... Tn >
struct TupleTypes : Types< Tn ... > {};

} // namespace Utility
} // namespace Detail

template< typename ... types >
class Tuple;

template< typename T >
struct TupleSize : IntegerConstant< Size, Detail::Utility::TupleSize< T >::value > {};

template< Size I, typename T >
struct TypeTupleElement : TypeRewrap< Detail::Utility::TypeTupleElement< I, T > > {};

template< Size I, typename T >
using TupleElement =  TypeUnwrap< TypeTupleElement< I, T > >;

template< Size I, typename ... Tn > BR_CONSTEXPR_AFTER_CXX11 TupleElement< I, Tuple< Tn ... > >       & get(Tuple< Tn ... >       &) noexcept;
template< Size I, typename ... Tn > BR_CONSTEXPR_AFTER_CXX11 TupleElement< I, Tuple< Tn ... > > const & get(Tuple< Tn ... > const &) noexcept;
template< Size I, typename ... Tn > BR_CONSTEXPR_AFTER_CXX11 TupleElement< I, Tuple< Tn ... > >      && get(Tuple< Tn ... >      &&) noexcept;

namespace Detail {
namespace Utility {

//******************************
//
// TupleSize
//
template< typename ... Tn >
struct TupleSize< Tuple< Tn ... > > : IntegerConstant< Size, sizeof...(Tn) > {};

template< typename T > class TupleSize< T const          > : TupleSize<T> {};
template< typename T > class TupleSize< T       volatile > : TupleSize<T> {};
template< typename T > class TupleSize< T const volatile > : TupleSize<T> {};

template< typename ...Tn >
struct TupleSize< TupleTypes< Tn ... > > : IntegerConstant< Size, sizeof...(Tn) > {};

//******************************
//
// TupleElement
//
template< Size I, typename ... Tn >
struct TypeTupleElement< I, Tuple< Tn ... > > : TypeTupleElement< I, TupleTypes< Tn ... > > {};

template< Size I, typename T > struct TypeTupleElement< I, T const          > : TypeAddConst        < TupleElement< I, T > > {};
template< Size I, typename T > struct TypeTupleElement< I, T       volatile > : TypeAddVolatile     < TupleElement< I, T > > {};
template< Size I, typename T > struct TypeTupleElement< I, T const volatile > : TypeAddConstVolatile< TupleElement< I, T > > {};

template< Size I >
struct TypeTupleElement< I, TupleTypes<> > {
	static_assert(I == 0, "TupleElement index out of range");
	static_assert(I != 0, "TupleElement index out of range");
};

template< typename THead, typename ... TTail >
struct TypeTupleElement< 0, TupleTypes< THead, TTail ... > > : TypeWrapper<THead> {};

template< Size I, typename THead, typename ... TTail >
struct TypeTupleElement< I, TupleTypes< THead, TTail ... > > : TypeTupleElement< I - 1, TupleTypes< TTail ... > > {};

//******************************
//
// IsTupleLike
//
template< typename T >
struct IsTupleLike : BooleanFalse {};

template< typename T > struct IsTupleLike< T const          > : IsTupleLike<T> {};
template< typename T > struct IsTupleLike< T       volatile > : IsTupleLike<T> {};
template< typename T > struct IsTupleLike< T const volatile > : IsTupleLike<T> {};

template< typename ... Tn >
struct IsTupleLike< Tuple< Tn ... > > :BooleanTrue {};

/*
template< typename T, Size S >
struct IsTupleLike< Array< T, S > > : BooleanTrue {};
*/

template< typename ... Tn >
struct IsTupleLike< TupleTypes< Tn ... > > : BooleanTrue {};

//******************************
//
// MakeTupleIndices
//
template< Size From, Size To, Size ... In >
struct TypeMakeTupleIndices;

template< Size From, Size To, Size ... In >
struct TypeMakeTupleIndices< From, To, In ... > : TypeMakeTupleIndices< From + 1, To, In ..., From > {};

template< Size To, Size ... In >
struct TypeMakeTupleIndices< To, To, In ... > : TypeWrapper< TupleIndices< In ... > > {};

template< Size From, Size To >
using MakeTupleIndices = TypeUnwrap< TypeMakeTupleIndices< From, To > >;


//******************************
//
// MakeTupleTypes
//
template< typename T, Size From, Size To, typename ... Tn >
struct TypeMakeTupleTypes;

template< Size I, typename T >
using MakeTupleType = Conditional<
	IsLValueReference<T>,
	TupleElement< I, T > &,
	TupleElement< I, T >
>;

template< typename T, Size From, Size To, typename ... Tn >
struct TypeMakeTupleTypes;

template< typename T, Size From, Size To, typename ... Tn >
struct TypeMakeTupleTypes< T, From, To, Tn ... > : TypeMakeTupleTypes< T, From + 1, To, Tn ..., MakeTupleType< From, RemoveReference<T> > > {
	static_assert(From <= To, "MakeTupleTypes input error");
};

template< typename T, Size To, typename ... Tn >
struct TypeMakeTupleTypes< T, To, To, Tn ... > : TypeWrapper< TupleTypes< Tn ... > > {};

template< typename T, Size From = 0, Size To = TupleSize< RemoveReference<T> >::value >
using MakeTupleTypes = TypeUnwrap< TypeMakeTupleTypes< T, From, To > >;

//******************************
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
	BooleanConstant< TupleSize< RemoveReference<TFrom> >::value == TupleSize<TTo>::value >,
	IsTupleConvertibleBasic<
		MakeTupleTypes<TFrom>,
		MakeTupleTypes<TTo>
	>
> {};

template< typename TFrom, typename TTo >
using IsTupleConvertible = BooleanAnd<
	IsTupleLike< RemoveReference<TFrom> >,
	IsTupleLike<TTo>,
	IsTupleConvertibleApply< TFrom, TTo >
>;

template< typename TFrom, typename TTo >
using NotTupleConvertible = BooleanNot< IsTupleConvertible< TFrom, TTo > >;

//******************************
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
	BooleanConstant< TupleSize<TTuple>::value == TupleSize< RemoveReference<TArgument> >::value >,
	IsTupleConstructibleBasic<
		MakeTupleTypes<TTuple>,
		MakeTupleTypes<TArgument>
	>
> {};

template< typename TTuple, typename TArgument >
using IsTupleConstructible = BooleanAnd<
	IsTupleLike<TTuple>,
	IsTupleLike< RemoveReference<TArgument> >,
	IsTupleConstructibleApply< TTuple, TArgument >
>;

template< typename TFrom, typename TTo >
using NotTupleConstructible = BooleanNot< IsTupleConstructible< TFrom, TTo > >;

//******************************
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
	BooleanConstant< TupleSize<TTuple>::value == TupleSize< RemoveReference<TArgument> >::value >,
	IsTupleAssignableBasic<
		MakeTupleTypes<TTuple>,
		MakeTupleTypes<TArgument>
	>
> {};

template< typename TTuple, typename TArgument >
using IsTupleAssignable = BooleanAnd<
	IsTupleLike<TTuple>,
	IsTupleLike< RemoveReference<TArgument> >,
	IsTupleAssignableApply< TTuple, TArgument >
>;

template< typename ... T >
struct IsAllDefaultConstructible;

template< typename ... T >
struct IsAllDefaultConstructible< TupleTypes< T ... > > : BooleanAnd< IsDefaultConstructible< T > ... > {};

template< typename TFrom, typename TTo >
using NotTupleAssignable = BooleanNot< IsTupleAssignable< TFrom, TTo > >;

struct NotUseAllocator {};

struct UseAllocatorWithTag {};

struct UseAllocatorWithoutTag {};

template< typename T, typename TAllocator, typename ... TArguments >
struct TypeAllocatorConstructorUsage : TypeWrapper<
	Conditional<
		UseAllocator< T, TAllocator >,
		Conditional<
			IsConstructible< T, AllocatorArgumentTag, TAllocator, TArguments ... >,
			UseAllocatorWithTag,
			UseAllocatorWithoutTag
		>,
		NotUseAllocator
	>
> {};

template< typename T, typename TAllocator, typename ... TArguments >
using AllocatorConstructorUsage = TypeUnwrap< TypeAllocatorConstructorUsage< T, TAllocator, TArguments ... > >;

template< Size I, typename T, bool = BooleanAnd< IsEmpty<T>, NotFinal<T> >::value >
class TupleLeaf;

template< Size I, typename T, bool B >
inline void swap(
	TupleLeaf< I, T, B > & x,
	TupleLeaf< I, T, B > & y
) noexcept(IsNothrowSwappable<T>::value) {
	swap(x.get(), y.get());
}

template< Size I, typename TElement, bool >
class TupleLeaf {
public:
	BR_CONSTEXPR_AFTER_CXX11 TupleLeaf() noexcept(HasNothrowDefaultConstructor<TElement>::value) : m_element() {
		m_assert();
	}

	TupleLeaf(TupleLeaf const &) = default;

	TupleLeaf(TupleLeaf &&) = default;

	template< typename TAllocator >
	TupleLeaf(NotUseAllocator, TAllocator const &) : m_element() {
		m_assert();
	}

	template< typename TAllocator >
	TupleLeaf(UseAllocatorWithTag, TAllocator const & allocator) : m_element(allocator_argument_tag, allocator) {
		m_assert();
	}

	template< typename TAllocator >
	TupleLeaf(UseAllocatorWithoutTag, TAllocator const & allocator) : m_element(allocator) {
		m_assert();
	}

	template<
		typename TValue,
		typename = EnableIf<
			BooleanAnd<
				NotSame< Decay<TValue>, TupleLeaf >,
				IsConstructible< TElement, TValue >
			>
		>
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 TupleLeaf(TValue && value) noexcept(
		IsNothrowConstructible< TElement, TValue >::value
	) : m_element(forward<TValue>(value)) {
		static_assert(
			BooleanOr<
				NotReference<TElement>,
				BooleanAnd<
					IsLValueReference<TElement>,
					BooleanOr<
						IsLValueReference<TValue>,
						IsSame<
							RemoveReference<TValue>,
							WrappedReference< RemoveReference<TElement> >
						>
					>
				>,
				BooleanAnd< IsRValueReference<TElement>, NotLValueReference<TValue> >
			>::value,
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(
		NotUseAllocator,
		TAllocator const &,
		TValue && value
	) : m_element(forward<TValue>(value)) {
		m_assert<TValue>();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(
		UseAllocatorWithTag,
		TAllocator const & allocator,
		TValue && value
	) : m_element(allocator_argument_tag, allocator, forward<TValue>(value)) {
		m_assert<TValue>();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(
		UseAllocatorWithoutTag,
		TAllocator const & allocator,
		TValue && value
	) : m_element(forward<TValue>(value), allocator) {
		m_assert<TValue>();
	}

	template< typename TValue >
	TupleLeaf & operator=(TValue && value) noexcept(
		IsNothrowAssignable< AddLValueReference<TElement>, TValue >::value
	) {
		m_element = forward<TValue>(value);
		return *this;
	}

	int swap(TupleLeaf & tuple_leaf) noexcept(IsNothrowSwappable<TupleLeaf>::value) {
		swap(*this, tuple_leaf);
		return 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 TElement       & get()       noexcept { return m_element; }
	BR_CONSTEXPR_AFTER_CXX11 TElement const & get() const noexcept { return m_element; }

private:
	TupleLeaf & operator=(TupleLeaf const &) = delete;

	void m_assert() const {
		static_assert(NotReference<TElement>::value, "Attempted to default construct a reference element in a Tuple");
	}

	template< typename TValue >
	void m_assert() const {
		static_assert(
			BooleanOr<
				NotReference<TElement>,
				BooleanAnd<
					IsLValueReference<TElement>,
					BooleanOr<
						IsLValueReference<TValue>,
						IsSame<
							RemoveReference<TValue>,
							WrappedReference< RemoveReference<TElement> >
						>
					>
				>
			>::value,
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

private:
	TElement m_element;
}; // class TupleLeaf

template< Size I, typename TElement >
class TupleLeaf< I, TElement, true > : TElement {
public:
	BR_CONSTEXPR_AFTER_CXX11 TupleLeaf() noexcept(HasNothrowDefaultConstructor<TElement>::value) {}

	template< typename TAllocator >
	TupleLeaf(NotUseAllocator, TAllocator const &) {}

	template< typename TAllocator >
	TupleLeaf(UseAllocatorWithTag, TAllocator const & allocator) : TElement(allocator_argument_tag, allocator) {}

	template< typename TAllocator >
	TupleLeaf(UseAllocatorWithoutTag, TAllocator const & allocator) : TElement(allocator) {}

	template<
		typename TValue,
		typename = EnableIf<
			BooleanAnd<
				NotSame< Decay<TValue>, TupleLeaf >,
				IsConstructible< TElement, TValue >
			>
		>
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 TupleLeaf(TValue && value) noexcept(
		IsNothrowConstructible< TElement, TValue >::value
	) : TElement(forward<TValue>(value)) {}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(NotUseAllocator, TAllocator const &, TValue && value)
		: TElement(forward<TValue>(value)) {}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(UseAllocatorWithTag, TAllocator const & allocator, TValue && value)
		: TElement(allocator_argument_tag, allocator, forward<TValue>(value)) {}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(UseAllocatorWithoutTag, TAllocator const & allocator, TValue && value)
		: TElement(forward<TValue>(value), allocator) {}

    TupleLeaf(TupleLeaf const &) = default;

    TupleLeaf(TupleLeaf &&) = default;

	template< typename TValue >
	TupleLeaf & operator=(TValue && value) noexcept(
		IsNothrowAssignable< AddLValueReference<TElement>, TValue >::value
	) {
		TElement::operator=(forward<TValue>(value));
		return *this;
	}

	int swap(TupleLeaf & tuple_leaf) noexcept(IsNothrowSwappable<TupleLeaf>::value) {

		swap(*this, tuple_leaf);
		return 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 TElement       & get()       noexcept { return static_cast< TElement       & >(*this); }
	BR_CONSTEXPR_AFTER_CXX11 TElement const & get() const noexcept { return static_cast< TElement const & >(*this); }

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
	BR_CONSTEXPR_AFTER_CXX11 TupleImp() noexcept(BooleanAnd< HasNothrowDefaultConstructor<T> ... >::value) {}

	TupleImp(TupleImp const &) = default;

	TupleImp(TupleImp &&) = default;

	template<
		Size ... IHead, typename ... THead,
		Size ... ITail, typename ... TTail,
		typename ... TValue
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 TupleImp(
		TupleIndices< IHead ... >, TupleTypes< THead ... >,
		TupleIndices< ITail ... >, TupleTypes< TTail ... >,
		TValue && ... value
	) noexcept(
		BooleanAnd<
			IsNothrowConstructible< THead, TValue > ...,
			HasNothrowDefaultConstructor<TTail> ...
		>::value
	) :
		TupleLeaf< IHead, THead >(forward<TValue>(value)) ...,
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
		TupleLeaf< IHead, THead >(AllocatorConstructorUsage< THead, TAllocator, TValue >(), allocator, forward<TValue>(value)) ...,
		TupleLeaf< ITail, TTail >(AllocatorConstructorUsage< TTail, TAllocator >(), allocator) ...
	{}

	template<
		typename TTuple,
		typename = EnableIf< IsTupleConstructible< Tuple< T ... >, TTuple > >
	>
	BR_CONSTEXPR_AFTER_CXX11 TupleImp(TTuple && tuple) noexcept(
		BooleanAnd<
			IsNothrowConstructible< T, TupleElement< I, MakeTupleTypes<TTuple> > > ...
		>::value
	) : TupleLeaf< I, T >(forward< TupleElement< I, MakeTupleTypes<TTuple> > >(get<I>(tuple))) ... {}

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
			AllocatorConstructorUsage< T, TAllocator, TupleElement< I, MakeTupleTypes<TTuple> > >(),
			allocator,
			forward< TupleElement< I, MakeTupleTypes<TTuple> > >(get<I>(tuple))
		) ...
	{}

	template< typename TTuple >
	EnableIf<
		IsTupleAssignable< Tuple< T ... >, TTuple >,
		TupleImp &
	> operator=(TTuple && tuple) noexcept(
		BooleanAnd<
			IsNothrowAssignable< T &, TupleElement< I, MakeTupleTypes<TTuple> > > ...
		>::value
	) {
		swallow(
			TupleLeaf< I, T >::operator=(
				forward< TupleElement< I, MakeTupleTypes<TTuple> > >(get<I>(tuple))
			) ...
		);
		return *this;
	}

	TupleImp & operator=(TupleImp const & tuple) noexcept(
		BooleanAnd< HasNothrowCopyAssign<T> ... >::value
	) {
		swallow(TupleLeaf< I, T >::operator=(static_cast< TupleLeaf< I, T > const & >(tuple).get()) ...);
		return *this;
	}

	TupleImp & operator=(TupleImp && tuple) noexcept(
		BooleanAnd< HasNothrowMoveAssign<T> ... >::value
	) {
		swallow(TupleLeaf< I, T >::operator=(forward< T >(static_cast< TupleLeaf< I, T > & >(tuple).get())) ...);
		return *this;
	}

	void swap(TupleImp & tuple) noexcept(BooleanAnd< IsNothrowSwappable<T> ... >::value) {
		swallow(TupleLeaf< I, T >::swap(static_cast< TupleLeaf< I, T > & >(tuple)) ...);
	}

	template< Size P >
	BR_CONSTEXPR_AFTER_CXX11 TupleElement< P, TupleTypes< T ... > > & get() noexcept {
		return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > > & >(*this).get();
	}

	template< Size P >
	BR_CONSTEXPR_AFTER_CXX11 TupleElement< P, TupleTypes< T ... > > const & get() const noexcept {
		return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > > const & >(*this).get();
	}

}; // class TupleImp< TupleIndices< I ... >, T ... >

} // namespace Utility
} // namespace Detail

/// Tuple
template < typename ... TElement >
class Tuple {
public:
	using Imp = Detail::Utility::TupleImp< Detail::Utility::MakeTupleIndices< 0, sizeof...(TElement) >, TElement ... >;

public:
	/**
	 * default constructor
	 */
	template<
		typename TDummy = BooleanTrue,
		typename =  EnableIf< BooleanAnd< TDummy, IsDefaultConstructible<TElement> ... > >
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple() noexcept(BooleanAnd< HasNothrowDefaultConstructor<TElement> ... >::value) {}

	/**
	 *	initialization conversion constructor
	 */
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(TElement const & ... element) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<TElement> ... >::value
	) : m_imp(
		Detail::Utility::MakeTupleIndices< 0, sizeof...(TElement) >(),
		Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TElement) >(),
		Detail::Utility::MakeTupleIndices< 0, 0 >(),
		Detail::Utility::MakeTupleTypes< Tuple, 0, 0 >(),
		element ...
	) {}

	/**
	 *	implicit initialization conversion constructor
	 */
    template<
		typename ... TValue,
		EnableIf<
			BooleanAnd<
				BooleanConstant< (sizeof...(TValue) <= sizeof...(TElement)) >,
				Detail::Utility::IsTupleConvertible<
					Tuple< TValue ... >, Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >
				>,
				Detail::Utility::IsAllDefaultConstructible<
					Detail::Utility::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >
				>
			>,
			bool
		> = false
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(
		TValue && ... value
	) noexcept(
		IsNothrowConstructible<
			Imp,
			Detail::Utility::MakeTupleIndices< 0, sizeof...(TValue) >,
			Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >,
			Detail::Utility::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >,
			Detail::Utility::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >,
			TValue ...
		>::value
	) : m_imp(
		Detail::Utility::MakeTupleIndices< 0, sizeof...(TValue) >(),
		Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::Utility::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::Utility::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward<TValue>(value) ...
	) {}

    template<
		typename ... TValue,
		EnableIf<
			BooleanAnd<
				BooleanConstant< (sizeof...(TValue) <= sizeof...(TElement)) >,
				Detail::Utility::IsTupleConstructible<
					Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >, Tuple< TValue ... >
				>,
				Detail::Utility::NotTupleConvertible<
					Tuple< TValue ... >, Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >
				>,
				Detail::Utility::IsAllDefaultConstructible<
					Detail::Utility::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >
				>
			>,
			bool
		> = false
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(
		TValue && ... value
	) noexcept(
		IsNothrowConstructible<
			Imp,
			Detail::Utility::MakeTupleIndices< 0, sizeof...(TValue) >,
			Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >,
			Detail::Utility::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >,
			Detail::Utility::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >,
			TValue ...
		>::value
	) : m_imp(
		Detail::Utility::MakeTupleIndices< 0, sizeof...(TValue) >(),
		Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::Utility::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::Utility::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward<TValue>(value) ...
	) {}

	/**
	 *	copy constructor
	 */
	Tuple(Tuple const &) = default;

	/**
	 *	move constructor
	 */
	Tuple(Tuple &&) = default;

	/**
	 *	implicit move conversion constructor
	 */
	template<
		typename TTuple,
		EnableIf<
			Detail::Utility::IsTupleConvertible< TTuple, Tuple >, bool
		> = false
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(TTuple && tuple) noexcept(
		IsNothrowConstructible< Imp, TTuple >::value
	) : m_imp(forward< TTuple >(tuple)) {}

	template<
		typename TTuple,
		EnableIf<
			BooleanAnd<
				Detail::Utility::IsTupleConstructible< Tuple, TTuple >,
				Detail::Utility::NotTupleConvertible< TTuple, Tuple >
			>,
			bool
		> = false
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(TTuple && tuple) noexcept(
		IsNothrowConstructible< Imp, TTuple >::value
	) : m_imp(forward<TTuple>(tuple)) {}

	/**
	 *	allocator version initialization constructor
	 */
	template< typename TAllocator >
	Tuple(AllocatorArgumentTag, TAllocator const & allocator, TElement const & ... element) : m_imp(
		allocator_argument_tag,
		allocator,
		Detail::Utility::MakeTupleIndices< 0, sizeof...(TElement) >(),
		Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TElement) >(),
		Detail::Utility::MakeTupleIndices< 0, 0 >(),
		Detail::Utility::MakeTupleTypes< Tuple, 0, 0 >(),
		element ...
	) {}

	/**
	 *	allocator version implicit initialization conversion constructor
	 */
    template<
		typename TAllocator,
		typename ... TValue,
		typename = EnableIf<
			BooleanAnd<
				BooleanConstant< sizeof...(TValue) <= sizeof...(TElement) >,
				Detail::Utility::IsTupleConstructible<
					Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >, Tuple< TValue ... >
				>,
				Detail::Utility::IsAllDefaultConstructible<
					Detail::Utility::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >
				>
			>
		>
	>
	Tuple(AllocatorArgumentTag, TAllocator const & allocator, TValue && ... value) : m_imp(
		allocator_argument_tag,
		allocator,
		Detail::Utility::MakeTupleIndices<  0, sizeof...(TValue) >(),
		Detail::Utility::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::Utility::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::Utility::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward<TValue>(value) ...
	) {}

	/**
	 * allocator version move conversion constructor
	 */
	template<
		typename TAllocator, typename TTuple,
		typename = EnableIf< Detail::Utility::IsTupleConvertible< TTuple, Tuple > >
	>
	Tuple(AllocatorArgumentTag, TAllocator const & allocator, TTuple && tuple) : m_imp(
		allocator_argument_tag, allocator, forward< TTuple >(tuple)
	) {}

	/**
	 * implicit move conversion assignment
	 */
	template<
		typename TTuple,
	 	typename = EnableIf< Detail::Utility::IsTupleAssignable< Tuple, TTuple > >
	>
	Tuple & operator=(TTuple && tuple) noexcept(
		IsNothrowAssignable< Imp &, TTuple >::value
	) {
		m_imp.operator=(forward<TTuple>(tuple));
		return *this;
	}

	/**
	 * swap
	 */
	void swap(Tuple & tuple) noexcept(
		BooleanAnd< IsNothrowSwappable<TElement> ... >::value
	) {
		;
		m_imp.swap(tuple.m_imp);
	}

	/**
	 *  get element at \em I
	 */
	template< Size I >
	BR_CONSTEXPR_AFTER_CXX11 TupleElement< I, Tuple > & get() noexcept {
		return m_imp.get< I >();
	}

	/**
	 *  get element at \em I
	 */
	template< Size I >
	BR_CONSTEXPR_AFTER_CXX11 TupleElement< I, Tuple > const & get() const noexcept {
		return m_imp.get< I >();
	}

private:
	Imp m_imp;

}; // class Tuple< TElement ... >

template <>
class Tuple<> {
public:
	BR_CONSTEXPR_AFTER_CXX11 Tuple() noexcept {}

	template< typename TAllocator >
	Tuple(AllocatorArgumentTag, TAllocator const &) noexcept {}

	template< typename TAllocator >
	Tuple(AllocatorArgumentTag, TAllocator const &, Tuple const &) noexcept {}

	template< typename TValue >
	Tuple(Array< TValue, 0 >) noexcept {}

	template< typename TAllocator, typename TValue >
	Tuple(AllocatorArgumentTag, TAllocator const &, Array< TValue, 0 >) noexcept {}

	void swap(Tuple &) noexcept {}
}; // class Tuple<>

template< typename ... TElement >
void swap(
	Tuple< TElement ... > & lhs, Tuple< TElement ... > & rhs
) noexcept(
	BooleanAnd< IsNothrowSwappable<TElement> ... >::value
) {

	lhs.swap(rhs);
}

template< Size I, typename ... TElement >
inline BR_CONSTEXPR_AFTER_CXX11 TupleElement< I, Tuple< TElement ... > > & get(
	Tuple< TElement ... > & tuple
) noexcept {
	return tuple.get< I >();
}

template< Size I, typename ... TElement >
inline BR_CONSTEXPR_AFTER_CXX11 TupleElement< I, Tuple< TElement ... > > const & get(
	Tuple< TElement ... > const & tuple
) noexcept {
	return tuple.get<I>();
}

template< Size I, typename ... TElement >
inline BR_CONSTEXPR_AFTER_CXX11 TupleElement< I, Tuple< TElement ... > > && get(
	Tuple< TElement ... > && tuple
) noexcept {
	return static_cast< TupleElement< I, Tuple< TElement ... > > && >(tuple.get< I >());
}

template< typename ... T >
inline BR_CONSTEXPR_AFTER_CXX11 Tuple< T & ... > tie(T & ... t) noexcept {
	return Tuple< T & ... >(t ...);
}

namespace Detail {
namespace Utility {

struct IgnoreTag {
	template< typename TT >
	IgnoreTag const & operator=(TT &&) const { return *this; }
};

} // namespace Utility
} // namespace Detail

constexpr static auto ignore = Detail::Utility::IgnoreTag();

namespace Detail {
namespace Utility {

template< typename T >
struct TypeMakeTupleReturnBasic : TypeWrapper<T> {};

template< typename T >
struct TypeMakeTupleReturnBasic< WrappedReference<T> > : TypeAddLValueReference<T> {};

template< typename T >
struct TypeMakeTupleReturn : TypeMakeTupleReturnBasic< Decay<T> > {};

template< typename T >
using MakeTupleReturn = TypeUnwrap< TypeMakeTupleReturn<T> >;

} // namespace Utility
} // namespace Detail

template< typename ... T >
inline BR_CONSTEXPR_AFTER_CXX11 Tuple< Detail::Utility::MakeTupleReturn< T > ... > make_tuple(T && ... t) {
	return Tuple< Detail::Utility::MakeTupleReturn< T > ... >(forward<T>(t) ...);
}

template< typename ... T >
inline BR_CONSTEXPR_AFTER_CXX11 Tuple< T && ... > forward_as_tuple(T && ... t) noexcept {
	return Tuple< T && ... >(forward<T>(t) ...);
}

namespace Detail {
namespace Utility {

template< Size I >
struct TupleCompare {
	template< typename T0, typename T1 >
	static BR_CONSTEXPR_AFTER_CXX11 bool equal(T0 const & t0, T1 const & t1) {
		return TupleCompare< I-1 >::equal(t0, t1) && get< I-1 >(t0) == get< I-1 >(t1);
	}

	template< typename T0, typename T1 >
	static BR_CONSTEXPR_AFTER_CXX11 bool less(T0 const & t0, T1 const & t1) {
		return TupleCompare< I-1 >::less(t0, t1) || (!TupleCompare< I-1 >::less(t1, t0) && get< I-1 >(t0) < get< I-1 >(t1));
	}
};

template<>
struct TupleCompare< 0 > {
	template< typename T0, typename T1 >
	static BR_CONSTEXPR_AFTER_CXX11 bool equal(T0 const &, T1 const &) {
		return true;
	}

	template< typename T0, typename T1 >
	static BR_CONSTEXPR_AFTER_CXX11 bool less(T0 const &, T1 const &) {
		return false;
	}
};

} // namespace Utility
} // namespace Detail

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 bool operator==(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return Detail::Utility::TupleCompare< sizeof...(T0) >::equal(t0, t1);
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 bool operator!=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return !(t0 == t1);
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 bool operator<(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return Detail::Utility::TupleCompare< sizeof...(T0) >::less(t0, t1);
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 bool operator>(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return t1 < t0;
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 bool operator<=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return !(t1 < t0);
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 bool operator>=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) {
	return !(t0 < t1);
}

namespace Detail {
namespace Utility {

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
	IsTupleLike< RemoveReference<TTuple1> >::value,
	TTuple1,
	TTuple ...
> {};

template< typename ... TTuple >
struct TypeTupleCatResult;

template< typename TTuple0, typename ... TTuple >
struct TypeTupleCatResult< TTuple0, TTuple ... > : TypeTupleCatResultBasic<
	Tuple<>,
	IsTupleLike< RemoveReference<TTuple0> >::value,
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
	Tuple< T ..., MapQualifier< TTuple, TupleElement< I, RemoveReference<TTuple> > > && ... >
> {};

template< typename ... T, Size ... I, typename TTuple0, typename TTuple1, typename ... TTuple >
struct TypeTupleCatResultReferenceBasic<
	Tuple< T ... >, TupleIndices< I ... >, TTuple0, TTuple1, TTuple ...
> : TypeTupleCatResultReferenceBasic<
	Tuple< T ..., MapQualifier< TTuple0, TupleElement< I, RemoveReference<TTuple0> > > && ... >,
	MakeTupleIndices< 0, TupleSize< RemoveReference<TTuple1> >::value >,
	TTuple1,
	TTuple ...
> {};

template< typename TTuple0, typename ... TTuple >
struct TypeTupleCatResultReference : TypeTupleCatResultReferenceBasic<
	Tuple<>,
	MakeTupleIndices< 0, TupleSize< RemoveReference<TTuple0> >::value >,
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
	BR_CONSTEXPR_AFTER_CXX11 TupleCatResultReference<
		Tuple< T ... > &&, TTuple &&
	> operator()(
		Tuple< T ... > head, TTuple && tail
	) {
		return forward_as_tuple(forward<T>(get<IHead>(head)) ..., get<ITail>(forward<TTuple>(tail)) ...);
	}

	template< typename TTuple0, typename TTuple1, typename ... TTuples >
	BR_CONSTEXPR_AFTER_CXX11 TupleCatResultReference<
		Tuple< T ... > &&, TTuple0 &&, TTuple1 &&, TTuples && ...
	> operator()(
		Tuple< T ... > head, TTuple0 && tail0, TTuple1 && tail1, TTuples && ... tails
	) {
		using NoRefTuple0 = RemoveReference<TTuple0>;
		return TupleCat<
			Tuple< T ..., MapQualifier< TTuple0, TupleElement< ITail, NoRefTuple0 > > && ... >,
			MakeTupleIndices< 0, sizeof...(T) + TupleSize< NoRefTuple0 >::value >,
			MakeTupleIndices< 0, TupleSize< RemoveReference<TTuple1> >::value >
		>()(
			forward_as_tuple(forward<T>(get<IHead>(head)) ..., get<ITail>(forward<TTuple0>(tail0)) ...),
			forward<TTuple1>(tail1),
			forward<TTuples>(tails) ...
		);
	}
};

} // namespace Utility
} // namespace Detail

inline BR_CONSTEXPR_AFTER_CXX11 Tuple<> tuple_cat() {
	return Tuple<>();
}

template< typename TTuple0, typename ... TTuples >
inline BR_CONSTEXPR_AFTER_CXX11 Detail::Utility::TupleCatResult< TTuple0, TTuples ... > tuple_cat(
	TTuple0 && tuple0, TTuples ... tuples
) {
	return Detail::Utility::TupleCat<
		Tuple<>,
		Detail::Utility::TupleIndices<>,
		Detail::Utility::MakeTupleIndices< 0, TupleSize< RemoveReference<TTuple0> >::value >
	>()(
		Tuple<>(), forward<TTuple0>(tuple0), forward<TTuples>(tuples) ...
	);
}

// template< typename ... T, typename TAllocator >
// struct IsUseAllocator< Tuple< T ... >, TAllocator > : BooleanTrue {};

} // namespace BR