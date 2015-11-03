/**
 * @file
 * @brief Array
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/exception/out_of_range_exception.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/current_function.hpp>
#include <libbr/utility/enumerator.hpp>
#include <libbr/utility/integer_constant.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

/**
 * @brief C风格数组包装
 * @tparam TElement 数组元素类型
 * @tparam Size 数组长度
 */
template< typename TElement, Size S >
class Array;

template< typename T >
struct TypeTupleSize;

template< typename T, Size S >
struct TypeTupleSize< Array< T, S > > : IntegerConstant< Size, S > {
};

template< Size I, typename T >
struct TypeTupleElement;

template< Size I, typename T, Size S >
struct TypeTupleElement< I, Array< T, S > > : TypeWrapper<T> {
};

template< Size I, typename T, Size S >
constexpr inline auto get(Array< T, S > & A) noexcept -> T & {
	static_assert(I < S, "Index out of bounds.");
	return A[I];
}

template< Size I, typename T, Size S >
constexpr inline auto get(Array< T, S > const & A) noexcept -> T const & {
	static_assert(I < S, "Index out of bounds.");
	return A[I];
}

template< Size I, typename T, Size S >
constexpr inline auto get(Array< T, S > && A) noexcept -> T && {
	static_assert(I < S, "Index out of bounds.");
	return move(A[I]);
}

template< typename TElement, Size S >
class Array {
public:
	using Element = TElement;

	using Reference = Element &;

	using ConstReference = Element const &;

	using Pointer = Element *;

	using ConstPointer = Element const *;

	using Iterator = Pointer;

	using ConstIterator = ConstPointer;

	using Size = BR::Size;

	using Difference = PointerDifference;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

public:
	constexpr Array() noexcept = default;

	Array(Array const & _dummy) noexcept = default;

	Array(Array && _dummy) noexcept = default;

	template< typename TFunctor >
	Array(TFunctor functor) {
		for (Size i = 0; i < S; ++i) {
			auto t = i;
			m_elements[i] = functor(t);
		}
	}

	~Array() noexcept = default;

	auto operator=(Array const & _dummy) noexcept -> Array & = default;

	auto operator=(Array && _dummy) noexcept -> Array & = default;

	auto fill(Element const & element) -> Array & {
		fill_n(m_elements, S, element);
		return *this;
	}

	void swap(Array & array) noexcept(IsNothrowSwappable< Element [S] >::value) {
		using BR::swap;
		swap(m_elements, array.m_elements);
	}

	auto begin() noexcept -> Iterator {
		return Iterator(m_elements);
	}

	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(m_elements);
	}

	auto end() noexcept -> Iterator {
		return Iterator(m_elements + S);
	}

	auto end() const noexcept -> ConstIterator {
		return ConstIterator(m_elements + S);
	}

	auto rbegin() noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	auto rbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(end());
	}

	auto rend() noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	auto rend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(begin());
	}

	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	auto crbegin() const noexcept -> ConstIterator {
		return rbegin();
	}

	auto cend() const noexcept -> ConstIterator {
		return end();
	}

	auto crend() const noexcept -> ConstIterator {
		return rend();
	}

	constexpr auto size() const noexcept -> Size {
		return S;
	}

	constexpr auto max_size() const noexcept -> Size {
		return S;
	}

	constexpr auto empty() const noexcept -> bool {
		return S == 0;
	}

	auto operator[](Size i) -> Reference {
		return m_elements[i];
	}

	constexpr auto operator[](Size i) const -> ConstReference {
		return m_elements[i];
	}

	auto at(Size i) -> Reference {
		if (i >= S) {
			throw OutOfRangeException(BR_CURRENT_FUNCTION);
		}
		return operator[](i);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto at(Size i) const -> ConstReference {
		if (i >= S) {
			throw OutOfRangeException(BR_CURRENT_FUNCTION);
		}
		return operator[](i);
	}

	auto front() -> Reference {
		return operator[](0);
	}

	constexpr auto front() const -> ConstReference {
		return operator[](0);
	}

	auto back() -> Reference {
		return operator[](S > 0 ? S - 1 : 0);
	}

	constexpr auto back() const -> ConstReference {
		return operator[](S > 0 ? S - 1 : 0);
	}

	auto data() noexcept -> Element * {
		return m_elements;
	}

	auto data() const noexcept -> Element const * {
		return m_elements;
	}

	auto each() noexcept -> Enumerator<Iterator> {
		return make_enumerator(begin(), end());
	}

	template< typename TFunctor >
	auto each(TFunctor functor) noexcept -> Array {
		each().each(functor);
		return *this;
	}

	auto each() const noexcept -> Enumerator<ConstIterator> {
		return make_enumerator(begin(), end());
	}

	template< typename TFunctor >
	auto each(TFunctor functor) const noexcept -> Array {
		each().each(functor);
		return *this;
	}

	auto reverse_each() noexcept -> Enumerator<ReverseIterator> {
		return make_enumerator(rbegin(), rend());
	}

	template< typename TFunctor >
	auto reverse_each(TFunctor functor) noexcept -> Array {
		reverse_each().each(functor);
		return *this;
	}

	auto reverse_each() const noexcept -> Enumerator<ConstReverseIterator> {
		return make_enumerator(rbegin(), rend());
	}

	template< typename TFunctor >
	auto reverse_each(TFunctor functor) const noexcept -> Array {
		reverse_each().each(functor);
		return *this;
	}

	auto operator==(Array const & y) const -> bool {
		return equal(begin(), end(), y.begin(), y.end());
	}

	auto operator!=(Array const & y) const -> bool {
		return !(*this == y);
	}

	auto operator<(Array const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}

	auto operator>(Array const & y) const -> bool {
		return y < *this;
	}

	auto operator<=(Array const & y) const -> bool {
		return !(y < *this);
	}

	auto operator>=(Array const & y) const -> bool {
		return !(*this < y);
	}

private:
	Element m_elements[S > 0 ? S : 1];
}; // struct Array< TElement, S >

template< typename T, Size S>
void swap(Array< T, S > & x, Array< T, S > & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

} // namespace BR