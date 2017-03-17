#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/is_nothrow_constructible.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace DynamicArray {

template< typename TPointer, typename TAllocator, Boolean = BooleanAnd< IsEmpty<TAllocator>, NotFinal<TAllocator> >{} >
struct Storage;

template< typename TPointer, typename TAllocator >
struct Storage< TPointer, TAllocator, false > {
public:
	using Pointer = TPointer;

	using Allocator = TAllocator;

public:
	Storage() : m_allocator(), m_storage_begin(nullptr), m_end(nullptr), m_storage_end(nullptr) {
	}

	Storage(Allocator const & allocator) : m_allocator(allocator), m_storage_begin(nullptr), m_end(nullptr), m_storage_end(nullptr) {
	}

	Storage(Storage && storage) : m_allocator(move(storage.m_allocator)), m_storage_begin(move(storage.m_storage_begin)), m_end(move(storage.m_end)), m_storage_end(move(storage.m_storage_end)) {
	}

	auto allocator() noexcept -> Allocator & {
		return m_allocator;
	}

	auto allocator() const noexcept -> Allocator const & {
		return m_allocator;
	}

	auto storage_begin() noexcept -> Pointer & {
		return m_storage_begin;
	}

	auto storage_begin() const noexcept -> Pointer const & {
		return m_storage_begin;
	}

	auto begin() noexcept -> Pointer & {
		return m_storage_begin;
	}

	auto begin() const noexcept -> Pointer const & {
		return m_storage_begin;
	}

	auto end() noexcept -> Pointer & {
		return m_end;
	}

	auto end() const noexcept -> Pointer const & {
		return m_end;
	}

	auto storage_end() noexcept -> Pointer & {
		return m_storage_end;
	}

	auto storage_end() const noexcept -> Pointer const & {
		return m_storage_end;
	}

private:
	Allocator m_allocator;
	Pointer m_storage_begin;
	Pointer m_end;
	Pointer m_storage_end;

}; // struct Storage< TPointer, TAllocator, false >

template< typename TPointer, typename TAllocator >
struct Storage< TPointer, TAllocator, true > : private TAllocator {
public:
	using Pointer = TPointer;

	using Allocator = TAllocator;

public:
	Storage() : Allocator(), m_storage_begin(), m_end(), m_storage_end() {
	}

	Storage(Allocator const & allocator) : Allocator(allocator), m_storage_begin(nullptr), m_end(nullptr), m_storage_end(nullptr) {
	}

	Storage(Storage && storage) : Allocator(move(storage)), m_storage_begin(move(storage.m_storage_begin)), m_end(move(storage.m_end)), m_storage_end(move(storage.m_storage_end)) {
	}

	auto allocator() noexcept -> Allocator & {
		return static_cast< Allocator & >(*this);
	}

	auto allocator() const noexcept -> Allocator const & {
		return static_cast< Allocator const & >(*this);
	}

	auto storage_begin() noexcept -> Pointer & {
		return m_storage_begin;
	}

	auto storage_begin() const noexcept -> Pointer const & {
		return m_storage_begin;
	}

	auto begin() noexcept -> Pointer & {
		return m_storage_begin;
	}

	auto begin() const noexcept -> Pointer const & {
		return m_storage_begin;
	}

	auto end() noexcept -> Pointer & {
		return m_end;
	}

	auto end() const noexcept -> Pointer const & {
		return m_end;
	}

	auto storage_end() noexcept -> Pointer & {
		return m_storage_end;
	}

	auto storage_end() const noexcept -> Pointer const & {
		return m_storage_end;
	}

private:
	Pointer m_storage_begin;
	Pointer m_end;
	Pointer m_storage_end;

}; // struct Storage< TPointer, TAllocator, true >

} // namespace DynamicArray
} // namespace Container
} // namespace Detail
} // namespace BR
