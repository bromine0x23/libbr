#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/swap.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {
namespace _ {
namespace Memory {
namespace UniquePointer {

template< typename TPointer, typename TDeleter, Boolean = is_empty<TDeleter> && not_final<TDeleter> >
class Storage;

template< typename TPointer, typename TDeleter >
class Storage< TPointer, TDeleter, false > {
public:
	using Pointer = TPointer;
	using Deleter = TDeleter;

private:
	Deleter _deleter;
	Pointer _pointer;

public:
	constexpr Storage() noexcept(
		has_nothrow_default_constructor<Deleter> && has_nothrow_default_constructor<Pointer>
	) : _deleter(), _pointer() {
	}

	constexpr Storage(Pointer && pointer) noexcept(
		has_nothrow_default_constructor<Deleter> && has_nothrow_move_constructor<Pointer>
	) : _deleter(), _pointer(transfer(pointer)) {
	}

	constexpr Storage(Pointer && pointer, Deleter const & deleter) noexcept(
		has_nothrow_copy_constructor<Deleter> && has_nothrow_move_constructor<Pointer>
	) : _deleter(deleter), _pointer(transfer(pointer)) {
	}

	constexpr Storage(Pointer && pointer, Deleter && deleter) noexcept(
		has_nothrow_move_constructor<Deleter> && has_nothrow_move_constructor<Pointer>
	) : _deleter(transfer(deleter)), _pointer(transfer(pointer)) {
	}

	constexpr Storage(Storage && storage) noexcept(
		has_nothrow_move_constructor<Deleter> && has_nothrow_move_constructor<Pointer>
	) : _deleter(transfer(storage._deleter)), _pointer(transfer(storage._pointer)) {
	}

	constexpr auto deleter() noexcept -> Deleter & {
		return _deleter;
	}

	constexpr auto deleter() const noexcept -> Deleter const & {
		return _deleter;
	}

	constexpr auto pointer() noexcept -> Pointer & {
		return _pointer;
	}

	constexpr auto pointer() const noexcept -> Pointer const & {
		return _pointer;
	}

	constexpr void swap(Storage & storage) noexcept {
		using BR::swap;
		swap(_deleter, storage._deleter);
		swap(_pointer, storage._pointer);
	}
}; // struct Storage< TPointer, TDeleter, false >

template< typename TPointer, typename TDeleter >
class Storage< TPointer, TDeleter, true > : private TDeleter {
public:
	using Pointer = TPointer;
	using Deleter = TDeleter;

private:
	Pointer _pointer;

public:
	constexpr Storage() noexcept(
		has_nothrow_default_constructor<Deleter> && has_nothrow_default_constructor<Pointer>
	) : Deleter(), _pointer() {
	}

	constexpr Storage(Pointer && pointer) noexcept(
		has_nothrow_default_constructor<Deleter> && has_nothrow_move_constructor<Pointer>
	) : Deleter(), _pointer(transfer(pointer)) {
	}

	constexpr Storage(Pointer && pointer, Deleter const & deleter) noexcept(
		has_nothrow_copy_constructor<Deleter> && has_nothrow_move_constructor<Pointer>
	) : Deleter(deleter), _pointer(transfer(pointer)) {
	}

	constexpr Storage(Pointer && pointer, Deleter && deleter) noexcept(
		has_nothrow_move_constructor<Deleter> && has_nothrow_move_constructor<Pointer>
	) : Deleter(transfer(deleter)), _pointer(transfer(pointer)) {
	}

	constexpr Storage(Storage && storage) noexcept(
		has_nothrow_move_constructor<Deleter> && has_nothrow_move_constructor<Pointer>
	) : Deleter(transfer(storage)), _pointer(transfer(storage._pointer)) {
	}

	constexpr auto deleter() noexcept -> Deleter & {
		return static_cast<Deleter &>(*this);
	}

	constexpr auto deleter() const noexcept -> Deleter const & {
		return static_cast<Deleter const &>(*this);
	}

	constexpr auto pointer() noexcept -> Pointer & {
		return _pointer;
	}

	constexpr auto pointer() const noexcept -> Pointer const & {
		return _pointer;
	}

	constexpr void swap(Storage & storage) noexcept {
		using BR::swap;
		swap(_pointer, storage._pointer);
	}
}; // struct Storage< TPointer, TDeleter, false >

} // namespace UniquePointer
} // namespace Memory
} // namespace _
} // namespace BR