#pragma once

#include <libbr/config.hpp>
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
#include <libbr/type_transform/decay.hpp>
#include <libbr/utility/conjunction.hpp>
#include <libbr/utility/enable_if.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace Containers {

template< typename TFirst, typename TSecond >
class Pair;

template< typename TFirst, typename TSecond >
constexpr auto make_pair(TFirst && first, TSecond && second) -> Pair< Decay<TFirst>, Decay<TSecond> > {
	return Pair< Decay<TFirst>, Decay<TSecond> >(forward<TFirst>(first), forward<TSecond>(second));
}

template< typename TFirst, typename TSecond >
constexpr inline auto swap(
	Pair<TFirst, TSecond>& x,
	Pair<TFirst, TSecond>& y
) noexcept(
	is_nothrow_swappable<TFirst> && is_nothrow_swappable<TSecond>
) -> EnableIf< Conjunction< IsSwappable<TFirst>, IsSwappable<TSecond> > > {
	x.swap(y);
}

} // namespace Containers



inline namespace Containers {

template< typename TFirst, typename TSecond = TFirst >
class Pair {

public:
	using First  = TFirst;
	using Second = TSecond;

public:
	First  first;
	Second second;

private:
	template< typename TOtherFirst, typename TOtherSecond >
	using IsParticipateOverload = Conjunction< IsConvertible< TOtherFirst, First >, IsConvertible< TOtherSecond, Second > >;

public:
	template< bool dummy = true, typename = EnableIf< Conjunction< BooleanConstant<dummy>, HasDefaultConstructor<First>, HasDefaultConstructor<Second> > > >
	constexpr Pair(
	) noexcept(
		has_nothrow_default_constructor<First> && has_nothrow_default_constructor<Second>
	): first(), second() {
	}

	Pair(Pair const &) noexcept(has_nothrow_copy_constructor<First> && has_nothrow_copy_constructor<Second>) = default;

	Pair(Pair &&) noexcept(has_nothrow_move_constructor<First> && has_nothrow_move_constructor<Second>) = default;

	constexpr Pair(
		First const & x,
		Second const & y
	) noexcept(
		has_nothrow_copy_constructor<First> && has_nothrow_copy_constructor<Second>
	) : first(x), second(y) {
	}

	template< typename TOtherFirst, typename TOtherSecond, typename = EnableIf< IsParticipateOverload< TOtherFirst, TOtherSecond > > >
	constexpr Pair(
		Pair< TOtherFirst, TOtherSecond > const & pair
	) : first(pair.first), second(pair.second) {
	}

	template< typename TOtherFirst, typename TOtherSecond >
	constexpr Pair(
		Pair< TOtherFirst, TOtherSecond > && pair,
		EnableIf< Conjunction< IsConvertible< TOtherFirst, First >, IsConvertible< TOtherSecond, Second > > > * = nullptr
	) : first(forward<TOtherFirst>(pair.first)), second(forward<TOtherSecond>(pair.second)) {
	}

	template< typename TOtherFirst, typename TOtherSecond, typename = EnableIf< IsParticipateOverload< TOtherFirst, TOtherSecond > > >
	constexpr Pair(
		TOtherFirst && x,
		TOtherSecond && y
	) : first(forward<TOtherFirst>(x)), second(forward<TOtherSecond>(y)) {
	}

	~Pair() noexcept = default;

	constexpr auto operator=(
		Pair const & pair
	) noexcept(
		has_nothrow_copy_assignment<First> && has_nothrow_copy_assignment<Second>
	) -> Pair & {
		first = pair.first;
		second = pair.second;
		return *this;
	}

	constexpr auto operator=(
		Pair && pair
	) noexcept(
		has_nothrow_move_assignment<First> && has_nothrow_move_assignment<Second>
	) -> Pair & {
		first = forward<First>(pair.first);
		second = forward<Second>(pair.second);
		return *this;
	}

	template< typename TOtherFirst, typename TOtherSecond, typename = EnableIf< Conjunction< IsAssignable< First &, TOtherFirst const & >, IsAssignable< Second &, TOtherSecond const & > > > >
	constexpr auto operator=(
		Pair< TOtherFirst, TOtherSecond > const & pair
	) noexcept(
		is_nothrow_assignable< First &, TOtherFirst const & > && is_nothrow_assignable< Second &, TOtherSecond const & >
	) -> Pair & {
		first = pair.first;
		second = pair.second;
		return *this;
	}

	template< typename TOtherFirst, typename TOtherSecond, typename = EnableIf< Conjunction< IsAssignable< First &, TOtherFirst >, IsAssignable< Second &, TOtherSecond > > > >
	constexpr auto operator=(
		Pair< TOtherFirst, TOtherSecond > && pair
	) noexcept(
		is_nothrow_assignable< First &, TOtherFirst > && is_nothrow_assignable< Second &, TOtherSecond >
	) -> Pair & {
		first = forward<First>(pair.first);
		second = forward<Second>(pair.second);
		return *this;
	}

	constexpr auto swap(
		Pair & pair
	) noexcept(
		is_nothrow_swappable<First> && is_nothrow_swappable<Second>
	) -> Pair & {
		using Utility::swap;
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
}; // class Pair< TFirst, TSecond >



} // namespace Containers

} // namespace BR