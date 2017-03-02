/**
 * @file
 * @brief 枚举器
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/invoke.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/iterator/prev.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

/**
 * 枚举器
 * @tparam TIterator
 */
template< typename TIterator >
class Enumerator;

/**
 * @param begin
 * @param end
 * @return
 */
template< typename TIterator >
constexpr auto make_enumerator(TIterator begin, TIterator end) noexcept -> Enumerator<TIterator> {
	return Enumerator<TIterator>(begin, end);
}



namespace Detail {
namespace Enumerator {

template< typename TIterator, bool = IsBaseOf< BidirectionalTraversalTag, typename IteratorTraits<TIterator>::Category >{} >
class Base;

template< typename TIterator >
class Base< TIterator, true > {
public:
	using Iterator = TIterator;

	using Element = typename IteratorTraits<Iterator>::Element;

	using Reference = typename IteratorTraits<Iterator>::Reference;

public:
	constexpr Base(Iterator begin, Iterator end) : m_begin(begin), m_end(end), m_current(prev(begin)) {
	}

	constexpr auto begin() const noexcept -> Iterator {
		return m_begin;
	}

	constexpr auto end() const noexcept -> Iterator {
		return m_end;
	}

	auto move() -> bool {
		if (m_current != m_end) {
			++m_current;
		}
		return m_current != m_end;
	}

	auto next() -> Reference {
		if (move()) {
			return peek();
		}
	}

	auto peek() const -> Reference {
		return *m_current;
	}

	void rewind() {
		m_current = prev(m_begin);
	}

protected:
	void m_rewind() {
		m_current = prev(m_begin);
	}

private:
	TIterator const m_begin, m_end;
	TIterator m_current;
};

template< typename TIterator >
class Base< TIterator, false > {
public:
	using Iterator = TIterator;

	using Element = typename IteratorTraits<Iterator>::Element;

	using Reference = typename IteratorTraits<Iterator>::Reference;

public:
	constexpr Base(Iterator begin, Iterator end) : m_begin(begin), m_end(end), m_current(begin) {
	}

	constexpr auto begin() const noexcept -> Iterator {
		return m_begin;
	}

	constexpr auto end() const noexcept -> Iterator {
		return m_end;
	}

	auto move() -> bool {
		if (m_first_move) {
			m_current = m_begin;
			m_first_move = false;
		} else {
			if (m_current != m_end) {
				++m_current;
			}
		}
		return m_current != m_end;
	}

	auto next() -> Reference {
		if (move()) {
			return peek();
		}
	}

	auto peek() const -> Reference {
		return *m_current;
	}

	void rewind() {
		m_first_move = true;
	}

protected:
	void m_rewind() {
		m_first_move = true;
	}

private:
	TIterator const m_begin, m_end;
	TIterator m_current;
	bool m_first_move = true;
};

} // namespace Enumerator
} // namespace Detail

template< typename TIterator >
class Enumerator : public Detail::Enumerator::Base<TIterator> {
private:
	using Base = Detail::Enumerator::Base<TIterator>;

public:
	using Iterator = typename Base::Iterator;

	using Element = typename Base::Element;

	using Reference = typename Base::Reference;

public:
	constexpr Enumerator(Iterator begin, Iterator end) : Base(begin, end) {
	}

	constexpr auto each() const noexcept -> Enumerator {
		return make_enumerator(this->begin(), this->end());
	}

	template< typename TFunctor, typename ... TArgs >
	auto each(TFunctor functor, TArgs && ... args) -> Enumerator & {
		for (auto iterator = this->begin(); iterator != this->end(); ++iterator) {
			invoke(functor, *iterator, forward<TArgs>(args)...);
		}
		return *this;
	}

	template< typename TFunctor, typename ... TArgs >
	auto each(TFunctor functor, TArgs && ... args) const -> Enumerator const & {
		for (auto iterator = this->begin(); iterator != this->end(); ++iterator) {
			invoke(functor, *iterator, forward<TArgs>(args)...);
		}
		return *this;
	}

	auto rewind() -> Enumerator & {
		Base::rewind();
		return *this;
	}
};

} // namespace BR
