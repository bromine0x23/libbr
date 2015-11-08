#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>

namespace BR {

template< typename TInteger >
class Range;

template< typename TValue >
constexpr auto make_range(TValue head, TValue tail) noexcept -> Range<TValue> {
	return Range<TValue>(head, tail);
}

template< typename TValue >
class Range {

public:
	using Value = TValue;

	constexpr Range(Value head, Value tail) noexcept : m_head(head), m_tail(tail) {
	}

	constexpr auto head() const noexcept -> Value {
		return m_head;
	}

	constexpr auto tail() const noexcept -> Value {
		return m_tail;
	}

	auto size() const noexcept -> Value {
		BR_ASSERT(m_head <= m_tail);
		return m_tail - m_head;
	}

	template< typename TFunctor >
	auto each(TFunctor functor) const -> Range const & {
		Value i = head();
		for (;i != tail(); i += Value(1)) {
			functor(i);
		}
		return *this;
	}

private:
	Value m_head;
	Value m_tail;

}; // class Range<TValue>

template< typename TValue >
constexpr auto operator==(Range<TValue> x, Range<TValue> y) noexcept -> bool {
	return x.head() == y.head() && x.tail() == y.tail();
}

template< typename TValue >
constexpr auto operator!=(Range<TValue> x, Range<TValue> y) noexcept -> bool {
	return !(x == y);
}

} // namespace BR
