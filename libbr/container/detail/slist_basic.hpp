#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/detail/allocator_helpers.hpp>
#include <libbr/container/detail/slist_algorithms.hpp>
#include <libbr/container/detail/slist_iterator.hpp>
#include <libbr/container/detail/slist_node.hpp>
#include <libbr/container/detail/node_destructor.hpp>
#include <libbr/container/detail/raw_array.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace SList {


template< typename TElement, typename TAllocator >
class Basic {
public:
	using Element = TElement;

	using Allocator = TAllocator;

protected:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using VoidPointer = typename AllocatorTraits::VoidPointer;

	using Node = SList::Node< Element, VoidPointer >;

	using NodeAllocator = typename AllocatorTraits::template Rebind<Node>;

	using NodeAllocatorTraits = BR::AllocatorTraits<NodeAllocator>;

	using NodePointer = typename NodeAllocatorTraits::Pointer;

	using BasicNode = typename Node::Base;

	using BasicNodeAllocator = typename AllocatorTraits::template Rebind<BasicNode>;

	using BasicNodeAllocatorTraits = BR::AllocatorTraits<BasicNodeAllocator>;

	using BasicNodePointer = typename BasicNodeAllocatorTraits::Pointer;

	using BasicNodePointerTraits = PointerTraits<BasicNodePointer>;

	using NodeDestructor = Container::NodeDestructor<NodeAllocator>;

	using NodeHolder = UniquePointer< Node, NodeDestructor >;

	using Algorithms = SList::Algorithms<NodePointer>;

public:

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using Size = typename AllocatorTraits::Size;

	using Difference = typename AllocatorTraits::Difference;

	using Iterator = SList::Iterator<NodePointer>;

	using ConstIterator = SList::ConstIterator<NodePointer>;

public:
	Basic() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) : m_impl() {
	}

	Basic(Allocator const & allocator) : m_impl(NodeAllocator(allocator), BasicNode{}) {
	}

	Basic(Basic && list) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : m_impl(move(list.m_impl)) {
		Algorithms::init(list.m_head());
	}

	~Basic() {
		m_clear();
	}

protected:
	auto m_allocator() noexcept -> NodeAllocator & {
		return m_impl.template get<NodeAllocator>();
	}

	auto m_allocator() const noexcept -> NodeAllocator const & {
		return m_impl.template get<NodeAllocator>();
	}

	auto m_head() const noexcept -> NodePointer {
		return static_cast<NodePointer>(BasicNodePointerTraits::make_pointer(const_cast<BasicNode &>(m_impl.template get<BasicNode>())));
	}

	auto m_before_begin() const noexcept -> NodePointer {
		return m_head();
	}

	auto m_begin() const noexcept -> NodePointer {
		return m_head()->next;
	}

	auto m_end() const noexcept -> NodePointer {
		return nullptr;
	}

	auto m_empty() const noexcept -> bool {
		return m_begin() == m_end();
	}

	void m_copy_assign_allocator(Basic const & list) {
		m_copy_assign_allocator(list, typename NodeAllocatorTraits::IsPropagateOnContainerCopyAssignment{});
	}

	void m_move_assign(Basic & list) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<NodeAllocator> >{}) {
		m_move_assign(list, typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment{});
	}

	template< typename... TArgs >
	auto m_construct_node(TArgs &&... args) -> NodeHolder {
		auto & allocator = m_allocator();
		NodeHolder holder(NodeAllocatorTraits::allocate(allocator, 1), NodeDestructor(allocator, 1));
		Algorithms::init(holder.get());
		NodeAllocatorTraits::construct(allocator, address_of(holder->element), forward<TArgs>(args)...);
		holder.get_deleter().constructed = true;
		return holder;
	}

	void m_assign(Element const & element, Size count) {
		auto prev = m_before_begin(), node = m_begin(), end = m_end();
		for (; node != end && count > 0; node = node->next, (void)--count) {
			node->element = element;
			prev = node;
		}
		if (node == end) {
			m_insert_after(prev, element, count);
		} else {
			m_erase_after(prev, end);
		}
	}

	template< typename TInputIterator >
	void m_assign(TInputIterator first, TInputIterator last) {
		auto prev = m_before_begin(), node = m_begin(), end = m_end();
		for (; node != end && first != last; node = node->next, (void)++first) {
			node->element = *first;
			prev = node;
		}
		if (node == end) {
			m_insert_after(prev, first, last);
		} else {
			m_erase_after(prev, end);
		}
	}

	void m_prepare_after(NodePointer const & position, Size count) {
		if (count > 0) {
			auto holder = m_construct_node();
			auto first = holder.release(), prev_last = first;
			BR_TRY {
				for (; --count > 0; prev_last = prev_last->next) {
					holder = m_construct_node();
					prev_last->next = holder.release();
				}
			} BR_CATCH(...) {
				for (; first != nullptr;) {
					auto next = first->next;
					destroy_node(m_allocator(), first);
					first = next;
				}
				BR_RETHROW;
			}
			Algorithms::link_after(position, first, prev_last);
		}
	}

	void m_resize(Size new_size) {
		Size size = 0;
		auto prev = m_head(), node = m_begin();
		for (; node != m_end() && size < new_size; prev = prev->next, node = node->next, ++size) {}
		if (node != m_end()) {
			m_erase_after(prev, m_end());
		} else {
			m_prepare_after(prev, new_size - size);
		}
	}

	void m_resize(Size new_size, Element const & element) {
		Size size = 0;
		auto prev = m_head(), node = m_begin();
		for (; node != m_end() && size < new_size; prev = prev->next, node = node->next, ++size) {}
		if (node != m_end()) {
			m_erase_after(prev, m_end());
		} else {
			m_insert_after(prev, element, new_size - size);
		}
	}

	auto m_insert_after(NodePointer position, NodeHolder holder) -> NodePointer {
		auto node = m_insert_after(position, holder.get());
		holder.release();
		return node;
	}

	auto m_insert_after(NodePointer position, NodePointer const & node) -> NodePointer {
		Algorithms::link_after(position, node);
		return node;
	}

	auto m_insert_after(NodePointer const & prev, Element const & element, Size count) -> NodePointer {
		auto result = prev;
		if (count > 0) {
			auto holder = m_construct_node(element);
			auto first = holder.release(), prev_last = first;
			BR_TRY {
				for (; --count > 0; prev_last = prev_last->next) {
					holder = m_construct_node(element);
					prev_last->next = holder.release();
				}
			} BR_CATCH(...) {
				for (; first != nullptr;) {
					auto next = first->next;
					destroy_node(m_allocator(), first);
					first = next;
				}
				BR_RETHROW;
			}
			Algorithms::link_after(prev, first, prev_last);
			result = prev_last;
		}
		return result;
	}

	template< typename TInputIterator >
	auto m_insert_after(NodePointer const & prev, TInputIterator f, TInputIterator l) -> NodePointer {
		auto result = prev;
		if (f != l) {
			auto holder = m_construct_node(*f);
			auto first = holder.release(), prev_last = first;
			BR_TRY {
				for (++f; f != l; ++f, (void)(prev_last = prev_last->next)) {
					holder = m_construct_node(*f);
					prev_last->next = holder.release();
				}
			} BR_CATCH(...) {
				for (; first != nullptr;) {
					auto next = first->next;
					destroy_node(m_allocator(), first);
					first = next;
				}
				BR_RETHROW;
			}
			Algorithms::link_after(result, first, prev_last);
			result = prev_last;
		}
		return result;
	}

	auto m_erase_after(NodePointer prev) -> NodePointer {
		auto node = prev->next;
		auto result = node->next;
		Algorithms::unlink_after(prev);
		destroy_node(m_allocator(), node);
		return result;
	}

	auto m_erase_after(NodePointer prev_first, NodePointer last) -> NodePointer {
		Algorithms::unlink_after(prev_first, last);
		auto first = prev_first->next;
		for (; first != last;) {
			auto node = first;
			first = first->next;
			destroy_node(m_allocator(), node);
		}
		return last;
	}

	void m_clear() noexcept {
		for (auto node = m_begin(); node != m_end();) {
			auto next = node->next;
			destroy_node(m_allocator(), node);
			node = next;
		}
		Algorithms::init(m_head());
	}

	template< typename TUnaryPredicate >
	void m_remove(TUnaryPredicate & predicate) {
		for (auto prev = m_head(), node = m_begin(), end = m_end(); node != end; node = prev->next) {
			if (predicate(node->element)) {
				auto last = node->next;
				for (; last != end && predicate(last->element); last = last->next) {}
				m_erase_after(prev, last);
				if (last == end) {
					break;
				}
				prev = last;
			} else {
				prev = prev->next;
			}
		}
	}

	void m_splice_after(NodePointer const & prev, Basic & list) {
		if (!list.m_empty()) {
			auto prev_first = list.m_head();
			auto prev_last = Algorithms::find_prev(prev_first, list.m_end());
			Algorithms::transfer_after(prev, prev_first, prev_last);
		}
	}

	void m_splice_after(NodePointer const & prev, Basic & list, NodePointer const & node) {
		Algorithms::transfer_after(prev, node);
	}

	void m_splice_after(NodePointer const & prev, Basic & list, NodePointer const & prev_first, NodePointer const & last) {
		if (prev != prev_first && prev_first != last) {
			auto prev_last = Algorithms::find_prev(prev_first, last);
			Algorithms::transfer_after(prev, prev_first, prev_last);
		}
	}

	void m_splice_after_closed(NodePointer const & prev, Basic & list, NodePointer const & prev_first, NodePointer const & prev_last) {
		Algorithms::transfer_after(prev, prev_first, prev_last);
	}

	template< typename TBinaryPredicate >
	void m_unique(TBinaryPredicate & predicate) {
		auto const end = m_end();
		for (auto node = m_begin(); node != end;) {
			auto next = node->next;
			for (; next != end && predicate(node->element, next->element); next = next->next) {}
			if (node->next != next) {
				m_erase_after(node, next);
			}
			node = next;
		}
	}

	template< typename TComparator >
	void m_merge(Basic & list, TComparator & comparator) {
		auto prev = m_before_begin();
		for (; !list.m_empty();) {
			auto prev_last = list.m_before_begin(), last = list.m_begin();
			auto node = prev->next;
			for (; node != m_end() && !comparator(last->element, node->element); prev = node, (void)(node = node->next)) {}
			if (node == m_end()) {
				m_splice_after(prev, list);
				break;
			}
			prev_last = last;
			last = last->next;
			for (; last != list.m_end() && comparator(last->element, node->element); prev_last = last, (void)(last = last->next)) {}
			m_splice_after_closed(prev, list, list.m_before_begin(), prev_last);
		}
	}

	template< typename TComparator >
	void m_sort(TComparator & comparator) {
		if (m_empty()) {
			return;
		}
		Basic carry(m_allocator());
		RawArray<Basic, 64> counter(m_allocator());
		auto fill = 0;
		for (; !m_empty(); ) {
			carry.m_splice_after(carry.m_before_begin(), *this, this->m_before_begin());
			auto i = 0;
			for(; i < fill && !counter[i].m_empty(); ) {
				counter[i].m_merge(carry, comparator);
				carry.m_swap(counter[i++]);
			}
			BR_ASSERT(counter[i].m_empty());
			carry.m_swap(counter[i]);
			if (i == fill) {
				++fill;
			}
		}
		for (auto i = 1; i < fill; ++i) {
			counter[i].m_merge(counter[i-1], comparator);
		}
		m_swap(counter[fill-1]);
	}

	void m_swap(Basic & list) noexcept(typename NodeAllocatorTraits::IsAlwaysEqual{}) {
		using BR::swap;
		swap_allocator(m_allocator(), list.m_allocator());
		Algorithms::swap(m_head(), list.m_head());
	}

	void m_reverse() {
		if (!m_empty()) {
			Algorithms::reverse(m_head());
		}
	}

private:
	void m_copy_assign_allocator(Basic const & list, BooleanTrue) {
		if (m_allocator() != list.m_allocator()) {
			m_clear();
		}
		m_allocator() = list.m_allocator();
	}

	void m_copy_assign_allocator(Basic const & tree, BooleanFalse) {
	}

	void m_move_assign(Basic & list, BooleanTrue) noexcept(HasNothrowMoveAssignment<NodeAllocator>{}) {
		m_clear();
		m_splice_after(m_before_begin(), list);
	}

	void m_move_assign(Basic & list, BooleanFalse) {
		if (m_allocator() != list.m_allocator()) {
			m_assign(list.m_begin(), list.m_end());
		} else {
			m_move_assign(list, BooleanTrue{});
		}
	}

protected:
	BR::Tuple< NodeAllocator, BasicNode > m_impl;

}; // class Basic<TElement, TAllocator>

} // namespace SList
} // namespace Container
} // namespace Detail
} // namespace BR