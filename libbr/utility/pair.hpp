#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/is_convertible.hpp>
#include <libbr/type_operate/has_nothrow_move_assignment.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>

#if defined(BR_CPP14)
#  define BR_PAIR_CONSTEXPR constexpr
#else
#  define BR_PAIR_CONSTEXPR
#endif // defined

namespace BR {

template< typename T0, typename T1 >
struct Pair {
public:
	using First  = T0;
	using Second = T1;

public:
	First first;
	Second second;

public:
	constexpr Pair() : first(), second() { }

	template< typename U0, typename U1,
		typename = TypeOperate::EnableIf<
			TypeOperate::BooleanAnd<
				TypeOperate::IsConvertible< U0 const &, T0 >,
				TypeOperate::IsConvertible< U1 const &, T1 >
			>
		>
	>
	constexpr Pair(Pair< U0, U1 > const &P)
		: first(P.first), second(P.second) { }

	template< typename U0, typename U1,
		typename = TypeOperate::EnableIf<
			TypeOperate::BooleanAnd<
				TypeOperate::IsConvertible< U0 const &, T0 >,
				TypeOperate::IsConvertible< U1 const &, T1 >
			>
		>
	>
	constexpr Pair(Pair< U0, U1 > &&P)
		: first(forward< U0 >(P.first)), second(forward< U1 >(P.second)) { }

	constexpr Pair(Pair const &) = default;

	constexpr Pair(Pair &&) = default;

	constexpr Pair(First const &x, Second const &y)
		: first(x), second(y) { }

	template< typename U0, typename U1,
		typename = TypeOperate::EnableIf<
			TypeOperate::BooleanAnd<
				TypeOperate::IsConvertible< U0 const &, T0 >,
				TypeOperate::IsConvertible< U1 const &, T1 >
			>
		>
	>
	constexpr Pair(U0 const &x, U1 const &y)
		: first(forward< U0 >(x)), second(forward< U1 >(y)) { }

	Pair &operator=(Pair const &P) {
		first = P.first;
		second = P.second;
		return *this;
	}

	template< typename U0, typename U1 >
	Pair &operator=(Pair< U0, U1 > const &P) {
		first = P.first;
		second = P.second;
		return *this;
	}

	Pair &operator=(
		Pair &&P
	) noexcept(
		TypeOperate::BooleanAnd<
			TypeOperate::HasNothrowMoveAssignment< T0 >,
			TypeOperate::HasNothrowMoveAssignment< T1 >
		>::value
	) {
		first = forward< T0 >(P.first);
		second = forward< T1 >(P.second);
		return *this;
	}

	template< typename U0, typename U1 >
	Pair &operator=(Pair< U0, U1 > &&P) {
		first = forward< U0 >(P.first);
		second = forward< U1 >(P.second);
		return *this;
	}

	Pair &swap(
		Pair &P
	) noexcept(
	noexcept(swap(first, P.first)) && noexcept(swap(second, P.second))
	) {
		swap(first, P.first);
		swap(second, P.second);
		return *this;
	}

	bool operator==(Pair const &Y) const {
		return first = Y.first && second = Y.second;
	}

	bool operator!=(Pair const &Y) const {
		return !(*this == Y);
	}

	bool operator<(Pair const &Y) const {
		return first < Y.first || (!(Y.first < first) && second < Y.second);
	}

	bool operator>(Pair const &Y) const {
		return Y < *this;
	}

	bool operator<=(Pair const &Y) const {
		return !(Y < *this);
	}

	bool operator>=(Pair const &Y) const {
		return !(*this < Y);
	}
};

template< typename T0, typename T1 >
inline void swap(
	Pair< T0, T1 > &X,
	Pair< T0, T1 > &Y
) noexcept(
noexcept(X.swap(Y))
) {
	X.swap(Y);
}

template< typename T0, typename T1 >
BR_PAIR_CONSTEXPR Pair<
	TypeOperate::Decay< T0 >,
	TypeOperate::Decay< T1 >
> make_pair(T0 && x, T1 && y) {
	return Pair< TypeOperate::Decay< T0 >, TypeOperate::Decay< T1 > >(forward< T0 >(x), forward< T1 >(y));
}

namespace Detail {

using namespace TypeOperate;

template< typename T >
struct TupleSize;

template< Size I, typename T >
struct TypeTupleElement;

template< typename T0, typename T1 >
struct TupleSize< Pair< T0, T1 > > : TypeOperate::IntegerConstant< Size, 2 > {};

template< typename T0, typename T1 >
struct TypeTupleElement< 0, Pair< T0, T1 > > : TypeOperate::TypeWrapper< T0 > {};

template< typename T0, typename T1 >
struct TypeTupleElement< 1, Pair< T0, T1 > > : TypeOperate::TypeWrapper< T1 > {};

template< Size I >
struct PairGet;

template<>
struct PairGet< 0 > {

};

}
// TODO
// template< Size I, typename T0, typename T1 > BR_PAIR_CONSTEXPR Detail::TupleElement< I, Pair< T0, T1 > >       & get(Pair< T0, T1 >       &) noexcept;
// template< Size I, typename T0, typename T1 > BR_PAIR_CONSTEXPR Detail::TupleElement< I, Pair< T0, T1 > > const & get(Pair< T0, T1 > const &) noexcept;
// template< Size I, typename T0, typename T1 > BR_PAIR_CONSTEXPR Detail::TupleElement< I, Pair< T0, T1 > >      && get(Pair< T0, T1 >      &&) noexcept;

} // namespace BR

#undef BR_PAIR_CONSTEXPR