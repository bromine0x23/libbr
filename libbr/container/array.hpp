#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Container {

template< typename TElement, Size S >
struct Array {
	using Element        = TElement;
	using Reference      = Element &;
	using ConstReference = Element const &;
	using Pointer        = Element *;
	using ConstPointer   = Element const *;
	using Iterator       = Pointer;
	using ConstIterator  = ConstPointer;
	using Size           = BR::Size;
	using Difference     = PointerDifference;

	/* TODO
	using ReverseIterator =;
	using ConstReverseIterator =;
	 */

	void fill(Element const & element) {
		// TODO: fill_n(m_elements, S, element);
	}

	void swap(Array & array) noexcept(
		noexcept(BR::swap(make_reference< Element [S] >(), make_reference< Element [S] >()))
	) {
		BR::swap(m_elements, array.m_elements);
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

	/* TODO
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
	 */

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
			// TODO: throw out_of_range("Array::at");
		}
		return m_elements[i];
	}

	BR_CONSTEXPR_AFTER_CPP11 ConstReference at(Size i) const {
		if (i >= S) {
			// TODO: throw out_of_range("Array::at");
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
}; // struct Array

template< typename TElement, Size S>
void swap(Array< TElement, S > & x, Array< TElement, S > & y) noexcept(
	noexcept(make_reference< Array< TElement, S > >().swap(make_reference< Array< TElement, S > >()))
) {
	x.swap(y);
}

} // namespace Container
} // namespace BR