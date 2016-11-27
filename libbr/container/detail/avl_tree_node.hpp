#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/avl_tree_balance.hpp>
#include <libbr/container/detail/binary_tree_node.hpp>
#include <libbr/memory/pointer_traits.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace AVLTree {

template< typename TNodePointer >
struct BasicNode : public BinaryTree::BasicNode<TNodePointer> {
	using NodePointer = TNodePointer;

	constexpr BasicNode() noexcept = default;

	Balance balance;
};

template< typename TElement, typename TVoidPointer >
using Node = BinaryTree::Node< TElement, TVoidPointer, BasicNode >;

} // namespace AVLTree
} // namespace Container
} // namespace Detail
} // namespace BR