#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/rb_tree_color.hpp>
#include <libbr/container/detail/binary_tree_node.hpp>
#include <libbr/memory/pointer_traits.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace RBTree {

template< typename TNodePointer >
struct BasicNode : public BinaryTree::BasicNode<TNodePointer> {
	using NodePointer = TNodePointer;

	constexpr BasicNode() noexcept = default;

	Color color;
};

template< typename TElement, typename TVoidPointer >
using Node = BinaryTree::Node< TElement, TVoidPointer, BasicNode >;

} // namespace RBTree
} // namespace Container
} // namespace Detail
} // namespace BR