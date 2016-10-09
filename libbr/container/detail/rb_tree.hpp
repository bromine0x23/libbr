#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/binary_tree.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace RBTree {

template< typename TVoidPointer >
struct BasicNode : public BinaryTree::BasicNode<TVoidPointer> {
	bool is_black;
};

template< typename TNode >
struct NodeTraits : public BinaryTree::NodeTraits<TNode> {
private:
	using Base = BinaryTree::NodeTraits<TNode>;

public:
	using Node = typename Base::Node;

	using BasicNode = typename Base::BasicNode;

	using NodePointer = typename Base::NodePointer;

	using NodeConstPointer = typename Base::NodeConstPointer;

	using BasicNodePointer = typename Base::BasicNodePointer;

	using BasicNodeConstPointer = typename Base::BasicNodeConstPointer;

public:
	constexpr static bool get_color(BasicNodePointer const & node) noexcept {
		return node.is_black;
	}

	constexpr static bool get_color(BasicNodeConstPointer const & node) noexcept {
		return node.is_black;
	}

	constexpr static bool is_black(BasicNodePointer const & node) noexcept {
		return node.is_black;
	}

	constexpr static bool is_black(BasicNodeConstPointer const & node) noexcept {
		return node.is_black;
	}

	constexpr static bool is_red(BasicNodePointer const & node) noexcept {
		return !node.is_black;
	}

	constexpr static bool is_red(BasicNodeConstPointer const & node) noexcept {
		return !node.is_black;
	}

	static void set_color(BasicNodePointer const & node, bool color) noexcept {
		node.is_black = color;
	}

	static void set_black(BasicNodePointer const & node) noexcept {
		node.is_black = true;
	}

	static bool set_red(BasicNodePointer const & node) noexcept {
		node.is_black = false;
	}
}; // struct NodeTraits<TNode>

template< typename TNodeTraits >
struct AlgorithmTraits : public BinaryTree::AlgorithmTraits<TNodeTraits> {
public:
	using NodeTraits = TNodeTraits;

private:
	using Base = BinaryTree::AlgorithmTraits<TNodeTraits>;

public:
	using Node = typename Base::Node;

	using NodePointer = typename Base::NodePointer;

	using NodeConstPointer = typename Base::NodeConstPointer;

private:
	static void rebalance_after_insertion(NodePointer const & header, NodePointer node) {
		NodeTraits::set_red(node);
		for (;;) {
			auto parent = NodeTraits::get_parent(node);
			auto const grandparent = NodeTraits::get_parent(parent);

			if (parent == header || NodeTraits::is_black(parent) || grandparent == header) {
				break;
			}
			NodeTraits::set_red(grandparent);

			auto const grandparent_left = NodeTraits::get_left(grandparent);
			auto const parent_is_left_child = parent == grandparent_left;
			auto const parent_brother = parent_is_left_child ? NodeTraits::get_right(grandparent) : grandparent_left;

			if (parent_brother != nullptr && NodeTraits::is_red(parent_brother)) {
				NodeTraits::set_black(parent);
				NodeTraits::set_black(parent_brother);
				node = grandparent;
			} else {
				auto const node_is_left_child = NodeTraits::get_left(parent) == node;
				if (parent_is_left_child) {
					if (!node_is_left_child) {
						Base::rotate_left_no_parent_fix(parent, node);
						parent = node;
					}
					Base::rotate_right(header, grandparent, NodeTraits::get_parent(grandparent), parent);
				} else {
					if (node_is_left_child) {
						Base::rotate_right_no_parent_fix(parent, node);
						parent = node;
					}
					Base::rotate_left(header, grandparent, NodeTraits::get_parent(grandparent), parent);
				}
				NodeTraits::set_black(parent);
				break;
			}
		}
		NodeTraits::set_black(NodeTraits::get_parent(header));
	}

}; // struct AlgorithmTraits<TNodeTraits>

} // namespace RBTree
} // namespace Container
} // namespace Detail
} // namespace BR