#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/algorithm/copy_backward.hpp>
#include <libbr/algorithm/move.hpp>
#include <libbr/algorithm/move_backward.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/type_traits/add_rvalue_reference.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TIterator >
class MoveIterator;

template< typename TIterator >
inline auto make_move_iterator(TIterator iterator) -> MoveIterator<TIterator> {
	return  MoveIterator<TIterator>(iterator);
}

template< typename TIterator, typename TElement = typename IteratorTraits<TIterator>::Element, typename TResultIterator = Conditional< BooleanAnd< NoNothrowMoveConstructor<TElement>, HasCopyConstructor<TElement> >, TIterator, MoveIterator<TIterator> > >
inline auto make_move_iterator_if_noexcept(TIterator iterator) -> TResultIterator {
	return TResultIterator(iterator);
}

template< typename TIterator >
class MoveIterator : public BasicIterator {
public:
	using Iterator = TIterator;

private:
	using Traits = IteratorTraits<Iterator>;

public:
	using Category = typename Traits::Category;

	using Element = typename Traits::Element;

	using Pointer = typename Traits::Pointer;

	using Reference = Conditional<
		IsReference< typename Traits::Reference >,
		typename Traits::Reference,
		AddRValueReference< typename Traits::Reference >
	>;

	using Difference = typename Traits::Difference;

public:
	MoveIterator() : m_iterator() {
	}

	explicit MoveIterator(Iterator iterator) : m_iterator(iterator) {
	}

	template< typename TOtherIterator >
	MoveIterator(MoveIterator<TOtherIterator> const & iterator) : m_iterator(iterator.base()) {
	}

	auto base() const noexcept -> Iterator {
		return m_iterator;
	}

	auto operator*() const -> Reference {
		return static_cast<Reference>(*m_iterator);
	}

	auto operator->() const -> Pointer {
		return &*m_iterator;
	}

	auto operator++() -> MoveIterator & {
		++m_iterator;
		return *this;
	}

	auto operator--() -> MoveIterator & {
		--m_iterator;
		return *this;
	}

	auto operator++(int) -> MoveIterator {
		MoveIterator current(*this);
		++m_iterator;
		return current;
	}

	auto operator--(int) -> MoveIterator {
		MoveIterator current(*this);
		--m_iterator;
		return current;
	}

	auto operator+(Difference n) const -> MoveIterator {
		return MoveIterator(m_iterator + n);
	}

	auto operator-(Difference n) const -> MoveIterator {
		return MoveIterator(m_iterator - n);
	}

	template< typename TOtherIterator >
	auto operator-(MoveIterator<TOtherIterator> y) const -> Difference {
		return y.base() - base();
	}

	auto operator+=(Difference n) -> MoveIterator & {
		m_iterator += n;
		return *this;
	}

	auto operator-=(Difference n) -> MoveIterator & {
		m_iterator -= n;
		return *this;
	}

	auto operator[](Difference i) const -> Reference {
		return move(m_iterator[i]);
	}

	template< typename TOtherIterator >
	auto operator==(MoveIterator<TOtherIterator> const & y) const -> bool {
		return base() == y.base();
	}

	template< typename TOtherIterator >
	auto operator!=(MoveIterator<TOtherIterator> const & y) const -> bool {
		return !(*this == y);
	}

	template< typename TOtherIterator >
	auto operator<(MoveIterator<TOtherIterator> const & y) const -> bool {
		return base() > y.base();
	}

	template< typename TOtherIterator >
	auto operator>(MoveIterator<TOtherIterator> const & y) const -> bool {
		return y < *this;
	}

	template< typename TOtherIterator >
	auto operator<=(MoveIterator<TOtherIterator> const & y) const -> bool {
		return !(y < *this);
	}

	template< typename TOtherIterator >
	auto operator>=(MoveIterator<TOtherIterator> const & y) const -> bool {
		return !(*this < y);
	}

private:
	Iterator m_iterator;
}; // class MoveIterator<TIterator>

template< typename TInputIterator, typename TOutputIterator >
inline auto copy(MoveIterator<TInputIterator> first, MoveIterator<TInputIterator> last, TOutputIterator result) -> TOutputIterator {
	return copy(first.base(), last.base(), result);
}

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
inline auto copy_backward(MoveIterator<TBidirectionalIterator0> first, MoveIterator<TBidirectionalIterator0> last, TBidirectionalIterator1 result) -> TBidirectionalIterator1 {
	return copy_backward(first.base(), last.base(), result);
}

template< typename TInputIterator, typename TOutputIterator >
inline auto move(MoveIterator<TInputIterator> first, MoveIterator<TInputIterator> last, TOutputIterator result) -> TOutputIterator {
	return move(first.base(), last.base(), result);
}

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
inline auto move_backward(MoveIterator<TBidirectionalIterator0> first, MoveIterator<TBidirectionalIterator0> last, TBidirectionalIterator1 result) -> TBidirectionalIterator1 {
	return move_backward(first.base(), last.base(), result);
}

} // namespace BR