#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_empty.hpp>
#include <libbr/type_operate/is_final.hpp>
#include <libbr/type_operate/is_nothrow_copy_constructible.hpp>
#include <libbr/type_operate/is_nothrow_move_constructible.hpp>
#include <libbr/type_operate/is_nothrow_swappable.hpp>
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

namespace Detail {
namespace CompressedPair {

template< typename TFirst, typename TSecond >
class CommonPair {
public:
	using First  = TFirst;
	using Second = TSecond;

	using FirstReference  = RemoveReference<First>  &;
	using SecondReference = RemoveReference<Second> &;

	using FirstConstReference  = RemoveReference<First>  const &;
	using SecondConstReference = RemoveReference<Second> const &;

	CommonPair() {};

	explicit CommonPair(First first) : m_first(forward<First>(first)) {}

	explicit CommonPair(Second second) : m_second(forward<Second>(second)) {}

	CommonPair(First first, Second second) : m_first(forward<First>(first)), m_second(forward<Second>(second)) {}

	CommonPair(CommonPair const &) = default;

	CommonPair(CommonPair &&) = default;

	CommonPair & operator=(CommonPair const &) = default;

	CommonPair & operator=(CommonPair &&) = default;

	FirstReference      first()       noexcept { return m_first; }
	FirstConstReference first() const noexcept { return m_first; }

	SecondReference      second()       noexcept { return m_second; }
	SecondConstReference second() const noexcept { return m_second; }

	void swap(CommonPair & pair) noexcept(
		BooleanAnd<
			IsNothrowSwappable<First>,
			IsNothrowSwappable<Second>
		>::value
	) {
		using ::BR::swap;
		swap(m_first, pair.m_first);
		swap(m_second, pair.m_second);
	}

private:
	First  m_first;
	Second m_second;
}; // class CommonPair< TFirst, TSecond >

template< typename TFirst, typename TSecond >
class FirstBasePair : private TFirst {
public:
	using First  = TFirst;
	using Second = TSecond;

	using FirstReference  = First  &;
	using SecondReference = RemoveReference<Second> &;

	using FirstConstReference  = First  const &;
	using SecondConstReference = RemoveReference<Second> const &;

private:
	Second m_second;

	FirstBasePair() {};

	explicit FirstBasePair(First first) : First(first) {}

	explicit FirstBasePair(Second second) : m_second(forward<Second>(second)) {}

	FirstBasePair(First first, Second second) : First(first), m_second(forward<Second>(second)) {}

	FirstBasePair(FirstBasePair const &) = default;

	FirstBasePair(FirstBasePair &&) = default;

	FirstBasePair & operator=(FirstBasePair const &) = default;

	FirstBasePair & operator=(FirstBasePair &&) = default;

	FirstReference      first()       noexcept { return *this; }
	FirstConstReference first() const noexcept { return *this; }

	SecondReference      second()       noexcept { return m_second; }
	SecondConstReference second() const noexcept { return m_second; }

	void swap(FirstBasePair & pair) noexcept(IsNothrowSwappable<Second>::value) {
		using ::BR::swap;
		swap(m_second, pair.m_second);
	}
}; // class FirstBasePair< TFirst, TSecond >

template< typename TFirst, typename TSecond >
class SecondBasePair : private TSecond {
public:
	using First  = TFirst;
	using Second = TSecond;

	using FirstReference  = RemoveReference<First>  &;
	using SecondReference = Second &;

	using FirstConstReference  = RemoveReference<First>  const &;
	using SecondConstReference = Second const &;

private:
	First m_first;

	SecondBasePair() {};

	explicit SecondBasePair(First first) : m_first(forward<First>(first)) {}

	explicit SecondBasePair(Second second) : Second(second) {}

	SecondBasePair(First first, Second second) : m_first(forward<First>(first)), Second(second) {}

	SecondBasePair(SecondBasePair const &) = default;

	SecondBasePair(SecondBasePair &&) = default;

	SecondBasePair & operator=(SecondBasePair const &) = default;

	SecondBasePair & operator=(SecondBasePair &&) = default;

	FirstReference      first()       noexcept { return m_first; }
	FirstConstReference first() const noexcept { return m_first; }

	SecondReference      second()       noexcept { return *this; }
	SecondConstReference second() const noexcept { return *this; }

	void swap(SecondBasePair & pair) noexcept(IsNothrowSwappable<First>::value) {
		using ::BR::swap;
		swap(m_first, pair.m_first);
	}
}; // class FirstBasePair< TFirst, TSecond >

template< typename TFirst, typename TSecond >
class AllBasePair : private TFirst, private TSecond {
public:
	using First  = TFirst;
	using Second = TSecond;

	using FirstReference  = First  &;
	using SecondReference = Second &;

	using FirstConstReference  = First  const &;
	using SecondConstReference = Second const &;

	AllBasePair() {};

	explicit AllBasePair(First first) : First(first) {}

	explicit AllBasePair(Second second) : Second(second) {}

	AllBasePair(First first, Second second) : First(first), Second(second) {}

	AllBasePair(AllBasePair const &) = default;

	AllBasePair(AllBasePair &&) = default;

	AllBasePair & operator=(AllBasePair const &) = default;

	AllBasePair & operator=(AllBasePair &&) = default;

	FirstReference      first()       noexcept { return *this; }
	FirstConstReference first() const noexcept { return *this; }

	SecondReference      second()       noexcept { return *this; }
	SecondConstReference second() const noexcept { return *this; }

	void swap(AllBasePair & pair) noexcept {}
};

template< typename TFirst, typename TSecond >
using SelectBase = Conditional<
	BooleanAnd< IsEmpty<TFirst>, NotFinal<TFirst> >,
	Conditional<
		BooleanAnd< IsEmpty<TSecond>, NotFinal<TSecond>, NotSame< TFirst, TSecond > >,
		AllBasePair< TFirst, TSecond >,
		FirstBasePair< TFirst, TSecond >
	>,
	Conditional<
		BooleanAnd< IsEmpty<TSecond>, NotFinal<TSecond> >,
		SecondBasePair< TFirst, TSecond >,
		CommonPair< TFirst, TSecond >
	>
>;

} // namespace CompressedPair
} // namespace Detail

template< typename TFirst, typename TSecond >
class CompressedPair : private Detail::CompressedPair::SelectBase< TFirst, TSecond > {
	using Base = Detail::CompressedPair::SelectBase< TFirst, TSecond >;

public:
	using First  = TFirst;
	using Second = TSecond;

	using FirstReference  = typename Base::FirstReference;
	using SecondReference = typename Base::SecondReference;

	using FirstConstReference  = typename Base::FirstConstReference;
	using SecondConstReference = typename Base::SecondConstReference;

public:
	CompressedPair() {}

	explicit CompressedPair(First first) : Base(forward<First>(first)) {}

	explicit CompressedPair(Second second) : Base(forward<Second>(second)) {}

	CompressedPair(First first, Second second) : Base(forward<First>(first), forward<Second>(second)) {}

	CompressedPair(CompressedPair const &) = default;

	CompressedPair(CompressedPair &&) = default;

	CompressedPair & operator=(CompressedPair const &) = default;

	CompressedPair & operator=(CompressedPair &&) = default;

	FirstReference      first()       noexcept { return Base::first(); }
	FirstConstReference first() const noexcept { return Base::first(); }

	SecondReference      second()       noexcept { return Base::second; }
	SecondConstReference second() const noexcept { return Base::second; }

	void swap(CompressedPair & pair) noexcept(
		BooleanAnd< IsNothrowSwappable<First>, IsNothrowSwappable<Second> >::value
	) {
		Base::swap(pair);
	}

};

} // namespace BR