#pragma once

#include <libbr/config.hpp>
#include "out_of_range_exception.hpp"
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/type_operate/is_nothrow_swappable.hpp>
#include <libbr/utility/current_function.hpp>
#include <libbr/utility/current_function.hpp>
#include <libbr/utility/integer_constant.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename TElement, Size S >
class Array {
	using Element              = TElement;
	using Reference            = Element &;
	using ConstReference       = Element const &;
	using Pointer              = Element *;
	using ConstPointer         = Element const *;
	using Iterator             = Pointer;
	using ConstIterator        = ConstPointer;
	using Size                 = BR::Size;
	using Difference           = PointerDifference;
	using ReverseIterator      = BR::ReverseIterator< Iterator >;
	using ConstReverseIterator = BR::ReverseIterator< ConstIterator >;

	void fill(Element const & element) {
		// TODO: fill_n(m_elements, S, element);
	}

	void swap(Array & array) noexcept(
		noexcept(IsNothrowSwappable< Element [S] >::value)
	) {
		swap(m_elements, array.m_elements);
	}

	Iterator begin() noexcept {
		return Iterator(m_elements);
	}

	ConstIterator begin() const noexcept {
		return ConstIterator(m_elements);
	}

	Iterator end() noexcept {
		return Iterator(m_elements + S);
	}

	ConstIterator end() const noexcept {
		return ConstIterator(m_elements + S);
	}


	ReverseIterator rbegin() noexcept {
		return ReverseIterator(end());
	}

	ConstReverseIterator rbegin() const noexcept {
		return ConstReverseIterator(end());
	}

	ReverseIterator rend() noexcept {
		return ReverseIterator(begin());
	}

	ConstReverseIterator rend() const noexcept {
		return ConstReverseIterator(begin());
	}

	ConstIterator cbegin() const noexcept {
		return begin();
	}

	ConstIterator crbegin() const noexcept {
		return rbegin();
	}

	ConstIterator cend() const noexcept {
		return end();
	}

	ConstIterator crend() const noexcept {
		return rend();
	}

	constexpr Size size() const noexcept {
		return S;
	}

	constexpr Size max_size() const noexcept {
		return S;
	}

	constexpr bool empty() const noexcept {
		return S == 0;
	}

	               Reference operator[](Size i)       { return m_elements[i]; }
	constexpr ConstReference operator[](Size i) const { return m_elements[i]; }

	Reference at(Size i) {
		if (i >= S) {
			throw IndexOutOfRangeException(BR_CURRENT_FUNCTION);
		}
		return m_elements[i];
	}

	BR_CONSTEXPR_AFTER_CXX11 ConstReference at(Size i) const {
		if (i >= S) {
			throw IndexOutOfRangeException(BR_CURRENT_FUNCTION);
		}
		return m_elements[i];
	}

	               Reference front()       { return m_elements[0]; }
	constexpr ConstReference front() const { return m_elements[0]; }

	               Reference back()       { return m_elements[S > 0 ? S - 1 : 0]; }
	constexpr ConstReference back() const { return m_elements[S > 0 ? S - 1 : 0]; }

	Element       * data()       noexcept { return m_elements; }
	Element const * data() const noexcept { return m_elements; }

private:
	Element m_elements[S > 0 ? S : 1];
}; // struct Array< TElement, S >

template< typename T, Size S >
inline bool operator==(Array< T, S > const & X, Array< T, S > const & Y) {
	// TODO: return equal(X.begin(), X.end(), Y.begin());
	return false;
}

template< typename T, Size S >
inline bool operator!=(Array< T, S > const & X, Array< T, S > const & Y) {
	return !(X == Y);
}

template< typename T, Size S >
inline bool operator<(Array< T, S > const & X, Array< T, S > const & Y) {
	// TODO: return lexicographical_compare(X.begin(), X.end(), Y.begin(), Y.end());
	return false;
}

template< typename T, Size S >
inline bool operator>(Array< T, S > const & X, Array< T, S > const & Y) {
	return Y < X;
}

template< typename T, Size S >
inline bool operator<=(Array< T, S > const & X, Array< T, S > const & Y) {
	return !(Y < X);
}

template< typename T, Size S >
inline bool operator>=(Array< T, S > const & X, Array< T, S > const & Y) {
	return !(X < Y);
}

template< typename T, Size S>
void swap(Array< T, S > & x, Array< T, S > & y) noexcept(IsNothrowSwappable< Array< T, S > >::value) {
	x.swap(y);
}

template< typename T >
struct TupleSize;

template< typename T, Size S >
struct TupleSize< Array< T, S > > : IntegerConstant< Size, S > {};

template< Size I, typename T >
struct TypeTupleElement;

template< Size I, typename T, Size S >
struct TypeTupleElement< I, Array< T, S > > : TypeWrapper< T > {};

template< Size I, typename T, Size S >
inline BR_CONSTEXPR_AFTER_CXX11 T & get(Array< T, S > & A) noexcept  {
	static_assert(I < S, "Index out of bounds.");
	return A[I];
}

template< Size I, typename T, Size S >
inline BR_CONSTEXPR_AFTER_CXX11 T const & get(Array< T, S > const & A) noexcept  {
	static_assert(I < S, "Index out of bounds.");
	return A[I];
}

template< Size I, typename T, Size S >
inline BR_CONSTEXPR_AFTER_CXX11 T && get(Array< T, S > && A) noexcept  {
	static_assert(I < S, "Index out of bounds.");
	return move(A[I]);
}

} // namespace BR