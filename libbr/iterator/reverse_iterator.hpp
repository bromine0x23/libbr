#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/operators/decrementable.hpp>
#include <libbr/operators/incrementable.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TIterator >
class ReverseIterator;

template< typename TIterator >
inline auto make_reverse_iterator(TIterator iterator) -> ReverseIterator<TIterator> {
	return ReverseIterator<TIterator>(iterator);
}

template< typename TIterator >
class ReverseIterator :
	public BasicIterator,
	public Incrementable< ReverseIterator<TIterator> >,
	public Decrementable< ReverseIterator<TIterator> >
{
public:
	using Iterator = TIterator;

private:
	using Traits = IteratorTraits<Iterator>;

public:
	using Category = typename Traits::Category;

	using Element = typename Traits::Element;

	using Pointer = typename Traits::Pointer;

	using Reference = typename Traits::Reference;

	using Difference = typename Traits::Difference;

	ReverseIterator() : m_iterator() {
	}

	explicit ReverseIterator(Iterator iterator) : m_iterator(iterator) {
	}

	template< typename TOtherIterator >
	ReverseIterator(ReverseIterator<TOtherIterator> const & iterator) : m_iterator(iterator.base()) {
	}

	auto base() const noexcept -> Iterator {
		return m_iterator;
	}

	auto operator*() const -> Reference {
		Iterator current = m_iterator;
		return *--current;
	}

	auto operator->() const -> Pointer {
		return address_of(operator*());
	}

	auto operator++() -> ReverseIterator & {
		--m_iterator;
		return *this;
	}

	auto operator--() -> ReverseIterator & {
		++m_iterator;
		return *this;
	}

	auto operator+(Difference n) const -> ReverseIterator {
		return ReverseIterator(m_iterator - n);
	}

	auto operator-(Difference n) const -> ReverseIterator {
		return ReverseIterator(m_iterator + n);
	}

	template< typename TOtherIterator >
	auto operator-(ReverseIterator<TOtherIterator> y) const -> Difference {
		return y.base() - base();
	}

	auto operator+=(Difference n) -> ReverseIterator & {
		m_iterator -= n;
		return *this;
	}

	auto operator-=(Difference n) -> ReverseIterator & {
		m_iterator += n;
		return *this;
	}

	auto operator[](Difference i) const -> Reference {
		return m_iterator[-i - 1];
	}

	template< typename TOtherIterator >
	auto operator==(ReverseIterator<TOtherIterator> const & y) const -> bool {
		return base() == y.base();
	}

	template< typename TOtherIterator >
	auto operator!=(ReverseIterator<TOtherIterator> const & y) const -> bool {
		return !(*this == y);
	}

	template< typename TOtherIterator >
	auto operator<(ReverseIterator<TOtherIterator> const & y) const -> bool {
		return base() > y.base();
	}

	template< typename TOtherIterator >
	auto operator>(ReverseIterator<TOtherIterator> const & y) const -> bool {
		return y < *this;
	}

	template< typename TOtherIterator >
	auto operator<=(ReverseIterator<TOtherIterator> const & y) const -> bool {
		return !(y < *this);
	}

	template< typename TOtherIterator >
	auto operator>=(ReverseIterator<TOtherIterator> const & y) const -> bool {
		return !(*this < y);
	}

private:
	Iterator m_iterator;
}; // class ReverseIterator<TIterator>

} // namespace BR