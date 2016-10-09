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
#include <libbr/container/detail/tuple_forward.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/enumerator.hpp>
#include <libbr/utility/integral_constant.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

/**
 * @brief C风格数组包装
 * @tparam TElement 数组元素类型
 * @tparam S 数组长度
 *
 * 是类元组类型
 */
template< typename T, Size N >
class Array;

template< typename T, Size S >
struct TupleSize< Array< T, S > > : IntegralConstant< Size, S > {};

template< Size I, typename T, Size S >
struct TypeTupleElement< I, Array< T, S > > : TypeWrapper<T> {};

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

template< Size I, typename T, Size S >
constexpr inline auto get(Array< T, S > const && A) noexcept -> T const && {
	static_assert(I < S, "Index out of bounds.");
	return move(A[I]);
}

template< typename T, Size N >
void swap(Array< T, N > & x, Array< T, N > & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

template< typename TElement, Size N >
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
	template< typename TFunctor >
	static auto build(TFunctor && functor) -> Array {
		Array array;
		for (Size i = 0; i < N; ++i) {
			auto t = i;
			array[i] = functor(t);
		}
		return array;
	}

	/**
	 * @brief 填充数组
	 * @param element 填充值
	 */
	auto fill(Element const & element) -> Array & {
		fill_n(m_elements, N, element);
		return *this;
	}

	/**
	 * @brief 交换
	 */
	void swap(Array & array) noexcept(IsNothrowSwappable< CArray< Element, N > >::value) {
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
		return Iterator(m_elements + N);
	}

	auto end() const noexcept -> ConstIterator {
		return ConstIterator(m_elements + N);
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
		return N;
	}

	constexpr auto max_size() const noexcept -> Size {
		return N;
	}

	constexpr auto empty() const noexcept -> bool {
		return N == 0;
	}

	auto operator[](Size i) -> Reference {
		return m_elements[i];
	}

	constexpr auto operator[](Size i) const -> ConstReference {
		return m_elements[i];
	}

	auto at(Size i) -> Reference {
		if (i >= N) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		return operator[](i);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto at(Size i) const -> ConstReference {
		if (i >= N) {
			throw_index_exception(BR_CURRENT_FUNCTION);
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
		return operator[](N > 0 ? N - 1 : 0);
	}

	constexpr auto back() const -> ConstReference {
		return operator[](N > 0 ? N - 1 : 0);
	}

	auto data() noexcept -> Element * {
		return m_elements;
	}

	auto data() const noexcept -> Element const * {
		return m_elements;
	}

	auto operator==(Array const & y) const -> bool {
		return equal(begin(), end(), y.begin(), y.end());
	}

	auto operator!=(Array const & y) const -> bool {
		return !operator==(y);
	}

	auto operator<(Array const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}

	auto operator>(Array const & y) const -> bool {
		return y.operator<(*this);
	}

	auto operator<=(Array const & y) const -> bool {
		return !y.operator<(*this);
	}

	auto operator>=(Array const & y) const -> bool {
		return !operator<(y);
	}

private:
	Element m_elements[N > 0 ? N : 1];
}; // struct Array< TElement, S >

} // namespace BR