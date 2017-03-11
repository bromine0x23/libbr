#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/pointer_traits.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace DList {

template< typename TNodePointer >
struct BasicNode;

template< typename TElement, typename TVoidPointer >
struct Node;

template< typename TElement, typename TVoidPointer >
using HeadNode = BasicNode< typename PointerTraits<TVoidPointer>::template Rebind< Node<TElement, TVoidPointer> > >;

template< typename TNodePointer >
struct BasicNode {
	using NodePointer = TNodePointer;

	using BasicNodePointer = typename PointerTraits<NodePointer>::template Rebind<BasicNode>;

	auto self() -> NodePointer {
		return static_cast<NodePointer>(PointerTraits<BasicNodePointer>::make_pointer(*this));
	}

	NodePointer prev;
	NodePointer next;
};

template< typename TElement, typename TVoidPointer >
struct Node : public HeadNode< TElement, TVoidPointer > {
	using Base = HeadNode< TElement, TVoidPointer >;
	using Element = TElement;

	Element element;
};

} // namespace DList
} // namespace Container
} // namespace Detail
} // namespace BR