#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/binary_tree_basic.hpp>
#include <libbr/container/detail/splay_tree_algorithms.hpp>
#include <libbr/container/detail/binary_tree_node.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace SplayTree {

template< typename TNodePointer >
struct BasicNode : public BinaryTree::BasicNode<TNodePointer> {};

template< typename TElement, typename TVoidPointer >
using Node = BinaryTree::Node< TElement, TVoidPointer, BasicNode >;

struct Traits {
	template< typename TElement, typename TVoidPointer >
	using Node = SplayTree::Node<TElement, TVoidPointer>;

	template< typename TNodePointer >
	using Algorithms = SplayTree::Algorithms<TNodePointer>;
};

template< typename TElement, typename TComparator, typename TAllocator >
class Basic : public BinaryTree::Basic<TElement, TComparator, TAllocator, Traits> {
private:
	using Base = BinaryTree::Basic<TElement, TComparator, TAllocator, Traits>;

public:
	using Element = TElement;

	using Comparator = TComparator;

	using Allocator = TAllocator;

protected:
	using NodeAllocator = typename Base::NodeAllocator;

	using NodePointer = typename Base::NodePointer;

	using Algorithms = typename Base::Algorithms;

protected:
	Basic() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) : Base() {
	}

	explicit Basic(Allocator const & allocator) : Base(allocator) {
	}

	Basic(Comparator const & comparator, Allocator const & allocator = Allocator{}) : Base(comparator, allocator) {
	}

	Basic(Basic && tree) noexcept(BooleanAnd< HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<NodeAllocator> >{}) : Base(move(tree)) {
	}

	Basic(Basic && tree, Allocator const & allocator): Base(move(tree), allocator) {
	}

	~Basic() = default;

	void m_splay_up(NodePointer pointer) {
		return Algorithms::splay_up(this->m_header(), pointer);
	}

	template< typename TKey >
	auto m_splay_down(TKey const & key) -> NodePointer {
		return Algorithms::splay_down(this->m_header(), key, this->m_comparator());
	}

}; // class Basic< TElement, TComparator, TAllocator >

} // namespace SplayTree
} // namespace Container
} // namespace Detail
} // namespace BR