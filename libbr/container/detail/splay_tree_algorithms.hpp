#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/detail/binary_tree_algorithms.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace SplayTree {

template< typename TNodePointer >
struct Algorithms : public BinaryTree::Algorithms<TNodePointer> {
public:
	using Base = BinaryTree::Algorithms<TNodePointer>;

	using NodePointer = TNodePointer;

protected:
	struct SplayDownFixer {
		SplayDownFixer(
			NodePointer const & header, NodePointer const & node, NodePointer const & left_most, NodePointer const & right_most
		) : header(header), left_most(left_most), right_most(right_most), node(node), left(header), right(header) {
		}

		~SplayDownFixer() {
			assemble();

			header->parent = node;
			node->parent = header;

			header->left = left_most;
			header->right = right_most;
		}

	private:
		void assemble() {
			auto const old_left  = node->left;
			auto const old_right = node->right;
			left->right = old_left;
			right->left = old_right;
			if (old_left != nullptr) {
				old_left->parent = left;
			}
			if (old_right != nullptr) {
				old_right->parent = right;
			}

			auto const header_right = header->right;
			auto const header_left  = header->left;
			node->left = header_right;
			node->right = header_left;
			if (header_right != nullptr) {
				header_right->parent = node;
			}
			if (header_left != nullptr) {
				header_left->parent = node;
			}
		}

	public:
		NodePointer const header, left_most, right_most;
		NodePointer node, left, right;
	}; // struct SplayDownFixer

public:
	template< typename TKey, typename TComparator >
	static auto find(NodePointer const & header, TKey const & key, TComparator comparator) -> NodePointer {
		splay_down(header, key, comparator);
		return Base::find(header, key, comparator);
	}

	template< typename TKey, typename TComparator >
	static auto lower_bound(NodePointer const & header, TKey const & key, TComparator comparator) -> NodePointer {
		splay_down(header, key, comparator);
		return Base::lower_bound(header, key, comparator);
	}

	template< typename TKey, typename TComparator >
	static auto upper_bound(NodePointer const & header, TKey const & key, TComparator comparator) -> NodePointer {
		splay_down(header, key, comparator);
		return Base::upper_bound(header, key, comparator);
	}

	template< typename TKey, typename TComparator >
	static auto equal_range(NodePointer const & header, TKey const & key, TComparator comparator) -> Pair< NodePointer, NodePointer > {
		splay_down(header, key, comparator);
		return Base::equal_range(header, key, comparator);
	}

	template< typename TKey, typename TComparator >
	static auto bounded_range(NodePointer const & header, TKey const & lower_key, TKey const & upper_key, TComparator comparator, bool left_closed = true, bool right_closed = true) -> Pair< NodePointer, NodePointer > {
		splay_down(header, lower_key, comparator);
		return Base::bounded_range(header, lower_key, upper_key, comparator, left_closed, right_closed);

	}

		template< typename TComparator >
	static auto insert_unique_check(NodePointer const & header, NodePointer const & hint, NodePointer const & new_node, TComparator comparator, typename Base::InsertCommitData & data) -> Pair< NodePointer, bool > {
		splay_down(header, new_node->element, comparator);
		return Base::insert_unique_check(header, hint, new_node, comparator, data);
	}

	template< typename TComparator >
	static auto insert_unique_check(NodePointer const & header, NodePointer const & new_node, TComparator comparator, typename Base::InsertCommitData & data) -> Pair< NodePointer, bool > {
		splay_down(header, new_node->element, comparator);
		return Base::insert_unique_check(header, new_node, comparator, data);
	}

	template< typename TComparator >
	static auto insert_equal(NodePointer const & header, NodePointer const & hint, NodePointer const & new_node, TComparator comparator) -> NodePointer {
		splay_down(header, new_node->element, comparator);
		return Base::insert_equal(header, hint, new_node, comparator);
	}

	template< typename TComparator >
	static auto insert_equal_lower_bound(NodePointer const & header, NodePointer const & new_node, TComparator comparator) -> NodePointer {
		splay_down(header, new_node->element, comparator);
		return Base::insert_equal_lower_bound(header, new_node, comparator);
	}

	template< typename TComparator >
	static auto insert_equal_upper_bound(NodePointer const & header, NodePointer const & new_node, TComparator comparator) -> NodePointer {
		splay_down(header, new_node->element, comparator);
		return Base::insert_equal_upper_bound(header, new_node, comparator);
	}

	static void erase(NodePointer const & header, NodePointer const & target) {
		if (target->left != nullptr) {
			splay_up(header, Base::prev_node(target));
		}
		Base::erase(header, target);
	}
	static void splay_up(NodePointer const & header, NodePointer const & node) {
		auto n = node == header ? header->right : node;
		auto t = header;
		if (n == t) {
			return;
		}
		for (;;) {
			auto p = n->parent;
			auto g = p->parent;
			if (p == t) {
				break;
			}
			if (g == t) {
				rotate(n);
			} else if ((p->left == n && g->left == p) || (p->right == n && g->right == p)) {
				rotate(p);
				rotate(n);
			} else {
				rotate(n);
			}
		}
	}

	template< typename TKey, typename TComparator >
	static auto splay_down(NodePointer const & header, TKey const & key, TComparator comparator) -> NodePointer {
		auto const old_root = header->parent;
		auto const left_most = header->left;
		auto const right_most = header->right;
		if (left_most == right_most) {
			return old_root != nullptr ? old_root : header;
		}

		header->left = nullptr;
		header->right = nullptr;

		SplayDownFixer fixer(header, old_root, left_most, right_most);

		for (;;) {
			if (comparator(key, fixer.node->element)) {
				auto const left = fixer.node->left;
				if (left == nullptr) {
					break;
				}
				if (comparator(key, left->element)) {
					Base::rotate_right_no_parent_fix(fixer.node, left);
					fixer.node = left;
					if (fixer.node->left == nullptr) {
						break;
					}
				}
				link_right(fixer.node, fixer.right);
			} else if (comparator(fixer.node->element, key)) {
				auto const right = fixer.node->right;
				if (right == nullptr) {
					break;
				}
				if (comparator(right->element, key)) {
					Base::rotate_left_no_parent_fix(fixer.node, right);
					fixer.node = right;
					if (fixer.node->right == nullptr) {
						break;
					}
				}
				link_left(fixer.node, fixer.left);
			} else {
				break;
			}
		}
		return fixer.node;
	};

protected:
	static void link_left(NodePointer & t, NodePointer & l) {
		l->right = t;
		t->parent = l;
		l = t;
		t = t->right;
	}

	static void link_right(NodePointer & t, NodePointer & r) {
		r->left = t;
		t->parent = r;
		r = t;
		t = t->left;
	}

	static void rotate(NodePointer const & n) {
		auto p = n->parent;
		auto g = p->parent;
		bool const g_is_header = Base::is_header(g);
		if (p->left == n) {
			p->left = n->right;
			if (p->left != nullptr) {
				p->left->parent = p;
			}
			n->right = p;
		} else {
			p->right = n->left;
			if (p->right != nullptr) {
				p->right->parent = p;
			}
			n->left = p;
		}

		p->parent = n;
		n->parent = g;

		if (g_is_header) {
			if (g->parent == p) {
				g->parent = n;
			} else {
				g->right = n;
			}
		} else {
			if (g->left == p) {
				g->left = n;
			} else {
				g->right = n;
			}
		}
	}

}; // struct Algorithms<TNodePointer>

} // namespace SplayTree
} // namespace Container
} // namespace Detail
} // namespace BR