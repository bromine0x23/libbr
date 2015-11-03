#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_traits/has_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assign.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/piecewise_construct_tag.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename TFirst, typename TSecond >
class Pair;

template< typename TFirst, typename TSecond >
constexpr auto make_pair(TFirst && x, TSecond && y) -> Pair< Decay<TFirst>, Decay<TSecond> > {
	return Pair< Decay<TFirst>, Decay<TSecond> >(forward<TFirst>(x), forward<TSecond>(y));
}

template< typename ... Tn >
class Tuple;

template< typename T >
struct TypeTupleSize;

template< typename T0, typename T1 >
struct TypeTupleSize< Pair< T0, T1 > > : IntegerConstant< Size, 2 > {
};

template< Size I, typename T >
struct TypeTupleElement;

template< typename T0, typename T1 >
struct TypeTupleElement< 0, Pair< T0, T1 > > : TypeWrapper<T0> {
};

template< typename T0, typename T1 >
struct TypeTupleElement< 1, Pair< T0, T1 > > : TypeWrapper<T1> {
};

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > & P) noexcept -> TypeUnwrap< TypeTupleElement< I, Pair< T0, T1 > > > &;

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > const & P) noexcept -> TypeUnwrap< TypeTupleElement< I, Pair< T0, T1 > > > const &;

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > && P) noexcept -> TypeUnwrap< TypeTupleElement< I, Pair< T0, T1 > > > &&;

template< typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > & P) noexcept -> T0 & {
	return get<0>(P);
}

template< typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > const & P) noexcept -> T0 const & {
	return get<0>(P);
}

template< typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > && P) noexcept -> T0 && {
	return get<0>(move(P));
}

template< typename T0, typename T1 >
constexpr auto get(Pair< T1, T0 > & P) noexcept -> T0 & {
	return get<1>(P);
}

template< typename T0, typename T1 >
constexpr auto get(Pair< T1, T0 > const & P) noexcept -> T0 const & {
	return get<1>(P);
}

template< typename T0, typename T1 >
constexpr auto get(Pair< T1, T0 > && P) noexcept -> T0 && {
	return get<1>(move(P));
}

template< typename TFirst, typename TSecond >
class Pair {
public:
	using First = TFirst;

	using Second = TSecond;

public:
	First first;
	Second second;

private:

	template< typename TOtherFirst, typename TOtherSecond >
	using IsConstructible = BooleanAnd< IsConvertible< TOtherFirst const &, First >, IsConvertible< TOtherSecond const &, Second > >;

public:
	template< typename _TDummy = EnableIf< BooleanAnd< HasDefaultConstructor<First>, HasDefaultConstructor<Second> > > >
	constexpr Pair() : first(), second() {
	}

	constexpr Pair(Pair const &) = default;

	constexpr Pair(Pair &&) = default;

	constexpr Pair(First const & x, Second const & y) : first(x), second(y) {
	}

	template< typename TOtherFirst, typename TOtherSecond, typename _TDummy = EnableIf< IsConstructible< TOtherFirst, TOtherSecond > > >
	constexpr Pair(Pair< TOtherFirst, TOtherSecond > const & P) : first(P.first), second(P.second) {
	}

	template< typename TOtherFirst, typename TOtherSecond, typename _TDummy = EnableIf< IsConstructible< TOtherFirst, TOtherSecond > > >
	constexpr Pair(Pair< TOtherFirst, TOtherSecond > && P) : first(forward<TOtherFirst>(P.first)), second(forward<TOtherSecond>(P.second)) {
	}

	template< typename TOtherFirst, typename TOtherSecond, typename _TDummy = EnableIf< IsConstructible< TOtherFirst, TOtherSecond > > >
	constexpr Pair(TOtherFirst && x, TOtherSecond && y) : first(forward<TOtherFirst>(x)), second(forward<TOtherSecond>(y)) {
	}

	~Pair() noexcept = default;

	auto operator=(Pair const & P) -> Pair & {
		first = P.first;
		second = P.second;
		return *this;
	}

	template< typename TOtherFirst, typename TOtherSecond >
	auto operator=(Pair< TOtherFirst, TOtherSecond > const & P) -> Pair & {
		first = P.first;
		second = P.second;
		return *this;
	}

	auto operator=(Pair && P) noexcept(BooleanAnd< HasNothrowMoveAssign<First>, HasNothrowMoveAssign<Second> >()) -> Pair & {
		first = forward<First>(P.first);
		second = forward<Second>(P.second);
		return *this;
	}

	template< typename TOtherFirst, typename TOtherSecond >
	auto operator=(Pair< TOtherFirst, TOtherSecond > && P) -> Pair & {
		first = forward<TOtherFirst>(P.first);
		second = forward<TOtherSecond>(P.second);
		return *this;
	}

	auto swap(Pair & P) noexcept(noexcept(swap(first, P.first)) && noexcept(swap(second, P.second))) -> Pair & {
		swap(first, P.first);
		swap(second, P.second);
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

	template< Size I >
	auto get() noexcept -> decltype(BR::get<I>(*this)) {
		return BR::get<I>(*this);
	}

	template< Size I >
	constexpr auto get() const noexcept -> decltype(BR::get<I>(*this)) {
		return BR::get<I>(*this);
	}

	template< typename T >
	auto get() noexcept -> decltype(BR::get<T>(*this)) {
		return BR::get<T>(*this);
	}

	template< typename T >
	constexpr auto get() const noexcept -> decltype(BR::get<T>(*this)) {
		return BR::get<T>(*this);
	}

}; // class Pair< TFirst, TSecond >

template< typename TFirst, typename TSecond >
inline void swap(Pair< TFirst, TSecond > & x, Pair< TFirst, TSecond > & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

namespace Detail {
namespace Container {

template< typename T >
struct IsTupleLike;

template< typename T0, typename T1 >
struct IsTupleLike< Pair< T0, T1 > > : BooleanTrue {
};

template< Size I >
struct PairGetter;

template<>
struct PairGetter<0> {
	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > & P) const noexcept -> T0 & {
		return P.first;
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > const & P) const noexcept -> T0 const & {
		return P.first;
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > && P) const noexcept -> T0 && {
		return move(P.first);
	}
};

template<>
struct PairGetter<1> {
	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > & P) const noexcept -> T1 & {
		return P.second;
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > const & P) const noexcept -> T1 const & {
		return P.second;
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(Pair< T0, T1 > && P) const noexcept -> T1 && {
		return move(P.second);
	}
};

} // namespace Container
} // namespace Detail

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > & P) noexcept -> TypeUnwrap< TypeTupleElement< I, Pair< T0, T1 > > > & {
	return Detail::Container::PairGetter<I>()(P);
}

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > const & P) noexcept -> TypeUnwrap< TypeTupleElement< I, Pair< T0, T1 > > > const & {
	return Detail::Container::PairGetter<I>()(P);
}

template< Size I, typename T0, typename T1 >
constexpr auto get(Pair< T0, T1 > && P) noexcept -> TypeUnwrap< TypeTupleElement< I, Pair< T0, T1 > > > && {
	return Detail::Container::PairGetter<I>()(move(P));
}

} // namespace BR