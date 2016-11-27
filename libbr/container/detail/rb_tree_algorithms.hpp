#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/detail/binary_tree_algorithms.hpp>
#include <libbr/container/detail/rb_tree_color.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace RBTree {

template< typename TNodePointer >
struct Algorithms : public BinaryTree::Algorithms<TNodePointer> {
public:
	using Base = BinaryTree::Algorithms<TNodePointer>;

	using NodePointer = TNodePointer;

public:
	static auto is_header(NodePointer const & node) noexcept -> bool {
		return node->color == Color::red && Base::is_header(node);
	}

	static void init_header(NodePointer const & header) noexcept {
		Base::init_header(header);
		header->color = Color::red;
	}

	static void insert_unique_commit(NodePointer const & header, NodePointer const & new_node, typename Base::InsertCommitData const & data) {
		Base::insert_commit(header, new_node, data);
		rebalance_after_insertion(header, new_node);
	}

	template< typename TComparator >
	static auto insert_equal(NodePointer const & header, NodePointer const & hint, NodePointer const & new_node, TComparator comparator) -> NodePointer {
		Base::insert_equal(header, hint, new_node, comparator);
		rebalance_after_insertion(header, new_node);
		return new_node;
	}

	template< typename TComparator >
	static auto insert_equal_lower_bound(NodePointer const & header, NodePointer const & new_node, TComparator comparator) -> NodePointer {
		Base::insert_equal_lower_bound(header, new_node, comparator);
		rebalance_after_insertion(header, new_node);
		return new_node;
	}

	template< typename TComparator >
	static auto insert_equal_upper_bound(NodePointer const & header, NodePointer const & new_node, TComparator comparator) -> NodePointer {
		Base::insert_equal_upper_bound(header, new_node, comparator);
		rebalance_after_insertion(header, new_node);
		return new_node;
	}

	static auto erase(NodePointer const & header, NodePointer const & target) -> NodePointer {
		typename Base::RebalanceData data;
		Base::erase(header, target, data);
		rebalance_after_erasure(header, target, data);
		return target;
	}

	static auto verify(NodePointer const & header) -> bool {
		auto const root = header->parent;
		if (root == nullptr) {
			return true;
		}
		if (root->color == Color::red) {
			BR_ASSERT(false);
			return false;
		}
		return verify_recursion(header->parent) != 0U;
	}

protected:
	static auto verify_recursion(NodePointer node) -> Size {
		if (node == nullptr) {
			return 1;
		}
		if (node->left != nullptr && node->left->parent != node) {
			BR_ASSERT(false);
			return 0;
		}
		if (node->right != nullptr && node->right->parent != node) {
			BR_ASSERT(false);
			return 0;
		}
		if (node->left == node->right && node->left != nullptr) {
			BR_ASSERT(false);
			return 0;
		}
		if (node->color == Color::red) {
			if (node->left != nullptr && node->left->color == Color::red) {
				BR_ASSERT(false);
				return 0;
			}
			if (node->right != nullptr && node->right->color == Color::red) {
				BR_ASSERT(false);
				return 0;
			}
		}
		auto height = verify_recursion(node->left);
		if (height == 0U) {
			return 0U;
		}
		if (height != verify_recursion(node->right)) {
			BR_ASSERT(false);
			return 0U;
		}
		if (node->color == Color::black) {
			++height;
		}
		return height;
	}

	static void rebalance_after_insertion(NodePointer const & header, NodePointer node) {
		node->color = Color::red;
		for (;;) {
			auto parent = node->parent;
			auto const grandparent = parent->parent;
			if (parent == header || parent->color == Color::black || grandparent == header) {
				break;
			}

			grandparent->color = Color::red;
			auto const grandparent_left = grandparent->left;
			auto const parent_is_left_child = parent == grandparent_left;
			auto const parent_brother = parent_is_left_child ? grandparent->right : grandparent_left;

			if (parent_brother != nullptr && parent_brother->color == Color::red) {
				parent->color = Color::black;
				parent_brother->color = Color::black;
				node = grandparent;
			} else {
				auto const node_is_left_child = parent->left == node;
				if (parent_is_left_child) {
					if (!node_is_left_child) {
						Base::rotate_left_no_parent_fix(parent, node);
						parent = node;
					}
					Base::rotate_right(header, grandparent, parent, grandparent->parent);
				} else {
					if (node_is_left_child) {
						Base::rotate_right_no_parent_fix(parent, node);
						parent = node;
					}
					Base::rotate_left(header, grandparent, parent, grandparent->parent);
				}
				parent->color = Color::black;
				break;
			}
		}
		header->parent->color = Color::black;
	}

	static void rebalance_after_erasure(NodePointer const & header, NodePointer const & target, typename Base::RebalanceData const & data) {
		Color target_color;
		if (data.y != target) {
			target_color = data.y->color;
			data.y->color = target->color;
		} else {
			target_color = target->color;
		}
		if (target_color != Color::red) {
			rebalance_after_erasure_restore_invariants(header, data.x, data.x_parent);
		}
	}

	static void rebalance_after_erasure_restore_invariants(NodePointer const & header, NodePointer node, NodePointer parent) {
		for(;;) {
			if (parent == header || (node != nullptr && node->color != Color::black)) {
				break;
			}
			auto const parent_left = parent->left;
			if (node == parent_left) {
				auto w = parent->right;
				if (w->color == Color::red) {
					w->color = Color::black;
					parent->color = Color::red;
					Base::rotate_left(header, parent, w, parent->parent);
					w = parent->right;
				}
				auto const w_left = w->left;
				auto const w_right = w->right;
				if ((w_left == nullptr || w_left->color == Color::black) && (w_right == nullptr || w_right->color == Color::black)) {
					w->color = Color::red;
					node = parent;
					parent = parent->parent;
				} else {
					if (w_right == nullptr || w_right->color == Color::black) {
						w_left->color = Color::black;
						w->color = Color::red;
						Base::rotate_right(header, w, w_left, w->parent);
						w = parent->right;
					}
					w->color = parent->color;
					parent->color = Color::black;
					auto const w_right_new = w->right;
					if (w_right_new != nullptr) {
						w_right_new->color = Color::black;
					}
					Base::rotate_left(header, parent, parent->right, parent->parent);
					break;
				}
			} else {
				auto w = parent_left;
				if (w->color == Color::red) {
					w->color = Color::black;
					parent->color = Color::red;
					Base::rotate_right(header, parent, w, parent->parent);
					w = parent->left;
				}
				auto const w_left = w->left;
				auto const w_right = w->right;
				if ((w_left == nullptr || w_left->color == Color::black) && (w_right == nullptr || w_right->color == Color::black)) {
					w->color = Color::red;
					node = parent;
					parent = parent->parent;
				} else {
					if (w_left == nullptr || w_left->color == Color::black) {
						w_right->color = Color::black;
						w->color = Color::red;
						Base::rotate_left(header, w, w_right, w->parent);
						w = parent->left;
					}

					w->color = parent->color;
					parent->color = Color::black;
					auto const w_left_new = w->left;
					if (w_left_new != nullptr) {
						w_left_new->color = Color::black;
					}
					Base::rotate_right(header, parent, parent->right, parent->parent);
					break;
				}
			}
		}
		if (node != nullptr) {
			node->color = Color::black;
		}
	}

}; // struct Algorithms<TNodePointer>

} // namespace RBTree
} // namespace Container
} // namespace Detail
} // namespace BR