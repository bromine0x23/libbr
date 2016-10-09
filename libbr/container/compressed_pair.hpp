#pragma once

#include <libbr/config.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/make_integral_sequence.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/integral_sequence.hpp>
#include <libbr/utility/piecewise_construct_tag.hpp>

namespace BR {

namespace Detail {
namespace Container {

template<
	typename TFirst,
	typename TSecond,
	bool is_first_derivable  = BooleanAnd< IsEmpty<TFirst>, NotFinal<TFirst> >::value,
	bool is_second_derivable = BooleanAnd< IsEmpty<TSecond>, NotFinal<TSecond> >::value
>
class CompressedPairBasic;

template< typename TFirst, typename TSecond >
class CompressedPairBasic< TFirst, TSecond, false, false > {
public:
	using First = TFirst;

	using Second = TSecond;

	using FirstReference = RemoveReference<First> &;

	using SecondReference = RemoveReference<Second> &;

	using FirstConstReference = RemoveReference<First> const &;

	using SecondConstReference = RemoveReference<Second> const &;

	CompressedPairBasic() {
	};

	CompressedPairBasic(CompressedPairBasic const &) = default;

	CompressedPairBasic(CompressedPairBasic &&) = default;

	explicit CompressedPairBasic(First first) : m_first(forward<First>(first)) {
	}

	explicit CompressedPairBasic(Second second) : m_second(forward<Second>(second)) {
	}

	CompressedPairBasic(First first, Second second) : m_first(forward<First>(first)), m_second(forward<Second>(second)) {
	}

	template< typename... T0, typename... T1, Size... I0, Size... I1 >
	CompressedPairBasic(
		PiecewiseConstructTag _tag, Tuple<T0...> t0, Tuple<T1...> t1, IndexSequence<I0...> _i0, IndexSequence<I1...> _i1
	) : m_first(forward<T0>(get<I0>(t0))...), m_second(forward<T0>(get<I1>(t1))...) {
	}

	~CompressedPairBasic() = default;

	auto operator=(CompressedPairBasic const &) -> CompressedPairBasic & = default;

	auto operator=(CompressedPairBasic &&) -> CompressedPairBasic & = default;

	auto first() noexcept -> FirstReference {
		return m_first;
	}

	auto first() const noexcept -> FirstConstReference {
		return m_first;
	}

	auto second() noexcept -> SecondReference {
		return m_second;
	}

	auto second() const noexcept -> SecondConstReference {
		return m_second;
	}

	void swap(CompressedPairBasic & pair) noexcept(BooleanAnd< IsNothrowSwappable<First>, IsNothrowSwappable<Second> >()()) {
		using BR::swap;
		swap(m_first, pair.m_first);
		swap(m_second, pair.m_second);
	}

private:
	First  m_first;
	Second m_second;
}; // class CompressedPairBasic< TFirst, TSecond, false, false >

template< typename TFirst, typename TSecond >
class CompressedPairBasic< TFirst, TSecond, true, false > : private TFirst {
public:
	using First = TFirst;

	using Second = TSecond;

	using FirstReference = First &;

	using SecondReference = RemoveReference<Second> &;

	using FirstConstReference = First const &;

	using SecondConstReference = RemoveReference<Second> const &;

public:
	CompressedPairBasic() {
	};

	CompressedPairBasic(CompressedPairBasic const &) = default;

	CompressedPairBasic(CompressedPairBasic &&) = default;

	explicit CompressedPairBasic(First first) : First(first) {
	}

	explicit CompressedPairBasic(Second second) : m_second(forward<Second>(second)) {
	}

	CompressedPairBasic(First first, Second second) : First(first), m_second(forward<Second>(second)) {
	}

	template< typename... T0, typename... T1, Size... I0, Size... I1 >
	CompressedPairBasic(
		PiecewiseConstructTag _tag, Tuple<T0...> t0, Tuple<T1...> t1, IndexSequence<I0...> _i0, IndexSequence<I1...> _i1
	) : First(forward<T0>(get<I0>(t0))...), m_second(forward<T0>(get<I1>(t1))...) {
	}

	~CompressedPairBasic() = default;

	auto operator=(CompressedPairBasic const &) -> CompressedPairBasic & = default;

	auto operator=(CompressedPairBasic &&) -> CompressedPairBasic & = default;

	auto first() noexcept -> FirstReference {
		return *this;
	}

	auto first() const noexcept -> FirstConstReference {
		return *this;
	}

	auto second() noexcept -> SecondReference {
		return m_second;
	}

	auto second() const noexcept -> SecondConstReference {
		return m_second;
	}

	void swap(CompressedPairBasic & pair) noexcept(IsNothrowSwappable<Second>()()) {
		using BR::swap;
		swap(m_second, pair.m_second);
	}

private:
	Second m_second;

}; // class CompressedPairBasic< TFirst, TSecond, true, false >

template< typename TFirst, typename TSecond >
class CompressedPairBasic< TFirst, TSecond, false, true > : private TSecond {
public:
	using First = TFirst;

	using Second = TSecond;

	using FirstReference = RemoveReference<First> &;

	using SecondReference = Second &;

	using FirstConstReference = RemoveReference<First> const &;

	using SecondConstReference = Second const &;

public:
	CompressedPairBasic() {
	};

	CompressedPairBasic(CompressedPairBasic const &) = default;

	CompressedPairBasic(CompressedPairBasic &&) = default;

	explicit CompressedPairBasic(First first) : m_first(forward<First>(first)) {
	}

	explicit CompressedPairBasic(Second second) : Second(second) {
	}

	CompressedPairBasic(First first, Second second) : m_first(forward<First>(first)), Second(second) {
	}

	template< typename... T0, typename... T1, Size... I0, Size... I1 >
	CompressedPairBasic(
		PiecewiseConstructTag _tag, Tuple<T0...> t0, Tuple<T1...> t1, IndexSequence<I0...> _i0, IndexSequence<I1...> _i1
	) : Second(forward<T0>(get<I1>(t1))...), m_first(forward<T0>(get<I0>(t0))...) {
	}

	~CompressedPairBasic() = default;

	auto operator=(CompressedPairBasic const &) -> CompressedPairBasic & = default;

	auto operator=(CompressedPairBasic &&) -> CompressedPairBasic & = default;

	auto first() noexcept -> FirstReference {
		return m_first;
	}

	auto first() const noexcept -> FirstConstReference {
		return m_first;
	}

	auto second() noexcept -> SecondReference {
		return *this;
	}

	auto second() const noexcept -> SecondConstReference {
		return *this;
	}

	void swap(CompressedPairBasic & pair) noexcept(IsNothrowSwappable<First>()()) {
		using BR::swap;
		swap(m_first, pair.m_first);
	}

private:
	First m_first;

}; // class CompressedPairBasic< TFirst, TSecond, false, true >

template< typename TFirst, typename TSecond >
class CompressedPairBasic< TFirst, TSecond, true, true > : private TFirst, private TSecond {
public:
	using First = TFirst;

	using Second = TSecond;

	using FirstReference = First &;

	using SecondReference = Second &;

	using FirstConstReference = First const &;

	using SecondConstReference = Second const &;

	CompressedPairBasic() {
	};

	CompressedPairBasic(CompressedPairBasic const &) = default;

	CompressedPairBasic(CompressedPairBasic &&) = default;

	explicit CompressedPairBasic(First first) : First(first) {
	}

	explicit CompressedPairBasic(Second second) : Second(second) {
	}

	CompressedPairBasic(First first, Second second) : First(first), Second(second) {
	}

	template< typename... T0, typename... T1, Size... I0, Size... I1 >
	CompressedPairBasic(
		PiecewiseConstructTag _tag, Tuple<T0...> t0, Tuple<T1...> t1, IndexSequence<I0...> _i0, IndexSequence<I1...> _i1
	) : First(forward<T0>(get<I0>(t0))...), Second(forward<T0>(get<I1>(t1))...) {
	}

	~CompressedPairBasic() = default;

	auto operator=(CompressedPairBasic const &) -> CompressedPairBasic & = default;

	auto operator=(CompressedPairBasic &&) -> CompressedPairBasic & = default;

	auto first() noexcept -> FirstReference {
		return *this;
	}

	auto first() const noexcept -> FirstConstReference {
		return *this;
	}

	auto second() noexcept -> SecondReference {
		return *this;
	}

	auto second() const noexcept -> SecondConstReference {
		return *this;
	}

	void swap(CompressedPairBasic & pair) noexcept {
	}
};

template< typename TFirst, typename TSecond >
using CompressedPair = CompressedPairBasic< TFirst, TSecond >;

} // namespace Container
} // namespace Detail

template< typename TFirst, typename TSecond >
class CompressedPair : private Detail::Container::CompressedPair< TFirst, TSecond > {
	using Base = Detail::Container::CompressedPair< TFirst, TSecond >;

public:
	using First = TFirst;

	using Second = TSecond;

	using FirstReference = typename Base::FirstReference;

	using SecondReference = typename Base::SecondReference;

	using FirstConstReference = typename Base::FirstConstReference;

	using SecondConstReference = typename Base::SecondConstReference;

public:
	CompressedPair() {
	}

	CompressedPair(CompressedPair const &) = default;

	CompressedPair(CompressedPair &&) = default;

	explicit CompressedPair(First first) : Base(forward<First>(first)) {
	}

	explicit CompressedPair(Second second) : Base(forward<Second>(second)) {
	}

	CompressedPair(First first, Second second) : Base(forward<First>(first), forward<Second>(second)) {
	}

	template< typename... TArgs0, typename... TArgs1 >
	CompressedPair(
		PiecewiseConstructTag _tag, Tuple<TArgs0...> args0, Tuple<TArgs1...> args1
	) : Base(
		piecewise_construct_tag, move(args0), move(args1), MakeIndexSequence< 0, sizeof...(TArgs0) >(), MakeIndexSequence< 0, sizeof...(TArgs1) >()
	) {
	}

	~CompressedPair() = default;

	auto operator=(CompressedPair const &) -> CompressedPair & = default;

	auto operator=(CompressedPair &&) -> CompressedPair & = default;

	auto first() noexcept -> FirstReference {
		return Base::first();
	}

	auto first() const noexcept -> FirstConstReference {
		return Base::first();
	}

	auto second() noexcept -> SecondReference {
		return Base::second();
	}

	auto second() const noexcept -> SecondConstReference {
		return Base::second();
	}

	void swap(CompressedPair & pair) noexcept(BooleanAnd< IsNothrowSwappable<First>, IsNothrowSwappable<Second> >()()) {
		Base::swap(pair);
	}

};

} // namespace BR