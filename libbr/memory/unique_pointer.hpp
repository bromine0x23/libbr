/**
 * @file
 * @brief class UniquePointer
 * @author Bromine0x23
 * @since 2015/10/25
 */
#pragma once

#include <libbr/assert/assert.hpp>
#include <libbr/container/compressed_pair.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/memory/default_deleter.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/remove_extent.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TElement, typename TDeleter = DefaultDeleter<TElement> >
class UniquePointer;

template< typename TElement, typename... TArgs >
inline auto make_unique_pointer(TArgs &&... args) -> EnableIf< NotArray<TElement>, UniquePointer<TElement> > {
	return UniquePointer<TElement>(new TElement(forward<TArgs>(args)...));
}

template< typename TElement >
inline auto make_unique_pointer(Size count) -> EnableIf< IsArrayUnknownBounds<TElement>, UniquePointer<TElement> > {
	return UniquePointer<TElement>(new RemoveExtent<TElement>[count]());
}

template< typename TElement, typename... TArgs >
inline auto make_unique_pointer(TArgs &&... args) -> EnableIf< IsArrayKnownBounds<TElement> > = delete;

namespace Detail {
namespace Memory {
namespace UniquePointer {

#define BR_TYPE_OPERATE_TYPE_NAME Pointer
#include <libbr/type_traits/has_member_type.inc>

template< typename TElement, typename TDeleter, bool = HasMemberTypePointer<TDeleter>::value >
struct TypePointer;

template< typename TElement, typename TDeleter >
struct TypePointer< TElement, TDeleter, true > : TypeWrapper< typename TDeleter::Pointer > {
};

template< typename TElement, typename TDeleter >
struct TypePointer< TElement, TDeleter, false > : TypeWrapper< TElement * > {
};

template< typename TElement, typename TDeleter >
using Pointer = TypeUnwrap< TypePointer< TElement, TDeleter> >;

template< typename TDeleter >
using DeleterLValue = Conditional< IsReference<TDeleter>, TDeleter, TDeleter const & >;

template< typename TDeleter >
using DeleterRValue = RemoveReference<TDeleter> &&;

} // namespace UniquePointer
} // namespace Memory
} // namespace Detail

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

	constexpr UniquePointer(NullPointer _dummy) noexcept : m_impl(Pointer()){
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

	template< typename TOtherElement, typename TOtherDeleter, typename _TDummy = EnableIf< IsConstructible< TOtherElement, TOtherDeleter > > >
	UniquePointer(UniquePointer< TOtherElement, TOtherDeleter > && p) noexcept : m_impl(p.release(), forward<TOtherDeleter>(p.get_deleter())) {
	}

	~UniquePointer() {
		reset();
	}

	auto operator=(UniquePointer && p) noexcept -> UniquePointer & {
		reset(p.release());
		m_impl.second() = forward<Deleter>(p.get_deleter());
		return *this;
	}

	template< typename TOtherElement, typename TOtherDeleter, typename _TDummy = EnableIf< IsAssignable< TOtherElement, TOtherDeleter > > >
	auto operator=(UniquePointer< TOtherElement, TOtherDeleter > && p) noexcept -> UniquePointer & {
		reset(p.release());
		m_impl.second() = forward<TOtherDeleter>(p.get_deleter());
		return *this;
	}

	auto operator=(NullPointer _dummy) noexcept -> UniquePointer & {
		reset();
		return *this;
	}

	auto operator*() const -> AddLValueReference<Element> {
		return *m_impl.first();
	}

	auto operator->() const noexcept -> Pointer {
		return m_impl.first();
	}

	auto get() const noexcept -> Pointer {
		return m_impl.first();
	}

	auto get_deleter() noexcept -> RemoveReference<Deleter> & {
		return m_impl.second();
	}

	auto get_deleter() const noexcept -> RemoveReference<Deleter> const & {
		return m_impl.second();
	}

	explicit operator bool() const noexcept {
		return m_impl.first() != nullptr;
	}

	auto release() noexcept -> Pointer {
		auto t = m_impl.first();
		m_impl.first() = Pointer();
		return t;
	}

	void reset(Pointer p = Pointer()) noexcept {
		auto t = m_impl.first();
		m_impl.first() = p;
		if (t) {
			m_impl.second()(t);
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
		return !(*this == y);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return Less<void>()(get(), y.get());
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator>(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return y < *this;
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !(y < *this);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator>=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !(*this < y);
	}

	auto operator==(NullPointer _dummy) const -> bool {
		return !(*this);
	}

	auto operator!=(NullPointer _dummy) const -> bool {
		return static_cast<bool>(*this);
	}

	auto operator<(NullPointer _dummy) const -> bool {
		return Less<void>()(get(), nullptr);
	}

	auto operator>(NullPointer _dummy) const -> bool {
		return nullptr < *this;
	}

	auto operator<=(NullPointer _dummy) const -> bool {
		return !(nullptr < *this);
	}

	auto operator>=(NullPointer _dummy) const -> bool {
		return !(*this < nullptr);
	}

private:
	CompressedPair< Pointer, Deleter > m_impl;

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

	template< typename TOtherPointer, typename _TDummy = EnableIf< IsCompatible<TOtherPointer> > >
	UniquePointer(TOtherPointer p, Detail::Memory::UniquePointer::DeleterLValue<Deleter> d) noexcept : m_impl(p, d) {
	}

	template< typename TOtherPointer, typename _TDummy = EnableIf< IsCompatible<TOtherPointer> > >
	UniquePointer(TOtherPointer p, Detail::Memory::UniquePointer::DeleterRValue<Deleter> d) noexcept : m_impl(p, move(d)) {
		static_assert(NotReference<TDeleter>(), "rvalue deleter bound to reference");
	}

	UniquePointer(UniquePointer && p) noexcept : m_impl(p.release(), forward<Deleter>(p.get_deleter())) {
	}

	template< typename TOtherElement, typename TOtherDeleter, typename _TDummy = EnableIf< IsConstructible< TOtherElement, TOtherDeleter > > >
	UniquePointer(UniquePointer< TOtherElement, TOtherDeleter > && p) noexcept : m_impl(p.release(), forward<TOtherDeleter>(p.get_deleter())) {
	}

	~UniquePointer() {
		reset();
	}

	auto operator=(UniquePointer && p) noexcept -> UniquePointer & {
		reset(p.release());
		m_impl.second() = forward<Deleter>(p.get_deleter());
		return *this;
	}

	template< typename TOtherElement, typename TOtherDeleter, typename _TDummy = EnableIf< IsAssignable< TOtherElement, TOtherDeleter > > >
	auto operator=(UniquePointer< TOtherElement, TOtherDeleter > && p) noexcept -> UniquePointer & {
		reset(p.release());
		m_impl.second() = forward<TOtherDeleter>(p.get_deleter());
		return *this;
	}

	auto operator=(NullPointer _dummy) noexcept -> UniquePointer & {
		reset();
		return *this;
	}

	auto operator[](Size i) const -> AddLValueReference<Element> {
		return m_impl.first()[i];
	}

	auto get() const noexcept -> Pointer {
		return m_impl.first();
	}

	auto get_deleter() noexcept -> RemoveReference<Deleter> & {
		return m_impl.second();
	}

	auto get_deleter() const noexcept -> RemoveReference<Deleter> const & {
		return m_impl.second();
	}

	explicit operator bool() const noexcept {
		return m_impl.first() != nullptr;
	}

	auto release() noexcept -> Pointer {
		auto t = m_impl.first();
		m_impl.first() = Pointer();
		return t;
	}

	template< typename TOtherPointer, typename _TDummy = EnableIf< IsCompatible<TOtherPointer> > >
	void reset(Pointer p) noexcept {
		auto t = m_impl.first();
		m_impl.first() = p;
		if (t) {
			m_impl.second()(t);
		}
	}

	void reset(NullPointer _dummy) noexcept {
		auto t = m_impl.first();
		m_impl.first() = nullptr;
		if (t) {
			m_impl.second()(t);
		}
	}

	void reset() noexcept {
		auto t = m_impl.first();
		m_impl.first() = nullptr;
		if (t) {
			m_impl.second()(t);
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
		return !(*this == y);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return Less<void>()(get(), y.get());
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator>(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return y < *this;
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !(y < *this);
	}

	template< typename TOtherElement, typename TOtherDeleter >
	auto operator>=(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> bool {
		return !(*this < y);
	}

	auto operator==(NullPointer _dummy) const -> bool {
		return !(*this);
	}

	auto operator!=(NullPointer _dummy) const -> bool {
		return static_cast<bool>(*this);
	}

	auto operator<(NullPointer _dummy) const -> bool {
		return Less<void>()(get(), nullptr);
	}

	auto operator>(NullPointer _dummy) const -> bool {
		return nullptr < *this;
	}

	auto operator<=(NullPointer _dummy) const -> bool {
		return !(nullptr < *this);
	}

	auto operator>=(NullPointer _dummy) const -> bool {
		return !(*this < nullptr);
	}

private:
	CompressedPair< Pointer, Deleter > m_impl;

}; // class UniquePointer< TElement[], TDeleter >

template< typename TElement, typename TDeleter >
inline void swap(UniquePointer< TElement, TDeleter > & x, UniquePointer< TElement, TDeleter > & y) noexcept {
	x.swap(y);
}

template< typename TElement, typename TDeleter >
inline auto operator==(NullPointer _dummy, UniquePointer< TElement, TDeleter > const & y) -> bool {
	return !y;
}

template< typename TElement, typename TDeleter >
inline auto operator!=(NullPointer _dummy, UniquePointer< TElement, TDeleter > const & y) -> bool {
	return static_cast<bool>(y);
}

template< typename TElement, typename TDeleter >
inline auto operator<(NullPointer _dummy, UniquePointer< TElement, TDeleter > const & y) -> bool {
	return Less<void>()(nullptr, y.get());
}

template< typename TElement, typename TDeleter >
inline auto operator>(NullPointer _dummy, UniquePointer< TElement, TDeleter > const & y) -> bool {
	return y < nullptr;
}

template< typename TElement, typename TDeleter >
inline auto operator<=(NullPointer _dummy, UniquePointer< TElement, TDeleter > const & y) -> bool {
	return !(y < nullptr);
}

template< typename TElement, typename TDeleter >
inline auto operator>=(NullPointer _dummy, UniquePointer< TElement, TDeleter > const & y) -> bool {
	return !(nullptr < y);
}

} // namespace BR


