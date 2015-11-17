/**
 * @file
 * @brief Optional
 * @author Bromine0x23
 * @since 2015/11/7
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/optional/in_place_tag.hpp>
#include <libbr/optional/null_optional.hpp>
#include <libbr/optional/throw_optional_access_exception.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_traits/has_copy_constructor.hpp>
#include <libbr/type_traits/has_move_constructor.hpp>
#include <libbr/type_traits/has_nothrow_destructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assign.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/has_operator_address_of.hpp>
#include <libbr/type_traits/has_trivial_destructor.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/is_object.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename T >
class Optional;

template< typename T >
inline void swap(Optional<T> & x, Optional<T> & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

template< typename TValue >
constexpr inline auto make_optional(TValue && value) -> Optional< Decay<TValue> > {
	return Optional< Decay<TValue> >(forward<TValue>(value));
}

namespace Detail {
namespace Utility {

template< typename T, bool = HasTrivialDestructor<T>::value >
class OptionalStorage;

template< typename T >
class OptionalStorage< T, true > {
	using Value = T;

protected:
	constexpr OptionalStorage() noexcept :  m_null_state('\0'), m_engaged(false) {
	}

	OptionalStorage(OptionalStorage const & storage) :  m_engaged(storage.m_engaged) {
		if (m_engaged) {
			::new(address_of(m_value)) Value(storage.m_value);
		}
	}

	OptionalStorage(OptionalStorage && storage) noexcept(HasNothrowMoveConstructor<Value>::value) :  m_engaged(storage.m_engaged) {
		if (m_engaged) {
			::new(address_of(m_value)) Value(move(storage.m_value));
		}
	}

	constexpr OptionalStorage(Value const & value) :  m_value(value), m_engaged(true) {
	}

	constexpr OptionalStorage(Value && value) :  m_value(move(value)), m_engaged(true) {
	}

	template< typename ... TArgs>
	constexpr explicit OptionalStorage(InPlaceTag, TArgs && ... args) : m_value(forward<TArgs>(args)...), m_engaged(true) {
	}

	~OptionalStorage() = default;

protected:
	union {
		char m_null_state;
		Value m_value;
	};
	bool m_engaged;
};

template< typename T >
class OptionalStorage< T, false > {
	using Value = T;

protected:
	constexpr OptionalStorage() noexcept :  m_null_state('\0'), m_engaged(false) {
	}

	OptionalStorage(OptionalStorage const & storage) :  m_engaged(storage.m_engaged) {
		if (m_engaged) {
			::new(address_of(m_value)) Value(storage.m_value);
		}
	}

	OptionalStorage(OptionalStorage && storage) noexcept(HasNothrowMoveConstructor<Value>::value) :  m_engaged(storage.m_engaged) {
		if (m_engaged) {
			::new(address_of(m_value)) Value(move(storage.m_value));
		}
	}

	constexpr OptionalStorage(Value const & value) :  m_value(value), m_engaged(true) {
	}

	constexpr OptionalStorage(Value && value) :  m_value(move(value)), m_engaged(true) {
	}

	template< typename ... TArgs>
	constexpr explicit OptionalStorage(InPlaceTag, TArgs && ... args) : m_value(forward<TArgs>(args)...), m_engaged(true) {
	}

	~OptionalStorage() {
		if (m_engaged) {
			m_value.~Value();
		}
	}

protected:
	union {
		char m_null_state;
		Value m_value;
	};
	bool m_engaged;
};

} // namespace Utility
} // namespace Detail

template< typename T >
class Optional : private Detail::Utility::OptionalStorage<T> {
	using Base = Detail::Utility::OptionalStorage<T>;

public:
	using Value = T;

	static_assert(NotReference<Value>::value, "Instantiation of Optional with a reference type is ill-formed.");
	static_assert(NotSame< RemoveConstVolatile<Value>, InPlaceTag >::value, "Instantiation of optional with a in_place_t type is ill-formed.");
	static_assert(NotSame< RemoveConstVolatile<Value>, NullOptional >::value, "Instantiation of optional with a in_place_t type is ill-formed.");
	static_assert(IsObject<Value>::value, "Instantiation of optional with a non-object type is undefined behavior.");
	static_assert(HasNothrowDestructor<Value>::value, "Instantiation of optional with an object type that is not noexcept destructible is undefined behavior.");

	constexpr Optional() noexcept {
	}

	Optional(Optional const &) = default;

	Optional(Optional &&) = default;

	~Optional() = default;

	constexpr Optional(NullOptional) noexcept {
	}

	constexpr Optional(Value const & value) : Base(value) {
	}

	constexpr Optional(Value && value) : Base(move(value)) {
	}

	template< typename ... TArgs, typename = EnableIf< IsConstructible< Value, TArgs ...> > >
	constexpr explicit Optional(InPlaceTag, TArgs && ... args) : Base(in_place_tag, forward<TArgs>(args)...) {
	}

	template< typename TOtherValue, typename ... TArgs, typename = EnableIf< IsConstructible< Value, InitializerList<TOtherValue> &, TArgs ...> > >
	constexpr explicit Optional(InPlaceTag, InitializerList<TOtherValue> list, TArgs && ... args) : Base(in_place_tag, list, forward<TArgs>(args)...) {
	}

	auto operator=(NullOptional) noexcept -> Optional & {
		if (this->m_engaged) {
			this->m_value.~Value();
			this->m_engaged = false;
		}
		return *this;
	}

	auto operator=(Optional const & optional) -> Optional & {
		if (this->m_engaged == optional.m_engaged) {
			if (this->m_engaged) {
				this->m_value = optional.m_value;
			}
		} else {
			if (this->m_engaged) {
				this->m_value.~Value();
			} else {
				::new(address_of(this->m_value)) Value(optional.m_value);
			}
			this->m_engaged = optional.m_engaged;
		}
		return *this;
	}

	auto operator=(Optional && optional) noexcept(BooleanAnd< HasNothrowMoveConstructor<Value>, HasNothrowMoveAssign<Value> >::value) -> Optional & {
		if (this->m_engaged == optional.m_engaged) {
			if (this->m_engaged) {
				this->m_value = move(optional.m_value);
			}
		} else {
			if (this->m_engaged) {
				this->m_value.~Value();
			} else {
				::new(address_of(this->m_value)) Value(move(optional.m_value));
			}
			this->m_engaged = optional.m_engaged;
		}
		return *this;
	}

	template< typename TOtherValue, typename = EnableIf< BooleanAnd< IsSame< Value, Decay<TOtherValue> >, IsConstructible< Value, TOtherValue >, IsAssignable< Value &, TOtherValue > > > >
	auto operator=(TOtherValue && value)-> Optional & {
		if (this->m_engaged) {
			this->m_value = forward<TOtherValue>(value);
		} else {
			::new(address_of(this->m_value)) Value(forward<TOtherValue>(value));
			this->m_engaged = true;
		}
		return *this;
	}

	template< typename ... TArgs, typename = EnableIf< IsConstructible< Value, TArgs... > > >
	void emplace(TArgs && ... args) {
		operator=(null_optional);
		::new(address_of(this->m_value)) Value(forward<TArgs>(args)...);
		this->m_engaged = true;
	}

	template< typename TOtherValue, typename ... TArgs, typename = EnableIf< IsConstructible< Value, InitializerList<TOtherValue> &, TArgs... > > >
	void emplace(InitializerList<TOtherValue> list, TArgs && ... args) {
		operator=(null_optional);
		::new(address_of(this->m_value)) Value(list, forward<TArgs>(args)...);
		this->m_engaged = true;
	}

	void swap(Optional & optional) noexcept(BooleanAnd< HasNothrowMoveConstructor<Value>, IsNothrowSwappable<Value> >::value) {
		using BR::swap;
		if (this->m_engaged == optional.m_engaged) {
			if (this->m_engaged) {
				swap(this->m_value, optional.m_value);
			}
		} else {
			if (this->m_engaged) {
				::new(address_of(optional.m_value)) Value(move(this->m_value));
				this->m_value.~Value();
			} else {
				::new(address_of(this->m_value)) Value(move(optional.m_value));
				optional.m_value.~Value();
			}
			swap(this->m_engaged, optional.m_engaged);
		}
	}

	BR_CONSTEXPR_AFTER_CXX11 auto operator->() const -> Value const * {
		BR_ASSERT(this->m_engaged);
		return m_operator_arrow(HasOperatorAddressOf<Value>());
	}

	BR_CONSTEXPR_AFTER_CXX11 auto operator->() -> Value const * {
		BR_ASSERT(this->m_engaged);
		return address_of(this->m_value);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto operator*() const & -> Value const & {
		BR_ASSERT(this->m_engaged);
		return this->m_value;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto operator*() & -> Value & {
		BR_ASSERT(this->m_engaged);
		return this->m_value;
	}

	constexpr explicit operator bool() const noexcept {
		return this->m_engaged;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto value() const -> Value const & {
		if (!this->m_engaged) {
			throw_optional_access_exception();
		}
		return this->m_value;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto value() -> Value & {
		if (!this->m_engaged) {
			throw_optional_access_exception();
		}
		return this->m_value;
	}

	template< typename TOtherValue >
	constexpr auto value_or(TOtherValue && value) const & -> Value {
		static_assert(HasCopyConstructor<Value>::value, "Optional<T>::value_or: Value must be copy constructible");
		static_assert(IsConvertible< TOtherValue, Value>::value, "Optional<T>::value_or: TOtherValue must be convertible to Value");
		return this->m_engaged ? this->m_value : static_cast<Value>(forward<TOtherValue>(value));
	}

	template< typename TOtherValue >
	constexpr auto value_or(TOtherValue && value) && -> Value {
		static_assert(HasCopyConstructor<Value>::value, "Optional<T>::value_or: Value must be copy constructible");
		static_assert(IsConvertible< TOtherValue, Value>::value, "Optional<T>::value_or: TOtherValue must be convertible to Value");
		return this->m_engaged ? move(this->m_value) : static_cast<Value>(forward<TOtherValue>(value));
	}

	constexpr auto operator==(Optional const & y) const -> bool {
		return operator bool() == y.operator bool() && (!operator bool() || operator*() == y.operator*());
	}

	constexpr auto operator==(NullOptional) const -> bool {
		return !operator bool();
	}

	constexpr auto operator==(Value value) const -> bool {
		return operator bool() ? operator*() == value : false;
	}

	constexpr auto operator!=(Optional const & y) const -> bool {
		return !operator==(y);
	}

	constexpr auto operator!=(NullOptional) const -> bool {
		return !operator==(null_optional);
	}

	constexpr auto operator!=(Value value) const -> bool {
		return !operator==(value);
	}

	constexpr auto operator<(Optional const & y) const -> bool {
		return !y.operator bool() && (!operator bool() || operator*() < y.operator*());
	}

	constexpr auto operator<(NullOptional) const -> bool {
		return false;
	}

	constexpr auto operator<(Value value) const -> bool {
		return operator bool() ? operator*() < value : true;
	}

	constexpr auto operator>(Optional const & y) const -> bool {
		return y.operator<(*this);
	}

	constexpr auto operator>(NullOptional) const -> bool {
		return operator bool();
	}

	constexpr auto operator>(Value value) const -> bool {
		return operator bool() ? value < operator*() : false;
	}

	constexpr auto operator<=(Optional const & y) const -> bool {
		return !operator>(y);
	}

	constexpr auto operator<=(NullOptional) const -> bool {
		return !operator>(null_optional);
	}

	constexpr auto operator<=(Value value) const -> bool {
		return !operator>(value);
	}

	constexpr auto operator>=(Optional const & y) const -> bool {
		return !operator<(y);
	}

	constexpr auto operator>=(NullOptional) const -> bool {
		return !operator<(null_optional);
	}

	constexpr auto operator>=(Value value) const -> bool {
		return !operator<(value);
	}

private:
	auto m_operator_arrow(BooleanTrue) const -> Value const * {
		return addressof(this->m_value);
	}

	constexpr auto m_operator_arrow(BooleanFalse) const -> Value const * {
		return &this->m_value;
	}

}; // class Optional<T>


} // namespace BR