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

	static void swap(NodePointer const head0, NodePointer const & head1) {
		using BR::swap;
		swap(head0->next, head1->next);
	}

	template< typename TUnaryPredicate >
	static void stable_partition(NodePointer before_begin, NodePointer const & end, TUnaryPredicate predicate, StablePartitionInfo & info) {
		auto bcur = before_begin;
		auto cur  = bcur->next;
		auto new_f = end;
		Size size_left = 0, size_right = 0;
		for (; cur != end;) {
			if (predicate(cur)) {
				++size_left;
				bcur = cur;
				cur  = cur->next;
			} else{
				++size_right;
				auto last_to_remove = bcur;
				new_f = cur;
				bcur = cur;
				cur  = cur->next;
				BR_TRY {
					for (; cur != end; ) {
						if (predicate(cur)) {
							++size_left;
							last_to_remove->next = cur;
							last_to_remove = cur;
							auto nxt = cur->next;
							bcur->next = nxt;
							cur = nxt;
						} else{
							++size_right;
							bcur = cur;
							cur  = cur->next;
						}
					}
				} BR_CATCH(...) {
					last_to_remove->next = new_f;
					BR_RETHROW;
				}
				last_to_remove->next = new_f;
				break;
			}
		}
		info.size_left = size_left;
		info.size_right = size_right;
		info.begin_right = new_f;
		info.new_last = bcur;
	}

}; // struct Algorithms<TNodePointer>

} // namespace ForwardList
} // namespace Container
} // namespace Detail
} // namespace BR