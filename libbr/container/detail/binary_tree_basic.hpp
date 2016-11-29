#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/binary_tree_algorithms.hpp>
#include <libbr/container/detail/binary_tree_node.hpp>
#include <libbr/container/detail/binary_tree_iterator.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace BinaryTree {

template< typename TAllocator >
struct NodeDestructor : public UnaryFunctor<typename AllocatorTraits<TAllocator>::Pointer> {
	using Allocator = TAllocator;

private:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
	using Pointer = typename AllocatorTraits::Pointer;

	explicit NodeDestructor(Allocator & allocator, bool constructed = false) noexcept : m_allocator(allocator), constructed(constructed) {
	}

	void operator()(Pointer pointer) noexcept {
		if (constructed) {
			AllocatorTraits::destroy(m_allocator, address_of(pointer->element));
		}
		if (pointer != nullptr) {
			AllocatorTraits::deallocate(m_allocator, pointer, 1);
		}
	}

public:
	bool constructed;

private:
	Allocator & m_allocator;
};

struct Traits {
	template< typename TElement, typename TVoidPointer >
	using Node = BinaryTree::Node<TElement, TVoidPointer>;

	template< typename TNodePointer >
	using Algorithms = BinaryTree::Algorithms<TNodePointer>;
};

template< typename TElement, typename TComparator, typename TAllocator, typename TTraits = Traits >
class Basic {

public:
	using Element = TElement;

	using Comparator = TComparator;

	using Allocator = TAllocator;

protected:
	using Traits = TTraits;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using VoidPointer = typename AllocatorTraits::VoidPointer;

	using Node = typename Traits::template Node<Element, VoidPointer>;

	using NodeAllocator = typename AllocatorTraits::template Rebind<Node>;

	using NodeAllocatorTraits = BR::AllocatorTraits<NodeAllocator>;

	using NodePointer = typename NodeAllocatorTraits::Pointer;

	using NodePointerTraits = PointerTraits<NodePointer>;

	using BasicNode = typename Node::Base;

	using BasicNodeAllocator = typename AllocatorTraits::template Rebind<BasicNode>;

	using BasicNodeAllocatorTraits = BR::AllocatorTraits<BasicNodeAllocator>;

	using BasicNodePointer = typename BasicNodeAllocatorTraits::Pointer;

	using BasicNodePointerTraits = PointerTraits<BasicNodePointer>;

	using NodeDestructor = BinaryTree::NodeDestructor<NodeAllocator>;

	using NodeHolder = UniquePointer< Node, NodeDestructor >;

	using Algorithms = typename Traits::template Algorithms<NodePointer>;

public:
	using Reference = Element &;

	using ConstReference = Element const &;

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using Size = typename AllocatorTraits::Size;

	using Difference = typename AllocatorTraits::Difference;

	using Iterator = BinaryTree::Iterator<NodePointer>;

	using ConstIterator = BinaryTree::ConstIterator<NodePointer>;

protected:
	Basic() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) : m_impl(0) {
		Algorithms::init_header(m_header());
	}

	explicit Basic(Allocator const & allocator) : m_impl(0, NodeAllocator(allocator)) {
		Algorithms::init_header(m_header());
	}

	Basic(Comparator const & comparator, Allocator const & allocator = Allocator{}) : m_impl(0, NodeAllocator(allocator), comparator) {
		Algorithms::init_header(m_header());
	}

	Basic(Basic && tree) noexcept(BooleanAnd< HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<NodeAllocator> >{}) : m_impl(move(tree.m_impl)) {
		if (m_size() == 0) {
			Algorithms::init_header(m_header());
		} else {
			m_header()->parent->parent = m_header();
			Algorithms::init_header(tree.m_header());
			tree.m_size() = 0;
		}
	}

	Basic(Basic && tree, Allocator const & allocator): m_impl(0, NodeAllocator(allocator), tree.m_comparator()) {
		if (allocator != tree.m_allocator()) {
			if (m_size() == 0) {
				Algorithms::init_header(m_header());
			} else {
				m_header()->parent->parent = m_header();
				Algorithms::init_header(tree.m_header());
				tree.m_size() = 0;
			}
		} else {
			auto e = m_end();
			for (; tree.m_size() != 0;) {
				m_insert_equal(e, m_construct_node(move(tree.m_remove(tree.m_begin())->element)));
			}
		}
	}

	~Basic() {
		m_destroy_subtree(m_header()->parent);
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

	auto m_comparator() noexcept -> Comparator & {
		return m_impl.template get<Comparator>();
	}

	auto m_comparator() const noexcept -> Comparator const & {
		return m_impl.template get<Comparator>();
	}

	auto m_header() const noexcept -> NodePointer {
		return static_cast<NodePointer>(BasicNodePointerTraits::make_pointer(const_cast<BasicNode &>(m_impl.template get<BasicNode>())));
	}

	auto m_root() const noexcept -> NodePointer {
		NodePointer p = m_header()->parent;
		return p != nullptr ? p : m_header();
	}

	auto m_left_most() const noexcept -> NodePointer {
		return static_cast<NodePointer>(m_header()->left);
	}

	auto m_right_most() const noexcept -> NodePointer {
		return static_cast<NodePointer>(m_header()->right);
	}

	auto m_begin() const noexcept -> NodePointer {
		return m_left_most();
	}

	auto m_end() const noexcept -> NodePointer {
		return static_cast<NodePointer>(m_header());
	}

	void m_copy_assign_allocator(Basic const & tree) {
		m_copy_assign_allocator(tree, typename NodeAllocatorTraits::IsPropagateOnContainerCopyAssignment{});
	}

	void m_move_assign(Basic & tree) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<NodeAllocator>, HasNothrowMoveAssignment<Comparator> >{}) {
		m_move_assign(tree, typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment{});
	}

	template< typename TInputIterator >
	void m_assign_unique(TInputIterator first, TInputIterator last) {
		if (m_size() != 0) {
			if (m_size() != 0) {
				NodePointer cache = m_detach();
#if !defined(BR_NO_EXCEPTIONS)
				try {
#endif
					for (; cache != nullptr && first != last; ) {
						cache->element = *first;
						NodePointer next = m_detach(cache);
						m_insert_unique(cache);
						cache = next;
					}
#if !defined(BR_NO_EXCEPTIONS)
				} catch (...) {
					for (; cache->parent != nullptr; cache = cache->parent) {}
					m_destroy_subtree(cache);
					throw;
				}
#endif
				if (cache != nullptr) {
					for (; cache->parent != nullptr; cache = cache->parent) {}
					m_destroy_subtree(cache);
				}
			}
			for (; first != last; ++first) {
				m_insert_unique(m_construct_node(*first));
			}
		}
	}

	template< typename TInputIterator >
	void m_assign_equal(TInputIterator first, TInputIterator last) {
		if (m_size() != 0) {
			NodePointer cache = m_detach();
#if !defined(BR_NO_EXCEPTIONS)
			try {
#endif
				for (; cache != nullptr && first != last; ) {
					cache->element = *first;
					NodePointer next = m_detach(cache);
					m_insert_equal(cache);
					cache = next;
				}
#if !defined(BR_NO_EXCEPTIONS)
			} catch (...) {
				for (; cache->parent != nullptr; cache = cache->parent) {}
				m_destroy_subtree(cache);
				throw;
			}
#endif
			if (cache != nullptr) {
				for (; cache->parent != nullptr; cache = cache->parent) {}
				m_destroy_subtree(cache);
			}
		}
		for (; first != last; ++first) {
			m_insert_equal(m_construct_node(*first));
		}
	}

	template< typename... TArgs >
	auto m_construct_node(TArgs &&... args) -> NodeHolder {
		auto & allocator = m_allocator();
		NodeHolder holder(NodeAllocatorTraits::allocate(allocator, 1), NodeDestructor(allocator, 1));
		NodeAllocatorTraits::construct(allocator, address_of(holder->element), forward<TArgs>(args)...);
		holder.get_deleter().constructed = true;
		return holder;
	}

	template< typename TKey >
	auto m_find(TKey const & key) const -> NodePointer {
		return Algorithms::find(m_header(), key, m_comparator());
	}

	template< typename TKey >
	auto m_lower_bound(TKey const & key) const -> NodePointer {
		return Algorithms::lower_bound(m_header(), key, m_comparator());
	}

	template< typename TKey >
	auto m_upper_bound(TKey const & key) const -> NodePointer {
		return Algorithms::upper_bound(m_header(), key, m_comparator());
	}

	template< typename TKey >
	auto m_equal_range(TKey const & key) const -> Pair< NodePointer, NodePointer > {
		return Algorithms::equal_range(m_header(), key, m_comparator());
	}

	template< typename TKey >
	auto m_bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed, bool right_closed) const -> Pair< NodePointer, NodePointer > {
		return Algorithms::bounded_range(m_header(), lower_key, upper_key, m_comparator(), left_closed, right_closed);
	}

	template< typename TKey >
	auto m_count(TKey const & key) const -> Size {
		auto range = m_equal_range(key);
		Size n = 0;
		for (; range.first != range.second; range.first = Algorithms::next_node(range.first)) {
			++n;
		}
		return n;
	}

	auto m_insert_unique(NodeHolder holder) -> Pair< NodePointer, bool > {
		auto result = m_insert_unique(holder.get());
		holder.release();
		return result;
	}

	auto m_insert_unique(NodePointer node) -> Pair< NodePointer, bool > {
		typename Algorithms::InsertCommitData data;
		auto result = Algorithms::insert_unique_check(m_header(), node, m_comparator(), data);
		if (result.second) {
			Algorithms::insert_unique_commit(m_header(), node, data);
			++m_size();
			return make_pair(node, true);
		} else {
			return make_pair(result.first, false);
		}
	}

	auto m_insert_unique(NodePointer hint, NodeHolder holder) -> NodePointer {
		auto result = m_insert_unique(hint, holder.get());
		holder.release();
		return result;
	}

	auto m_insert_unique(NodePointer hint, NodePointer node) -> NodePointer {
		typename Algorithms::InsertCommitData data;
		auto result = Algorithms::insert_unique_check(m_header(), hint, node, m_comparator(), data);
		if (result.second) {
			Algorithms::insert_unique_commit(m_header(), node, data);
			++m_size();
			return node;
		} else {
			return result.first;
		}
	}

	auto m_insert_equal(NodeHolder holder) -> NodePointer {
		auto result = m_insert_equal(holder.get());
		holder.release();
		return result;
	}

	auto m_insert_equal(NodePointer node) -> NodePointer {
		auto result = Algorithms::insert_equal_upper_bound(m_header(), node, m_comparator());
		++m_size();
		return result;
	}

	auto m_insert_equal(NodePointer hint, NodeHolder holder) -> NodePointer {
		auto result = m_insert_equal(hint, holder.get());
		holder.release();
		return result;
	}

	auto m_insert_equal(NodePointer hint, NodePointer node) -> NodePointer {
		auto result = Algorithms::insert_equal(m_header(), hint, node, m_comparator());
		++m_size();
		return result;
	}

	auto m_erase(NodePointer pointer) -> NodePointer {
		auto ret = Algorithms::next_node(pointer);
		Algorithms::erase(m_header(), pointer);
		auto & allocator = m_allocator();
		NodeAllocatorTraits::destroy(allocator, address_of(pointer->element));
		NodeAllocatorTraits::deallocate(allocator, pointer, 1);
		--m_size();
		return ret;
	}

	void m_clear() noexcept {
		m_destroy_subtree(m_root());
		m_size() = 0;
		Algorithms::init_header(m_header());
	}

	void m_swap(Basic & tree) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsAlwaysEqual, IsNothrowSwappable<Comparator> >{}) {
		using BR::swap;
		m_swap_allocator(m_allocator(), tree.m_allocator());
		Algorithms::swap(m_header(), tree.m_header());
		swap(m_size(), tree.m_size());
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y) noexcept(typename NodeAllocatorTraits::IsAlwaysEqual{}) {
		m_swap_allocator(x, y, typename NodeAllocatorTraits::IsPropagateOnContainerSwap{});
	}

	auto m_detach() -> NodePointer {
		NodePointer cache = m_left_most();
		Algorithms::init_header(m_header());
		m_size() = 0;
		return Algorithms::get_leaf(cache);
	}

	auto m_detach(NodePointer cache) -> NodePointer {
		if (cache->parent == nullptr) {
			return nullptr;
		}
		if (cache->parent->left == cache) {
			cache->parent->left = nullptr;
			cache = cache->parent;
			if (cache->right == nullptr) {
				return cache;
			}
			return Algorithms::get_leaf(cache->right);
		} else {
			cache->parent->right == nullptr;
			cache = cache->parent;
			if (cache->left == nullptr) {
				return cache;
			}
			return Algorithms::get_leaf(cache->left);
		}
	}

	auto m_remove(NodePointer pointer) noexcept -> NodeHolder {
		Algorithms::erase(m_header(), pointer);
		--m_size();
		return NodeHolder(pointer, NodeDestructor(m_allocator(), 1));
	}

private:
	void m_copy_assign_allocator(Basic const & tree, BooleanTrue) {
		if (m_allocator() != tree.m_allocator()) {
			m_clear();
		}
		m_allocator() = tree.m_allocator();
	}

	void m_copy_assign_allocator(Basic const & tree, BooleanFalse) {
	}

	void m_move_assign(Basic & tree, BooleanTrue) noexcept(BooleanAnd< HasNothrowMoveAssignment<NodeAllocator>, HasNothrowMoveAssignment<Comparator> >{}) {
		m_destroy_subtree(m_root());
		m_header()->left = tree.m_header()->left;
		m_header()->right = tree.m_header()->right;
		m_header()->parent = tree.m_header()->parent;
		m_copy_assign_allocator(tree);
		m_comparator() = move(tree.m_comparator());
		m_size() = tree.m_size();
		if (m_size() == 0) {
			m_header()->left = m_header()->right = m_header();
		} else {
			m_header()->parent->parent = m_header();
			Algorithms::init_header(tree.m_header());
			tree.m_size() = 0;
		}
	}

	void m_move_assign(Basic & tree, BooleanFalse) {
		if (m_allocator() == tree.m_allocator()) {
			m_move_assign(tree, BooleanTrue{});
		} else {
			m_comparator() = move(tree.m_comparator());
			auto end = m_end();
			if (m_size() != 0) {
				NodePointer cache = m_detach();
#if !defined(BR_NO_EXCEPTIONS)
				try {
#endif
					for (; cache != nullptr && tree.m_size() != 0; ) {
						cache->element = move(tree.m_remove(tree.m_begin())->element);
						NodePointer next = m_detach(cache);
						m_insert_equal(cache);
						cache = next;
					}
#if !defined(BR_NO_EXCEPTIONS)
				} catch (...) {
					for (; cache->parent != nullptr; cache = cache->parent) {}
					m_destroy_subtree(cache);
					throw;
				}
#endif
				if (cache != nullptr) {
					for (; cache->parent != nullptr; cache = cache->parent) {}
					m_destroy_subtree(cache);
				}
			}
			for (; tree.m_size() != 0; ) {
				m_insert_equal(end, m_construct_node(move(tree.m_remove(tree.m_begin())->element)));
			}
		}
	}

	void m_destroy_node(NodePointer node) {
		auto & allocator = m_allocator();
		NodeAllocatorTraits::destroy(allocator, address_of(node->element));
		NodeAllocatorTraits::deallocate(allocator, node, 1);
	}

	void m_destroy_subtree(NodePointer node) {
		for (; node != nullptr;) {
			auto save = node->left;
			if (save != nullptr) {
				node->left = save->right;
				save->right = node;
			} else {
				save = node->right;
				m_destroy_node(node);
			}
			node = save;
		}
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanFalse) noexcept {
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanTrue) noexcept(IsNothrowSwappable<NodeAllocator>{}) {
		using BR::swap;
		swap(x, y);
	}

private:
	Tuple< Size, NodeAllocator, Comparator, BasicNode > m_impl;
}; // class Basic< TElement, TComparator, TAllocator >

} // namespace BinaryTree
} // namespace Container
} // namespace Detail
} // namespace BR