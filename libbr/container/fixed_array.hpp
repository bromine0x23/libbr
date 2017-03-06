/**
 * @file
 * @brief FixedArray
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/container/detail/tuple_forward.hpp>
#include <libbr/enumerate/enumerator.hpp>
#include <libbr/enumerate/enumerable.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>
#include <libbr/utility/integral_constant.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Container {

/**
 * @brief C风格数组包装
 * @tparam TElement 数组元素类型
 * @tparam S 数组长度
 *
 * 是类元组类型
 */
template< typename T, Size N >
class FixedArray;

/**
 *
 * @tparam T
 * @tparam N
 * @param x
 * @param y
 */
template< typename T, Size N >
void swap(FixedArray< T, N > & x, FixedArray< T, N > & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

template< typename T, Size S >
struct TupleSize< FixedArray< T, S > > : IntegralConstant< Size, S > {};

template< Size I, typename T, Size S >
struct TypeTupleElement< I, FixedArray< T, S > > : TypeWrapper<T> {};

template< Size I, typename T, Size S >
constexpr inline auto get(FixedArray< T, S > & A) noexcept -> T & {
	static_assert(I < S, "Index out of bounds.");
	return A[I];
}

template< Size I, typename T, Size S >
constexpr inline auto get(FixedArray< T, S > const & A) noexcept -> T const & {
	static_assert(I < S, "Index out of bounds.");
	return A[I];
}

template< Size I, typename T, Size S >
constexpr inline auto get(FixedArray< T, S > && A) noexcept -> T && {
	static_assert(I < S, "Index out of bounds.");
	return move(A[I]);
}

template< Size I, typename T, Size S >
constexpr inline auto get(FixedArray< T, S > const && A) noexcept -> T const && {
	static_assert(I < S, "Index out of bounds.");
	return move(A[I]);
}

} // namespace Container


inline namespace Container {

template< typename TElement, Size N >
struct FixedArray {
private:
	using Self = FixedArray;

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
	static auto build(TFunctor functor) -> Self {
		Self array;
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
	auto fill(Element const & element) -> Self & {
		fill_n(elements, N, element);
		return *this;
	}

	/**
	 * @brief 交换
	 */
	void swap(Self & array) noexcept(IsNothrowSwappable< CArray< Element, N > >{}) {
		using BR::swap;
		swap(elements, array.elements);
	}

	auto begin() noexcept -> Iterator {
		return Iterator(elements);
	}

	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(elements);
	}

	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	auto end() noexcept -> Iterator {
		return Iterator(elements + N);
	}

	auto end() const noexcept -> ConstIterator {
		return ConstIterator(elements + N);
	}

	auto cend() const noexcept -> ConstIterator {
		return end();
	}

	auto rbegin() noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	auto rbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(end());
	}

	auto crbegin() const noexcept -> ConstReverseIterator {
		return rbegin();
	}

	auto rend() noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	auto rend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(begin());
	}

	auto crend() const noexcept -> ConstReverseIterator {
		return rend();
	}

	constexpr auto size() const noexcept -> Size {
		return N;
	}

	constexpr auto max_size() const noexcept -> Size {
		return N;
	}

	constexpr auto empty() const noexcept -> Boolean {
		return N == 0;
	}

	auto operator[](Size i) -> Reference {
		return elements[i];
	}

	constexpr auto operator[](Size i) const -> ConstReference {
		return elements[i];
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
		return elements;
	}

	auto data() const noexcept -> Element const * {
		return elements;
	}

	auto operator==(Self const & y) const -> Boolean {
		return equal(begin(), end(), y.begin(), y.end());
	}

	auto operator<(Self const & y) const -> Boolean {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}

	friend auto operator!=(Self const & x, Self const & y) -> Boolean { return !static_cast<Boolean>(x == y); }
	friend auto operator> (Self const & x, Self const & y) -> Boolean { return y < x; }
	friend auto operator<=(Self const & x, Self const & y) -> Boolean { return !static_cast<bool>(y < x); }
	friend auto operator>=(Self const & x, Self const & y) -> Boolean { return !static_cast<bool>(x < y); }

public:
	Element elements[N > 0 ? N : 1];
}; // struct FixedArray< TElement, S >

} // namespace Container

} // namespace BR