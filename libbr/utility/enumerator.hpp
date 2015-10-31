/**
 * @file
 * @brief class Enumerator
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename T >
class Enumerator;

template< typename T >
constexpr auto make_enumerator(T first, T last) noexcept -> Enumerator<T> {
	return Enumerator<T>(first, last);
}

template< typename T >
class Enumerator {

public:
	using Iterator = T;

	using Element = typename IteratorTraits<Iterator>::Element;

	using Size = typename IteratorTraits<Iterator>::Difference;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	constexpr Enumerator(Iterator first, Iterator last) noexcept : m_first(first), m_last(last) {
	}

	template< typename TFirst, typename TLast, typename _TDummy = EnableIf< BooleanAnd< IsConvertible< TFirst, Iterator >, IsConvertible< TLast, Iterator > > > >
	constexpr Enumerator(TFirst first, TLast last) noexcept(
		BooleanAnd< IsNothrowConstructible< Iterator, TFirst >, IsNothrowConstructible< Iterator, TLast > >()
	) : m_first(first), m_last(last) {
	}

	constexpr Enumerator(Pair< Iterator, Iterator > pair) noexcept : m_first(pair.first), m_last(pair.second) {
	}

	template< typename TFirst, typename TLast, typename _TDummy = EnableIf< BooleanAnd< IsConvertible< TFirst, Iterator >, IsConvertible< TLast, Iterator > > > >
	constexpr Enumerator(Pair< TFirst, TLast > pair) noexcept(
		BooleanAnd< IsNothrowConstructible< Iterator, TFirst >, IsNothrowConstructible< Iterator, TLast > >()
	) : m_first(pair.first), m_last(pair.second) {
	}

	constexpr auto begin() const noexcept -> Iterator {
		return m_first;
	}

	constexpr auto end() const noexcept -> Iterator {
		return m_last;
	}

	constexpr auto rbegin() const noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	constexpr auto rend() const noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	auto is_empty() const noexcept -> bool {
		return begin() == end();
	}

	auto size() const noexcept -> Size {
		return distance(begin(), end());
	}

	constexpr auto each() const noexcept -> Enumerator<Iterator> {
		return make_enumerator(begin(), end());
	}

	template< typename TFunctor >
	auto each(TFunctor functor) const -> Enumerator const & {
		auto iterator = begin();
		for (;iterator != end(); ++iterator) {
			functor(*iterator);
		}
		return *this;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto reverse_each() const noexcept -> Enumerator<ReverseIterator> {
		return make_enumerator(rbegin(), rend());
	}

	template< typename TFunctor >
	auto reverse_each(TFunctor functor) const -> Enumerator const & {
		reverse_each().each(functor);
		return *this;
	}

	template< typename TFunctor >
	auto each_with_index(TFunctor functor) const -> Enumerator const & {
		auto iterator = begin();
		for (Size index = 0; iterator != end(); ++iterator, ++index) {
			functor(*iterator, index);
		}
		return *this;
	}

	template< typename TFunctor, typename TArgument >
	auto each_with_argument(TArgument && argument, TFunctor functor) const -> Enumerator const & {
		for (auto iterator = begin(); iterator != end(); ++iterator) {
			functor(*iterator, forward<TArgument>(argument));
		}
		return *this;
	}

	template< typename TUnaryPredicate >
	auto all(TUnaryPredicate predicate) const -> bool {
		for (auto iterator = begin(); iterator != end(); ++iterator) {
			if (!predicate(*iterator)) {
				return false;
			}
		}
		return true;
	}

	template< typename TUnaryPredicate >
	auto none(TUnaryPredicate predicate) const -> bool {
		for (auto iterator = begin(); iterator != end(); ++iterator) {
			if (predicate(*iterator)) {
				return false;
			}
		}
		return true;
	}

	template< typename TValue >
	auto include(TValue const & value) const -> bool {
		for (auto iterator = begin(); iterator != end(); ++iterator) {
			if (*iterator == value) {
				return true;
			}
		}
		return false;
	}

	template< typename TUnaryPredicate >
	auto any(TUnaryPredicate predicate) const -> bool {
		for (auto iterator = begin(); iterator != end(); ++iterator) {
			if (predicate(*iterator)) {
				return true;
			}
		}
		return false;
	}

	template< typename TValue >
	auto find(TValue const & value) const -> Iterator {
		auto i = begin();
		for (; i != end(); ++i) {
			if (*i == value) {
				break;
			}
		}
		return i;
	}

	template< typename TUnaryPredicate >
	auto find_if(TUnaryPredicate predicate) const -> Iterator {
		auto i = begin();
		for (; i != end(); ++i) {
			if (predicate(*i)) {
				break;
			}
		}
		return i;
	}

private:
	Iterator m_first;
	Iterator m_last;
}; // class Enumerator<T>

} // namespace BR
