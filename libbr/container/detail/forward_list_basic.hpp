#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/detail/allocator_helpers.hpp>
#include <libbr/container/detail/forward_list_algorithms.hpp>
#include <libbr/container/detail/forward_list_iterator.hpp>
#include <libbr/container/detail/forward_list_node.hpp>
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
namespace ForwardList {


template< typename TElement, typename TAllocator >
class Basic {
public:
	using Element = TElement;

	using Allocator = TAllocator;

protected:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using VoidPointer = typename AllocatorTraits::VoidPointer;

	using Node = ForwardList::Node< Element, VoidPointer >;

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

	using Algorithms = ForwardList::Algorithms<NodePointer>;

public:
	using Reference = Element &;

	using ConstReference = Element const &;

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using Size = typename AllocatorTraits::Size;

	using Difference = typename AllocatorTraits::Difference;

	using Iterator = ForwardList::Iterator<NodePointer>;

	using ConstIterator = ForwardList::ConstIterator<NodePointer>;

public:
	Basic() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) : m_impl() {
	}

	Basic(Allocator const & allocator) : m_impl(NodeAllocator(allocator)) {
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

	void m_prepare_after(NodePointer const & position, Size count) {
		if (count > 0) {
			auto holder = m_construct_node();
			auto first = holder.release(), prev_last = first;
			BR_TRY {
				for (; count-- > 0; prev_last = prev_last->next) {
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

	auto m_insert_after(NodePointer const & position, Element const & element, Size count) -> NodePointer {
		auto result = position;
		if (count > 0) {
			auto holder = m_construct_node(element);
			auto first = holder.release(), prev_last = first;
			BR_TRY {
				for (; count-- > 0; prev_last = prev_last->next) {
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
			Algorithms::link_after(position, first, prev_last);
			result = prev_last;
		}
		return result;
	}

	template< typename TInputIterator >
	auto m_insert_after(NodePointer const & position, TInputIterator f, TInputIterator l) -> NodePointer {
		auto result = position;
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

	auto m_erase_after(NodePointer position) -> NodePointer {
		auto result = position->next;
		Algorithms::unlink_after(position);
		destroy_node(m_allocator(), position);
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
		return first;
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

	auto m_splice_after(NodePointer const & prev, Basic & list) -> NodePointer {
		auto last_inserted = prev;
		if (!list.m_empty()) {
			auto prev_first = list.m_head();
			auto prev_last = Algorithms::find_prev(prev_first, list.m_end());
			Algorithms::transfer_after(prev, prev_first, prev_last);
			last_inserted = prev_last;
		}
		return last_inserted;
	}

	void m_splice_after(NodePointer const & prev, Basic & list, NodePointer const & node) {
		Algorithms::transfer_after(prev, node, node->next);
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

	template< typename TComparator >
	auto m_merge(Basic & list, TComparator & comparator) -> NodePointer {
		auto last_inserted = m_end();
		auto prev = m_head();
		for (; !list.m_empty();) {
			auto prev_last = list.m_head(), last = prev_last->next;
			auto node = prev->next;
			for (; node != m_end() && !comparator(last->element, node->element); node = node->next) {
				prev = node;
			}
			if (node == m_end()) {
				last_inserted = m_splice_after(prev, list);
			}
			for (; last != list.m_end() && !comparator(last->element, node->element); last = last->next) {
				prev_last = last;
			}
			m_splice_after_closed(prev, list, list.m_head(), prev_last);
			last_inserted = prev_last;
		}
		return last_inserted;
	}

	template< typename TComparator >
	void m_sort(TComparator & comparator) {
		if (m_empty()) {
			return;
		}
		Basic carry(m_allocator());
		RawArray<Basic, 64> counter(m_allocator());
		auto fill = 0;
		NodePointer last_inserted;
		for (; !m_empty(); ) {
			last_inserted = m_begin();
			carry.m_splice_after(carry.m_before_begin(), *this, this->m_before_begin());
			auto i = 0;
			for(; i < fill && !counter[i].m_empty(); ) {
				carry.m_swap(counter[i]);
				last_inserted = carry.m_merge(counter[i++], comparator);
			}
			BR_ASSERT(counter[i].m_empty());

			auto const last_element = Algorithms::find_prev(last_inserted, carry.m_end());
			counter[i].m_splice_after_closed(counter[i].m_before_begin(), carry, carry.m_before_begin(), last_element);
			if (i == fill) {
				++fill;
			}
		}
		for (auto i = 1; i < fill; ++i) {
			last_inserted = counter[i].m_merge(counter[i-1], comparator);
		}
		--fill;
		auto last_element = Algorithms::find_prev(last_inserted, counter[fill].m_end());
		m_splice_after_closed(m_before_begin(), counter[fill], counter[fill].m_before_begin(), last_element);
	}

	void m_swap(Basic & list) noexcept(typename NodeAllocatorTraits::IsAlwaysEqual{}) {
		using BR::swap;
		swap_allocator(m_allocator(), list.m_allocator());
		Algorithms::swap(m_head(), list.m_head());
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
		m_splice_after(m_end(), list);
	}

	void m_move_assign(Basic & list, BooleanFalse) {
		if (m_allocator() != list.m_allocator()) {
			m_assign(list.m_begin(), list.m_end());
		} else {
			m_move_assign(list, BooleanTrue{});
		}
	}

protected:
	Tuple< NodeAllocator, BasicNode > m_impl;

}; // class Basic<TElement, TAllocator>

} // namespace ForwardList
} // namespace Container
} // namespace Detail
} // namespace BR