/**
 * @file
 * @brief 逆向迭代器
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>

namespace BR {

inline namespace Iterators {

/**
 * @brief 逆向迭代器
 * @tparam TIterator 原迭代器类型
 */
template< typename TIterator >
class ReverseIterator;

template< typename TIterator >
constexpr inline auto make_reverse_iterator(TIterator iterator) -> ReverseIterator<TIterator> {
	return ReverseIterator<TIterator>(iterator);
}

} // namespace Iterators



inline namespace Iterators {

template< typename TIterator >
class ReverseIterator {
public:
	using Iterator = TIterator;

private:
	using Traits = IteratorTraits<Iterator>;

public:
	using IteratorCategory = typename Traits::IteratorCategory;

	using Element = typename Traits::Element;

	using Pointer = typename Traits::Pointer;

	using Reference = typename Traits::Reference;

	using Difference = typename Traits::Difference;

private:
	Iterator _iterator;

public:
	constexpr ReverseIterator() : _iterator() {
	}

	constexpr explicit ReverseIterator(Iterator iterator) : _iterator(iterator) {
	}

	template< typename TOtherIterator >
	constexpr ReverseIterator(ReverseIterator<TOtherIterator> const & iterator) : _iterator(iterator.base()) {
	}

	constexpr auto base() const noexcept -> Iterator {
		return _iterator;
	}

	constexpr auto operator*() const -> Reference {
		Iterator current = _iterator;
		return *--current;
	}

	constexpr auto operator->() const -> Pointer {
		return address_of(operator*());
	}

	constexpr auto operator++() -> ReverseIterator & {
		--_iterator;
		return *this;
	}

	constexpr auto operator++(int) -> ReverseIterator & {
		ReverseIterator result(*this);
		--_iterator;
		return result;
	}

	constexpr auto operator--() -> ReverseIterator & {
		++_iterator;
		return *this;
	}

	constexpr auto operator--(int) -> ReverseIterator & {
		ReverseIterator result(*this);
		++_iterator;
		return result;
	}

	constexpr auto operator+(Difference n) const -> ReverseIterator {
		return ReverseIterator(_iterator - n);
	}

	constexpr auto operator-(Difference n) const -> ReverseIterator {
		return ReverseIterator(_iterator + n);
	}

	template< typename TOtherIterator >
	constexpr auto operator-(ReverseIterator<TOtherIterator> y) const -> Difference {
		return y.base() - base();
	}

	constexpr auto operator+=(Difference n) -> ReverseIterator & {
		_iterator -= n;
		return *this;
	}

	constexpr auto operator-=(Difference n) -> ReverseIterator & {
		_iterator += n;
		return *this;
	}

	constexpr auto operator[](Difference i) const -> Reference {
		return _iterator[-i - 1];
	}

	template< typename TOtherIterator >
	constexpr auto operator==(ReverseIterator<TOtherIterator> const & y) const -> Boolean {
		return base() == y.base();
	}

	template< typename TOtherIterator >
	constexpr auto operator!=(ReverseIterator<TOtherIterator> const & y) const -> Boolean {
		return !(*this == y);
	}

	template< typename TOtherIterator >
	constexpr auto operator<(ReverseIterator<TOtherIterator> const & y) const -> Boolean {
		return base() > y.base();
	}

	template< typename TOtherIterator >
	constexpr auto operator>(ReverseIterator<TOtherIterator> const & y) const -> Boolean {
		return y < *this;
	}

	template< typename TOtherIterator >
	constexpr auto operator<=(ReverseIterator<TOtherIterator> const & y) const -> Boolean {
		return !(y < *this);
	}

	template< typename TOtherIterator >
	constexpr auto operator>=(ReverseIterator<TOtherIterator> const & y) const -> Boolean {
		return !(*this < y);
	}
}; // class ReverseIterator<TIterator>

} // namespace Iterators

} // namespace BR