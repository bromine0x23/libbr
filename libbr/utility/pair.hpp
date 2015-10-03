#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/is_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/piecewise_construct_tag.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename ... Tn >
class Tuple;

template< typename T0, typename T1 >
class Pair {
public:
	using First  = T0;
	using Second = T1;

public:
	First first;
	Second second;

public:
	constexpr Pair() : first(), second() { }

	template< typename U0, typename U1,
		typename = EnableIf<
			BooleanAnd<
				IsConvertible< U0 const &, T0 >,
				IsConvertible< U1 const &, T1 >
			>
		>
	>
	BR_CONSTEXPR_AFTER_CXX11 Pair(Pair< U0, U1 > const & P) : first(P.first), second(P.second) {}

	template< typename U0, typename U1,
		typename = EnableIf<
			BooleanAnd<
				IsConvertible< U0 const &, T0 >,
				IsConvertible< U1 const &, T1 >
			>
		>
	>
	BR_CONSTEXPR_AFTER_CXX11 Pair(Pair< U0, U1 > && P) : first(forward< U0 >(P.first)), second(forward< U1 >(P.second)) {}

	Pair(Pair const &) = default;

	Pair(Pair &&) = default;

	BR_CONSTEXPR_AFTER_CXX11 Pair(First const & x, Second const & y) : first(x), second(y) {}

	template< typename U0, typename U1,
		typename = EnableIf<
			BooleanAnd< IsConvertible< U0 const &, T0 >, IsConvertible< U1 const &, T1 > >
		>
	>
	BR_CONSTEXPR_AFTER_CXX11 Pair(U0 const & x, U1 const & y) : first(forward< U0 >(x)), second(forward< U1 >(y)) {}

	Pair & operator=(Pair const & P) {
		first = P.first;
		second = P.second;
		return *this;
	}

	template< typename U0, typename U1 >
	Pair & operator=(Pair< U0, U1 > const & P) {
		first = P.first;
		second = P.second;
		return *this;
	}

	Pair & operator=(
		Pair && P
	) noexcept(
		BooleanAnd< HasNothrowMoveAssignment< T0 >, HasNothrowMoveAssignment< T1 > >::value
	) {
		first = forward< T0 >(P.first);
		second = forward< T1 >(P.second);
		return *this;
	}

	template< typename U0, typename U1 >
	Pair & operator=(Pair< U0, U1 > && P) {
		first = forward< U0 >(P.first);
		second = forward< U1 >(P.second);
		return *this;
	}

	Pair & swap(
		Pair & P
	) noexcept(
		BooleanAnd< IsNothrowSwappable< First >, IsNothrowSwappable< Second > >::value
	) {
		swap(first, P.first);
		swap(second, P.second);
		return *this;
	}
};

template< typename T0, typename T1 >
inline BR_CONSTEXPR_AFTER_CXX11 bool operator==(Pair< T0, T1 > const & X, Pair< T0, T1 > const & Y) {
	return X.first = Y.first && Y.second = Y.second;
}

template< typename T0, typename T1 >
inline BR_CONSTEXPR_AFTER_CXX11 bool operator!=(Pair< T0, T1 > const & X, Pair< T0, T1 > const & Y) {
	return !(X == Y);
}

template< typename T0, typename T1 >
inline BR_CONSTEXPR_AFTER_CXX11 bool operator<(Pair< T0, T1 > const & X, Pair< T0, T1 > const & Y) {
	return X.first < Y.first || (!(Y.first < X.first) && X.second < Y.second);
}

template< typename T0, typename T1 >
inline BR_CONSTEXPR_AFTER_CXX11 bool operator>(Pair< T0, T1 > const & X, Pair< T0, T1 > const & Y) {
	return Y < X;
}

template< typename T0, typename T1 >
inline BR_CONSTEXPR_AFTER_CXX11 bool operator<=(Pair< T0, T1 > const & X, Pair< T0, T1 > const & Y) {
	return !(Y < X);
}

template< typename T0, typename T1 >
inline BR_CONSTEXPR_AFTER_CXX11 bool operator>=(Pair< T0, T1 > const & X, Pair< T0, T1 > const & Y) {
	return !(X < Y);
}

template< typename T0, typename T1, typename = EnableIf< BooleanAnd< IsSwappable<T0>, IsSwappable<T1> > > >
inline void swap(
	Pair< T0, T1 > & X,
	Pair< T0, T1 > & Y
) noexcept(IsNothrowSwappable< Pair< T0, T1 > >::value) {
	X.swap(Y);
}

template< typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 Pair<
	Decay< T0 >,
	Decay< T1 >
> make_pair(T0 && x, T1 && y) {
	return Pair< Decay< T0 >, Decay< T1 > >(forward< T0 >(x), forward< T1 >(y));
}

namespace Detail {
namespace Utility {

template< typename T >
struct IsTupleLike;

template< typename T0, typename T1 >
struct IsTupleLike< Pair< T0, T1 > > : BooleanTrue {};

template< Size I >
struct PairGetter;

template<>
struct PairGetter<0> {
	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 T0 & operator()(Pair< T0, T1 > & P) const noexcept {
		return P.first;
	}

	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 T0 const & operator()(Pair< T0, T1 > const & P) const noexcept {
		return P.first;
	}

	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 T0 && operator()(Pair< T0, T1 > && P) const noexcept {
		return forward(P.first);
	}
};

template<>
struct PairGetter<1> {
	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 T1 & operator()(Pair< T0, T1 > & P) const noexcept {
		return P.second;
	}

	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 T1 const & operator()(Pair< T0, T1 > const & P) const noexcept {
		return P.second;
	}

	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 T1 && operator()(Pair< T0, T1 > && P) const noexcept {
		return forward(P.second);
	}
};

} // namespace Utility
} // namespace Detail

template< typename T >
struct TupleSize;

template< typename T0, typename T1 >
struct TupleSize< Pair< T0, T1 > > : IntegerConstant< Size, 2 > {};

template< Size I, typename T >
struct TypeTupleElement;

template< typename T0, typename T1 >
struct TypeTupleElement< 0, Pair< T0, T1 > > : TypeWrapper<T0> {};

template< typename T0, typename T1 >
struct TypeTupleElement< 1, Pair< T0, T1 > > : TypeWrapper<T1> {};

template< Size I, typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 auto get(Pair< T0, T1 > & P) noexcept -> decltype(Detail::Utility::PairGetter<I>()(P)) {
	return Detail::Utility::PairGetter<I>()(P);
}

template< Size I, typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 auto get(Pair< T0, T1 > const & P) noexcept -> decltype(Detail::Utility::PairGetter<I>()(P)) {
	return Detail::Utility::PairGetter<I>()(P);
}

template< Size I, typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 auto get(Pair< T0, T1 > && P) noexcept -> decltype(Detail::Utility::PairGetter<I>()(move(P))) {
	return Detail::Utility::PairGetter<I>()(move(P));
}

#if defined(BR_AFTER_CPP11)

template< typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 T0 & get(Pair< T0, T1 > & P) noexcept {
	return Detail::Utility::PairGetter<0>()(P);
}

template< typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 T0 const & get(Pair< T0, T1 > const & P) noexcept {
	return Detail::Utility::PairGetter<0>()(P);
}

template< typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 T0 && get(Pair< T0, T1 > && P) noexcept {
	return Detail::Utility::PairGetter<0>()(move(P));
}

template< typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 T0 & get(Pair< T1, T0 > & P) noexcept {
	return Detail::Utility::PairGetter<1>()(P);
}

template< typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 T0 const & get(Pair< T1, T0 > const & P) noexcept {
	return Detail::Utility::PairGetter<1>()(P);
}

template< typename T0, typename T1 >
BR_CONSTEXPR_AFTER_CXX11 T0 && get(Pair< T1, T0 > && P) noexcept {
	return Detail::Utility::PairGetter<1>()(move(P));
}

#endif

} // namespace BR