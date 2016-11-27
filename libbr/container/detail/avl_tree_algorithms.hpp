#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/detail/binary_tree_algorithms.hpp>
#include <libbr/container/detail/avl_tree_balance.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace AVLTree {

template< typename TNodePointer >
struct Algorithms : public BinaryTree::Algorithms<TNodePointer> {
public:
	using Base = BinaryTree::Algorithms<TNodePointer>;

	using NodePointer = TNodePointer;

public:
	static auto is_header(NodePointer const & node) noexcept -> bool {
		return node->balance == Balance::zero && Base::is_header(node);
	}

	static void init_header(NodePointer const & header) noexcept {
		Base::init_header(header);
		header->balance = Balance::zero;
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
		Size height;
		return verify_recursion(header->parent, height);
	}

protected:
	static auto verify_recursion(NodePointer node, Size & height) -> bool  {
		if (node == nullptr) {
			height = 0;
			return true;
		}
		Size left_height, right_height;
		if (!verify_recursion(node->left, left_height) || !verify_recursion(node->right, right_height)) {
			return false;
		}
		height = 1U + (left_height > right_height ? left_height : right_height);
		if (left_height == right_height) {
			if (node->balance != Balance::zero) {
				BR_ASSERT(false);
				return false;
			}
		} else if (left_height < right_height) {
			if (right_height - left_height > 1) {
				BR_ASSERT(false);
				return false;
			} else if (node->balance != Balance::positive) {
				BR_ASSERT(false);
				return false;
			}
		} else {
			if (left_height - right_height > 1) {
				BR_ASSERT(false);
				return false;
			} else if (node->balance != Balance::negative) {
				BR_ASSERT(false);
				return false;
			}
		}
		return true;
	}

	static void rebalance_after_insertion(NodePointer const & header, NodePointer node) {
		node->balance = Balance::zero;
		for (auto root = header->parent; node != root; root = header->parent) {
			auto const parent = node->parent;
			auto const is_left_child = node == parent->left;

			switch (parent->balance) {
				case Balance::zero:
					parent->balance = is_left_child ? Balance::negative : Balance::positive;
					node = parent;
					break;
				case Balance::negative:
					if (is_left_child) {
						if (node->balance == Balance::positive) {
							rotate_left_right(header, parent, node);
						} else {
							rotate_right(header, parent, node, parent->parent);
						}
					} else {
						parent->balance = Balance::zero;
					}
					return;
				case Balance::positive:
					if (is_left_child) {
						parent->balance = Balance::zero;
					} else {
						if (node->balance == Balance::negative) {
							rotate_right_left(header, parent, node);
						} else {
							rotate_left(header, parent, node, parent->parent);
						}
					}
					return;
			}
		}
	}

	static void rebalance_after_erasure(NodePointer const & header, NodePointer const & target, typename Base::RebalanceData const & data) {
		if (data.y != target) {
			data.y->balance = target->balance;
		}
		rebalance_after_erasure_restore_invariants(header, data.x, data.x_parent);
	}

	static void rebalance_after_erasure_restore_invariants(NodePointer const & header, NodePointer x, NodePointer x_parent) {
		for (auto root = header->parent; x != root; root = header->parent) {
			auto const x_parent_balance = x_parent->balance;
			auto const x_parent_left = x_parent->left;
			auto const x_parent_right = x_parent->right;
			switch (x_parent_balance) {
				case Balance::zero:
					x_parent->balance = (x == x_parent_right ? Balance::negative : Balance::positive);
					return;
				case Balance::negative:
					if (x == x_parent_left) {
						x_parent->balance = Balance::zero;
						x = x_parent;
					} else {
						if (x_parent_left->balance == Balance::positive) {
							x = rotate_left_right(header, x_parent, x_parent_left);
						} else {
							rotate_right(header, x_parent, x_parent_left, x_parent->parent);
							x = x_parent_left;
						}
						if (x->balance == Balance::positive) {
							return;
						}
					}
					break;
				case Balance::positive:
					if (x == x_parent_right) {
						x_parent->balance = Balance::zero;
						x = x_parent;
					} else {
						if (x_parent_right->balance == Balance::negative) {
							x = rotate_right_left(header, x_parent, x_parent_right);
						} else {
							rotate_left(header, x_parent, x_parent_right, x_parent->parent);
							x = x_parent_right;
						}
						if (x->balance == Balance::negative) {
							return;
						}
					}
					break;
			}
			x_parent = x->parent;
		}
	}

	static void left_right_balancing(NodePointer const & parent, NodePointer const & l, NodePointer const & r) {
		auto const c_balance = parent->balance;
		parent->balance = Balance::zero;
		switch (c_balance) {
			case Balance::negative:
				l->balance = Balance::zero;
				r->balance = Balance::positive;
				break;
			case Balance::zero:
				l->balance = Balance::zero;
				r->balance = Balance::zero;
				break;
			case Balance::positive:
				l->balance = Balance::negative;
				r->balance = Balance::zero;
				break;
		}
	}

	static auto rotate_left_right(NodePointer const & header, NodePointer const & node, NodePointer const left) -> NodePointer {
		auto const left_right = left->right;
		Base::rotate_left_no_parent_fix(left, left_right);
		Base::rotate_right(header, node, left_right, node->parent);
		left_right_balancing(left_right, left, node);
		return left_right;
	}

	static auto rotate_right_left(NodePointer const & header, NodePointer const & node, NodePointer const right) -> NodePointer {
		auto const right_left = right->left;
		Base::rotate_right_no_parent_fix(right, right_left);
		Base::rotate_left(header, node, right_left, node->parent);
		left_right_balancing(right_left, node, right);
		return right_left;
	}

	static void rotate_left(NodePointer const & header, NodePointer const & node, NodePointer const right, NodePointer const parent) {
		Base::rotate_left(header, node, right, parent);
		if (right->balance == Balance::positive) {
			node->balance = Balance::zero;
			right->balance = Balance::zero;
		} else {
			node->balance = Balance::positive;
			right->balance = Balance::negative;
		}
	}

	static void rotate_right(NodePointer const & header, NodePointer const & node, NodePointer left, NodePointer parent) {
		Base::rotate_right(header, node, left, parent);
		if (left->balance == Balance::negative) {
			node->balance = Balance::zero;
			left->balance = Balance::zero;
		} else {
			node->balance = Balance::negative;
			left->balance = Balance::positive;
		}
	}

}; // struct Algorithms<TNodePointer>

} // namespace RBTree
} // namespace Container
} // namespace Detail
} // namespace BR