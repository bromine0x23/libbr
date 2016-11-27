#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/pointer_traits.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace BinaryTree {

template< typename TNodePointer >
struct BasicNode;

template< typename TElement, typename TVoidPointer, template< typename > class TBasicNode = BasicNode >
struct Node;

template< typename TElement, typename TVoidPointer, template< typename >  class TBasicNode >
using HeadNode = TBasicNode< typename PointerTraits<TVoidPointer>::template Rebind< Node<TElement, TVoidPointer, TBasicNode> > >;

template< typename TNodePointer >
struct BasicNode {
	using NodePointer = TNodePointer;

	constexpr BasicNode() noexcept = default;

	NodePointer parent;
	NodePointer left;
	NodePointer right;
};

template< typename TElement, typename TVoidPointer, template< typename > class TBasicNode >
struct Node : public HeadNode< TElement, TVoidPointer, TBasicNode > {
	using Base = HeadNode< TElement, TVoidPointer, TBasicNode >;
	using Element = TElement;

	Element element;
};

} // namespace BinaryTree
} // namespace Container
} // namespace Detail
} // namespace BR