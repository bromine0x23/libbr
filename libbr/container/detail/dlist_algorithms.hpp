#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace DList {

template< typename TNodePointer >
struct Algorithms {
public:
	using NodePointer = TNodePointer;

	struct StablePartitionInfo {
		Size size_left;
		Size size_right;
		NodePointer begin_right;
	};

public:
	static void init_header(NodePointer const & header) {
		header->prev = header->next = header;
	}

	static void link_before(NodePointer const & next, NodePointer const & node) {
		auto const prev = next->prev;
		node->prev = prev;
		node->next = next;
		prev->next = node;
		next->prev = node;
	}

	static void link_before(NodePointer const & p, NodePointer const & f, NodePointer const & l) {
		auto & prev = p->prev;
		f->prev = prev;
		l->next = p;
		prev->next = f;
		prev = l;
	}

	static void link_after(NodePointer const & prev, NodePointer const & node) {
		auto const next = prev->prev;
		node->prev = prev;
		node->next = next;
		prev->next = node;
		next->prev = node;
	}

	static auto unlink(NodePointer const & node) -> NodePointer {
		auto next = node->next;
		auto prev = node->prev;
		prev->next = next;
		next->prev = prev;
		return next;
	}

	static void unlink(NodePointer const & first, NodePointer const & last) {
		if (first != last) {
			auto prev_first = first->prev;
			last->prev = prev_first;
			prev_first->next = last;
		}
	}

	static void swap(NodePointer const & header0, NodePointer const & header1) {
		using BR::swap;
		if (header0 == header1) {
			return;
		}
		swap(header0->prev, header1->prev);
		swap(header0->next, header1->next);
		if (header0->next == header1) {
			header0->prev = header0->next = header0;
		} else {
			header0->prev->next = header0->next->prev = header0;
		}
		if (header1->next == header0) {
			header1->prev = header1->next = header1;
		} else {
			header1->prev->next = header1->next->prev = header1;
		}
	}

	static void insert_front(NodePointer const & header, NodePointer const & f, NodePointer const & l) {
		f->prev = header;
		l->next = header->next;
		l->next->prev = l;
		header->next = f;
	}

	static void transfer(NodePointer const & p, NodePointer const & f, NodePointer const & l) {
		if (f != l) {
			auto prev_p = p->prev, prev_f = f->prev, prev_l = l->prev;
			prev_l->next = p; p->prev = prev_l;
			prev_f->next = l; l->prev = prev_f;
			prev_p->next = f; f->prev = prev_p;
		}
	}

	static void transfer(NodePointer const & p, NodePointer const & n) {
		auto next_n = n->next;
		if (next_n != p && n != p) {
			auto prev_p = p->prev, prev_n = n->prev;
			prev_p->next = n; n->prev = prev_p;
			n->next = p; p->prev = n;
			next_n->prev = prev_n; prev_n->next = next_n;
		}
	}

	static void reverse(NodePointer const & p) {
		auto f = p->next;
		auto i = f->next;
		for (auto const e = p; i != e;) {
			auto n = i;
			i = i->next;
			transfer(f, n, i);
			f = n;
		}
	}

	template< typename TUnaryPredicate >
	static void stable_partition(NodePointer begin, NodePointer const & end, TUnaryPredicate predicate, StablePartitionInfo & info) {
		auto bcur = begin->prev;
		auto new_f = end;
		Size size_left = 0, size_right = 0;
		for (auto cur = begin; cur != end;) {
			if (predicate(cur->element)) {
				++size_left;
				bcur = cur;
				cur  = cur->next;
			} else {
				++size_right;
				auto last_to_remove = bcur;
				new_f = cur;
				bcur = cur;
				cur  = cur->next;
				BR_TRY {
					for (; cur != end;) {
						if (predicate(cur->element)) {
							++size_left;
							last_to_remove->next = cur;
							cur->prev = last_to_remove;
							last_to_remove = cur;
							auto next = cur->next;
							bcur->next = next;
							next->prev = bcur;
							cur = next;
						} else{
							++size_right;
							bcur = cur;
							cur  = cur->next;
						}
					}
				} BR_CATCH(...) {
					last_to_remove->next = new_f;
					new_f->prev = last_to_remove;
					BR_RETHROW;
				}
				last_to_remove->next = new_f;
				new_f->prev = last_to_remove;
				break;
			}
		}
		info.size_left = size_left;
		info.size_right = size_right;
		info.begin_right = new_f;
	}

}; // struct Algorithms<TNodePointer>

} // namespace DList
} // namespace Container
} // namespace Detail
} // namespace BR