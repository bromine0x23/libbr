/**
 * @file
 * @brief class template Tuple
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_const_volatile.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_volatile.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/map_qualifier.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/types.hpp>
#include <libbr/type_traits/allocator_constructor_usage.hpp>
#include <libbr/type_traits/has_default_constructor.hpp>
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
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_use_allocator.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/integer_constant.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/wrapped_reference.hpp>

namespace BR {

template< typename ... types >
class Tuple;

template< typename T >
struct TupleSize;

template< Size I, typename T >
struct TypeTupleElement;

template< Size I, typename T >
using TupleElement = TypeUnwrap< TypeTupleElement< I, T > >;

template< Size I, typename ... Tn >
BR_CONSTEXPR_AFTER_CXX11 auto get(Tuple< Tn ... > & tuple) noexcept -> TupleElement< I, Tuple< Tn ... > > &;

template< Size I, typename ... Tn >
BR_CONSTEXPR_AFTER_CXX11 auto get(Tuple< Tn ... > const & tuple) noexcept -> TupleElement< I, Tuple< Tn ... > > const &;

template< Size I, typename ... Tn >
BR_CONSTEXPR_AFTER_CXX11 auto get(Tuple< Tn ... > && tuple) noexcept -> TupleElement< I, Tuple< Tn ... > > &&;

template< typename ... T >
BR_CONSTEXPR_AFTER_CXX11 auto tie(T & ... t) noexcept -> Tuple< T & ... >;

struct IgnoreTag {
	template< typename TT >
	auto operator=(TT && _dummy) const -> IgnoreTag const & {
		return *this;
	}
};

constexpr auto ignore = IgnoreTag();

template< typename ... T >
inline BR_CONSTEXPR_AFTER_CXX11 auto forward_as_tuple(T && ... t) noexcept -> Tuple< T && ... > {
	return Tuple< T && ... >(forward<T>(t) ...);
}

#if defined(BR_CXX14)

template< typename T >
constexpr auto tuple_size = integer_constant< TupleSize<T> >;

#endif // defined(BR_CXX14)

namespace Detail {
namespace Container {

template< Size ... indices >
struct TupleIndices : Integers< Size, indices ... > {
};

template< typename ... TTypes >
struct TupleTypes : Types< TTypes ... > {
};

template< typename T >
struct TupleSize;

template< typename ... TTypes >
struct TupleSize< Tuple< TTypes ... > > : IntegerConstant< Size, sizeof...(TTypes) > {
};

template< typename T >
struct TupleSize< T const > : TupleSize<T> {
};

template< typename T >
struct TupleSize< T volatile > : TupleSize<T> {
};

template< typename T >
struct TupleSize< T const volatile > : TupleSize<T> {
};

template< typename ...TTypes >
struct TupleSize< TupleTypes< TTypes ... > > : IntegerConstant< Size, sizeof...(TTypes) > {
};

template< Size I, typename T >
struct TypeTupleElement;

template< Size I, typename ... TTypes >
struct TypeTupleElement< I, Tuple< TTypes ... > > : TypeTupleElement< I, TupleTypes< TTypes ... > > {
};

template< Size I, typename T >
struct TypeTupleElement< I, T const > : TypeAddConst< TupleElement< I, T > > {
};

template< Size I, typename T >
struct TypeTupleElement< I, T volatile > : TypeAddVolatile< TupleElement< I, T > > {
};

template< Size I, typename T >
struct TypeTupleElement< I, T const volatile > : TypeAddConstVolatile< TupleElement< I, T > > {
};

template< Size I, typename ... TTypes >
struct TypeTupleElement< I, TupleTypes< TTypes ... > > : TypeWrapper< typename TupleTypes< TTypes ... >::template Get<I> > {
};

template< Size I, typename T >
using TupleElement = TypeUnwrap< TypeTupleElement< I, T > >;

template< typename T >
struct IsTupleLike : BooleanFalse {
};

template< typename T >
struct IsTupleLike< T const > : IsTupleLike<T> {
};

template< typename T >
struct IsTupleLike< T volatile > : IsTupleLike<T> {
};

template< typename T >
struct IsTupleLike< T const volatile > : IsTupleLike<T> {
};

template< typename ... TTypes >
struct IsTupleLike< Tuple< TTypes ... > > : BooleanTrue {
};

template< typename ... TTypes >
struct IsTupleLike< TupleTypes< TTypes ... > > : BooleanTrue {
};

template< Size from, Size to, Size ... indices >
struct TypeMakeTupleIndices;

template< Size from, Size to, Size ... indices >
struct TypeMakeTupleIndices : TypeMakeTupleIndices< from + 1, to, indices ..., from > {
};

template< Size to, Size ... indices >
struct TypeMakeTupleIndices< to, to, indices ... > : TypeWrapper< TupleIndices< indices ... > > {
};

template< Size from, Size to >
using MakeTupleIndices = TypeUnwrap< TypeMakeTupleIndices< from, to > >;

template< Size I, typename T >
using MakeTupleType = Conditional< IsLValueReference<T>, AddLValueReference< TupleElement< I, T > >, TupleElement< I, T > >;

template< typename T, Size from, Size to, typename ... TTypes >
struct TypeMakeTupleTypes;

template< typename T, Size from, Size to, typename ... TTypes >
struct TypeMakeTupleTypes : TypeMakeTupleTypes< T, from + 1, to, TTypes ..., MakeTupleType< from, RemoveReference<T> > > {
	static_assert(from <= to, "MakeTupleTypes input error");
};

template< typename T, Size to, typename ... TTypes >
struct TypeMakeTupleTypes< T, to, to, TTypes ... > : TypeWrapper< TupleTypes< TTypes ... > > {
};

template< typename T, Size from = 0, Size to = TupleSize< RemoveReference<T> >::value >
using MakeTupleTypes = TypeUnwrap< TypeMakeTupleTypes< T, from, to > >;

template< typename TFrom, typename TTo >
struct IsTupleConvertibleBasic : BooleanFalse {
};

template< typename ... TFrom, typename ... TTo >
struct IsTupleConvertibleBasic< TupleTypes< TFrom ... >, TupleTypes< TTo ... > > : BooleanAnd< IsConvertible< TFrom, TTo > ... > {
};

template< typename TFrom, typename TTo >
struct IsTupleConvertibleApply : BooleanAnd<
	BooleanConstant< TupleSize< RemoveReference<TFrom> >::value == TupleSize<TTo>::value >,
	IsTupleConvertibleBasic< MakeTupleTypes<TFrom>, MakeTupleTypes<TTo> >
> {
};

template< typename TFrom, typename TTo >
using IsTupleConvertible = BooleanAnd< IsTupleLike< RemoveReference<TFrom> >, IsTupleLike<TTo>, IsTupleConvertibleApply< TFrom, TTo > >;

template< typename TFrom, typename TTo >
using NotTupleConvertible = BooleanNot< IsTupleConvertible< TFrom, TTo > >;

template< typename T0, typename T1 >
struct IsTupleConstructibleBasic : BooleanFalse {
};

template< typename ... TElement, typename ... TValue >
struct IsTupleConstructibleBasic< TupleTypes< TElement ... >, TupleTypes< TValue ... > > : BooleanAnd< IsConstructible< TElement, TValue > ... > {
};

template< typename TTuple, typename TArgument >
struct IsTupleConstructibleApply : BooleanAnd<
	BooleanConstant< TupleSize<TTuple>::value == TupleSize< RemoveReference<TArgument> >::value >,
	IsTupleConstructibleBasic< MakeTupleTypes<TTuple>, MakeTupleTypes<TArgument> > > {
};

template< typename TTuple, typename TArgument >
using IsTupleConstructible = BooleanAnd< IsTupleLike<TTuple>, IsTupleLike< RemoveReference<TArgument> >, IsTupleConstructibleApply< TTuple, TArgument > >;

template< typename TFrom, typename TTo >
using NotTupleConstructible = BooleanNot< IsTupleConstructible< TFrom, TTo > >;

template< typename T0, typename T1 >
struct IsTupleAssignableBasic : BooleanFalse {
};

template< typename ... TElement, typename ... TValue >
struct IsTupleAssignableBasic< TupleTypes< TElement ... >, TupleTypes< TValue ... > > : BooleanAnd< IsAssignable< TElement &, TValue > ... > {
};

template< typename TTuple, typename TArgument >
struct IsTupleAssignableApply : BooleanAnd<
	BooleanConstant< TupleSize<TTuple>::value == TupleSize< RemoveReference<TArgument> >::value >,
	IsTupleAssignableBasic< MakeTupleTypes<TTuple>, MakeTupleTypes<TArgument> >
> {
};

template< typename TTuple, typename TArgument >
using IsTupleAssignable = BooleanAnd< IsTupleLike<TTuple>, IsTupleLike< RemoveReference<TArgument> >, IsTupleAssignableApply< TTuple, TArgument > >;

template< typename ... T >
struct IsAllDefaultConstructible;

template< typename ... T >
struct IsAllDefaultConstructible< TupleTypes< T ... > > : BooleanAnd< HasDefaultConstructor<T> ... > {
};

template< Size I, typename TElement, bool _dummy = BooleanAnd< IsEmpty<TElement>, NotFinal<TElement> >::value >
class TupleLeaf;

template< Size I, typename T, bool B >
inline void swap(TupleLeaf< I, T, B > & x, TupleLeaf< I, T, B > & y) noexcept(noexcept(swap(x.get(), y.get()))) {
	swap(x.get(), y.get());
}

template< Size I, typename TElement >
class TupleLeaf< I, TElement, false > {
public:
	BR_CONSTEXPR_AFTER_CXX11 TupleLeaf() noexcept(HasNothrowDefaultConstructor<TElement>()) : m_element() {
		m_assert();
	}

	TupleLeaf(TupleLeaf const & leaf) = default;

	TupleLeaf(TupleLeaf && leaf) = default;

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used > _dummy, TAllocator const & _allocator) : m_element() {
		m_assert();
	}

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag > _dummy, TAllocator const & allocator) : m_element(allocator_argument_tag, allocator) {
		m_assert();
	}

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag > _dummy, TAllocator const & allocator) : m_element(allocator) {
		m_assert();
	}

	template< typename TValue, typename _TDummy = EnableIf< BooleanAnd< NotSame< Decay<TValue>, TupleLeaf >, IsConstructible< TElement, TValue > > > >
	explicit BR_CONSTEXPR_AFTER_CXX11 TupleLeaf(TValue && value) noexcept(IsNothrowConstructible< TElement, TValue >()) : m_element(forward<TValue>(value)) {
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
			>(),
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used > _dummy, TAllocator const & _allocator, TValue && value) : m_element(forward<TValue>(value)) {
		m_assert<TValue>();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag > _dummy, TAllocator const & allocator, TValue && value) : m_element(allocator_argument_tag, allocator, forward<TValue>(value)) {
		m_assert<TValue>();
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag > _dummy, TAllocator const & allocator, TValue && value) : m_element(forward<TValue>(value), allocator) {
		m_assert<TValue>();
	}

	template< typename TValue >
	auto operator=(TValue && value) noexcept(IsNothrowAssignable< AddLValueReference<TElement>, TValue >()) -> TupleLeaf & {
		m_element = forward<TValue>(value);
		return *this;
	}

	auto swap(TupleLeaf & leaf) noexcept(IsNothrowSwappable<TupleLeaf>()) -> int {
		swap(*this, leaf);
		return 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto get() noexcept -> TElement & {
		return m_element;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto get() const noexcept -> TElement const & {
		return m_element;
	}

private:
	auto operator=(TupleLeaf const & leaf) -> TupleLeaf & = delete;

	void m_assert() const {
		static_assert(NotReference<TElement>(), "Attempted to default construct a reference element in a Tuple");
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
						IsSame< RemoveReference<TValue>, WrappedReference< RemoveReference<TElement> > >
					>
				>
			>(),
			"Attempted to construct a reference element in a Tuple with an rvalue"
		);
	}

private:
	TElement m_element;
}; // class TupleLeaf

template< Size I, typename TElement >
class TupleLeaf< I, TElement, true > : TElement {
public:
	BR_CONSTEXPR_AFTER_CXX11 TupleLeaf() noexcept(HasNothrowDefaultConstructor<TElement>()) {
	}

	TupleLeaf(TupleLeaf const & leaf) = default;

	TupleLeaf(TupleLeaf && leaf) = default;

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used > _dummy, TAllocator const & _allocator) {
	}

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag > _dummy, TAllocator const & allocator) : TElement(allocator_argument_tag, allocator) {
	}

	template< typename TAllocator >
	TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag > _dummy, TAllocator const & allocator) : TElement(allocator) {
	}

	template< typename TValue, typename = EnableIf< BooleanAnd< NotSame< Decay<TValue>, TupleLeaf >, IsConstructible< TElement, TValue > > > >
	explicit BR_CONSTEXPR_AFTER_CXX11 TupleLeaf(TValue && value) noexcept(IsNothrowConstructible< TElement, TValue >()) : TElement(forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::not_used > _dummy, TAllocator const & _allocator, TValue && value) : TElement(forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_with_tag > _dummy, TAllocator const & allocator, TValue && value) : TElement(allocator_argument_tag, allocator, forward<TValue>(value)) {
	}

	template< typename TValue, typename TAllocator >
	explicit TupleLeaf(AllocatorConstructorUsageConstant< AllocatorConstructorUsageType::use_without_tag > _dummy, TAllocator const & allocator, TValue && value) : TElement(forward<TValue>(value), allocator) {
	}

	template< typename TValue >
	auto operator=(TValue && value) noexcept(IsNothrowAssignable< AddLValueReference<TElement>, TValue >()) -> TupleLeaf & {
		TElement::operator=(forward<TValue>(value));
		return *this;
	}

	auto swap(TupleLeaf & leaf) noexcept(IsNothrowSwappable<TupleLeaf>()) -> int {
		swap(*this, leaf);
		return 0;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto get() noexcept -> TElement & {
		return static_cast< TElement & >(*this);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto get() const noexcept -> TElement const & {
		return static_cast< TElement const & >(*this);
	}

private:
	auto operator=(TupleLeaf const & leaf) -> TupleLeaf & = delete;
}; // class TupleLeaf< I, TElement, true >

template< typename ... TTypes >
void swallow(TTypes &&...) noexcept {
}

template< typename I, typename ... TTypes >
class TupleImp;

template< Size ... I, typename ... T >
class TupleImp< TupleIndices< I ... >, T ... > : public TupleLeaf< I, T > ... {
public:
	BR_CONSTEXPR_AFTER_CXX11 TupleImp() noexcept(BooleanAnd< HasNothrowDefaultConstructor<T> ... >()) {
	}

	TupleImp(TupleImp const & tuple) = default;

	TupleImp(TupleImp && tuple) = default;

	template< Size ... IHead, typename ... THead, Size ... ITail, typename ... TTail, typename ... TValue >
	explicit BR_CONSTEXPR_AFTER_CXX11 TupleImp(
		TupleIndices< IHead... > _ih, TupleTypes< THead... > _th, TupleIndices< ITail... > _it, TupleTypes< TTail... > _tt, TValue && ... value
	) noexcept(
		BooleanAnd< IsNothrowConstructible< THead, TValue >..., HasNothrowDefaultConstructor<TTail>... >()
	) : TupleLeaf< IHead, THead >(forward<TValue>(value))..., TupleLeaf< ITail, TTail >()... {
	}

	template< typename TAllocator, Size ... IHead, typename ... THead, Size ... ITail, typename ... TTail, typename ... TValue >
	explicit TupleImp(
		AllocatorArgumentTag _dummy, TAllocator const & allocator, TupleIndices< IHead ... > _ih, TupleTypes< THead ... > _th, TupleIndices< ITail ... > _it, TupleTypes< TTail ... > _tt, TValue && ... value
	) : TupleLeaf< IHead, THead >(AllocatorConstructorUsage< THead, TAllocator, TValue >(), allocator, forward<TValue>(value)) ...,  TupleLeaf< ITail, TTail >(AllocatorConstructorUsage< TTail, TAllocator >(), allocator) ... {
	}

	template< typename TTuple, typename _TDummy = EnableIf< IsTupleConstructible< Tuple< T ... >, TTuple > > >
	BR_CONSTEXPR_AFTER_CXX11 TupleImp(TTuple && tuple) noexcept(
		BooleanAnd< IsNothrowConstructible< T, TupleElement< I, MakeTupleTypes<TTuple> > > ... >()
	) : TupleLeaf< I, T >(forward< TupleElement< I, MakeTupleTypes<TTuple> > >(BR::get<I>(tuple))) ... {
	}

	template< typename TAllocator, typename TTuple, typename _TDummy = EnableIf< IsTupleConstructible< Tuple< T ... >, TTuple > > >
	TupleImp(
		AllocatorArgumentTag _dummy, TAllocator const & allocator, TTuple && tuple
	) : TupleLeaf< I, T >(AllocatorConstructorUsage< T, TAllocator, TupleElement< I, MakeTupleTypes<TTuple> > >(), allocator, forward< TupleElement< I, MakeTupleTypes<TTuple> > >(get<I>(tuple))) ...  {
	}

	template< typename TTuple, typename _TDummy = EnableIf< IsTupleAssignable< Tuple< T ... >, TTuple > > >
	auto operator=(TTuple && tuple) noexcept(
		BooleanAnd< IsNothrowAssignable< T &, TupleElement< I, MakeTupleTypes<TTuple> > > ... >::value
	) -> TupleImp & {
		swallow(TupleLeaf< I, T >::operator=(forward< TupleElement< I, MakeTupleTypes<TTuple> > >(BR::get<I>(tuple))) ...);
		return *this;
	}

	auto operator=(TupleImp const & tuple) noexcept(BooleanAnd< HasNothrowCopyAssign<T> ... >::value) -> TupleImp & {
		swallow(TupleLeaf< I, T >::operator=(static_cast< TupleLeaf< I, T > const & >(tuple).get()) ...);
		return *this;
	}

	auto operator=(TupleImp && tuple) noexcept(BooleanAnd< HasNothrowMoveAssign<T> ... >::value) -> TupleImp &  {
		swallow(TupleLeaf< I, T >::operator=(forward< T >(static_cast< TupleLeaf< I, T > & >(tuple).get())) ...);
		return *this;
	}

	void swap(TupleImp & tuple) noexcept(BooleanAnd< IsNothrowSwappable<T> ... >::value) {
		swallow(TupleLeaf< I, T >::swap(static_cast< TupleLeaf< I, T > & >(tuple)) ...);
	}

	template< Size P >
	BR_CONSTEXPR_AFTER_CXX11 auto get() noexcept -> TupleElement< P, TupleTypes< T ... > > & {
		return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > > & >(*this).get();
	}

	template< Size P >
	BR_CONSTEXPR_AFTER_CXX11 auto get() const noexcept -> TupleElement< P, TupleTypes< T ... > > const & {
		return static_cast< TupleLeaf< P, TupleElement< P, TupleTypes< T ... > > > const & >(*this).get();
	}

}; // class TupleImp< TupleIndices< I ... >, T ... >

} // namespace Container
} // namespace Detail

template < typename ... TElement >
class Tuple {
public:
	using Imp = Detail::Container::TupleImp< Detail::Container::MakeTupleIndices< 0, sizeof...(TElement) >, TElement ... >;

public:
	/**
	 * default constructor
	 */
	template< typename _TDummy0 = BooleanTrue, typename _TDummy1 = EnableIf< BooleanAnd< _TDummy0, HasDefaultConstructor<TElement> ... > > >
	BR_CONSTEXPR_AFTER_CXX11 Tuple() noexcept(BooleanAnd< HasNothrowDefaultConstructor<TElement> ... >()) {
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
		BooleanAnd< HasNothrowCopyConstructor<TElement> ... >()
	) : m_imp(Detail::Container::MakeTupleIndices< 0, sizeof...(TElement) >(), Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TElement) >(), Detail::Container::MakeTupleIndices< 0, 0 >(), Detail::Container::MakeTupleTypes< Tuple, 0, 0 >(), elements ...) {
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
		> _dummy = false
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(TValue && ... value) noexcept(
		IsNothrowConstructible<
			Imp,
			Detail::Container::MakeTupleIndices< 0, sizeof...(TValue) >,
			Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >,
			Detail::Container::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >,
			Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >,
			TValue ...
		>()
	) : m_imp(
		Detail::Container::MakeTupleIndices< 0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
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
		> _dummy = false
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(TValue && ... value) noexcept(
		IsNothrowConstructible<
			Imp,
			Detail::Container::MakeTupleIndices< 0, sizeof...(TValue) >,
			Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >,
			Detail::Container::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >,
			Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >,
			TValue ...
		>()
	) : m_imp(
		Detail::Container::MakeTupleIndices< 0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward<TValue>(value) ...
	) {
	}

	/**
	 *	implicit move conversion constructor
	 */
	template<
		typename TTuple,
		EnableIf< Detail::Container::IsTupleConvertible< TTuple, Tuple >, bool > _dummy = false
	>
	BR_CONSTEXPR_AFTER_CXX11 Tuple(TTuple && tuple) noexcept(
		IsNothrowConstructible< Imp, TTuple >()
	) : m_imp(forward< TTuple >(tuple)) {
	}

	template<
		typename TTuple,
		EnableIf<
			BooleanAnd<
				Detail::Container::IsTupleConstructible< Tuple, TTuple >,
				Detail::Container::NotTupleConvertible< TTuple, Tuple >
			>,
			bool
		> _dummy = false
	>
	explicit BR_CONSTEXPR_AFTER_CXX11 Tuple(TTuple && tuple) noexcept(
		IsNothrowConstructible< Imp, TTuple >()
	) : m_imp(forward<TTuple>(tuple)) {
	}

	/**
	 *	allocator version initialization constructor
	 */
	template< typename TAllocator >
	Tuple(AllocatorArgumentTag _dummy, TAllocator const & allocator, TElement const & ... element) : m_imp(
		allocator_argument_tag,
		allocator,
		Detail::Container::MakeTupleIndices< 0, sizeof...(TElement) >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TElement) >(),
		Detail::Container::MakeTupleIndices< 0, 0 >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, 0 >(),
		element ...
	) {}

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
		> _dummy0 = false
	>
	Tuple(AllocatorArgumentTag _dummy, TAllocator const & allocator, TValue && ... value) : m_imp(
		allocator_argument_tag,
		allocator,
		Detail::Container::MakeTupleIndices<  0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleTypes< Tuple, 0, sizeof...(TValue) >(),
		Detail::Container::MakeTupleIndices< sizeof...(TValue), sizeof...(TElement) >(),
		Detail::Container::MakeTupleTypes< Tuple, sizeof...(TValue), sizeof...(TElement) >(),
		forward<TValue>(value) ...
	) {}

	/**
	 * allocator version move conversion constructor
	 */
	template< typename TAllocator, typename TTuple, typename _TDummy = EnableIf< Detail::Container::IsTupleConvertible< TTuple, Tuple > > >
	Tuple(AllocatorArgumentTag _dummy, TAllocator const & allocator, TTuple && tuple) : m_imp(
		allocator_argument_tag, allocator, forward< TTuple >(tuple)
	) {
	}

	/**
	 * implicit move conversion assignment
	 */
	template< typename TTuple, typename _TDummy = EnableIf< Detail::Container::IsTupleAssignable< Tuple, TTuple > > >
	auto operator=(TTuple && tuple) noexcept(IsNothrowAssignable< Imp &, TTuple >()) -> Tuple & {
		m_imp.operator=(forward<TTuple>(tuple));
		return *this;
	}

	/**
	 * swap
	 */
	void swap(Tuple & tuple) noexcept(BooleanAnd< IsNothrowSwappable<TElement> ... >()) {
		m_imp.swap(tuple.m_imp);
	}

	/**
	 *  get element at \em I
	 */
	template< Size I >
	BR_CONSTEXPR_AFTER_CXX11 auto get() noexcept -> TupleElement< I, Tuple > & {
		return m_imp.get<I>();
	}

	/**
	 *  get element at \em I
	 */
	template< Size I >
	BR_CONSTEXPR_AFTER_CXX11 auto get() const noexcept -> TupleElement< I, Tuple > const & {
		return m_imp.get<I>();
	}

private:
	Imp m_imp;

}; // class Tuple< TElement ... >

template <>
class Tuple<> {
public:
	constexpr Tuple() noexcept = default;

	template< typename TAllocator >
	constexpr Tuple(AllocatorArgumentTag _tag, TAllocator const & _allocator) noexcept {
	}

	template< typename TAllocator >
	constexpr Tuple(AllocatorArgumentTag _tag, TAllocator const & _allocator, Tuple const & _tuple) noexcept {
	}

	template< typename TValue >
	constexpr Tuple(Array< TValue, 0 > _array) noexcept {}

	template< typename TAllocator, typename TValue >
	constexpr Tuple(AllocatorArgumentTag _dummy, TAllocator const & _allocator, Array< TValue, 0 > _array) noexcept {
	}

	void swap(Tuple & tuple) noexcept {
	}
}; // class Tuple<>

template< typename T >
struct TupleSize : IntegerRewrap< Detail::Container::TupleSize< T > > {
};

template< Size I, typename T >
struct TypeTupleElement : TypeRewrap< Detail::Container::TypeTupleElement< I, T > > {
};

template< typename ... TElement >
void swap(Tuple< TElement ... > & lhs, Tuple< TElement ... > & rhs) noexcept(noexcept(lhs.swap(rhs))) {
	lhs.swap(rhs);
}

template< Size I, typename ... Tn >
BR_CONSTEXPR_AFTER_CXX11 inline  auto get(Tuple< Tn ... > & tuple) noexcept -> TupleElement< I, Tuple< Tn ... > > & {
	return tuple.get<I>();
};

template< Size I, typename ... Tn >
BR_CONSTEXPR_AFTER_CXX11 inline  auto get(Tuple< Tn ... > const & tuple) noexcept -> TupleElement< I, Tuple< Tn ... > > const & {
	return tuple.get<I>();
};

template< Size I, typename ... Tn >
BR_CONSTEXPR_AFTER_CXX11 inline  auto get(Tuple< Tn ... > && tuple) noexcept -> TupleElement< I, Tuple< Tn ... > > && {
	return move(tuple.get< I >());
};

template< typename ... Tn >
BR_CONSTEXPR_AFTER_CXX11 inline auto tie(Tn & ... t) noexcept -> Tuple< Tn & ... > {
	return Tuple< Tn & ... >(t ...);
}

namespace Detail {
namespace Container {

template< typename T >
struct TypeMakeTupleReturnBasic : TypeWrapper<T> {};

template< typename T >
struct TypeMakeTupleReturnBasic< WrappedReference<T> > : TypeAddLValueReference<T> {};

template< typename T >
struct TypeMakeTupleReturn : TypeMakeTupleReturnBasic< Decay<T> > {};

template< typename T >
using MakeTupleReturn = TypeUnwrap< TypeMakeTupleReturn<T> >;

} // namespace Container
} // namespace Detail

template< typename ... T >
inline BR_CONSTEXPR_AFTER_CXX11 auto make_tuple(T && ... t) -> Tuple< Detail::Container::MakeTupleReturn< T > ... > {
	return Tuple< Detail::Container::MakeTupleReturn< T > ... >(forward<T>(t) ...);
}

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
struct TypeTupleCatType< Tuple< T0 ... >, TupleTypes< T1 ... > > : TypeWrapper< Tuple< T0 ..., T1 ...  > > {
};

template< typename TResult, bool is_tuple_like, typename ... TTuple >
struct TypeTupleCatResultBasic {
};

template< typename ... T, typename TTuple >
struct TypeTupleCatResultBasic< Tuple< T ... >, true, TTuple > : TypeTupleCatType< Tuple< T ... >, MakeTupleTypes< RemoveReference< TTuple > > > {
};

template< typename ... T, typename TTuple0, typename TTuple1, typename ... TTuple >
struct TypeTupleCatResultBasic< Tuple< T ... >, true, TTuple0, TTuple1, TTuple ... > : TypeTupleCatResultBasic< TupleCatType< Tuple< T ... >, MakeTupleTypes< RemoveReference< TTuple0 > > >, IsTupleLike< RemoveReference<TTuple1> >::value, TTuple1, TTuple ... > {
};

template< typename ... TTuple >
struct TypeTupleCatResult;

template< typename TTuple0, typename ... TTuple >
struct TypeTupleCatResult< TTuple0, TTuple ... > : TypeTupleCatResultBasic< Tuple<>, IsTupleLike< RemoveReference<TTuple0> >::value, TTuple0, TTuple ... > {
};

template<>
struct TypeTupleCatResult<> : TypeWrapper< Tuple<> > {
};

template< typename ... TTuple >
using TupleCatResult = TypeUnwrap< TypeTupleCatResult< TTuple ... > >;

template< typename TResult, typename TIndices, typename TTuple0, typename ... TTuple >
struct TypeTupleCatResultReferenceBasic;

template< typename ... T, Size ... I, typename TTuple >
struct TypeTupleCatResultReferenceBasic< Tuple< T ... >, TupleIndices< I ... >, TTuple > : TypeWrapper<
	Tuple< T ..., MapQualifier< TTuple, TupleElement< I, RemoveReference<TTuple> > > && ... >
> {
};

template< typename ... T, Size ... I, typename TTuple0, typename TTuple1, typename ... TTuple >
struct TypeTupleCatResultReferenceBasic< Tuple< T ... >, TupleIndices< I ... >, TTuple0, TTuple1, TTuple ... > : TypeTupleCatResultReferenceBasic<
	Tuple< T ..., MapQualifier< TTuple0, TupleElement< I, RemoveReference<TTuple0> > > && ... >, MakeTupleIndices< 0, TupleSize< RemoveReference<TTuple1> >::value >, TTuple1, TTuple ...
> {
};

template< typename TTuple0, typename ... TTuple >
struct TypeTupleCatResultReference : TypeTupleCatResultReferenceBasic< Tuple<>, MakeTupleIndices< 0, TupleSize< RemoveReference<TTuple0> >::value >, TTuple0, TTuple ... > {
};

template< typename ... TTuple >
using TupleCatResultReference = TypeUnwrap< TypeTupleCatResultReference< TTuple ... > >;

template< typename TResult, typename TIHead, typename TITail >
struct TupleCat;

template< typename ... T, Size ... IHead, Size ... ITail >
struct TupleCat< Tuple<  T ... >, TupleIndices< IHead ... >, TupleIndices< ITail ... > > {
	template< typename TTuple >
	BR_CONSTEXPR_AFTER_CXX11 auto operator()(Tuple< T ... > head, TTuple && tail) -> TupleCatResultReference< Tuple< T ... > &&, TTuple && > {
		return forward_as_tuple(forward<T>(get<IHead>(head)) ..., get<ITail>(forward<TTuple>(tail)) ...);
	}

	template< typename TTuple0, typename TTuple1, typename ... TTuples >
	BR_CONSTEXPR_AFTER_CXX11 auto operator()(Tuple< T ... > head, TTuple0 && tail0, TTuple1 && tail1, TTuples && ... tails) -> TupleCatResultReference< Tuple< T ... > &&, TTuple0 &&, TTuple1 &&, TTuples && ... > {
		using NoRefTuple0 = RemoveReference<TTuple0>;
		return TupleCat<
			Tuple< T ..., MapQualifier< TTuple0, TupleElement< ITail, NoRefTuple0 > > && ... >, MakeTupleIndices< 0, sizeof...(T) + TupleSize< NoRefTuple0 >::value >, MakeTupleIndices< 0, TupleSize< RemoveReference<TTuple1> >::value >
		>()(
			forward_as_tuple(forward<T>(get<IHead>(head)) ..., get<ITail>(forward<TTuple0>(tail0)) ...), forward<TTuple1>(tail1), forward<TTuples>(tails) ...
		);
	}
};

} // namespace Container
} // namespace Detail

BR_CONSTEXPR_AFTER_CXX11 inline  auto tuple_cat() -> Tuple<> {
	return Tuple<>();
}

template< typename TTuple0, typename ... TTuples >
BR_CONSTEXPR_AFTER_CXX11 inline auto tuple_cat(TTuple0 && tuple0, TTuples ... tuples) -> Detail::Container::TupleCatResult< TTuple0, TTuples ... > {
	return Detail::Container::TupleCat<
		Tuple<>, Detail::Container::TupleIndices<>, Detail::Container::MakeTupleIndices< 0, TupleSize< RemoveReference<TTuple0> >::value >
	>()(
		Tuple<>(), forward<TTuple0>(tuple0), forward<TTuples>(tuples) ...
	);
}

template< typename T, typename TAllocator >
struct IsUseAllocator;


template< typename ... T, typename TAllocator >
struct IsUseAllocator< Tuple< T ... >, TAllocator > : BooleanTrue {
};

template< typename T, typename TAllocator >
struct NotUseAllocator;

template< typename ... T, typename TAllocator >
struct NotUseAllocator< Tuple< T ... >, TAllocator > : BooleanFalse {
};


} // namespace BR