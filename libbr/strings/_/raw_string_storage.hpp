#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {
namespace _ {
namespace Strings {
namespace RawString {

template< typename TCoalition, typename TAllocator, Boolean = is_empty<TAllocator> && not_final<TAllocator> >
struct Storage;

template< typename TCoalition, typename TAllocator >
struct Storage< TCoalition, TAllocator, false > {

public:
	using Coalition = TCoalition;
	using Allocator = TAllocator;

private:
	Allocator _allocator;
	Coalition _coalition;

public:
	constexpr Storage() : _allocator(), _coalition() {
	}

	constexpr explicit Storage(Allocator const & allocator) : _allocator(allocator), _coalition() {
	}

	constexpr Storage(Storage && storage) noexcept : _allocator(transfer(storage._allocator)), _coalition(transfer(storage._coalition)) {
	}

	constexpr auto allocator() -> Allocator & {
		return _allocator;
	}

	constexpr auto allocator() const -> Allocator const & {
		return _allocator;
	}

	constexpr auto coalition() -> Coalition & {
		return _coalition;
	}

	constexpr auto coalition() const -> Coalition const & {
		return _coalition;
	}
};

template< typename TCoalition, typename TAllocator >
struct Storage< TCoalition, TAllocator, true > : protected TAllocator {

public:
	using Coalition = TCoalition;
	using Allocator = TAllocator;

private:
	Coalition _coalition;

public:
	constexpr Storage() : Allocator(), _coalition() {
	}

	constexpr explicit Storage(Allocator const & allocator) : Allocator(allocator), _coalition() {
	}

	constexpr Storage(Storage && storage) noexcept : Allocator(transfer(storage)), _coalition(transfer(storage._coalition)) {
	}

	constexpr auto allocator() noexcept -> Allocator & {
		return static_cast<Allocator &>(*this);
	}
	constexpr auto allocator() const noexcept -> Allocator const & {
		return static_cast<Allocator const &>(*this);
	}

	constexpr auto coalition() -> Coalition & {
		return _coalition;
	}

	constexpr auto coalition() const -> Coalition const & {
		return _coalition;
	}
};

} // namespace RawString
} // namespace Strings
} // namespace _
} // namespace BR