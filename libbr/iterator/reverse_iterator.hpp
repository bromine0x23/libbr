#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>

namespace BR {
namespace Iterator {

template< typename TIterator >
class ReverseIterator : public BR::Iterator::Iterator<
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
	using Reference  = typename Base::Reference;

	ReverseIterator() : m_iterator() {}

	explicit ReverseIterator(Iterator iterator) : m_iterator(iterator) {}

	template< typename TOtherIterator >
	ReverseIterator(ReverseIterator< TOtherIterator > const & iterator) : m_iterator(iterator.base()) {}

	Iterator base() const {
		return m_iterator;
	}

	Reference operator*() const {
		Iterator current = m_iterator;
		return *--current;
	}

	Pointer operator->() const {
		return Memory::address_of(operator*());
	}

	ReverseIterator & operator++() { --m_iterator; return *this; }
	ReverseIterator & operator--() { ++m_iterator; return *this; }

	ReverseIterator operator++(int) { ReverseIterator current(*this); --current; return current; }
	ReverseIterator operator--(int) { ReverseIterator current(*this); ++current; return current; }

	ReverseIterator operator+(Difference n) const { return ReverseIterator(m_iterator - n); }
	ReverseIterator operator-(Difference n) const { return ReverseIterator(m_iterator + n); }

	ReverseIterator & operator+=(Difference n) { m_iterator -= n; return *this; }
	ReverseIterator & operator-=(Difference n) { m_iterator += n; return *this; }

	Reference operator[](Difference i) const { return m_iterator[-i - 1]; }

private:
	Iterator m_iterator;
}; // class ReverseIterator< TIterator >

template< typename TIterator0, typename TIterator1 >
inline bool operator==(
	ReverseIterator< TIterator0 > const & x,
	ReverseIterator< TIterator1 > const & y
) {
	return x.base() == y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator!=(
	ReverseIterator< TIterator0 > const & x,
	ReverseIterator< TIterator1 > const & y
) {
	return x.base() != y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator<(
	ReverseIterator< TIterator0 > const & x,
	ReverseIterator< TIterator1 > const & y
) {
	return x.base() > y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator>(
	ReverseIterator< TIterator0 > const & x,
	ReverseIterator< TIterator1 > const & y
) {
	return x.base() < y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator<=(
	ReverseIterator< TIterator0 > const & x,
	ReverseIterator< TIterator1 > const & y
) {
	return x.base() >= y.base();
}

template< typename TIterator0, typename TIterator1 >
inline bool operator>=(
	ReverseIterator< TIterator0 > const & x,
	ReverseIterator< TIterator1 > const & y
) {
	return x.base() <= y.base();
}

template< typename TIterator >
inline ReverseIterator< TIterator > operator+(
	IteratorDifference< TIterator > const & n,
	ReverseIterator< TIterator > const & x
) {
	return ReverseIterator< TIterator >(x.base() - n);
}

template< typename TIterator0, typename TIterator1 >
inline IteratorDifference< TIterator0 > operator-(
	ReverseIterator< TIterator0 > const & x,
	ReverseIterator< TIterator1 > const & y
) {
	return y.base() - x.base();
}

template< typename TIterator >
inline ReverseIterator< TIterator > makeReverseIterator(TIterator iterator) {
	return ReverseIterator< TIterator >(iterator);
}

} // namespace Iterator
} // namespace BR