/**
 * @file
 * @brief 迭代器区间
 * @author Bromine0x23
 * @since 2015/11/12
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/iterator/prev.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_convertible.hpp>

namespace BR {

template< typename TIterator >
class IteratorRange;

template< typename TIterator >
constexpr auto make_iterator_range(TIterator begin, TIterator end) -> IteratorRange<TIterator> {
	return IteratorRange<TIterator>(begin, end);
}

template< typename TIterator, typename TDifference >
constexpr auto make_iterator_range_n(TIterator begin, TDifference n) -> IteratorRange<TIterator> {
	return IteratorRange<TIterator>(begin, next(begin, n));
}

namespace Detail {
namespace Iterator {

template< typename TIterator >
class IteratorRangeBasic {

public:
	using Element = typename IteratorTraits<TIterator>::Element;

	using Reference = typename IteratorTraits<TIterator>::Reference;

	using Size = BR::Size;

	using Difference = typename IteratorTraits<TIterator>::Difference;

	using Iterator = TIterator;

	using ConstIterator = TIterator;

public:
	constexpr auto begin() const -> Iterator {
		return cbegin();
	}

	constexpr auto end() const -> Iterator {
		return cend();
	}

	constexpr auto cbegin() const -> Iterator {
		return m_begin;
	}

	constexpr auto cend() const -> Iterator {
		return m_end;
	}

	constexpr auto is_empty() const -> bool {
		return m_begin == m_end;
	}

	constexpr explicit operator bool() const {
		return !is_empty();
	}

	constexpr auto operator!() const -> bool {
		return is_empty();
	}

	constexpr auto operator==(IteratorRangeBasic const & range) const -> bool {
		return m_begin == range.m_begin && m_end == range.m_end;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto front() const -> Reference {
		BR_ASSERT(operator bool());
		return *m_begin;
	}

	void drop_front() {
		BR_ASSERT(operator bool());
		++m_begin;
	}

	void drop_front(Difference n) {
		BR_ASSERT(n >= Difference());
		advance(m_begin, n);
	}

protected:
	constexpr IteratorRangeBasic() : m_begin(), m_end() {
	}

	template< typename TOtherIterator >
	constexpr IteratorRangeBasic(TOtherIterator begin, TOtherIterator end) : m_begin(begin), m_end(end) {
	}

	template< typename TOtherIterator >
	BR_CONSTEXPR_AFTER_CXX11 void m_assign(TOtherIterator first, TOtherIterator last) {
		m_begin = first;
		m_end = last;
	}

	TIterator m_begin;
	TIterator m_end;
}; // class IteratorRangeBasic<TIterator>

template< typename TIterator >
class IteratorRangeBidirectional : public IteratorRangeBasic<TIterator> {
private:
	using Base = IteratorRangeBasic<TIterator>;

public:
	using Iterator = typename Base::Iterator;

	using Reference = typename Base::Reference;

	using Difference = typename Base::Difference;

	BR_CONSTEXPR_AFTER_CXX11 auto back() const -> Reference {
		BR_ASSERT(this->operator bool());
		return *prev(this->m_end);
	}

	void drop_back() {
		BR_ASSERT(this->operator bool());
		--this->m_end;
	}

	void drop_back(Difference n) {
		BR_ASSERT(n >= Difference());
		advance(this->m_end, -n);
	}

	constexpr auto rbegin() const -> Iterator {
		return crbegin();
	}

	constexpr auto rend() const -> Iterator {
		return crend();
	}

	constexpr auto crbegin() const -> ReverseIterator<Iterator> {
		return ReverseIterator<Iterator>(this->m_begin);
	}

	constexpr auto crend() const -> ReverseIterator<Iterator> {
		return ReverseIterator<Iterator>(this->m_end);
	}

protected:
	constexpr IteratorRangeBidirectional() {
	}

	template< typename TOtherIterator >
	constexpr IteratorRangeBidirectional(TOtherIterator first, TOtherIterator last) : Base(first, last) {
	}

}; // class IteratorRangeBidirectional<TIterator>

template< typename TIterator >
class IteratorRangeRandomAccess : public IteratorRangeBidirectional<TIterator> {
private:
	using Base = IteratorRangeBidirectional<TIterator>;

public:
	using Reference = typename Base::Reference;

	using Size = typename Base::Size;

	using Difference = typename Base::Difference;

public:
	constexpr auto size() const -> Size {
		return this->m_end - this->m_begin;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto operator[](Difference index) const -> Reference {
		BR_ASSERT(index >= 0);
		BR_ASSERT(static_cast<Size>(index) < size());
		return this->m_begin[index];
	}

protected:
	constexpr IteratorRangeRandomAccess() {
	}

	template< typename TOtherIterator >
	constexpr IteratorRangeRandomAccess(TOtherIterator first, TOtherIterator last) : Base(first, last) {
	}

}; // class IteratorRangeRandomAccess<TIterator>

template< typename TIterator >
using IteratorRange = Conditional<
	IsConvertible< TIterator, RandomAccessTraversalTag >,
	IteratorRangeRandomAccess<TIterator>,
	Conditional<
		IsConvertible< TIterator, BidirectionalTraversalTag >,
		IteratorRangeBidirectional<TIterator>,
		IteratorRangeBasic<TIterator>
	>
>;

} // namespace Iterator
} // namespace Detail

template< typename TIterator >
class IteratorRange : public Detail::Iterator::IteratorRange<TIterator> {
private:
	using Base = Detail::Iterator::IteratorRange<TIterator>;

public:
	using Iterator = typename Base::Iterator;

	IteratorRange() {
	}

	template< typename TOtherIterator, typename = EnableIf< IsConvertible< TOtherIterator const &, Iterator > > >
	constexpr IteratorRange(IteratorRange<TOtherIterator> const & range) : Base(range.begin(), range.end()) {
	}

	template< typename TOtherIterator, typename = EnableIf< IsConvertible< TOtherIterator const &, Iterator > > >
	constexpr IteratorRange(Pair< TOtherIterator, TOtherIterator > const & pair) : Base(pair.first, pair.second) {
	}

	template< typename TOtherIterator >
	constexpr IteratorRange(TOtherIterator first, TOtherIterator last) : Base(first, last) {
	}

	template< typename TOtherIterator >
	BR_CONSTEXPR_AFTER_CXX11 auto operator=(IteratorRange<TOtherIterator> const & range) -> IteratorRange & {
		this->m_assign(range.begin(), range.end());
		return *this;
	}

	template< typename TOtherIterator >
	auto operator==(IteratorRange<TOtherIterator> const & y) -> bool {
		return equal(this->begin(), this->end(), y.begin(), y.end());
	}

	template< typename TOtherIterator >
	auto operator!=(IteratorRange<TOtherIterator> const & y) -> bool {
		return !operator==(y);
	}

	template< typename TOtherIterator >
	auto operator<(IteratorRange<TOtherIterator> const & y) -> bool {
		return lexicographical_compare(this->begin(), this->end(), y.begin(), y.end());
	}

	template< typename TOtherIterator >
	auto operator>(IteratorRange<TOtherIterator> const & y) -> bool {
		return y.operator<(*this);
	}

	template< typename TOtherIterator >
	auto operator<=(IteratorRange<TOtherIterator> const & y) -> bool {
		return !y.operator<(*this);
	}

	template< typename TOtherIterator >
	auto operator>=(IteratorRange<TOtherIterator> const & y) -> bool {
		return !operator<(y);
	}

}; // IteratorRange<TIterator>

} // namespace BR