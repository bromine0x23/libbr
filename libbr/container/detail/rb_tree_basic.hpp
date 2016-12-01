#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/binary_tree_basic.hpp>
#include <libbr/container/detail/rb_tree_algorithms.hpp>
#include <libbr/container/detail/rb_tree_node.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace RBTree {

struct Traits {
	template< typename TElement, typename TVoidPointer >
	using Node = RBTree::Node<TElement, TVoidPointer>;

	template< typename TNodePointer >
	using Algorithms = RBTree::Algorithms<TNodePointer>;
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

}; // class Basic< TElement, TComparator, TAllocator >

} // namespace RBTree
} // namespace Container
} // namespace Detail
} // namespace BR