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
namespace BinaryTree {

template< typename TSize, typename TNode, typename TAllocator, typename TComparator, Boolean = BooleanAnd< IsEmpty<TAllocator>, NotFinal<TAllocator> >{}, Boolean = BooleanAnd< IsEmpty<TComparator>, NotFinal<TComparator> >{} >
struct Storage;

template< typename TSize, typename TNode, typename TAllocator, typename TComparator >
struct Storage< TSize, TNode, TAllocator, TComparator, false, false > {
public:
	using Size = TSize;

	using Node = TNode;

	using Allocator = TAllocator;

	using Comparator = TComparator;

public:
	constexpr Storage() noexcept(
		BooleanAnd< HasNothrowDefaultConstructor<Allocator>, HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : m_allocator(), m_comparator(), m_size(0), m_node() {
	}

	constexpr Storage(Allocator const & allocator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : m_allocator(allocator), m_comparator(), m_size(0), m_node() {
	}

	constexpr Storage(Allocator const & allocator, Comparator const & comparator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowCopyConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : m_allocator(allocator), m_comparator(comparator), m_size(0), m_node() {
	}

	constexpr Storage(Storage && storage) noexcept(
		BooleanAnd< HasNothrowMoveConstructor<Allocator>, HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<Node> >{}
	) : m_allocator(move(storage.m_allocator)), m_comparator(move(storage.m_comparator)), m_size(move(storage.m_size)), m_node(move(storage.m_node)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto allocator() noexcept -> Allocator & {
		return m_allocator;
	}

	constexpr auto allocator() const noexcept -> Allocator const & {
		return m_allocator;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto comparator() noexcept -> Comparator & {
		return m_comparator;
	}

	constexpr auto comparator() const noexcept -> Comparator const & {
		return m_comparator;
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
	Comparator m_comparator;
	Size m_size;
	Node m_node;

}; // struct Storage< TSize, TNode, TAllocator, TComparator, false, false >

template< typename TSize, typename TNode, typename TAllocator, typename TComparator >
struct Storage< TSize, TNode, TAllocator, TComparator, false, true > : private TComparator {
public:
	using Size = TSize;

	using Node = TNode;

	using Allocator = TAllocator;

	using Comparator = TComparator;

public:
	Storage() noexcept(
		BooleanAnd< HasNothrowDefaultConstructor<Allocator>, HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Comparator(), m_allocator(), m_size(0), m_node() {
	}

	Storage(Allocator const & allocator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Comparator(), m_allocator(allocator), m_size(0), m_node() {
	}

	Storage(Allocator const & allocator, Comparator const & comparator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowCopyConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Comparator(comparator), m_allocator(allocator), m_size(0), m_node() {
	}

	Storage(Storage && storage) noexcept(
		BooleanAnd< HasNothrowMoveConstructor<Allocator>, HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<Node> >{}
	) : Comparator(move(storage)), m_allocator(move(storage.m_allocator)), m_size(move(storage.m_size)), m_node(move(storage.m_node)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto allocator() noexcept -> Allocator & {
		return m_allocator;
	}

	constexpr auto allocator() const noexcept -> Allocator const & {
		return m_allocator;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto comparator() noexcept -> Comparator & {
		return static_cast< Comparator & >(*this);
	}

	constexpr auto comparator() const noexcept -> Comparator const & {
		return static_cast< Comparator const & >(*this);
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

}; // struct Storage< TSize, TNode, TAllocator, TComparator, true, false >

template< typename TSize, typename TNode, typename TAllocator, typename TComparator >
struct Storage< TSize, TNode, TAllocator, TComparator, true, false > : private TAllocator {
public:
	using Size = TSize;

	using Node = TNode;

	using Allocator = TAllocator;

	using Comparator = TComparator;

public:
	Storage() noexcept(
		BooleanAnd< HasNothrowDefaultConstructor<Allocator>, HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Allocator(), m_comparator(), m_size(0), m_node() {
	}

	Storage(Allocator const & allocator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Allocator(allocator), m_comparator(), m_size(0), m_node() {
	}

	Storage(Allocator const & allocator, Comparator const & comparator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowCopyConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Allocator(allocator), m_comparator(comparator), m_size(0), m_node() {
	}

	Storage(Storage && storage) noexcept(
		BooleanAnd< HasNothrowMoveConstructor<Allocator>, HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<Node> >{}
	) : Allocator(move(storage)), Comparator(move(storage.m_comparator)), m_size(move(storage.m_size)), m_node(move(storage.m_node)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto allocator() noexcept -> Allocator & {
		return static_cast< Allocator & >(*this);
	}

	constexpr auto allocator() const noexcept -> Allocator const & {
		return static_cast< Allocator const & >(*this);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto comparator() noexcept -> Comparator & {
		return m_comparator;
	}

	constexpr auto comparator() const noexcept -> Comparator const & {
		return m_comparator;
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
	Comparator m_comparator;
	Size m_size;
	Node m_node;

}; // struct Storage< TSize, TNode, TAllocator, TComparator, false, true >

template< typename TSize, typename TNode, typename TAllocator, typename TComparator >
struct Storage< TSize, TNode, TAllocator, TComparator, true, true > : private TAllocator, private TComparator {
public:
	using Size = TSize;

	using Node = TNode;

	using Allocator = TAllocator;

	using Comparator = TComparator;

public:
	Storage() noexcept(
		BooleanAnd< HasNothrowDefaultConstructor<Allocator>, HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Allocator(), Comparator(), m_size(0), m_node() {
	}

	Storage(Allocator const & allocator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Allocator(allocator), Comparator(), m_size(0), m_node() {
	}

	Storage(Allocator const & allocator, Comparator const & comparator) noexcept(
		BooleanAnd< HasNothrowCopyConstructor<Allocator>, HasNothrowCopyConstructor<Comparator>, HasNothrowDefaultConstructor<Node> >{}
	) : Allocator(allocator), Comparator(comparator), m_size(0), m_node() {
	}

	Storage(Storage && storage) noexcept(
		BooleanAnd< HasNothrowMoveConstructor<Allocator>, HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<Node> >{}
	) : Allocator(move(storage)), Comparator(move(storage)), m_size(move(storage.m_size)), m_node(move(storage.m_node)) {
	}

	BR_CONSTEXPR_AFTER_CXX11 auto allocator() noexcept -> Allocator & {
		return static_cast< Allocator & >(*this);
	}

	constexpr auto allocator() const noexcept -> Allocator const & {
		return static_cast< Allocator const & >(*this);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto comparator() noexcept -> Comparator & {
		return static_cast< Comparator & >(*this);
	}

	constexpr auto comparator() const noexcept -> Comparator const & {
		return static_cast< Comparator const & >(*this);
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

}; // struct Storage< TSize, TNode, TAllocator, TComparator, false, true >

} // namespace BinaryTree
} // namespace Container
} // namespace Detail
} // namespace BR
