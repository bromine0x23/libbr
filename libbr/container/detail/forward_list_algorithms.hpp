#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace ForwardList {

template< typename TNodePointer >
struct Algorithms {
public:
	using NodePointer = TNodePointer;

	struct StablePartitionInfo {
		Size size_left;
		Size size_right;
		NodePointer begin_right;
		NodePointer new_last;
	};

public:
	static void init(NodePointer const & node) {
		node->next = nullptr;
	}

	static auto find_prev(NodePointer from, NodePointer const node) -> NodePointer {
		for (auto next_from = from->next; next_from != node; from = from->next, next_from = from->next) {}
		return from;
	}

	static void link_after(NodePointer const & prev, NodePointer const & node) {
		node->next = prev->next;
		prev->next = node;
	}

	static void link_after(NodePointer const & prev, NodePointer const & first, NodePointer const & prev_last) {
		prev_last->next = prev->next;
		prev->next = first;
	}

	static void unlink_after(NodePointer const & prev) {
		auto node = prev->next;
		prev->next = node->next;
	}

	static void unlink_after(NodePointer const & prev_first, NodePointer const & last) {
		prev_first->next = last;
	}

	static void transfer_after(NodePointer const & prev, NodePointer const & node) {
		auto next = node->next;
		if (prev != node && prev != next) {
			node->next = next->next;
			next->next = prev->next;
			prev->next = next;
		}
	}

	static void transfer_after(NodePointer const & prev, NodePointer const & prev_first, NodePointer const & prev_last) {
		if (prev != prev_first && prev != prev_last && prev_first != prev_last) {
			auto first = prev_first->next;
			auto last = prev_last->next;
			auto node = prev->next;
			prev_first->next = last;
			prev_last->next = node;
			prev->next = first;
		}
	}

	static void swap(NodePointer const & head0, NodePointer const & head1) {
		using BR::swap;
		swap(head0->next, head1->next);
	}

	static void reverse(NodePointer const & head) {
		auto node = head->next;
		for (auto next = node; (next = node->next) != nullptr; ) {
			transfer_after(head, node);
		}
	}

}; // struct Algorithms<TNodePointer>

} // namespace ForwardList
} // namespace Container
} // namespace Detail
} // namespace BR