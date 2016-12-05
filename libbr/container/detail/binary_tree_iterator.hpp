#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/binary_tree_algorithms.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/operators/decrementable.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/incrementable.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace BinaryTree {

template< template< typename, typename, typename, typename...> class TBasic, typename TElement, typename TComparator, typename TAllocator, typename... TClassArgs >
class Implement;

template< typename TNodePointer >
class Iterator;

template< typename TNodePointer >
class ConstIterator;

template< typename TNodePointer >
class Iterator :
	public IteratorWithCategory< ReadableTag, WritableTag, BidirectionalTraversalTag >,
	public EqualityComparable< Iterator<TNodePointer> >,
	public Incrementable< Iterator<TNodePointer> >,
	public Decrementable< Iterator<TNodePointer> >
{
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = PointerTraits<NodePointer>;

	using Node = typename NodePointerTraits::Element;

	using Algorithms = BinaryTree::Algorithms<NodePointer>;

	template< template< typename, typename, typename, typename...> class, typename, typename, typename, typename... >
	friend class Implement;

	template< typename >
	friend class ConstIterator;

public:
	using Element = typename Node::Element;

	using Pointer = typename NodePointerTraits::template Rebind<Element>;

	using Reference = Element &;

	using Difference = typename NodePointerTraits::Difference;

public:
	Iterator() noexcept : m_pointer(nullptr) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return PointerTraits<Pointer>::make_pointer(m_pointer->element);
	}

	auto operator++() -> Iterator & {
		m_pointer = Algorithms::next_node(m_pointer);
		return *this;
	}

	auto operator--() -> Iterator & {
		m_pointer = Algorithms::prev_node(m_pointer);
		return *this;
	}

	auto operator==(Iterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

private:
	explicit Iterator(NodePointer pointer) noexcept : m_pointer(pointer) {
	}

private:
	NodePointer m_pointer;
}; // class Iterator<TNodePointer>

template< typename TNodePointer >
class ConstIterator :
	public IteratorWithCategory< ReadableTag, BidirectionalTraversalTag >,
	public EqualityComparable< ConstIterator<TNodePointer> >,
	public EqualityComparable< ConstIterator<TNodePointer>, Iterator<TNodePointer> >,
	public Incrementable< ConstIterator<TNodePointer> >,
	public Decrementable< ConstIterator<TNodePointer> >
{
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = PointerTraits<TNodePointer>;

	using Node = typename NodePointerTraits::Element;

	using Algorithms = BinaryTree::Algorithms<NodePointer>;

	template< template< typename, typename, typename, typename...> class, typename, typename, typename, typename... >
	friend class Implement;

public:
	using Element = typename Node::Element;

	using Pointer = typename NodePointerTraits::template Rebind<Element const>;

	using Reference = Element const &;

	using Difference = typename NodePointerTraits::Difference;

public:
	ConstIterator() noexcept : m_pointer(nullptr) {
	}

	ConstIterator(Iterator<NodePointer> iterator) noexcept : m_pointer(iterator.m_pointer) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return PointerTraits<Pointer>::make_pointer(m_pointer->element);
	}

	auto operator++() -> ConstIterator & {
		m_pointer = Algorithms::next_node(m_pointer);
		return *this;
	}

	auto operator--() -> ConstIterator & {
		m_pointer = Algorithms::prev_node(m_pointer);
		return *this;
	}

	auto operator==(ConstIterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator==(Iterator<NodePointer> const  & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

private:
	explicit ConstIterator(NodePointer pointer) noexcept : m_pointer(pointer) {
	}

private:
	NodePointer m_pointer;
}; // class ConstIterator<TNodePointer>

} // namespace BinaryTree
} // namespace Container
} // namespace Detail
} // namespace BR