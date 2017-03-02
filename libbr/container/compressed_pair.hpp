#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/tuple_forward.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/make_integral_sequence.hpp>
#include <libbr/type_traits/remove_reference.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/integral_sequence.hpp>
#include <libbr/utility/piecewise_construct_tag.hpp>

namespace BR {

inline namespace Container {

template< typename TFirst, typename TSecond >
class CompressedPair;

template< typename T0, typename T1 >
struct TupleSize< CompressedPair< T0, T1 > > : public IntegralConstant< Size, 2 > {};

template< typename T0, typename T1 >
struct TypeTupleElement< 0, CompressedPair< T0, T1 > > : public TypeWrapper<T0> {};

template< typename T0, typename T1 >
struct TypeTupleElement< 1, CompressedPair< T0, T1 > > : public TypeWrapper<T1> {};

template< Size I, typename T0, typename T1 > constexpr auto get(CompressedPair< T0, T1 >        & P) noexcept -> TupleElement< I, CompressedPair< T0, T1 > >        & { return P.template get<I>(); }
template< Size I, typename T0, typename T1 > constexpr auto get(CompressedPair< T0, T1 > const  & P) noexcept -> TupleElement< I, CompressedPair< T0, T1 > > const  & { return P.template get<I>(); }
template< Size I, typename T0, typename T1 > constexpr auto get(CompressedPair< T0, T1 >       && P) noexcept -> TupleElement< I, CompressedPair< T0, T1 > >       && { return P.template get<I>(); }
template< Size I, typename T0, typename T1 > constexpr auto get(CompressedPair< T0, T1 > const && P) noexcept -> TupleElement< I, CompressedPair< T0, T1 > > const && { return P.template get<I>(); }

template< typename T0, typename T1 > constexpr auto get(CompressedPair< T0, T1 >        & P) noexcept -> T0        & { return P.template get<0>(); }
template< typename T0, typename T1 > constexpr auto get(CompressedPair< T0, T1 > const  & P) noexcept -> T0 const  & { return P.template get<0>(); }
template< typename T0, typename T1 > constexpr auto get(CompressedPair< T0, T1 >       && P) noexcept -> T0       && { return P.template get<0>(); }
template< typename T0, typename T1 > constexpr auto get(CompressedPair< T0, T1 > const && P) noexcept -> T0 const && { return P.template get<0>(); }

template< typename T0, typename T1 > constexpr auto get(CompressedPair< T1, T0 >        & P) noexcept -> T0        & { return P.template get<1>(); }
template< typename T0, typename T1 > constexpr auto get(CompressedPair< T1, T0 > const  & P) noexcept -> T0 const  & { return P.template get<1>(); }
template< typename T0, typename T1 > constexpr auto get(CompressedPair< T1, T0 >       && P) noexcept -> T0       && { return P.template get<1>(); }
template< typename T0, typename T1 > constexpr auto get(CompressedPair< T1, T0 > const && P) noexcept -> T0 const && { return P.template get<1>(); }

} // namespace Container



namespace Detail {
namespace Container {

template<
	typename TFirst,
	typename TSecond,
	bool is_first_derivable  = BooleanAnd< IsEmpty<TFirst>, NotFinal<TFirst> >{},
	bool is_second_derivable = BooleanAnd< IsEmpty<TSecond>, NotFinal<TSecond> >{}
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

	BR_CONSTEXPR_AFTER_CXX11 auto first() noexcept -> FirstReference {
		return m_first;
	}

	constexpr auto first() const noexcept -> FirstConstReference {
		return m_first;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto second() noexcept -> SecondReference {
		return m_second;
	}

	constexpr auto second() const noexcept -> SecondConstReference {
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

	BR_CONSTEXPR_AFTER_CXX11 auto first() noexcept -> FirstReference {
		return *this;
	}

	constexpr auto first() const noexcept -> FirstConstReference {
		return *this;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto second() noexcept -> SecondReference {
		return m_second;
	}

	constexpr auto second() const noexcept -> SecondConstReference {
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

	CompressedPairBasic(First first, Second second) : Second(second), m_first(forward<First>(first)) {
	}

	template< typename... T0, typename... T1, Size... I0, Size... I1 >
	CompressedPairBasic(
		PiecewiseConstructTag _tag, Tuple<T0...> t0, Tuple<T1...> t1, IndexSequence<I0...> _i0, IndexSequence<I1...> _i1
	) : Second(forward<T0>(get<I1>(t1))...), m_first(forward<T0>(get<I0>(t0))...) {
	}

	~CompressedPairBasic() = default;

	auto operator=(CompressedPairBasic const &) -> CompressedPairBasic & = default;

	auto operator=(CompressedPairBasic &&) -> CompressedPairBasic & = default;

	BR_CONSTEXPR_AFTER_CXX11 auto first() noexcept -> FirstReference {
		return m_first;
	}

	constexpr auto first() const noexcept -> FirstConstReference {
		return m_first;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto second() noexcept -> SecondReference {
		return *this;
	}

	constexpr auto second() const noexcept -> SecondConstReference {
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

	BR_CONSTEXPR_AFTER_CXX11 auto first() noexcept -> FirstReference {
		return *this;
	}

	constexpr auto first() const noexcept -> FirstConstReference {
		return *this;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto second() noexcept -> SecondReference {
		return *this;
	}

	constexpr auto second() const noexcept -> SecondConstReference {
		return *this;
	}

	void swap(CompressedPairBasic & pair) noexcept {
	}
}; // class CompressedPairBasic< TFirst, TSecond, true, true >

template< Size I >
struct CompressedPairGetter;

template<>
struct CompressedPairGetter<0> {
	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 auto operator()(CompressedPair< T0, T1 > & p) const noexcept -> T0 & {
		return p.first();
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(CompressedPair< T0, T1 > const & p) const noexcept -> T0 const & {
		return p.first();
	}

	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 auto operator()(CompressedPair< T0, T1 > && p) const noexcept -> T0 && {
		return move(p.first());
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(CompressedPair< T0, T1 > const && p) const noexcept -> T0 const && {
		return move(p.first());
	}
};

template<>
struct CompressedPairGetter<1> {
	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 auto operator()(CompressedPair< T0, T1 > & p) const noexcept -> T1 & {
		return p.second();
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(CompressedPair< T0, T1 > const & p) const noexcept -> T1 const & {
		return p.second();
	}

	template< typename T0, typename T1 >
	BR_CONSTEXPR_AFTER_CXX11 auto operator()(CompressedPair< T0, T1 > && p) const noexcept -> T1 && {
		return move(p.second());
	}

	template< typename T0, typename T1 >
	constexpr auto operator()(CompressedPair< T0, T1 > const && p) const noexcept -> T1 const && {
		return move(p.second());
	}
};

} // namespace Container
} // namespace Detail

inline namespace Container {

template< typename TFirst, typename TSecond >
class CompressedPair : private Detail::Container::CompressedPairBasic< TFirst, TSecond > {
	using Base = Detail::Container::CompressedPairBasic< TFirst, TSecond >;

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

	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()       &  noexcept -> TupleElement< I, CompressedPair >       &  { return Detail::Container::CompressedPairGetter<I>{}(*this); }
	template< Size I > constexpr                auto get() const &  noexcept -> TupleElement< I, CompressedPair > const &  { return Detail::Container::CompressedPairGetter<I>{}(*this); }
	template< Size I > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> TupleElement< I, CompressedPair >       && { return Detail::Container::CompressedPairGetter<I>{}(*this); }
	template< Size I > constexpr                auto get() const && noexcept -> TupleElement< I, CompressedPair > const && { return Detail::Container::CompressedPairGetter<I>{}(*this); }

	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()        & noexcept -> T        & { return get<T>(*this); }
	template< typename T > constexpr                auto get() const  & noexcept -> T const  & { return get<T>(*this); }
	template< typename T > BR_CONSTEXPR_AFTER_CXX11 auto get()       && noexcept -> T       && { return get<T>(*this); }
	template< typename T > constexpr                auto get() const && noexcept -> T const && { return get<T>(*this); }

	void swap(CompressedPair & pair) noexcept(BooleanAnd< IsNothrowSwappable<First>, IsNothrowSwappable<Second> >()()) {
		Base::swap(pair);
	}

}; // class CompressedPair< TFirst, TSecond >

} // namespace Container

} // namespace BR