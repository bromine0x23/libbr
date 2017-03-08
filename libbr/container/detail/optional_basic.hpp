#pragma once

#include <libbr/config.hpp>
#include <libbr/container/in_place_tag.hpp>
#include <libbr/memory/construct_at.hpp>
#include <libbr/memory/destroy_at.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/has_trivial_destructor.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace Container {

template< typename TValue, Boolean = HasTrivialDestructor<TValue>{} >
class OptionalBasic;

template< typename TValue >
class OptionalBasic< TValue, true > {
	using Value = TValue;

protected:
	constexpr OptionalBasic() noexcept : m_empty(), m_engaged(false) {
	}

	OptionalBasic(OptionalBasic const & optional) : m_engaged(optional.m_engaged) {
		if (m_engaged) {
			construct_at(address_of(m_value), optional.m_value);
		}
	}

	OptionalBasic(OptionalBasic && optional) noexcept(HasNothrowMoveConstructor<Value>{}) : m_engaged(optional.m_engaged) {
		if (m_engaged) {
			construct_at(address_of(m_value), move(optional.m_value));
		}
	}

	constexpr OptionalBasic(Value const & value) : m_value(value), m_engaged(true) {
	}

	constexpr OptionalBasic(Value && value) : m_value(move(value)), m_engaged(true) {
	}

	template<typename ... TArgs>
	constexpr explicit
	OptionalBasic(InPlaceTag, TArgs &&... args) : m_value(forward<TArgs>(args)...), m_engaged(true) {
	}

	~OptionalBasic() = default;

protected:
	struct Empty {};
	union {
		Empty m_empty;
		Value m_value;
	};
	bool m_engaged;
}; // class OptionalBasic< TValue, true >

template< typename TValue >
class OptionalBasic< TValue, false > {
	using Value = TValue;

protected:
	constexpr OptionalBasic() noexcept : m_empty(), m_engaged(false) {
	}

	OptionalBasic(OptionalBasic const & optional) : m_engaged(optional.m_engaged) {
		if (m_engaged) {
			construct_at(address_of(m_value), optional.m_value);
		}
	}

	OptionalBasic(OptionalBasic && optional) noexcept(HasNothrowMoveConstructor<Value>{}) : m_engaged(optional.m_engaged) {
		if (m_engaged) {
			construct_at(address_of(m_value), move(optional.m_value));
		}
	}

	constexpr OptionalBasic(Value const & value) : m_value(value), m_engaged(true) {
	}

	constexpr OptionalBasic(Value && value) : m_value(move(value)), m_engaged(true) {
	}

	template<typename ... TArgs>
	constexpr explicit OptionalBasic(InPlaceTag, TArgs &&... args) : m_value(forward<TArgs>(args)...), m_engaged(true) {
	}

	~OptionalBasic() {
		if (m_engaged) {
			m_value.~Value();
		}
	}

protected:
	struct Empty {};
	union {
		Empty m_empty;
		Value m_value;
	};
	bool m_engaged;
}; // class OptionalBasic< TValue, false >

} // namespace Container
} // namespace Detail
} // namespace BR