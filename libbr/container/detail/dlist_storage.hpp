#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/boolean_and.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace DList {

template< typename TSize, typename TNode, typename TAllocator, Boolean = BooleanAnd< IsEmpty<TAllocator>, NotFinal<TAllocator> >{} >
struct Storage;

template< typename TSize, typename TNode, typename TAllocator >
struct Storage< TSize, TNode, TAllocator, false > {
public:
	using Size = TSize;

	using Node = TNode;

	using Allocator = TAllocator;

public:
	constexpr Storage() noexcept(
		BooleanAnd< HasNothrowDefaultConstructor<Allocator>, HasNothrowDefaultConstructor<Node> >{}
	) : m_allocator(), m_size(0), m_node() {
	}

	constexpr Storage(Allocator const & allocator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowDefaultConstructor<Node> >{}
	) : m_allocator(allocator), m_size(0), m_node() {
	}

	constexpr Storage(Storage && storage) noexcept(
		BooleanAnd< HasNothrowMoveConstructor<Allocator>, HasNothrowMoveConstructor<Node> >{}
	) : m_allocator(move(storage.m_allocator)), m_size(move(storage.m_size)), m_node(move(storage.m_node)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto allocator() noexcept -> Allocator & {
		return m_allocator;
	}

	constexpr auto allocator() const noexcept -> Allocator const & {
		return m_allocator;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto size() noexcept -> Size & {
		return m_size;
	}

	constexpr auto size() const noexcept -> Size const & {
		return m_size;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto node() noexcept -> Node & {
		return m_node;
	}

	constexpr auto node() const noexcept -> Node const & {
		return m_node;
	}

private:
	Allocator m_allocator;
	Size m_size;
	Node m_node;

}; // struct Storage< TSize, TNode, TAllocator, false >

template< typename TSize, typename TNode, typename TAllocator >
struct Storage< TSize, TNode, TAllocator, true > : private TAllocator {
public:
	using Size = TSize;

	using Node = TNode;

	using Allocator = TAllocator;

public:
	constexpr Storage() noexcept(
		BooleanAnd< HasNothrowDefaultConstructor<Allocator>, HasNothrowDefaultConstructor<Node> >{}
	) : Allocator(), m_size(0), m_node() {
	}

	constexpr Storage(Allocator const & allocator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowDefaultConstructor<Node> >{}
	) : Allocator(allocator), m_size(0), m_node() {
	}

	constexpr Storage(Storage && storage) noexcept(
		BooleanAnd< HasNothrowMoveConstructor<Allocator>, HasNothrowMoveConstructor<Node> >{}
	) : Allocator(move(storage)), m_size(move(storage.m_size)), m_node(move(storage.m_node)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto allocator() noexcept -> Allocator & {
		return static_cast< Allocator & >(*this);
	}

	constexpr auto allocator() const noexcept -> Allocator const & {
		return static_cast< Allocator const & >(*this);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto size() noexcept -> Size & {
		return m_size;
	}

	constexpr auto size() const noexcept -> Size const & {
		return m_size;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto node() noexcept -> Node & {
		return m_node;
	}

	constexpr auto node() const noexcept -> Node const & {
		return m_node;
	}

private:
	Size m_size;
	Node m_node;

}; // struct Storage< TSize, TNode, TAllocator, true >

} // namespace DList
} // namespace Container
} // namespace Detail
} // namespace BR
