/**
 * @file
 * @brief Optional
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/in_place_tag.hpp>
#include <libbr/container/null_optional_tag.hpp>
#include <libbr/container/detail/optional_basic.hpp>
#include <libbr/container/detail/throw_optional_access_exception.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/decay.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_copy_constructor.hpp>
#include <libbr/type_traits/has_move_constructor.hpp>
#include <libbr/type_traits/has_nothrow_destructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
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
#include <libbr/type_traits/remove_const_volatile.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Container {

/**
 * @brief Manages an \e optional contained value, i.e. a value that may or may not be present.
 * @tparam T Type of element to contain.
 */
template<typename T>
class Optional;

template< typename TValue >
inline void swap(Optional<TValue> & x, Optional<TValue> & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

template< typename TValue >
constexpr inline auto make_optional(TValue && value) -> Optional< Decay<TValue> > {
	return Optional< Decay<TValue> >(forward<TValue>(value));
}

} // namespace Container



inline namespace Container {

template< typename TValue >
class Optional :
	private Detail::Container::Optional::Basic<TValue>,
	private EqualityComparable< Optional<TValue> >,
	private EqualityComparable< Optional<TValue>, NullOptionalTag >,
	private EqualityComparable< Optional<TValue>, TValue >
{
private:
	using Base = Detail::Container::Optional::Basic<TValue>;

public:
	using Value = TValue;

	static_assert(NotReference<Value>{}, "Instantiation of Optional with a reference type is ill-formed.");
	static_assert(
		NotSame<RemoveConstVolatile<Value>, InPlaceTag>{},
		"Instantiation of optional with a in_place_t type is ill-formed."
	);
	static_assert(
		NotSame<RemoveConstVolatile<Value>, NullOptionalTag>{},
		"Instantiation of optional with a in_place_t type is ill-formed."
	);
	static_assert(IsObject<Value>{}, "Instantiation of optional with a non-object type is undefined behavior.");
	static_assert(
		HasNothrowDestructor<Value>{},
		"Instantiation of optional with an object type that is not noexcept destructible is undefined behavior."
	);

	constexpr Optional() noexcept {
	}

	Optional(Optional const &) = default;

	Optional(Optional &&) = default;

	constexpr Optional(NullOptionalTag) noexcept {
	}

	constexpr Optional(Value const & value) : Base(value) {
	}

	constexpr Optional(Value && value) : Base(move(value)) {
	}

	template<typename ... TArgs, typename = EnableIf< IsConstructible<Value, TArgs ...> > >
	constexpr explicit Optional(InPlaceTag, TArgs &&... args) : Base(in_place_tag, forward<TArgs>(args)...) {
	}

	template<typename TOtherValue, typename ... TArgs, typename = EnableIf< IsConstructible<Value, InitializerList<TOtherValue> &, TArgs ...> > >
	constexpr explicit Optional(InPlaceTag, InitializerList<TOtherValue> list, TArgs &&... args) : Base(
		in_place_tag, list, forward<TArgs>(args)...
	) {
	}

	~Optional() = default;

	auto operator=(NullOptionalTag) noexcept -> Optional & {
		if (this->m_engaged) {
			this->m_value.~Value();
			this->m_engaged = false;
		}
		return *this;
	}

	auto operator=(Optional const &optional) -> Optional & {
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

	auto operator=(
		Optional &&optional
	) noexcept(BooleanAnd<HasNothrowMoveConstructor<Value>, HasNothrowMoveAssignment<Value> >{}) -> Optional & {
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

	template<typename TOtherValue, typename = EnableIf<BooleanAnd<IsSame<Value, Decay<TOtherValue> >, IsConstructible<Value, TOtherValue>, IsAssignable<Value &, TOtherValue> > > >
	auto operator=(TOtherValue &&value) -> Optional & {
		if (this->m_engaged) {
			this->m_value = forward<TOtherValue>(value);
		} else {
			::new(address_of(this->m_value)) Value(forward<TOtherValue>(value));
			this->m_engaged = true;
		}
		return *this;
	}

	template<typename ... TArgs, typename = EnableIf<IsConstructible<Value, TArgs...> > >
	void emplace(TArgs &&... args) {
		operator=(null_optional_tag);
		::new(address_of(this->m_value)) Value(forward<TArgs>(args)...);
		this->m_engaged = true;
	}

	template<typename TOtherValue, typename ... TArgs, typename = EnableIf<IsConstructible<Value, InitializerList<TOtherValue> &, TArgs...> > >
	void emplace(InitializerList<TOtherValue> list, TArgs &&... args) {
		operator=(null_optional_tag);
		::new(address_of(this->m_value)) Value(list, forward<TArgs>(args)...);
		this->m_engaged = true;
	}

	void swap(Optional &optional) noexcept(BooleanAnd<HasNothrowMoveConstructor<Value>, IsNothrowSwappable<Value> >{}) {
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

	/**
	 * ->
	 * @return
	 */
	//@{
	BR_CONSTEXPR_AFTER_CXX11 auto operator->() const -> Value const * {
		BR_ASSERT(this->m_engaged);
		return m_operator_arrow(HasOperatorAddressOf<Value>());
	}

	BR_CONSTEXPR_AFTER_CXX11 auto operator->() -> Value const * {
		BR_ASSERT(this->m_engaged);
		return address_of(this->m_value);
	}
	//@}

	/**
	 * *
	 * @return
	 */
	//@{
	BR_CONSTEXPR_AFTER_CXX11 auto operator*() const & -> Value const & {
		BR_ASSERT(this->m_engaged);
		return this->m_value;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto operator*() & -> Value & {
		BR_ASSERT(this->m_engaged);
		return this->m_value;
	}
	//@}

	constexpr explicit operator bool() const noexcept {
		return this->m_engaged;
	}

	/**
	 * @return
	 */
	//@{
	BR_CONSTEXPR_AFTER_CXX11 auto value() const -> Value const & {
		if (!this->m_engaged) {
			Detail::Container::throw_optional_access_exception();
		}
		return this->m_value;
	}
	//@}

	/**
	 * @return
	 */
	//@{
	BR_CONSTEXPR_AFTER_CXX11 auto value() -> Value & {
		if (!this->m_engaged) {
			Detail::Container::throw_optional_access_exception();
		}
		return this->m_value;
	}
	//@}

	/**
	 * @tparam TOtherValue
	 * @param value
	 * @return
	 */
	//@{
	template<typename TOtherValue>
	constexpr auto value_or(TOtherValue &&value) const & -> Value {
		static_assert(HasCopyConstructor<Value>{}, "Optional<T>::value_or: Value must be copy constructible");
		static_assert(
			IsConvertible<TOtherValue, Value>{}, "Optional<T>::value_or: TOtherValue must be convertible to Value"
		);
		return this->m_engaged ? this->m_value : static_cast<Value>(forward<TOtherValue>(value));
	}

	template<typename TOtherValue>
	BR_CONSTEXPR_AFTER_CXX11 auto value_or(TOtherValue &&value) && -> Value {
		static_assert(HasCopyConstructor<Value>{}, "Optional<T>::value_or: Value must be copy constructible");
		static_assert(
			IsConvertible<TOtherValue, Value>{}, "Optional<T>::value_or: TOtherValue must be convertible to Value"
		);
		return this->m_engaged ? move(this->m_value) : static_cast<Value>(forward<TOtherValue>(value));
	}
	//@}

	/**
	 * ==
	 * @param y
	 * @return
	 */
	//@{
	constexpr auto operator==(Optional const &y) const -> bool {
		return operator bool() == y.operator bool() && (!operator bool() || operator*() == y.operator*());
	}

	constexpr auto operator==(NullOptionalTag) const -> bool {
		return !operator bool();
	}

	constexpr auto operator==(Value value) const -> bool {
		return operator bool() ? operator*() == value : false;
	}
	//@}

	/**
	 * <
	 * @param y
	 * @return
	 */
	//@{
	constexpr auto operator<(Optional const &y) const -> bool {
		return !y.operator bool() && (!operator bool() || operator*() < y.operator*());
	}

	constexpr auto operator<(NullOptionalTag) const -> bool {
		return false;
	}

	constexpr auto operator<(Value value) const -> bool {
		return operator bool() ? operator*() < value : true;
	}
	//@}

	constexpr auto operator>(Optional const &y) const -> bool {
		return y.operator<(*this);
	}

	/**
	 * >
	 * @param y
	 * @return
	 */
	//@{
	constexpr auto operator>(NullOptionalTag) const -> bool {
		return operator bool();
	}

	constexpr auto operator>(Value value) const -> bool {
		return operator bool() ? value < operator*() : false;
	}
	//@}

	/**
	 * <=
	 * @param y
	 * @return
	 */
	//@{
	constexpr auto operator<=(Optional const &y) const -> bool {
		return !operator>(y);
	}

	constexpr auto operator<=(NullOptionalTag) const -> bool {
		return !operator>(null_optional_tag);
	}

	constexpr auto operator<=(Value value) const -> bool {
		return !operator>(value);
	}
	//@}

	/**
	 * >=
	 * @param y
	 * @return
	 */
	//@{
	constexpr auto operator>=(Optional const &y) const -> bool {
		return !operator<(y);
	}

	constexpr auto operator>=(NullOptionalTag) const -> bool {
		return !operator<(null_optional_tag);
	}

	constexpr auto operator>=(Value value) const -> bool {
		return !operator<(value);
	}
	//@}

private:
	auto m_operator_arrow(BooleanTrue) const -> Value const * {
		return addressof(this->m_value);
	}

	constexpr auto m_operator_arrow(BooleanFalse) const -> Value const * {
		return &this->m_value;
	}

}; // class Optional<T>

template<typename T>
constexpr auto operator<(NullOptionalTag x, Optional<T> const &y) -> bool {
	return y > x;
}

template<typename T>
constexpr auto operator>(NullOptionalTag x, Optional<T> const &y) -> bool {
	return y < x;
}

template<typename T>
constexpr auto operator<=(NullOptionalTag x, Optional<T> const &y) -> bool {
	return y <= x;
}

template<typename T>
constexpr auto operator>=(NullOptionalTag x, Optional<T> const &y) -> bool {
	return y >= x;
}

template<typename T>
constexpr auto operator<(T x, Optional<T> const &y) -> bool {
	return y > x;
}

template<typename T>
constexpr auto operator>(T x, Optional<T> const &y) -> bool {
	return y < x;
}

template<typename T>
constexpr auto operator<=(T x, Optional<T> const &y) -> bool {
	return y <= x;
}

template<typename T>
constexpr auto operator>=(T x, Optional<T> const &y) -> bool {
	return y >= x;
}

} // namespace Container

} // namespace BR