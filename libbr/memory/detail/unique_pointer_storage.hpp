#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/boolean_and.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Memory {
namespace UniquePointer {

template< typename TPointer, typename TDeleter, Boolean = Conjunction< IsEmpty<TDeleter>, NotFinal<TDeleter> >{} >
class Storage;

template< typename TPointer, typename TDeleter >
class Storage< TPointer, TDeleter, false > {
public:
	using Pointer = TPointer;

	using Deleter = TDeleter;

public:
	constexpr Storage() noexcept(
		Conjunction< HasNothrowDefaultConstructor<Deleter>, HasNothrowDefaultConstructor<Pointer> >{}
	) : m_deleter(), m_pointer() {
	}

	constexpr Storage(Pointer && pointer) noexcept(
		Conjunction< HasNothrowCopyConstructor<Deleter>, HasNothrowMoveConstructor<Pointer> >{}
	) : m_deleter(), m_pointer(move(pointer)) {
	}

	constexpr Storage(Pointer && pointer, Deleter const & deleter) noexcept(
		Conjunction< HasNothrowCopyConstructor<Deleter>, HasNothrowMoveConstructor<Pointer> >{}
	) : m_deleter(deleter), m_pointer(move(pointer)) {
	}

	constexpr Storage(Pointer && pointer, Deleter && deleter) noexcept(
		Conjunction< HasNothrowMoveConstructor<Deleter>, HasNothrowMoveConstructor<Pointer> >{}
	) : m_deleter(move(deleter)), m_pointer(move(pointer)) {
	}

	constexpr Storage(Storage && storage) noexcept(
		Conjunction< HasNothrowMoveConstructor<Deleter>, HasNothrowMoveConstructor<Pointer> >{}
	) : m_deleter(move(storage.m_deleter)), m_pointer(move(storage.m_pointer)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto deleter() noexcept -> Deleter & {
		return m_deleter;
	}

	constexpr auto deleter() const noexcept -> Deleter const & {
		return m_deleter;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto pointer() noexcept -> Pointer & {
		return m_pointer;
	}

	constexpr auto pointer() const noexcept -> Pointer const & {
		return m_pointer;
	}

	void swap(Storage & storage) noexcept {
		using BR::swap;
		swap(m_deleter, storage.m_deleter);
		swap(m_pointer, storage.m_pointer);
	}

private:
	Deleter m_deleter;
	Pointer m_pointer;
}; // struct Storage< TPointer, TDeleter, false >

template< typename TPointer, typename TDeleter >
class Storage< TPointer, TDeleter, true > : private TDeleter {
public:
	using Pointer = TPointer;

	using Deleter = TDeleter;

public:
	constexpr Storage() noexcept(
		Conjunction< HasNothrowDefaultConstructor<Deleter>, HasNothrowDefaultConstructor<Pointer> >{}
	) : Deleter(), m_pointer() {
	}

	constexpr Storage(Pointer && pointer) noexcept(
		Conjunction< HasNothrowCopyConstructor<Deleter>, HasNothrowMoveConstructor<Pointer> >{}
	) : Deleter(), m_pointer(move(pointer)) {
	}

	constexpr Storage(Pointer && pointer, Deleter const & deleter) noexcept(
		Conjunction< HasNothrowCopyConstructor<Deleter>, HasNothrowMoveConstructor<Pointer> >{}
	) : Deleter(deleter), m_pointer(move(pointer)) {
	}

	constexpr Storage(Pointer && pointer, Deleter && deleter) noexcept(
		Conjunction< HasNothrowMoveConstructor<Deleter>, HasNothrowMoveConstructor<Pointer> >{}
	) : Deleter(move(deleter)), m_pointer(move(pointer)) {
	}

	constexpr Storage(Storage && storage) noexcept(
		Conjunction< HasNothrowMoveConstructor<Deleter>, HasNothrowMoveConstructor<Pointer> >{}
	) : Deleter(move(storage)), m_pointer(move(storage.m_pointer)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto deleter() noexcept -> Deleter & {
		return static_cast<Deleter &>(*this);
	}

	constexpr auto deleter() const noexcept -> Deleter const & {
		return static_cast<Deleter const &>(*this);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto pointer() noexcept -> Pointer & {
		return m_pointer;
	}

	constexpr auto pointer() const noexcept -> Pointer const & {
		return m_pointer;
	}

	void swap(Storage & storage) noexcept {
		using BR::swap;
		swap(m_pointer, storage.m_pointer);
	}

private:
	Pointer m_pointer;
}; // struct Storage< TPointer, TDeleter, false >

} // namespace UniquePointer
} // namespace Memory
} // namespace Detail
} // namespace BR