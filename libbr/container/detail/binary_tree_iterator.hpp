#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/binary_tree_algorithms.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/memory/pointer_traits.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace BinaryTree {

template< typename TBase >
class Implement;

template< typename TNodePointer >
class Iterator;

template< typename TNodePointer >
class ConstIterator;

template< typename TNodePointer >
class Iterator : public IteratorWithCategory< ReadableTag, WritableTag, BidirectionalTraversalTag > {
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = PointerTraits<NodePointer>;

	using Node = typename NodePointerTraits::Element;

	using BasicNode = typename Node::Base;

	using BasicNodePointer = typename NodePointerTraits::template Rebind<BasicNode>;

	using Algorithms = BinaryTree::Algorithms<NodePointer>;

	template< typename >
	friend class Implement;

	template< typename >
	friend class ConstIterator;

public:
	struct Category : public IteratorTag, public ReadableTag, public WritableTag, public BidirectionalTraversalTag {};

	using Element = typename Node::Element;

	using Pointer = typename NodePointerTraits::template Rebind<Element>;

	using Reference = Element &;

	using Difference = typename NodePointerTraits::Difference;

	Iterator() noexcept : m_pointer(nullptr) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return NodePointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> Iterator & {
		m_pointer = Algorithms::next_node(m_pointer);
		return *this;
	}

	auto operator++(int) -> Iterator {
		Iterator temp(*this);
		operator++();
		return temp;
	}

	auto operator--() -> Iterator & {
		m_pointer = Algorithms::prev_node(m_pointer);
		return *this;
	}

	auto operator--(int) -> Iterator {
		Iterator temp(*this);
		operator--();
		return *temp;
	}

	auto operator==(Iterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator const & y) const -> bool {
		return !operator==(y);
	}

private:
	explicit Iterator(NodePointer pointer) noexcept : m_pointer(pointer) {
	}

private:
	NodePointer m_pointer;
}; // class Iterator<TNodePointer>

template< typename TNodePointer >
class ConstIterator : public IteratorWithCategory< ReadableTag, BidirectionalTraversalTag > {
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = PointerTraits<TNodePointer>;

	using Node = typename NodePointerTraits::Element;

	using BasicNode = typename Node::Base;

	using BasicNodePointer = typename NodePointerTraits::template Rebind<BasicNode>;

	using Algorithms = BinaryTree::Algorithms<NodePointer>;

	template< typename >
	friend class Implement;

public:
	struct Category : public IteratorTag, public ReadableTag, public BidirectionalTraversalTag {};

	using Element = typename Node::Element;

	using Pointer = typename NodePointerTraits::template Rebind<Element const>;

	using Reference = Element const &;

	using Difference = typename NodePointerTraits::Difference;

	ConstIterator() noexcept : m_pointer(nullptr) {
	}

	ConstIterator(Iterator<NodePointer> iterator) noexcept : m_pointer(iterator.m_pointer) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return NodePointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> ConstIterator & {
		m_pointer = Algorithms::next_node(m_pointer);
		return *this;
	}

	auto operator++(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator++();
		return temp;
	}

	auto operator--() -> ConstIterator & {
		m_pointer = Algorithms::prev_node(m_pointer);
		return *this;
	}

	auto operator--(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator--();
		return *temp;
	}

	auto operator==(ConstIterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(ConstIterator const & y) const -> bool {
		return !operator==(y);
	}

	auto operator==(Iterator<NodePointer> const  & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator<NodePointer> const  & y) const -> bool {
		return !operator==(y);
	}

private:
	explicit ConstIterator(NodePointer pointer) noexcept : m_pointer(pointer) {
	}

private:
	NodePointer m_pointer;
}; // class ConstIterator<TNodePointer>

template< typename TNodePointer >
inline auto operator==(Iterator<TNodePointer> const & x, ConstIterator<TNodePointer> const & y) -> bool {
	return y == x;
}

template< typename TNodePointer >
auto operator!=(Iterator<TNodePointer> const & x, ConstIterator<TNodePointer> const & y) -> bool {
	return y != x;
}

} // namespace BinaryTree
} // namespace Container
} // namespace Detail
} // namespace BR