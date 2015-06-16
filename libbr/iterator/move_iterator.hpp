#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_reference.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Iterator {

template< typename TIterator >
class MoveIterator : public BR::Iterator::Iterator<
	IteratorCategory  < TIterator >,
	IteratorValue     < TIterator >,
	IteratorDifference< TIterator >,
	IteratorPointer   < TIterator >,
	IteratorReference < TIterator >
> {
private:
	using Base = BR::Iterator::Iterator<
		IteratorCategory  < TIterator >,
		IteratorValue     < TIterator >,
		IteratorDifference< TIterator >,
		IteratorPointer   < TIterator >,
		IteratorReference < TIterator >
	>;

public:
	using Iterator   = TIterator;
	using Difference = typename Base::Difference;
	using Pointer    = typename Base::Pointer;
	using Reference  = typename TypeOperate::Conditional<
		typename Base::Reference,
		TypeOperate::AddRValueReference< typename Base::Reference >,
		typename Base::Reference
	>;

private:
	Iterator m_iterator;

public:
	MoveIterator() : m_iterator() {}

	explicit MoveIterator(Iterator iterator) : m_iterator(iterator) {}

	template< typename TOtherIterator >
	MoveIterator(MoveIterator< TOtherIterator > const & iterator) : m_iterator(iterator.base()) {}

	Iterator base() const {
		return m_iterator;
	}

	Reference operator*() const {
		return static_cast< Reference >(*m_iterator);
	}

	Pointer operator->() const {
		return &*m_iterator;
	}

	MoveIterator & operator++() { ++m_iterator; return *this; }
	MoveIterator & operator--() { --m_iterator; return *this; }

	MoveIterator operator++(int) { MoveIterator current(*this); ++m_iterator; return current; }
	MoveIterator operator--(int) { MoveIterator current(*this); --m_iterator; return current; }

	MoveIterator operator+(Difference n) const { return MoveIterator(m_iterator + n); }
	MoveIterator operator-(Difference n) const { return MoveIterator(m_iterator - n); }

	MoveIterator & operator+=(Difference n) { m_iterator += n; return *this; }
	MoveIterator & operator-=(Difference n) { m_iterator -= n; return *this; }

	Reference operator[](Difference i) const { return move(m_iterator[i]); }
}; // class MoveIterator< TIterator >

template< typename TIterator0, typename TIterator1 >
inline bool operator==(
	MoveIterator< TIterator0 > const & x,
	MoveIterator< TIterator1 > const & y
) {
	return x.base() == y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator!=(
	MoveIterator< TIterator0 > const & x,
	MoveIterator< TIterator1 > const & y
) {
	return x.base() != y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator<(
	MoveIterator< TIterator0 > const & x,
	MoveIterator< TIterator1 > const & y
) {
	return x.base() < y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator>(
	MoveIterator< TIterator0 > const & x,
	MoveIterator< TIterator1 > const & y
) {
	return x.base() > y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator<=(
	MoveIterator< TIterator0 > const & x,
	MoveIterator< TIterator1 > const & y
) {
	return x.base() <= y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator>=(
	MoveIterator< TIterator0 > const & x,
	MoveIterator< TIterator1 > const & y
) {
	return x.base() >= y.base();
}

template< typename TIterator >
inline MoveIterator< TIterator > operator+(IteratorDifference< TIterator > n, MoveIterator< TIterator > const & x) {
	return MoveIterator< TIterator >(x.base() + n);
}

template< typename TIterator0, typename TIterator1 >
inline IteratorDifference< TIterator0 > operator-(MoveIterator< TIterator0 > const & x, MoveIterator< TIterator1 > const & y)  {
	return x.base() - y.base();
}

template< typename TIterator >
inline MoveIterator< TIterator > makeMoveIterator(TIterator iterator)  {
	return  MoveIterator< TIterator >(iterator);
}

} // namespace Iterator
} // namespace BR