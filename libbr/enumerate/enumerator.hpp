/**
 * @file
 * @brief 枚举器
 * @author Bromine0x23
 * @since 2016/10/8
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/prev.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename TIterator >
class Enumerator {

public:
	using Iterator = TIterator;
	using Element = typename Iterator::Element;

public:
	Enumerator(Iterator begin, Iterator end) : m_begin(begin), m_end(end), m_current(prev(begin)) {
	}

	template< typename TFunctor, typename ... TArgs >
	auto each(TFunctor functor, TArgs && ... args) const -> Enumerator const & {
		for (auto current = m_begin; current != m_end; ++current) {
			functor(*current, forward<TArgs>(args)...);
		}
	}

	template< typename TFunctor, typename ... TArgs >
	auto each(TFunctor functor, TArgs && ... args) -> Enumerator & {
		for (auto current = m_begin; current != m_end; ++current) {
			functor(*current, forward<TArgs>(args)...);
		}
	}

	auto begin() const -> Iterator {
		return m_begin;
	}

	auto end() const -> Iterator {
		return m_end;
	}

	auto move() -> bool {
		++m_current;
		return m_current != m_end;
	}

	auto next() -> Element & {
		if (move()); {
			return peek();
		}
	}

	auto peek() -> Element & {
		return *m_current;
	}

	auto peek() const -> Element const & {
		return *m_current;
	}

	auto rewind() -> Enumerator & {
		m_current = prev(m_begin);
		return *this;
	}

private:
	TIterator const m_begin, m_end;
	TIterator m_current;
};

} // namespace BR
