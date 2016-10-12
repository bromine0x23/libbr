/**
 * @file
 * @brief class template Tuple
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/dummy_false.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_const_volatile.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_volatile.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/make_integral_sequence.hpp>
#include <libbr/type_operate/map_qualifier.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/types.hpp>
#include <libbr/type_traits/allocator_constructor_usage.hpp>
#include <libbr/type_traits/has_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_assignment.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_use_allocator.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/integral_constant.hpp>
#include <libbr/utility/integral_sequence.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/wrapped_reference.hpp>
#include <libbr/container/detail/tuple_forward.hpp>

namespace BR {

template< typename TFirst, typename TSecond >
class Pair;

template< typename ... TElement >
void swap(Tuple< TElement ... > & lhs, Tuple< TElement ... > & rhs) noexcept(noexcept(lhs.swap(rhs))) {
	lhs.swap(rhs);
}

template< Size I, typename ... Tn > constexpr auto get(Tuple< Tn ... >        & t) noexcept -> TupleElement< I, Tuple< Tn ... > >        & { return t.template get<I>(); }
template< Size I, typename ... Tn > constexpr auto get(Tuple< Tn ... > const  & t) noexcept -> TupleElement< I, Tuple< Tn ... > > const  & { return t.template get<I>(); }
template< Size I, typename ... Tn > constexpr auto get(Tuple< Tn ... >       && t) noexcept -> TupleElement< I, Tuple< Tn ... > >       && { return move(t.template get<I>()); }
template< Size I, typename ... Tn > constexpr auto get(Tuple< Tn ... > const && t) noexcept -> TupleElement< I, Tuple< Tn ... > > const && { return move(t.template get<I>()); }

template< typename T, typename ... Tn > constexpr auto get(Tuple< Tn ... >        & t) noexcept -> T        & { return t.template get<T>(); }
template< typename T, typename ... Tn > constexpr auto get(Tuple< Tn ... > const  & t) noexcept -> T const  & { return t.template get<T>(); }
template< typename T, typename ... Tn > constexpr auto get(Tuple< Tn ... >       && t) noexcept -> T       && { return move(t.template get<T>()); }
template< typename T, typename ... Tn > constexpr auto get(Tuple< Tn ... > const && t) noexcept -> T const && { return move(t.template get<T>()); }

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > & P) noexcept -> TupleElement< I, Pair< T0, T1 > > &;

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > const & P) noexcept -> TupleElement< I, Pair< T0, T1 > > const &;

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > && P) noexcept -> TupleElement< I, Pair< T0, T1 > > &&;

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > const && P) noexcept -> TupleElement< I, Pair< T0, T1 > > const &&;

template< typename ... Tn >
BR_CONSTEXPR_AFTER_CXX11 inline auto tie(Tn & ... t) noexcept -> Tuple< Tn & ... > {
	return Tuple< Tn & ... >(t ...);
}

template< typename ... T >
BR_CONSTEXPR_AFTER_CXX11 inline auto forward_as_tuple(T && ... t) noexcept -> Tuple< T && ... > {
	return Tuple< T && ... >(forward<T>(t)...);
}

template< typename T, typename TAllocator >
struct IsUseAllocator;

template< typename ... T, typename TAllocator >
struct IsUseAllocator< Tuple< T ... >, TAllocator > : public BooleanTrue {
};

template< typename T, typename TAllocator >
struct NotUseAllocator;

template< typename ... T, typename TAllocator >
struct NotUseAllocator< Tuple< T ... >, TAllocator > : public BooleanFalse {
};

namespace Detail {
namespace Container {

template< typename ... TTypes >
struct TupleTypes : public Types< TTypes ... > {};

} // namespace Container
} // namespace Detail

template< typename ... TTypes >
struct TupleSize< Tuple< TTypes ... > > : public IntegralConstant< Size, sizeof...(TTypes) > {};

template< typename ...TTypes >
struct TupleSize< Detail::Container::TupleTypes< TTypes ... > > : public IntegralConstant< Size, sizeof...(TTypes) > {};

template< Size I, typename ... TTypes >
struct TypeTupleElement< I, Tuple< TTypes ... > > : public TypeTupleElement< I, Detail::Container::TupleTypes< TTypes ... > > {};

template< Size I, typename ... TTypes >
struct TypeTupleElement< I, Detail::Container::TupleTypes< TTypes ... > > : public TypeWrapper< typename Detail::Container::TupleTypes< TTypes ... >::template Get<I> > {};

namespace Detail {
namespace Container {

template< typename T >
struct IsTupleLike : public BooleanFalse {};

template< typename T >
struct IsTupleLike< T const > : public IsTupleLike<T> {};

template< typename T >
struct IsTupleLike< T volatile > : public IsTupleLike<T> {};

template< typename T >
struct IsTupleLike< T const volatile > : public IsTupleLike<T> {};

template< typename ... TTypes >
struct IsTupleLike< Tuple< TTypes ... > > : public BooleanTrue {};

template< typename ... TTypes >
struct IsTupleLike< TupleTypes< TTypes ... > > : public BooleanTrue {};

template< typename T0, typename T1 >
struct IsTupleLike< Pair< T0, T1 > > : public BooleanTrue {};

template< Size I, typename T >
using MakeTupleType = Conditional< IsLValueReference<T>, AddLValueReference< BR::TupleElement< I, T > >, BR::TupleElement< I, T > >;

template< typename T, Size from, Size to, typename ... TTypes >
struct TypeMakeTupleTypes;

template< typename T, Size from, Size to, typename ... TTypes >
struct TypeMakeTupleTypes : public TypeRewrap< TypeMakeTupleTypes< T, from + 1, to, TTypes ..., MakeTupleType< from, RemoveReference<T> > > > {
	static_assert(from <= to, "MakeTupleTypes input error");
};

template< typename T, Size to, typename ... TTypes >
struct TypeMakeTupleTypes< T, to, to, TTypes ... > : public TypeWrapper< TupleTypes< TTypes ... > > {};

template< typename T, Size from = 0, Size to = TupleSize< RemoveReference<T> >::value >
using MakeTupleTypes = TypeUnwrap< TypeMakeTupleTypes< T, from, to > >;

template< typename TFrom, typename TTo >
struct IsTupleConvertibleBasic : public BooleanFalse {};

template< typename ... TFrom, typename ... TTo >
struct IsTupleConvertibleBasic< TupleTypes< TFrom ... >, TupleTypes< TTo ... > > : public BooleanAnd< IsConvertible< TFrom, TTo > ... > {};

template< typename TFrom, typename TTo >
struct IsTupleConvertibleApply : public BooleanAnd<
	BooleanConstant< (TupleSize< RemoveReference<TFrom> >::value == TupleSize<TTo>::value) >,
	IsTupleConvertibleBasic< MakeTupleTypes<TFrom>, MakeTupleTypes<TTo> >
> {};

template< typename TFrom, typename TTo >
struct IsTupleConvertible : public BooleanAnd< IsTupleLike< RemoveReference<TFrom> >, IsTupleLike<TTo>, IsTupleConvertibleApply< TFrom, TTo > > {};

template< typename TFrom, typename TTo >
using NotTupleConvertible = BooleanNot< IsTupleConvertible< TFrom, TTo > >;

template< typename T0, typename T1 >
struct IsTupleConstructibleBasic : public BooleanFalse {};

template< typename ... TElement, typename ... TValue >
struct IsTupleConstructibleBasic< TupleTypes< TElement ... >, TupleTypes< TValue ... > > : public BooleanAnd< IsConstructible< TElement, TValue > ... > {};

template< typename TTuple, typename TArgument >
struct IsTupleConstructibleApply : public BooleanAnd<
	BooleanConstant< (TupleSize<TTuple>::value == TupleSize< RemoveReference<TArgument> >::value) >,
	IsTupleConstructibleBasic< MakeTupleTypes<TTuple>, MakeTupleTypes<TArgument> > > {
};

template< typename TTuple, typename TArgument >
using IsTupleConstructible = BooleanAnd< IsTupleLike<TTuple>, IsTupleLike< RemoveReference<TArgument> >, IsTupleConstructibleApply< TTuple, TArgument > >;

template< typename TFrom, typename TTo >
using NotTupleConstructible = BooleanNot< IsTupleConstructible< TFrom, TTo > >;

template< typename T0, typename T1 >
struct IsTupleAssignableBasic : public BooleanFalse {};

template< typename ... TElement, typename ... TValue >
struct IsTupleAssignableBasic< TupleTypes< TElement ... >, TupleTypes< TValue ... > > : public BooleanAnd< IsAssignable< TElement &, TValue > ... > {};

template< typename TTuple, typename TArgument >
struct IsTupleAssignableApply : public BooleanAnd<
	BooleanConstant< (TupleSize<TTuple>{}() == TupleSize< RemoveReference<TArgument> >{}()) >,
	IsTupleAssignableBasic< MakeTupleTypes<TTuple>, MakeTupleTypes<TArgument> >
> {};

template< typename TTuple, typename TArgument >
using IsTupleAssignable = BooleanAnd< IsTupleLike<TTuple>, IsTupleLike< RemoveReference<TArgument> >, IsTupleAssignableApply< TTuple, TArgument > >;

template< typename ... T >
struct IsAllDefaultConstructible;

template< typename ... T >
struct IsAllDefaultConstructible< TupleTypes< T ... > > : public BooleanAnd< HasDefaultConstructor<T> ... > {};

template< Size I, typename TElement, bool = BooleanAnd< IsEmpty<TElement>, NotFinal<TElement> >{} >
class TupleLeaf;

template< Size I, typename T, bool B >
inline void swap(TupleLeaf< I, T, B > & x, TupleLeaf< I, T, B > & y) noexcept(noexcept(swap(x.get(), y.get()))) {
	using BR::swap;
	swap(x.get(), y.get());
}

template< Size I, typename TElement >
class TupleLeaf< I, TElement, false > {
public:
	BR_CONSTEXPR_AFTER_CXX11 TupleLeaf() noexcept(HasNothrowDefaultConstructor<TElement>{}) : m_element() {
		m_default_construct_check();
	}

	TupleLeaf(TupleLeaf const & leaf) = default;

	TupleLeaf(TupleLeaf && leaf) = default;

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >, TAllocator const & /*allocator*/) : m_element() {
		m_default_construct_check();
	}

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >, TAllocator const & allocator) : m_element(allocator_argument_tag, allocator) {
		m_default_construct_check();
	}

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >, TAllocator const & allocator) : m_element(allocator) {
		m_default_construct_check();
	}

	template< typename TValue, typename = EnableIf< BooleanAnd< NotSame< Decay<TValue>, TupleLeaf >, IsConstructible< TElement, TValue > > > >
	explicit BR_CONSTEXPR_AFTER_CXX11 TupleLeaf(TValue && value) noexcept(IsNothrowConstructible< TElement, TValue >{}) : m_element(forward<TValue>(value)) {
		m_construct_check_rvalue<TValue>();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >, TAllocator const & /*allocator*/, TValue && value) : m_element(forward<TValue>(value)) {
		m_construct_check_rvalue_with_allocator<TValue>();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >, TAllocator const & allocator, TValue && value) : m_element(allocator_argument_tag, allocator, forward<TValue>(value)) {
		m_construct_check_rvalue_with_allocator<TValue>();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >, TAllocator const & allocator, TValue && value) : m_element(forward<TValue>(value), allocator) {
		m_construct_check_rvalue_with_allocator<TValue>();
	}

	template< typename TValue >
	auto operator=(TValue && value) noexcept(IsNothrowAssignable< AddLValueReference<TElement>, TValue >()) -> TupleLeaf & {
		m_element = forward<TValue>(value);
		return *this;
	}

	auto swap(TupleLeaf & leaf) noexcept(IsNothrowSwappable<TupleLeaf>{}) -> int {
		using BR::swap;
		swap(*this, leaf);
		return 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> TElement        & { return m_element; }
	constexpr                auto get() const  & noexcept -> TElement const  & { return m_element; }
	BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TElement       && { return static_cast< TElement && >(m_element); }
	constexpr                auto get() const && noexcept -> TElement const && { return static_cast< TElement const && >(m_element); }

private:
	auto operator=(TupleLeaf const & leaf) -> TupleLeaf & = delete;

	void m_default_construct_check() const {
		static_assert(NotReference<TElement>{}, "Attempted to default construct a reference element in a Tuple");
	}

	template< typename TValue >
	void m_construct_check_rvalue() const {
		static_assert(
			BooleanOr<
				NotReference<TElement>,
				BooleanAnd<
					IsLValueReference<TElement>,
					BooleanOr<
						IsLValueReference<TValue>,
						IsSame< RemoveReference<TValue>, WrappedReference< RemoveReference<TElement> > >
					>
				>,
				BooleanAnd< IsRValueReference<TElement>, NotLValueReference<TValue> >
			>{},
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

	template< typename TValue >
	void m_construct_check_rvalue_with_allocator() const {
		static_assert(
			BooleanOr<
				NotReference<TElement>,
				BooleanAnd<
					IsLValueReference<TElement>,
					BooleanOr<
						IsLValueReference<TValue>,
						IsSame< RemoveReference<TValue>, WrappedReference< RemoveReference<TElement> > >
					>
				>
			>{},
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

private:
	TElement m_element;
}; // class TupleLeaf< I, TElement, false >

template< Size I, typename TElement >
class TupleLeaf< I, TElement, true > : private TElement {
public:
	BR_CONSTEXPR_AFTER_CXX11 TupleLeaf() noexcept(HasNothrowDefaultConstructor<TElement>{}) {
	}

	TupleLeaf(TupleLeaf const & leaf) = default;

	TupleLeaf(TupleLeaf && leaf) = default;

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >, TAllocator const & /*allocator*/) {
	}

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >, TAllocator const & allocator) : TElement(allocator_argument_tag, allocator) {
	}

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >, TAllocator const & allocator) : TElement(allocator) {
	}

	template< typename TValue, typename = EnableIf< BooleanAnd< NotSame< Decay<TValue>, TupleLeaf >, IsConstructible< TElement, TValue > > > >
	explicit BR_CONSTEXPR_AFTER_CXX11 TupleLeaf(TValue && value) noexcept(IsNothrowConstructible< TElement, TValue >{}) : TElement(forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used >, TAllocator const & _allocator, TValue && value) : TElement(forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag >, TAllocator const & allocator, TValue && value) : TElement(allocator_argument_tag, allocator, forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag >, TAllocator const & allocator, TValue && value) : TElement(forward<TValue>(value), allocator) {
	}

	template< typename TValue >
	auto operator=(TValue && value) noexcept(IsNothrowAssignable< AddLValueReference<TElement>, TValue >{}) -> TupleLeaf & {
		TElement::operator=(forward<TValue>(value));
		return *this;
	}

	auto swap(TupleLeaf & leaf) noexcept(IsNothrowSwappable<TupleLeaf>()) -> int {
		using BR::swap;
		swap(*this, leaf);
		return 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> TElement        & { return static_cast< TElement        & >(*this); }
	constexpr                auto get() const  & noexcept -> TElement const  & { return static_cast< TElement const  & >(*this); }
	BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TElement       && { return static_cast< TElement       && >(*this); }
	constexpr                auto get() const && noexcept -> TElement const && { return static_cast< TElement const && >(*this); }

private:
	auto operator=(TupleLeaf const & leaf) -> TupleLeaf & = delete;
}; // class TupleLeaf< I, TElement, true >

template< typename ... TTypes >
void swallow(TTypes &&...) noexcept {
}

template< typename T, typename ... TTypes >
struct FindTupleLeafChecker;

template< typename T >
struct FindTupleLeafChecker< T > : BooleanTrue {};

template< typename T, typename ... TTails >
struct FindTupleLeafChecker< T, T, TTails... > : BooleanFalse {};

template< typename T, typename THead, typename ... TTails >
struct FindTupleLeafChecker< T, THead, TTails... > : public BooleanRewrap< FindTupleLeafChecker< T, TTails... > > {};

template< typename T, Size I, typename ... TTypes >
struct TypeFindTupleLeafBasic;

template< typename T, Size I >
struct TypeFindTupleLeafBasic< T, I > {
	static_assert(DummyFalse<T>{}, "Type not found in type list.");
};

template< typename T, Size I, typename ... TTails >
struct TypeFindTupleLeafBasic< T, I, T, TTails... > : public TypeWrapper< TupleLeaf< I, T > > {
	static_assert(FindTupleLeafChecker< T, TTails... >{}, "Type can only occur once in type list.");
};

template< typename T, Size I, typename THead, typename ... TTails >
struct TypeFindTupleLeafBasic< T, I, THead, TTails... > : public TypeRewrap< TypeFindTupleLeafBasic< T, I + 1, TTails... > > {
};

template< typename T, typename ... TTypes >
using FindTupleLeaf = TypeUnwrap< TypeFindTupleLeafBasic< T, 0, TTypes... > >;

template< typename I, typename ... TTypes >
class TupleImp;

template< Size ... I, typename ... T >
class TupleImp< IndexSequence< I ... >, T ... > : public TupleLeaf< I, T > ... {
public:
	BR_CONSTEXPR_AFTER_CXX11 TupleImp() noexcept(BooleanAnd< HasNothrowDefaultConstructor<T> ... >{}) {
	}

	TupleImp(TupleImp const & tuple) = default;

	TupleImp(TupleImp && tuple) = default;

	template< Size ... IHead, typename ... THead, Size ... ITail, typename ... TTail, typename ... TValue >
	BR_CONSTEXPR_AFTER_CXX11 explicit TupleImp(
		IndexSequence< IHead... > /*ih*/, TupleTypes< THead... > /*th*/,
		IndexSequence< ITail... > /*it*/, TupleTypes< TTail... > /*tt*/,
		TValue && ... value
	) noexcept(
		BooleanAnd< IsNothrowConstructible< THead, TValue >..., HasNothrowDefaultConstructor<TTail>... >{}
	) : TupleLeaf< IHead, THead >(forward<TValue>(value))..., TupleLeaf< ITail, TTail >()... {
	}

	template< typename TAllocator, Size ... IHead, typename ... THead, Size ... ITail, typename ... TTail, typename ... TValue >
	explicit TupleImp(
		AllocatorArgumentTag, TAllocator const & allocator,
		IndexSequence< IHead ... > /*ih*/, TupleTypes< THead ... > /*th*/,
		IndexSequence< ITail ... > /*it*/, TupleTypes< TTail ... > /*tt*/,
		TValue && ... value
	) : TupleLeaf< IHead, THead >(AllocatorConstructorUsage< THead, TAllocator, TValue >(), allocator, forward<TValue>(value))..., TupleLeaf< ITail, TTail >(AllocatorConstructorUsage< TTail, TAllocator >(), allocator)... {
	}

	template< typename TTuple, typename = EnableIf< IsTupleConstructible< Tuple< T ... >, TTuple > > >
	BR_CONSTEXPR_AFTER_CXX11 TupleImp(TTuple && tuple) noexcept(
		BooleanAnd< IsNothrowConstructible< T, TupleElement< I, MakeTupleTypes<TTuple> > > ... >{}
	) : TupleLeaf< I, T >(forward< TupleElement< I, MakeTupleTypes<TTuple> > >(tuple.template get<I>())) ... {
	}

	template< typename TAllocator, typename TTuple, typename = EnableIf< IsTupleConstructible< Tuple< T ... >, TTuple > > >
	TupleImp(
		AllocatorArgumentTag, TAllocator const & allocator, TTuple && tuple
	) : TupleLeaf< I, T >(AllocatorConstructorUsage< T, TAllocator, TupleElement< I, MakeTupleTypes<TTuple> > >{}, allocator, forward< TupleElement< I, MakeTupleTypes<TTuple> > >(tuple.template get<I>())) ...  {
	}

	template< typename TTuple, typename = EnableIf< IsTupleAssignable< Tuple< T ... >, TTuple > > >
	auto operator=(TTuple && tuple) noexcept(
		BooleanAnd< IsNothrowAssignable< T &, TupleElement< I, MakeTupleTypes<TTuple> > > ... >{}
	) -> TupleImp & {
		swallow(TupleLeaf< I, T >::operator=(forward< TupleElement< I, MakeTupleTypes<TTuple> > >(tuple.template get<I>())) ...);
		return *this;
	}

	auto operator=(TupleImp const & tuple) noexcept(BooleanAnd< HasNothrowCopyAssignment<T> ... >{}) -> TupleImp & {
		swallow(TupleLeaf< I, T >::operator=(static_cast< TupleLeaf< I, T > const & >(tuple).get()) ...);
		return *this;
	}

	auto operator=(TupleImp && tuple) noexcept(BooleanAnd< HasNothrowMoveAssignment<T> ... >{}) -> TupleImp &  {
		swallow(TupleLeaf< I, T >::operator=(forward<T>(static_cast< TupleLeaf< I, T > & >(tuple).get())) ...);
		return *this;
	}

	void swap(TupleImp & tuple) noexcept(BooleanAnd< IsNothrowSwappable<T> ... >{}) {
		swallow(TupleLeaf< I, T >::swap(static_cast< TupleLeaf< I, T > & >(tuple)) ...);
	}

	template< Size P > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> TupleElement< P, TupleTypes< T ... > >        & { return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > >        & >(*this).get(); }
	template< Size P > constexpr                auto get() const  & noexcept -> TupleElement< P, TupleTypes< T ... > > const  & { return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > > const  & >(*this).get(); }
	template< Size P > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TupleElement< P, TupleTypes< T ... > >       && { return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > >       && >(*this).get(); }
	template< Size P > constexpr                auto get() const && noexcept -> TupleElement< P, TupleTypes< T ... > > const && { return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > > const && >(*this).get(); }

	template< typename TI > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> TI        & { return static_cast< FindTupleLeaf< TI, T... >        & >(*this).get(); }
	template< typename TI > constexpr                auto get() const  & noexcept -> TI const  & { return static_cast< FindTupleLeaf< TI, T... > const  & >(*this).get(); }
	template< typename TI > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TI       && { return static_cast< FindTupleLeaf< TI, T... >       && >(*this).get(); }
	template< typename TI > constexpr                auto get() const && noexcept -> TI const && { return static_cast< FindTupleLeaf< TI, T... > const && >(*this).get(); }

}; // class TupleImp< IndexSequence< I ... >, T ... >

} // namespace Container
} // namespace Detail

template < typename ... TElement >
class Tuple {
private:
	using Imp = Detail::Container::TupleImp< MakeIndexSequence< 0, sizeof...(TElement) >, TElement ... >;

public:
	/**
	 * default constructor
	 */
	template< bool dummy = true, typename = EnableIf< BooleanAnd< BooleanConstant<dummy>, HasDefaultConstructor<TElement> ... > > >
	BR_CONSTEXPR_AFTER_CXX11 Tuple() noexcept(BooleanAnd< HasNothrowDefaultConstructor<TElement> ... >{}) {
	}

	/**
	 *	copy constructor
	 */
	Tuple(Tuple const & tuple) = default;

	/**
	 *	move constructor
	 */
	Tuple(Tuple && tuple) = default;

	/**
	 *	initialization conversion constructor
	 */
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(TElement const & ... elements) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<TElement> ... >{}
	) : m_imp(MakeIndexSequence< 0, sizeof...(TElement) >(), Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TElement) >(), MakeIndexSequence< 0, 0 >(), Detail::Container::MakeTupleTypes< Tuple, 0, 0 >(), elements ...) {
	}

	/**
	 *	implicit initialization conversion constructor
	 */
	template<
		typename ... TValue,
		EnableIf<
			BooleanAnd<
				BooleanConstant< (sizeof...(TValue) <= sizeof...(TElement)) >,
				Detail::Container::IsTupleConvertible< Tuple< TValue ... >, Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) > >,
				Detail::Container::IsAllDefaultConstructible< Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) > >
			>,
			bool
		> = false
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(TValue && ... value) noexcept(
		IsNothrowConstructible<
			Imp,
			MakeIndexSequence< 0, sizeof...(TValue) >,
			Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >,
			MakeIndexSequence< sizeof...(TValue), sizeof...(TElement) >,
			Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >,
			TValue ...
		>{}
	) : m_imp(
		MakeIndexSequence< 0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		MakeIndexSequence< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward<TValue>(value) ...
	) {
	}

	template<
		typename ... TValue,
		EnableIf<
			BooleanAnd<
				BooleanConstant< (sizeof...(TValue) <= sizeof...(TElement)) >,
				Detail::Container::IsTupleConstructible< Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >, Tuple< TValue ... > >,
				Detail::Container::NotTupleConvertible< Tuple< TValue ... >, Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) > >,
				Detail::Container::IsAllDefaultConstructible< Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) > >
			>,
			bool
		> = false
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(TValue && ... value) noexcept(
		IsNothrowConstructible<
			Imp,
			MakeIndexSequence< 0, sizeof...(TValue) >,
			Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >,
			MakeIndexSequence< sizeof...(TValue), sizeof...(TElement) >,
			Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >,
			TValue ...
		>{}
	) : m_imp(
		MakeIndexSequence< 0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		MakeIndexSequence< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward<TValue>(value) ...
	) {
	}

	/**
	 *	implicit move conversion constructor
	 */
	template<
		typename TTuple,
		EnableIf< Detail::Container::IsTupleConvertible< TTuple, Tuple >, bool > = false
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(TTuple && tuple) noexcept(
		IsNothrowConstructible< Imp, TTuple >()
	) : m_imp(forward<TTuple>(tuple)) {
	}

	template<
		typename TTuple,
		EnableIf<
			BooleanAnd<
				Detail::Container::IsTupleConstructible< Tuple, TTuple >,
				Detail::Container::NotTupleConvertible< TTuple, Tuple >
			>,
			bool
		> = false
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(TTuple && tuple) noexcept(
		IsNothrowConstructible< Imp, TTuple >()
	) : m_imp(forward<TTuple>(tuple)) {
	}

	/**
	 *	allocator version initialization constructor
	 */
	template< typename TAllocator >
	Tuple(AllocatorArgumentTag, TAllocator const & allocator, TElement const & ... element) : m_imp(
		allocator_argument_tag,
		allocator,
		MakeIndexSequence< 0, sizeof...(TElement) >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TElement) >(),
		MakeIndexSequence< 0, 0 >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, 0 >(),
		element ...
	) {
	}

	/**
	 *	allocator version implicit initialization conversion constructor
	 */
	template<
		typename TAllocator,
		typename ... TValue,
		EnableIf<
			BooleanAnd<
				BooleanConstant< sizeof...(TValue) <= sizeof...(TElement) >,
				Detail::Container::IsTupleConstructible< Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >, Tuple< TValue ... > >,
				Detail::Container::IsAllDefaultConstructible< Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) > >
			>,
			bool
		> = false
	>
	Tuple(AllocatorArgumentTag, TAllocator const & allocator, TValue && ... value) : m_imp(
		allocator_argument_tag,
		allocator,
		MakeIndexSequence<  0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		MakeIndexSequence< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward<TValue>(value) ...
	) {
	}

	/**
	 * allocator version move conversion constructor
	 */
	template< typename TAllocator, typename TTuple, typename = EnableIf< Detail::Container::IsTupleConvertible< TTuple, Tuple > > >
	Tuple(AllocatorArgumentTag, TAllocator const & allocator, TTuple && tuple) : m_imp(
		allocator_argument_tag, allocator, forward< TTuple >(tuple)
	) {
	}

	/**
	 * implicit move conversion assignment
	 */
	template< typename TTuple, typename = EnableIf< Detail::Container::IsTupleAssignable< Tuple, TTuple > > >
	auto operator=(TTuple && tuple) noexcept(IsNothrowAssignable< Imp &, TTuple >{}) -> Tuple & {
		m_imp.operator=(forward<TTuple>(tuple));
		return *this;
	}

	/**
	 * swap
	 */
	void swap(Tuple & tuple) noexcept(BooleanAnd< IsNothrowSwappable<TElement> ... >{}) {
		m_imp.swap(tuple.m_imp);
	}

	/**
	 *  取第 \em I 个元素
	 */
	///@{
	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> TupleElement< I, Tuple >        & { return m_imp.template get<I>(); }
	template< Size I > constexpr                auto get() const  & noexcept -> TupleElement< I, Tuple > const  & { return m_imp.template get<I>(); }
	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TupleElement< I, Tuple >       && { return move(m_imp.template get<I>()); }
	template< Size I > constexpr                auto get() const && noexcept -> TupleElement< I, Tuple > const && { return move(m_imp.template get<I>()); }
	///@}

	/**
	 *  取类型 \em T 对应的元素
	 */
	///@{
	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> T        & { return m_imp.template get<T>(); }
	template< typename T > constexpr                auto get() const  & noexcept -> T const  & { return m_imp.template get<T>(); }
	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> T       && { return move(m_imp.template get<T>()); }
	template< typename T > constexpr                auto get() const && noexcept -> T const && { return move(m_imp.template get<T>()); }
	///@}

private:
	Imp m_imp;

}; // class Tuple< TElement ... >

template <>
class Tuple<> {
public:
	constexpr Tuple() noexcept = default;

	template< typename TAllocator >
	constexpr Tuple(AllocatorArgumentTag, TAllocator const &) noexcept {
	}

	template< typename TAllocator >
	constexpr Tuple(AllocatorArgumentTag, TAllocator const &, Tuple const &) noexcept {
	}

	void swap(Tuple & tuple) noexcept {
	}
}; // class Tuple<>

namespace Detail {
namespace Container {

template< typename T >
struct TypeMakeTupleReturnBasic : public TypeWrapper<T> {};

template< typename T >
struct TypeMakeTupleReturnBasic< WrappedReference<T> > : public TypeAddLValueReference<T> {};

template< typename T >
struct TypeMakeTupleReturn : public TypeMakeTupleReturnBasic< Decay<T> > {};

template< typename T >
using MakeTupleReturn = TypeUnwrap< TypeMakeTupleReturn<T> >;

} // namespace Container
} // namespace Detail

template< typename ... T >
BR_CONSTEXPR_AFTER_CXX11 inline auto make_tuple(T && ... t) -> Tuple< Detail::Container::MakeTupleReturn<T> ... > {
	return Tuple< Detail::Container::MakeTupleReturn<T> ... >(forward<T>(t) ...);
}

namespace Detail {
namespace Container {

struct IgnoreTag {
	template< typename TT >
	auto operator=(TT &&) const -> IgnoreTag const & {
		return *this;
	}
};

} // namespace Container
} // namespace Detail

constexpr auto ignore_tag = Detail::Container::IgnoreTag();

namespace Detail {
namespace Container {

template< Size I >
struct TupleCompare {
	template< typename T0, typename T1 >
	static BR_CONSTEXPR_AFTER_CXX11 auto equal(T0 const & t0, T1 const & t1) -> bool {
		return TupleCompare< I-1 >::equal(t0, t1) && get< I-1 >(t0) == get< I-1 >(t1);
	}

	template< typename T0, typename T1 >
	static BR_CONSTEXPR_AFTER_CXX11 auto less(T0 const & t0, T1 const & t1) -> bool {
		return TupleCompare< I-1 >::less(t0, t1) || (!TupleCompare< I-1 >::less(t1, t0) && get< I-1 >(t0) < get< I-1 >(t1));
	}
};

template<>
struct TupleCompare<0> {
	template< typename T0, typename T1 >
	static BR_CONSTEXPR_AFTER_CXX11 auto equal(T0 const &, T1 const &) -> bool {
		return true;
	}

	template< typename T0, typename T1 >
	static BR_CONSTEXPR_AFTER_CXX11 auto less(T0 const &, T1 const &) -> bool {
		return false;
	}
};

} // namespace Container
} // namespace Detail

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 auto operator==(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) -> bool {
	return Detail::Container::TupleCompare< sizeof...(T0) >::equal(t0, t1);
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 auto operator!=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) -> bool {
	return !(t0 == t1);
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 auto operator<(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) -> bool {
	return Detail::Container::TupleCompare< sizeof...(T0) >::less(t0, t1);
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 auto operator>(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) -> bool {
	return t1 < t0;
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 auto operator<=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) -> bool {
	return !(t1 < t0);
}

template< typename ... T0, typename ... T1 >
BR_CONSTEXPR_AFTER_CXX11 auto operator>=(Tuple< T0 ... > const & t0, Tuple< T1 ... > const & t1) -> bool {
	return !(t0 < t1);
}

namespace Detail {
namespace Container {

template< typename T0, typename T1 >
struct TypeTupleCatType;

template< typename T0, typename T1 >
using TupleCatType = TypeUnwrap< TypeTupleCatType< T0, T1 > >;

template< typename ... T0, typename ... T1 >
struct TypeTupleCatType< Tuple< T0 ... >, TupleTypes< T1 ... > > : public TypeWrapper< Tuple< T0 ..., T1 ...  > > {
};

template< typename TResult, bool is_tuple_like, typename ... TTuple >
struct TypeTupleCatResultBasic {
};

template< typename ... T, typename TTuple >
struct TypeTupleCatResultBasic< Tuple< T ... >, true, TTuple > : public TypeTupleCatType< Tuple< T ... >, MakeTupleTypes< RemoveReference< TTuple > > > {
};

template< typename ... T, typename TTuple0, typename TTuple1, typename ... TTuple >
struct TypeTupleCatResultBasic< Tuple< T ... >, true, TTuple0, TTuple1, TTuple ... > : public TypeTupleCatResultBasic< TupleCatType< Tuple< T ... >, MakeTupleTypes< RemoveReference< TTuple0 > > >, IsTupleLike< RemoveReference<TTuple1> >::value, TTuple1, TTuple ... > {
};

template< typename ... TTuple >
struct TypeTupleCatResult;

template< typename TTuple0, typename ... TTuple >
struct TypeTupleCatResult< TTuple0, TTuple ... > : public TypeTupleCatResultBasic< Tuple<>, IsTupleLike< RemoveReference<TTuple0> >::value, TTuple0, TTuple ... > {
};

template<>
struct TypeTupleCatResult<> : public TypeWrapper< Tuple<> > {};

template< typename ... TTuple >
using TupleCatResult = TypeUnwrap< TypeTupleCatResult< TTuple ... > >;

template< typename TResult, typename TIndices, typename TTuple0, typename ... TTuple >
struct TypeTupleCatResultReferenceBasic;

template< typename ... T, Size ... I, typename TTuple >
struct TypeTupleCatResultReferenceBasic< Tuple< T ... >, IndexSequence< I ... >, TTuple > : public TypeWrapper<
	Tuple< T ..., MapQualifier< TTuple, TupleElement< I, RemoveReference<TTuple> > > && ... >
> {
};

template< typename ... T, Size ... I, typename TTuple0, typename TTuple1, typename ... TTuple >
struct TypeTupleCatResultReferenceBasic< Tuple< T ... >, IndexSequence< I ... >, TTuple0, TTuple1, TTuple ... > : public TypeTupleCatResultReferenceBasic<
	Tuple< T ..., MapQualifier< TTuple0, TupleElement< I, RemoveReference<TTuple0> > > && ... >, MakeIndexSequence< 0, TupleSize< RemoveReference<TTuple1> >::value >, TTuple1, TTuple ...
> {
};

template< typename TTuple0, typename ... TTuple >
struct TypeTupleCatResultReference : public TypeTupleCatResultReferenceBasic< Tuple<>, MakeIndexSequence< 0, TupleSize< RemoveReference<TTuple0> >::value >, TTuple0, TTuple ... > {
};

template< typename ... TTuple >
using TupleCatResultReference = TypeUnwrap< TypeTupleCatResultReference< TTuple ... > >;

template< typename TResult, typename TIHead, typename TITail >
struct TupleCat;

template< typename ... T, Size ... IHead, Size ... ITail >
struct TupleCat< Tuple< T ... >, IndexSequence< IHead ... >, IndexSequence< ITail ... > > {
	template< typename TTuple >
	BR_CONSTEXPR_AFTER_CXX11 auto operator()(Tuple< T ... > head, TTuple && tail) -> TupleCatResultReference< Tuple< T ... > &&, TTuple && > {
		return forward_as_tuple(forward<T>(get<IHead>(head)) ..., get<ITail>(forward<TTuple>(tail)) ...);
	}

	template< typename TTuple0, typename TTuple1, typename ... TTuples >
	BR_CONSTEXPR_AFTER_CXX11 auto operator()(Tuple< T ... > head, TTuple0 && tail0, TTuple1 && tail1, TTuples && ... tails) -> TupleCatResultReference< Tuple< T ... > &&, TTuple0 &&, TTuple1 &&, TTuples && ... > {
		using NoRefTuple0 = RemoveReference<TTuple0>;
		return TupleCat<
			Tuple< T ..., MapQualifier< TTuple0, TupleElement< ITail, NoRefTuple0 > > && ... >, MakeIndexSequence< 0, sizeof...(T) + TupleSize< NoRefTuple0 >::value >, MakeIndexSequence< 0, TupleSize< RemoveReference<TTuple1> >::value >
		>()(
			forward_as_tuple(forward<T>(get<IHead>(head)) ..., get<ITail>(forward<TTuple0>(tail0)) ...), forward<TTuple1>(tail1), forward<TTuples>(tails) ...
		);
	}
};

} // namespace Container
} // namespace Detail

BR_CONSTEXPR_AFTER_CXX11 inline auto tuple_cat() -> Tuple<> {
	return Tuple<>();
}

template< typename TTuple0, typename ... TTuples >
BR_CONSTEXPR_AFTER_CXX11 inline auto tuple_cat(TTuple0 && tuple0, TTuples ... tuples) -> Detail::Container::TupleCatResult< TTuple0, TTuples ... > {
	return Detail::Container::TupleCat<
		Tuple<>, IndexSequence<>, MakeIndexSequence< 0, TupleSize< RemoveReference<TTuple0> >::value >
	>()(
		Tuple<>(), forward<TTuple0>(tuple0), forward<TTuples>(tuples) ...
	);
}

} // namespace BR