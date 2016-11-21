#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/memory/pointer_traits.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace BinaryTree {


template< typename TBasicNodePointer >
struct BasicAlgorithms {

	using NodePointer = TBasicNodePointer;


};

template< typename TNodePointer >
struct Algorithms {
public:
	using NodePointer = TNodePointer;

	using PointerTraits = BR::PointerTraits<NodePointer>;

	using Node = typename PointerTraits::Element;

	using BasicNode = typename Node::Base;

	using BasicNodePointer = typename PointerTraits::template Rebind<BasicNode>;

	struct InsertCommitData {
		bool link_left;
		NodePointer node;
	};

	struct RebalanceData {
		NodePointer x;
		NodePointer x_parent;
		NodePointer y;
	};

public:
	static auto is_header(NodePointer const & node) noexcept -> bool {
		if (node->parent == nullptr) {
			return true;
		}
		auto const left = node->left, right = node->right;
		if (left == nullptr || right == nullptr) {
			return false;
		}
		return left == right || left->parent != node || right->parent != node;
	}

	static auto get_header(NodePointer const & node) -> NodePointer {
		auto n = node;
		auto p = node->parent;
		if (p != nullptr) {
			auto pp = p->parent;
			if (n != pp) {
				do {
					n = p;
					p = pp;
					pp = pp->parent;
				} while(n != pp);
				n = p;
			} else if (!is_header(n)){
				n = p;
			}
		}
		return n;
	}

	static void init_header(NodePointer const & header) noexcept {
		header->parent = nullptr;
		header->left = header->right = header;
	}

	static auto find_left_most(NodePointer node) -> NodePointer {
		for (; node->left != nullptr;) {
			node = node->left;
		}
		return node;
	}

	static auto find_right_most(NodePointer node) -> NodePointer {
		for (; node->right != nullptr;) {
			node = node->right;
		}
		return node;
	}

	static auto prev_node(NodePointer const & node) -> NodePointer {
		if (is_header(node)) {
			return node->right;
		} else {
			auto const left = node->left;
			if (left != nullptr) {
				return find_right_most(left);
			}
		}
		auto n = node;
		auto p = n->parent;
		for (; n == p->left; p = p->parent) {
			n = p;
		}
		return p;
	}

	static auto next_node(NodePointer const & node) -> NodePointer {
		auto const right = node->right;
		if (right != nullptr) {
			return find_left_most(right);
		}
		auto n = node;
		auto p = n->parent;
		for (; n == p->right; p = p->parent) {
			n = p;
		}
		return n->right != p ? p : n;
	}

	static NodePointer get_leaf(NodePointer node) {
		for (;;) {
			if (node->left != nullptr) {
				node = node->left;
				continue;
			}
			if (node->right != nullptr) {
				node = node->right;
				continue;
			}
			break;
		}
		return node;
	}

	template< typename TKey, typename TComparator >
	static auto lower_bound(NodePointer const & header, TKey const & key, TComparator comparator) -> NodePointer {
		return lower_bound_loop(header->parent, header, key, comparator);
	}

	template< typename TKey, typename TComparator >
	static auto upper_bound(NodePointer const & header, TKey const & key, TComparator comparator) -> NodePointer {
		return upper_bound_loop(header->parent, header, key, comparator);
	}

	template< typename TKey, typename TComparator >
	static auto bounded_range(NodePointer const & header, TKey const & lower_key, TKey const & upper_key, TComparator comparator, bool left_closed = true, bool right_closed = true) -> Pair< NodePointer, NodePointer > {
		auto node = header->parent, result = header;
		for (; node != nullptr;) {
			if (comparator(node->element, lower_key)) {
				node = node->right;
			} else if (comparator(upper_key, node->element)){
				result = node;
				node = node->left;
			} else {
				return Pair< NodePointer, NodePointer >(
					left_closed ? lower_bound_loop(node->left, node, lower_key, comparator) : upper_bound_loop(node, result, lower_key, comparator),
					right_closed ? upper_bound_loop(node->right, result, upper_key, comparator) : lower_bound_loop(node, result, upper_key, comparator)
				);
			}
		}
		return Pair< NodePointer, NodePointer >(result, result);
	}

	template< typename TKey, typename TComparator >
	static auto equal_range(NodePointer const & header, TKey const & key, TComparator comparator) -> Pair< NodePointer, NodePointer > {
		return bounded_range(header, key, key, comparator, true, true);
	}

	template< typename TKey, typename TComparator >
	static auto find(NodePointer const & header, TKey const & key, TComparator comparator) -> NodePointer {
		NodePointer y = lower_bound(header, key, comparator);
		return (y == header || comparator(key, y->element)) ? header : y;
	}

	template< typename TKey, typename TComparator >
	static auto count(NodePointer const & header, TKey const & key, TComparator comparator) -> Size {
		Size n = 0;
		for (auto range = equal_range(header, key, comparator); range.first != range.second; range.first = next_node(range.first)) {
			++n;
		}
		return n;
	}

	template< typename TComparator >
	static auto insert_unique_check(NodePointer const & header, NodePointer const & hint, NodePointer const & new_node, TComparator comparator, InsertCommitData & data) -> Pair< NodePointer, bool > {
		if (hint == header || comparator(new_node->element, hint->element)) {
			NodePointer prev = hint;
			if (hint == header->left || comparator((prev = prev_node(hint))->element, new_node->element)) {
				bool link_left = header->parent != nullptr || hint->left == nullptr;
				data.link_left = link_left;
				data.node = link_left ? hint : prev;
			}
			return Pair< NodePointer, bool >(nullptr, true);
		}
		return insert_unique_check(header, new_node, comparator, data);
	}

	template< typename TComparator >
	static auto insert_unique_check(NodePointer const & header, NodePointer const & new_node, TComparator comparator, InsertCommitData & data) -> Pair< NodePointer, bool > {
		auto node = header;
		NodePointer prev = nullptr;
		bool left_child = true;
		for (auto p = node->parent; p != nullptr; p = (left_child = comparator(new_node->element, p->element)) ? p->left : (prev = node, p->right)) {
			node = p;
		}
		bool not_present = (prev == nullptr) || comparator(prev->element, new_node->element);
		if (not_present) {
			data.link_left = left_child;
			data.node = node;
		}
		return Pair< NodePointer, bool >(prev, not_present);
	}

	template< typename TComparator >
	static void insert_equal_check(NodePointer const & header, NodePointer const & hint, NodePointer const & new_node, TComparator comparator, InsertCommitData & data) {
		if (hint == header || !comparator(hint->element, new_node->element)) {
			auto prev = hint;
			if (hint == header->left || !comparator(new_node->element, (prev = prev_node(hint))->element)) {
				bool link_left = header->parent == nullptr || hint->left == nullptr;
				data.link_left = link_left;
				data.node = link_left ? hint : prev;
			} else{
				insert_equal_upper_bound_check(header, new_node, comparator, data);
			}
		} else {
			insert_equal_lower_bound_check(header, new_node, comparator, data);
		}
	}

	template< typename TComparator >
	static void insert_equal_lower_bound_check(NodePointer const & header, NodePointer const & new_node, TComparator comparator, InsertCommitData & data) {
		auto node = header;
		for (auto p = node->parent; p != nullptr; p = !comparator(p->element, new_node->element) ? p->left : p->right) {
			node = p;
		}
		data.link_left = (node == header) || !comparator(node->element, new_node->element);
		data.node = node;
	}

	template< typename TComparator >
	static void insert_equal_upper_bound_check(NodePointer const & header, NodePointer const & new_node, TComparator comparator, InsertCommitData & data) {
		auto node = header;
		for (auto p = node->parent; p != nullptr; p = comparator(new_node->element, p->element) ? p->left : p->right) {
			node = p;
		}
		data.link_left = (node == header) || comparator(new_node->element, node->element);
		data.node = node;
	}

	static void insert_commit(NodePointer const & header, NodePointer const & new_node, InsertCommitData & data) {
		auto parent = data.node;
		if (parent == header) {
			header->parent = header->left = header->right = new_node;
		} else if (data.link_left) {
			parent->left = new_node;
			if (parent == header->left) {
				header->left = new_node;
			}
		} else {
			parent->right = new_node;
			if (parent == header->right) {
				header->right = new_node;
			}
		}
		new_node->parent = parent;
		new_node->left = new_node->right = nullptr;
	}

	static void erase(NodePointer const & header, NodePointer const & target) {
		RebalanceData ignored;
		erase(header, target, ignored);
	}

protected:
	template< typename TKey, typename TComparator >
	static auto lower_bound_loop(NodePointer node, NodePointer result, TKey const & key, TComparator comparator) -> NodePointer {
		for (; node != nullptr;) {
			if (comparator(node->element, key)) {
				node = node->right;
			} else {
				result = node;
				node = node->left;
			}
		}
		return result;
	}

	template< typename TKey, typename TComparator >
	static auto upper_bound_loop(NodePointer node, NodePointer result, TKey const & key, TComparator comparator) -> NodePointer {
		for (; node != nullptr;) {
			if (comparator(key, node->element)) {
				result = node;
				node = node->left;
			} else {
				node = node->right;
			}
		}
		return result;
	}

	static void erase(NodePointer const & header, NodePointer const & target, RebalanceData & data) {
		auto const target_left = target->left, target_right = target->right;
		NodePointer x, y = target;
		if (target_left == nullptr) {
			x = target_right;
		} else if (target_right == nullptr) {
			x = target_left;
		} else {
			y = find_left_most(target_right);
			x = y->right;
		}
		NodePointer x_parent;
		auto const target_parent = target->parent;
		auto const target_is_left_child = target_parent->left == target;
		if (y != target) {
			y->left = target_left;
			target_left->parent = y;
			if (y != target_right) {
				y->right = target_right;
				target_right->parent = y;
				x_parent = y->parent;
				BR_ASSERT(x_parent->left == y);
				if (x != nullptr) {
					x->parent = x_parent;
				}
				x_parent->left = x;
			} else {
				x_parent = y;
			}
			y->parent = target_parent;
			set_child(header, target_parent, y, target_is_left_child);
		} else {
			x_parent = target_parent;
			if (x != nullptr) {
				x->parent = target_parent;
			}
			set_child(header, target_parent, x, target_is_left_child);
			if (header->left == target) {
				BR_ASSERT(target_left == nullptr);
				header->left = target_right != nullptr ? find_left_most(target_right) : target_parent;
			}
			if (header->right == target) {
				BR_ASSERT(target_right == nullptr);
				header->right = target_left != nullptr ? find_right_most(target_left) : target_parent;
			}
		}

		data.x = x;
		data.x_parent = x_parent;
		data.y = y;
	}

	static void set_child(NodePointer const & header, NodePointer const & node, NodePointer const & child, bool const at_left) noexcept {
		if (node == header) {
			header->parent = child;
		} else if (at_left) {
			node->left = child;
		} else {
			node->right = child;
		}
	}

	static void rotate_left_no_parent_fix(NodePointer const & node, NodePointer const & right) noexcept {
		auto right_left = right->left;
		node->right = right_left;
		if (right_left != nullptr) {
			right_left->parent = node;
		}
		right->left = node;
		node->parent = right;
	}

	static void rotate_left(NodePointer const & header, NodePointer const & node, NodePointer const & parent, NodePointer const & right) noexcept {
		auto const was_left = parent->left == node;
		rotate_left_no_parent_fix(node, right);
		right->parent = parent;
		set_child(header, parent, right, was_left);
	}

	static void rotate_right_no_parent_fix(NodePointer const & node, NodePointer const & left) noexcept {
		auto left_right = left->right;
		node->left = left_right;
		if (left_right != nullptr) {
			left_right->parent = node;
		}
		left->right = node;
		node->parent = left;
	}

	static void rotate_right(NodePointer const & header, NodePointer const & node, NodePointer const & parent, NodePointer const & left) noexcept {
		auto const was_left = parent->left == node;
		rotate_right_no_parent_fix(node, left);
		left->parent = parent;
		set_child(header, parent, left, was_left);
	}
};

} // namespace BinaryTree
} // namespace Container
} // namespace Detail
} // namespace BR