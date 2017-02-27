#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/allocator_helpers.hpp>
#include <libbr/container/detail/dlist_algorithms.hpp>
#include <libbr/container/detail/dlist_iterator.hpp>
#include <libbr/container/detail/dlist_node.hpp>
#include <libbr/container/detail/node_destructor.hpp>
#include <libbr/container/detail/raw_array.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/iterator/prev.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace DList {

template< typename TElement, typename TAllocator >
class Basic {

public:
	using Element = TElement;

	using Allocator = TAllocator;

protected:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using VoidPointer = typename AllocatorTraits::VoidPointer;

	using Node = DList::Node< Element, VoidPointer >;

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

	using Algorithms = DList::Algorithms<NodePointer>;

public:
	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using Size = typename AllocatorTraits::Size;

	using Difference = typename AllocatorTraits::Difference;

	using Iterator = DList::Iterator<NodePointer>;

	using ConstIterator = DList::ConstIterator<NodePointer>;

public:
	Basic() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) : m_impl(0) {
	}

	Basic(Allocator const & allocator) : m_impl(0, NodeAllocator(allocator)) {
	}

	Basic(Basic && list) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : m_impl(move(list.m_impl)) {
		if (m_size() == 0) {
			Algorithms::init_header(m_header());
		} else {
			m_header()->prev->next = m_header()->next->prev = m_header();
			Algorithms::init_header(list.m_header());
			list.m_size() = 0;
		}
	}

	~Basic() {
		m_clear();
	}

protected:
	auto m_size() noexcept -> Size & {
		return m_impl.template get<Size>();
	}

	auto m_size() const noexcept -> Size const & {
		return m_impl.template get<Size>();
	}

	auto m_allocator() noexcept -> NodeAllocator & {
		return m_impl.template get<NodeAllocator>();
	}

	auto m_allocator() const noexcept -> NodeAllocator const & {
		return m_impl.template get<NodeAllocator>();
	}

	auto m_header() const noexcept -> NodePointer {
		return static_cast<NodePointer>(BasicNodePointerTraits::make_pointer(const_cast<BasicNode &>(m_impl.template get<BasicNode>())));
	}

	auto m_begin() const noexcept -> NodePointer {
		return m_header()->next;
	}

	auto m_end() const noexcept -> NodePointer {
		return m_header();
	}

	auto m_empty() const noexcept -> bool {
		return m_size() == 0;
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
		NodeAllocatorTraits::construct(allocator, address_of(holder->element), forward<TArgs>(args)...);
		holder.get_deleter().constructed = true;
		return holder;
	}

	void m_assign(Element const & element, Size count) {
		auto node = m_begin();
		auto const end = m_end();
		for (; count > 0 && node != end; node = node->next, (void)--count) {
			node->element = element;
		}
		if (node == end) {
			m_insert(end, element, count);
		} else {
			m_erase(node, end);
		}
	}

	template< typename TInputIterator >
	void m_assign(TInputIterator first, TInputIterator last) {
		auto node = m_begin();
		auto const end = m_end();
		for (; first != last && node != end; node = node->next, (void)++first) {
			node->element = *first;
		}
		if (node == end) {
			m_insert(end, first, last);
		} else {
			m_erase(node, end);
		}
	}

	auto m_try_shrink(Size new_size) -> bool {
		if (new_size < this->m_size()) {
			auto begin = (new_size <= m_size() / 2) ? next(m_begin(), new_size) : prev(m_end(), m_size() - new_size);
			m_erase(begin, m_end());
			return true;
		} else {
			return false;
		}
	}

	void m_resize(Size new_size) {
		if (m_try_shrink(new_size)) {
			auto position = m_end();
			auto n = new_size - m_size();
			auto holder = m_construct_node();
			auto cache = holder.release();
			auto result = cache;
			BR_TRY {
				for (Size i = 1; i < n; ++i, cache = cache->next) {
					holder = m_construct_node();
					cache->next = holder.get();
					holder->prev = cache;
					holder.release();
				}
			} BR_CATCH(...) {
				for (; cache != nullptr;) {
					auto prev = cache->prev;
					destroy_node(m_allocator(), cache);
					cache = prev;
				}
				BR_RETHROW;
			}
			Algorithms::link_before(position, result, cache);
			m_size() += n;
		}
	}

	void m_resize(Size new_size, Element const & element) {
		if (m_try_shrink(new_size)) {
			m_insert(m_end(), element, new_size - m_size());
		}
	}

	auto m_insert(NodePointer position, NodeHolder holder) -> NodePointer {
		auto node = m_insert(position, holder.get());
		holder.release();
		return node;
	}

	auto m_insert(NodePointer position, NodePointer const & node) -> NodePointer {
		Algorithms::link_before(position, node);
		++m_size();
		return node;
	}

	auto m_insert(NodePointer const & position, Element const & element, Size n) -> NodePointer {
		auto result = position;
		if (n > 0) {
			auto holder = m_construct_node(element);
			auto cache = holder.release();
			result = cache;
			BR_TRY {
				for (Size i = 1; i < n; ++i, cache = cache->next) {
					holder = m_construct_node(element);
					cache->next = holder.get();
					holder->prev = cache;
					holder.release();
				}
			} BR_CATCH(...) {
				for (; cache != nullptr;) {
					auto prev = cache->prev;
					destroy_node(m_allocator(), cache);
					cache = prev;
				}
				BR_RETHROW;
			}
			Algorithms::link_before(position, result, cache);
			m_size() += n;
		}
		return result;
	}

	template< typename TInputIterator >
	auto m_insert(NodePointer const & position, TInputIterator first, TInputIterator last) -> NodePointer {
		auto result = position;
		if (first != last) {
			Size n = 0;
			auto holder = m_construct_node(*first);
			auto cache = holder.release();
			result = cache;
			BR_TRY {
				for (++first, (void)++n; first != last; ++first, (void)++n, cache = cache->next) {
					holder = m_construct_node(*first);
					cache->next = holder.get();
					holder->prev = cache;
					holder.release();
				}
			} BR_CATCH(...) {
				for (; cache != nullptr;) {
					auto prev = cache->prev;
					destroy_node(m_allocator(), cache);
					cache = prev;
				}
				BR_RETHROW;
			}
			Algorithms::link_before(position, result, cache);
			m_size() += n;
		}
		return result;
	}

	auto m_erase(NodePointer pointer) -> NodePointer {
		auto ret = pointer->next;
		Algorithms::unlink(pointer);
		destroy_node(m_allocator(), pointer);
		--m_size();
		return ret;
	}

	auto m_erase(NodePointer first, NodePointer last) -> NodePointer {
		Algorithms::unlink(first, last);
		for (; first != last;) {
			auto to_erase = first;
			first = first->next;
			destroy_node(m_allocator(), to_erase);
			--m_size();
		}
		return last;
	}

	void m_clear() noexcept {
		if (!m_empty()) {
			auto f = m_begin(), l = m_end();
			Algorithms::unlink(f, l->prev);
			m_size() = 0;
			for (; f != l;) {
				auto node = f;
				f = f->next;
				destroy_node(m_allocator(), node);
			}
		}
	}

	template< typename TUnaryPredicate >
	void m_remove(TUnaryPredicate & predicate) {
		typename Algorithms::StablePartitionInfo info;
		Algorithms::stable_partition(m_begin(), m_header(), predicate, info);
		m_erase(m_begin(), info.begin_right);
	}

	void m_splice(NodePointer const & position, Basic & list) {
		if (!list.m_empty()) {
			Algorithms::transfer(position, list.m_begin(), list.m_end());
			m_size() += list.m_size();
			list.m_size() = 0;
		}
	}

	void m_splice(NodePointer const & position, Basic & list, NodePointer const & node) {
		if (position != node && position != node->next) {
			Algorithms::transfer(position, node);
			--list.m_size();
			++m_size();
		}
	}

	void m_splice(NodePointer const & position, Basic & list, NodePointer const & first, NodePointer const & last) {
		if (first != last) {
			Size count = 0;
			for (auto node = first; node != last; node = node->next) {
				++count;
			}
			m_splice(position, list, first, last, count);
		}
	}

	void m_splice(NodePointer const & position, Basic & list, NodePointer const & first, NodePointer const & last, Size count) {
		if (count != 0) {
			Algorithms::transfer(position, first, last);
			list.m_size() -= count;
			m_size() += count;
		}
	}

	template< typename TBinaryPredicate >
	void m_unique(TBinaryPredicate & predicate) {
		auto const end = m_end();
		for (auto first = m_begin(); first != end;) {
			auto last = first->next;
			for (; last != end && predicate(first->element, last->element); last = last->next) {}
			first = first->next;
			if (first != last) {
				first = m_erase(first, last);
			}
		}
	}

	template< typename TComparator >
	void m_merge(Basic & list, TComparator & comparator) {
		auto b = m_begin(), e = m_end();
		auto e1 = list.m_end();
		for (; !list.m_empty();) {
			auto i1 = list.m_begin();
			for (; b != e && !comparator(i1->element, b->element); b = b->next) {}
			if (b == e) {
				m_splice(e, list);
				break;
			} else {
				Size n = 0;
				do {
					i1 = i1->next;
					++n;
				} while (i1 != e1 && comparator(i1->element, b->element));
				m_splice(b, list, list.m_begin(), i1, n);
			}
		}
	}

	template< typename TComparator >
	void m_sort(TComparator & comparator) {
		if (m_size() > 1) {
			Basic carry(m_allocator());
			RawArray<Basic, 64> counter(m_allocator());
			auto fill = 0;
			for (; !m_empty();) {
				carry.m_splice(carry.m_begin(), *this, m_begin());
				auto i = 0;
				for (; i < fill && !counter[i].m_empty();) {
					counter[i].m_merge(carry, comparator);
					carry.m_swap(counter[i++]);
				}
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
	}

	void m_reverse() {
		Algorithms::reverse(m_header());
	}

	void m_swap(Basic & list) noexcept(typename NodeAllocatorTraits::IsAlwaysEqual{}) {
		using BR::swap;
		swap_allocator(m_allocator(), list.m_allocator());
		Algorithms::swap(m_header(), list.m_header());
		swap(m_size(), list.m_size());
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
		m_splice(m_end(), list);
	}

	void m_move_assign(Basic & list, BooleanFalse) {
		if (m_allocator() != list.m_allocator()) {
			m_assign(list.m_begin(), list.m_end());
		} else {
			m_move_assign(list, BooleanTrue{});
		}
	}

protected:
	Tuple< Size, NodeAllocator, BasicNode > m_impl;

}; // class DList<TElement, TAllocator>

} // namespace DList
} // namespace Container
} // namespace Detail
} // namespace BR