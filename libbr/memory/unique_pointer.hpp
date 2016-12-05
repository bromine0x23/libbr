/**
 * @file
 * @brief class UniquePointer
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/assert/assert.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/memory/default_deleter.hpp>
#include <libbr/type_traits/add_lvalue_reference.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/remove_extent.hpp>
#include <libbr/type_traits/remove_reference.hpp>
#include <libbr/utility/dummy.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace Memory {

/**
 * UniquePointer
 * @tparam TElement
 * @tparam TDeleter
 */
template< typename TElement, typename TDeleter = DefaultDeleter<TElement> >
class UniquePointer;

/**
 *
 * @tparam TElement
 * @tparam TArgs
 * @param args
 * @return
 */
template< typename TElement, typename... TArgs >
inline auto make_unique_pointer(TArgs &&... args) -> EnableIf< NotArray<TElement>, UniquePointer<TElement> > {
	return UniquePointer<TElement>(new TElement(forward<TArgs>(args)...));
}

/**
 *
 * @tparam TElement
 * @param count
 * @return
 */
template< typename TElement >
inline auto make_unique_pointer(Size count) -> EnableIf< IsArrayUnknownBounds<TElement>, UniquePointer<TElement> > {
	return UniquePointer<TElement>(new RemoveExtent<TElement>[count]());
}


template< typename TElement, typename... TArgs >
inline auto make_unique_pointer(TArgs &&... args) -> EnableIf< IsArrayKnownBounds<TElement> > = delete;

/**
 * swap for UniquePointer
 * @tparam TElement
 * @tparam TDeleter
 * @param x
 * @param y
 */
template< typename TElement, typename TDeleter >
inline void swap(UniquePointer< TElement, TDeleter > & x, UniquePointer< TElement, TDeleter > & y) noexcept {
	x.swap(y);
}

} // namespace Memory



namespace Detail {
namespace Memory {
namespace UniquePointer {

BR_HAS_MEMBER_TYPE(Pointer)

template< typename TElement, typename TDeleter, bool = HasMemberTypePointer<TDeleter>{} >
struct TypePointer;

template< typename TElement, typename TDeleter >
using Pointer = TypeUnwrap< TypePointer< TElement, TDeleter> >;

template< typename TElement, typename TDeleter >
struct TypePointer< TElement, TDeleter, true > : TypeWrapper< typename TDeleter::Pointer > {
};

template< typename TElement, typename TDeleter >
struct TypePointer< TElement, TDeleter, false > : TypeWrapper< TElement * > {
};

template< typename TDeleter >
using DeleterLValue = Conditional< IsReference<TDeleter>, TDeleter, TDeleter const & >;

template< typename TDeleter >
using DeleterRValue = RemoveReference<TDeleter> &&;

} // namespace UniquePointer
} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TElement, typename TDeleter >
class UniquePointer {

public:
	using Element = TElement;

	using Deleter = TDeleter;

	using Pointer = Detail::Memory::UniquePointer::Pointer< Element, RemoveReference<Deleter> >;

private:
	template< typename TOtherElement, typename TOtherDeleter >
	using IsConstructible = BooleanAnd<
		NotArray<TOtherElement>,
		IsConvertible< typename UniquePointer< TOtherElement, TOtherDeleter >::Pointer, Pointer >,
		IsConvertible< TOtherDeleter, Deleter >,
		BooleanOr<
			NotReference<Deleter>,
			IsSame< Deleter, TOtherDeleter >
		>
	>;

	template< typename TOtherElement, typename TOtherDeleter >
	using IsAssignable = BooleanAnd<
		NotArray<TOtherElement>,
		IsConvertible< typename UniquePointer< TOtherElement, TOtherDeleter >::Pointer, Pointer >,
		IsAssignable< Deleter &, TOtherDeleter && >
	>;

public:
	constexpr UniquePointer() noexcept : m_impl(Pointer()) {
		static_assert(NotPointer<Deleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	constexpr UniquePointer(NullPointer) noexcept : m_impl(Pointer()) {
		static_assert(NotPointer<Deleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	explicit UniquePointer(Pointer p) noexcept : m_impl(move(p)) {
		static_assert(NotPointer<Deleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	UniquePointer(Pointer p, Detail::Memory::UniquePointer::DeleterLValue<Deleter> d) noexcept : m_impl(p, d) {
	}

	UniquePointer(Pointer p, Detail::Memory::UniquePointer::DeleterRValue<Deleter> d) noexcept : m_impl(p, move(d)) {
		static_assert(NotReference<TDeleter>(), "rvalue deleter bound to reference");
	}

	UniquePointer(UniquePointer && p) noexcept : m_impl(p.release(), forward<Deleter>(p.get_deleter())) {
	}

	template< typename TOtherElement, typename TOtherDeleter >
	UniquePointer(UniquePointer< TOtherElement, TOtherDeleter > && p, EnableIf< IsConstructible< TOtherElement, TOtherDeleter > > * = nullptr ) noexcept : m_impl(p.release(), forward<TOtherDeleter>(p.get_deleter())) {
	}

	~UniquePointer() {
		reset();
	}

	auto operator=(UniquePointer && p) noexcept -> UniquePointer & {
		reset(p.release());
		m_impl.template get<1>() = forward<Deleter>(p.get_deleter());
		return *this;
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator=(UniquePointer< TOtherElement, TOtherDeleter > && p) noexcept -> EnableIf< IsAssignable< TOtherElement, TOtherDeleter >, UniquePointer & > {
		using BR::get;
		reset(p.release());
		m_impl.template get<1>() = forward<TOtherDeleter>(p.get_deleter());
		return *this;
	}

	auto operator=(NullPointer) noexcept -> UniquePointer & {
		reset();
		return *this;
	}

	auto operator*() const -> AddLValueReference<Element> {
		return *(m_impl.template get<0>());
	}

	auto operator->() const noexcept -> Pointer {
		return m_impl.template get<0>();
	}

	auto get() const noexcept -> Pointer {
		return m_impl.template get<0>();
	}

	auto get_deleter() noexcept -> RemoveReference<Deleter> & {
		return m_impl.template get<1>();
	}

	auto get_deleter() const noexcept -> RemoveReference<Deleter> const & {
		return m_impl.template get<1>();
	}

	explicit operator bool() const noexcept {
		return m_impl.template get<0>() != nullptr;
	}

	auto release() noexcept -> Pointer {
		using BR::get;
		auto t = m_impl.template get<0>();
		m_impl.template get<0>() = Pointer();
		return t;
	}

	void reset(Pointer p = Pointer()) noexcept {
		using BR::get;
		auto t = m_impl.template get<0>();
		m_impl.template get<0>() = p;
		if (t != nullptr) {
			m_impl.template get<1>()(t);
		}
	}

	void swap(UniquePointer & p) noexcept {
		m_impl.swap(p.m_impl);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator==(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return get() == y.get();
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator!=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !operator==(y);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return Less<>()(get(), y.get());
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator>(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return y.operator<(*this);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !y.operator<(*this);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator>=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !operator<(y);
	}

	auto operator==(NullPointer) const -> bool {
		return !operator bool();
	}

	auto operator!=(NullPointer) const -> bool {
		return operator bool();
	}

	auto operator<(NullPointer) const -> bool {
		return Less<>()(get(), nullptr);
	}

	auto operator>(NullPointer) const -> bool {
		return Less<>()(nullptr, get());
	}

	auto operator<=(NullPointer) const -> bool {
		return !operator>(nullptr);
	}

	auto operator>=(NullPointer) const -> bool {
		return !operator<(nullptr);
	}

private:
	Tuple< Pointer, Deleter > m_impl;

}; // class UniquePointer< TPointer, TDeleter >

template< typename TElement, typename TDeleter >
class UniquePointer< TElement[], TDeleter > {

public:
	using Element = TElement;

	using Deleter = TDeleter;

	using Pointer = Detail::Memory::UniquePointer::Pointer< Element, RemoveReference<Deleter> >;

private:
	template< typename TOtherPointer >
	using IsCompatible = BooleanOr<
		IsSame< TOtherPointer, Pointer >,
		BooleanAnd<
			IsSame< Pointer, Element * >,
			IsPointer<TOtherPointer>,
			IsConvertible< TOtherPointer, Pointer >
		>
	>;

	template< typename TOtherElement, typename TOtherDeleter >
	using IsConstructible = BooleanAnd<
		IsArray<TOtherElement>,
		IsCompatible< typename UniquePointer< TOtherElement, TOtherDeleter >::Pointer >,
		IsConvertible< TOtherDeleter, Deleter >,
		BooleanOr<
			NotReference<Deleter>,
			IsSame< Deleter, TOtherDeleter >
		>
	>;

	template< typename TOtherElement, typename TOtherDeleter >
	using IsAssignable = BooleanAnd<
		IsArray<TOtherElement>,
		IsCompatible< typename UniquePointer< TOtherElement, TOtherDeleter >::Pointer >,
		IsAssignable< Deleter &, TOtherDeleter && >
	>;

public:
	constexpr UniquePointer() noexcept : m_impl(Pointer()) {
		static_assert(NotPointer<TDeleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	constexpr UniquePointer(NullPointer _dummy) noexcept : m_impl(Pointer()){
		static_assert(NotPointer<TDeleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	explicit UniquePointer(Pointer p) noexcept : m_impl(move(p)) {
		static_assert(NotPointer<TDeleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	template< typename TOtherPointer >
	UniquePointer(TOtherPointer p, Detail::Memory::UniquePointer::DeleterLValue<Deleter> d, EnableIf< IsCompatible<TOtherPointer> > * = nullptr) noexcept : m_impl(p, d) {
	}

	template< typename TOtherPointer >
	UniquePointer(TOtherPointer p, Detail::Memory::UniquePointer::DeleterRValue<Deleter> d, EnableIf< IsCompatible<TOtherPointer> > * = nullptr) noexcept : m_impl(p, move(d)) {
		static_assert(NotReference<TDeleter>(), "rvalue deleter bound to reference");
	}

	UniquePointer(UniquePointer && p) noexcept : m_impl(p.release(), forward<Deleter>(p.get_deleter())) {
	}

	template< typename TOtherElement, typename TOtherDeleter >
	UniquePointer(UniquePointer< TOtherElement, TOtherDeleter > && p, EnableIf< IsConstructible< TOtherElement, TOtherDeleter > > * = nullptr) noexcept : m_impl(p.release(), forward<TOtherDeleter>(p.get_deleter())) {
	}

	~UniquePointer() {
		reset();
	}

	auto operator=(UniquePointer && p) noexcept -> UniquePointer & {
		using BR::get;
		reset(p.release());
		get<1>(m_impl) = forward<Deleter>(p.get_deleter());
		return *this;
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator=(UniquePointer< TOtherElement, TOtherDeleter > && p) noexcept -> EnableIf< IsAssignable< TOtherElement, TOtherDeleter >, UniquePointer & > {
		using BR::get;
		reset(p.release());
		get<1>(m_impl) = forward<TOtherDeleter>(p.get_deleter());
		return *this;
	}

	auto operator=(NullPointer) noexcept -> UniquePointer & {
		reset();
		return *this;
	}

	auto operator[](Size i) const -> AddLValueReference<Element> {
		return m_impl.template get<0>()[i];
	}

	auto get() const noexcept -> Pointer {
		return m_impl.template get<0>();
	}

	auto get_deleter() noexcept -> RemoveReference<Deleter> & {
		return m_impl.template get<1>();
	}

	auto get_deleter() const noexcept -> RemoveReference<Deleter> const & {
		return m_impl.template get<1>();
	}

	explicit operator bool() const noexcept {
		return m_impl.template get<0>() != nullptr;
	}

	auto release() noexcept -> Pointer {
		auto t = m_impl.template get<0>();
		m_impl.template get<0>() = Pointer();
		return t;
	}

	template< typename TOtherPointer >
	auto reset(TOtherPointer p) noexcept -> EnableIf< IsCompatible<TOtherPointer> > {
		auto t = m_impl.template get<0>();
		m_impl.template get<0>() = p;
		if (t != nullptr) {
			m_impl.template get<1>()(t);
		}
	}

	void reset(NullPointer) noexcept {
		auto t = m_impl.template get<0>();
		m_impl.template get<0>() = nullptr;
		if (t != nullptr) {
			m_impl.template get<1>()(t);
		}
	}

	void reset() noexcept {
		auto t = m_impl.template get<0>();
		m_impl.template get<0>() = nullptr;
		if (t != nullptr) {
			m_impl.template get<1>()(t);
		}
	}

	void swap(UniquePointer & p) noexcept {
		m_impl.swap(p.m_impl);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator==(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return get() == y.get();
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator!=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !operator==(y);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return Less<>()(get(), y.get());
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator>(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return y.operator<(*this);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !y.operator<(*this);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator>=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !operator<(y);
	}

	auto operator==(NullPointer) const -> bool {
		return !operator bool();
	}

	auto operator!=(NullPointer) const -> bool {
		return operator bool();
	}

	auto operator<(NullPointer) const -> bool {
		return Less<>()(get(), nullptr);
	}

	auto operator>(NullPointer) const -> bool {
		return Less<>()(nullptr, get());
	}

	auto operator<=(NullPointer) const -> bool {
		return !operator>(nullptr);
	}

	auto operator>=(NullPointer) const -> bool {
		return !operator<(nullptr);
	}

private:
	Tuple< Pointer, Deleter > m_impl;

}; // class UniquePointer< TElement[], TDeleter >

} // namespace Memory

} // namespace BR