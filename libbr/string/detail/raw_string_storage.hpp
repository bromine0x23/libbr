#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_traits/boolean_and.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace String {
namespace RawString {

template< typename TCoalition, typename TAllocator, Boolean = Conjunction< IsEmpty<TAllocator>, NotFinal<TAllocator> >{} >
struct Storage;

template< typename TCoalition, typename TAllocator >
struct Storage< TCoalition, TAllocator, false > {
public:
	using Coalition = TCoalition;

	using Allocator = TAllocator;

public:
	constexpr Storage() : m_allocator(), m_coalition() {
	}

	constexpr Storage(Allocator const & allocator) : m_allocator(allocator), m_coalition() {
	}

	constexpr Storage(Storage && storage) : m_allocator(move(storage.m_allocator)), m_coalition(move(storage.m_coalition)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto allocator() -> Allocator & {
		return m_allocator;
	}

	constexpr auto allocator() const -> Allocator const & {
		return m_allocator;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto coalition() -> Coalition & {
		return m_coalition;
	}

	constexpr auto coalition() const -> Coalition const & {
		return m_coalition;
	}

private:
	Allocator m_allocator;
	Coalition m_coalition;
};

template< typename TCoalition, typename TAllocator >
struct Storage< TCoalition, TAllocator, true > : protected TAllocator {
public:
	using Coalition = TCoalition;

	using Allocator = TAllocator;

public:
	constexpr Storage() : Allocator(), m_coalition() {
	}

	constexpr Storage(Allocator const & allocator) : Allocator(allocator), m_coalition() {
	}

	constexpr Storage(Storage && storage) : Allocator(move(storage)), m_coalition(move(storage.m_coalition)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto allocator() noexcept -> Allocator & {
		return static_cast<Allocator &>(*this);
	}
	constexpr auto allocator() const noexcept -> Allocator const & {
		return static_cast<Allocator const &>(*this);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto coalition() -> Coalition & {
		return m_coalition;
	}

	constexpr auto coalition() const -> Coalition const & {
		return m_coalition;
	}

private:
	Coalition m_coalition;
};

} // namespace RawString
} // namespace String
} // namespace Detail
} // namespace BR