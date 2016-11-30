#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/dummy_false.hpp>
#include <libbr/container/detail/tuple_forward.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/decay.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_copy_assignment.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/has_default_constructor.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/make_integral_sequence.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/piecewise_construct_tag.hpp>
#include <libbr/utility/swap.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace Container {

template< typename TFirst, typename TSecond >
class Pair;

template< typename T0, typename T1 >
struct TupleSize< Pair< T0, T1 > > : public IntegralConstant< Size, 2 > {};

template< typename T0, typename T1 >
struct TypeTupleElement< 0, Pair< T0, T1 > > : public TypeWrapper<T0> {};

template< typename T0, typename T1 >
struct TypeTupleElement< 1, Pair< T0, T1 > > : public TypeWrapper<T1> {};

template< typename TFirst, typename TSecond >
constexpr auto make_pair(TFirst && x, TSecond && y) -> Pair< Decay<TFirst>, Decay<TSecond> > {
	return Pair< Decay<TFirst>, Decay<TSecond> >(forward<TFirst>(x), forward<TSecond>(y));
}

template< Size I, typename T0, typename T1 > constexpr auto get(Pair< T0, T1 >        & P) noexcept -> TupleElement< I, Pair< T0, T1 > >        & { return P.template get<I>(); }
template< Size I, typename T0, typename T1 > constexpr auto get(Pair< T0, T1 > const  & P) noexcept -> TupleElement< I, Pair< T0, T1 > > const  & { return P.template get<I>(); }
template< Size I, typename T0, typename T1 > constexpr auto get(Pair< T0, T1 >       && P) noexcept -> TupleElement< I, Pair< T0, T1 > >       && { return P.template get<I>(); }
template< Size I, typename T0, typename T1 > constexpr auto get(Pair< T0, T1 > const && P) noexcept -> TupleElement< I, Pair< T0, T1 > > const && { return P.template get<I>(); }

template< typename T0, typename T1 > constexpr auto get(Pair< T0, T1 >        & P) noexcept -> T0        & { return P.template get<0>(); }
template< typename T0, typename T1 > constexpr auto get(Pair< T0, T1 > const  & P) noexcept -> T0 const  & { return P.template get<0>(); }
template< typename T0, typename T1 > constexpr auto get(Pair< T0, T1 >       && P) noexcept -> T0       && { return P.template get<0>(); }
template< typename T0, typename T1 > constexpr auto get(Pair< T0, T1 > const && P) noexcept -> T0 const && { return P.template get<0>(); }

template< typename T0, typename T1 > constexpr auto get(Pair< T1, T0 >        & P) noexcept -> T0        & { return P.template get<1>(); }
template< typename T0, typename T1 > constexpr auto get(Pair< T1, T0 > const  & P) noexcept -> T0 const  & { return P.template get<1>(); }
template< typename T0, typename T1 > constexpr auto get(Pair< T1, T0 >       && P) noexcept -> T0       && { return P.template get<1>(); }
template< typename T0, typename T1 > constexpr auto get(Pair< T1, T0 > const && P) noexcept -> T0 const && { return P.template get<1>(); }

} // namespace Container



namespace Detail {
namespace Container {

template< Size I >
struct PairGetter;

template<>
struct PairGetter<0> {
	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > & p) const noexcept -> T0 & {
		return p.first;
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > const & p) const noexcept -> T0 const & {
		return p.first;
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > && p) const noexcept -> T0 && {
		return move(p.first);
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > const && p) const noexcept -> T0 const && {
		return move(p.first);
	}
};

template<>
struct PairGetter<1> {
	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > & p) const noexcept -> T1 & {
		return p.second;
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > const & p) const noexcept -> T1 const & {
		return p.second;
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > && p) const noexcept -> T1 && {
		return move(p.second);
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > const && p) const noexcept -> T1 const && {
		return move(p.second);
	}
};

} // namespace Container
} // namespace Detail

inline namespace Container {

template< typename TFirst, typename TSecond = TFirst >
class Pair {

public:
	using First = TFirst;

	using Second = TSecond;

private:
	template< typename TOtherFirst, typename TOtherSecond >
	using IsParticipateOverload = BooleanAnd< IsConvertible< TOtherFirst, First >, IsConvertible< TOtherSecond, Second > >;

public:
	template< typename = EnableIf< BooleanAnd< HasDefaultConstructor<First>, HasDefaultConstructor<Second> > > >
	constexpr Pair() noexcept(
		BooleanAnd< HasNothrowDefaultConstructor<First>, HasNothrowDefaultConstructor<Second> >{}
	) : first(), second() {
	}

	Pair(Pair const &) noexcept(BooleanAnd< HasNothrowCopyConstructor<First>, HasNothrowCopyConstructor<Second> >{}) = default;

	Pair(Pair &&) noexcept(BooleanAnd< HasNothrowMoveConstructor<First>, HasNothrowMoveConstructor<Second> >{}) = default;

	BR_CONSTEXPR_AFTER_CXX11 Pair(First const & x, Second const & y) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<First>, HasNothrowCopyConstructor<Second> >{}
	) : first(x), second(y) {
	}

	template< typename TOtherFirst, typename TOtherSecond, typename = EnableIf< IsParticipateOverload< TOtherFirst, TOtherSecond > > >
	BR_CONSTEXPR_AFTER_CXX11 Pair(Pair< TOtherFirst, TOtherSecond > const & pair) : first(pair.first), second(pair.second) {
	}

	template< typename TOtherFirst, typename TOtherSecond >
	BR_CONSTEXPR_AFTER_CXX11 Pair(Pair< TOtherFirst, TOtherSecond > && pair, EnableIf< BooleanAnd< IsConvertible< TOtherFirst, First >, IsConvertible< TOtherSecond, Second > > > * = nullptr) : first(forward<TOtherFirst>(pair.first)), second(forward<TOtherSecond>(pair.second)) {
	}

	template< typename TOtherFirst, typename TOtherSecond, typename = EnableIf< IsParticipateOverload< TOtherFirst, TOtherSecond > > >
	BR_CONSTEXPR_AFTER_CXX11 Pair(TOtherFirst && x, TOtherSecond && y) : first(forward<TOtherFirst>(x)), second(forward<TOtherSecond>(y)) {
	}

	template< typename... TArgs0, typename... TArgs1 >
	Pair(PiecewiseConstructTag, Tuple<TArgs0...> args0, Tuple<TArgs1...> args1) : Pair(
		piecewise_construct_tag, args0, args1, MakeIndexSequence< 0, sizeof...(TArgs0) >{}, MakeIndexSequence< 0, sizeof...(TArgs1) >{}
	) {
	}

	~Pair() noexcept = default;

	auto operator=(Pair const & pair) noexcept(BooleanAnd< HasNothrowCopyAssignment<First>, HasNothrowCopyAssignment<Second> >{}) -> Pair & {
		first = pair.first;
		second = pair.second;
		return *this;
	}

	auto operator=(Pair && pair) noexcept(BooleanAnd< HasNothrowMoveAssignment<First>, HasNothrowMoveAssignment<Second> >{}) -> Pair & {
		first = forward<First>(pair.first);
		second = forward<Second>(pair.second);
		return *this;
	}

	template< typename TOtherFirst, typename TOtherSecond, typename = EnableIf< BooleanAnd< IsAssignable< First &, TOtherFirst const & >, IsAssignable< Second &, TOtherSecond const & > > > >
	auto operator=(Pair< TOtherFirst, TOtherSecond > const & pair) noexcept(
		BooleanAnd< IsNothrowAssignable< First &, TOtherFirst const & >, IsNothrowAssignable< Second &, TOtherSecond const & > >{}
	) -> Pair & {
		first = pair.first;
		second = pair.second;
		return *this;
	}

	template< typename TOtherFirst, typename TOtherSecond, typename = EnableIf< BooleanAnd< IsAssignable< First &, TOtherFirst >, IsAssignable< Second &, TOtherSecond > > > >
	auto operator=(Pair< TOtherFirst, TOtherSecond > && pair) noexcept(
		BooleanAnd< IsNothrowAssignable< First &, TOtherFirst >, IsNothrowAssignable< Second &, TOtherSecond > >{}
	) -> Pair & {
		first = forward<First>(pair.first);
		second = forward<Second>(pair.second);
		return *this;
	}

	auto swap(Pair & pair) noexcept(BooleanAnd< IsNothrowSwappable<First>, IsNothrowSwappable<Second> >{}) -> Pair & {
		using BR::swap;
		swap(first, pair.first);
		swap(second, pair.second);
		return *this;
	}

	constexpr auto operator==(Pair const & y) const -> bool {
		return (first == y.first) && (second == y.second);
	}

	constexpr auto operator!=(Pair const & y) const -> bool {
		return !(*this == y);
	}

	constexpr auto operator<(Pair const & y) const -> bool {
		return (first < y.first) || (!(y.first < first) && second < y.second);
	}

	constexpr auto operator>(Pair const & y) const -> bool {
		return y < *this;
	}

	constexpr auto operator<=(Pair const & y) const -> bool {
		return !(y < *this);
	}

	constexpr auto operator>=(Pair const & y) const -> bool {
		return !(*this < y);
	}

	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()       &  noexcept -> TupleElement< I, Pair >       &  { return Detail::Container::PairGetter<I>{}(*this); }
	template< Size I > constexpr                auto get() const &  noexcept -> TupleElement< I, Pair > const &  { return Detail::Container::PairGetter<I>{}(*this); }
	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TupleElement< I, Pair >       && { return Detail::Container::PairGetter<I>{}(move(*this)); }
	template< Size I > constexpr                auto get() const && noexcept -> TupleElement< I, Pair > const && { return Detail::Container::PairGetter<I>{}(move(*this)); }

	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> T        & { return get<T>(*this); }
	template< typename T > constexpr                auto get() const  & noexcept -> T const  & { return get<T>(*this); }
	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> T       && { return get<T>(move(*this)); }
	template< typename T > constexpr                auto get() const && noexcept -> T const && { return get<T>(move(*this)); }

private:
	template< typename... TArgs0, typename... TArgs1, Size ... Idx0, Size ... Idx1 >
	Pair(
		PiecewiseConstructTag, Tuple<TArgs0...> & args0, Tuple<TArgs1...> & args1, IndexSequence<Idx0...>, IndexSequence<Idx1...>
	) : first(forward<TArgs0>(args0.template get<Idx0>())...), second(forward<TArgs1>(args1.template get<Idx1>())...) {
	}

public:
	First first;
	Second second;

}; // class Pair< TFirst, TSecond >

} // namespace Container

} // namespace BR