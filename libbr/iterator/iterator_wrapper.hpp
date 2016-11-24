/**
 * @file
 * @brief 迭代器包装
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_convertible.hpp>

namespace BR {

template<typename TIterator >
class PointerIterator;


template<typename TElement >
class PointerIterator {
public:
	using Iterator = TElement *;

	using Category = typename IteratorTraits<Iterator>::Category;

	using Element = typename IteratorTraits<Iterator>::Element;

	using Pointer = typename IteratorTraits<Iterator>::Pointer;

	using Reference = typename IteratorTraits<Iterator>::Reference;

	using Difference = typename IteratorTraits<Iterator>::Difference;

public:
	PointerIterator() noexcept: m_pointer() {
	}

	PointerIterator(PointerIterator const & wrapper) = default;

	template< typename TOtherElement>
	PointerIterator(PointerIterator<TOtherElement> const & wrapper, EnableIf< IsConvertible< TOtherElement *, TElement * > > * = nullptr) noexcept: m_pointer(wrapper.pointer()) {
	}

	~PointerIterator() = default;

	auto operator=(PointerIterator const & wrapper) -> PointerIterator & = default;

	auto operator*() const noexcept -> Reference {
		return *m_pointer;
	}

	auto operator->() const noexcept -> Pointer {
		return m_pointer;
	}

	auto operator++() noexcept -> PointerIterator & {
		++m_pointer;
		return *this;
	}

	auto operator++(int) noexcept -> PointerIterator {
		PointerIterator tmp(*this);
		operator++();
		return tmp;
	}

	auto operator--() noexcept -> PointerIterator & {
		--m_pointer;
		return *this;
	}

	auto operator--(int) noexcept -> PointerIterator {
		PointerIterator result(*this);
		operator--();
		return result;
	}

	auto operator+(Difference n) const noexcept -> PointerIterator {
		PointerIterator result(*this);
		result += n;
		return result;
	}

	auto operator+=(Difference n) noexcept -> PointerIterator & {
		m_pointer += n;
		return *this;
	}

	auto operator-(Difference n) const noexcept -> PointerIterator {
		return *this + (-n);
	}

	auto operator-=(Difference n) noexcept -> PointerIterator & {
		*this += -n;
		return *this;
	}

	auto operator[](Difference i) const noexcept -> Reference {
		return m_pointer[i];
	}

	auto pointer() const noexcept -> Element * {
		return m_pointer;
	}

private:
	Element * m_pointer;
};

} // namespace BR
