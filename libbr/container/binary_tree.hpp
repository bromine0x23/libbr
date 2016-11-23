/**
 * @file
 * @brief RBTree
 * @author Bromine0x23
 * @since 2016/5/11
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/detail/binary_tree_algorithm.hpp>
#include <libbr/container/detail/binary_tree_node.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/enumerate/enumerable.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_input_iterator.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Container {

/**
 * @tparam TElement
 * @tparam TComparator
 * @tparam TAllocator
 */
template< typename TElement, typename TComparator = Less<TElement>, typename TAllocator = Allocator<TElement> >
class BinaryTree;

} // inline namespace Container

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

template< typename TNodePointer >
class Iterator;

template< typename TNodeConstPointer >
class ConstIterator;

template< typename TNodePointer >
class Iterator : public IteratorWithCategory< ReadableTag, WritableTag, BidirectionalTraversalTag > {
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = PointerTraits<NodePointer>;

	using Node = typename NodePointerTraits::Element;

	using BasicNode = typename Node::Base;

	using BasicNodePointer = typename NodePointerTraits::template Rebind<BasicNode>;

	template< typename, typename, typename >
	friend class BR::BinaryTree;

	template< typename >
	friend class ConstIterator;

public:
	struct Category : public IteratorTag, public ReadableTag, public WritableTag, public BidirectionalTraversalTag {};

	using Element = typename Node::Element;

	using Pointer = typename NodePointerTraits::template Rebind<Element>;

	using Reference = Element &;

	using Difference = typename NodePointerTraits::Difference;

	Iterator() noexcept : m_pointer(nullptr) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return NodePointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> Iterator & {
		m_pointer = Algorithms<NodePointer>::next_node(m_pointer);
		return *this;
	}

	auto operator++(int) -> Iterator {
		Iterator temp(*this);
		operator++();
		return temp;
	}

	auto operator--() -> Iterator & {
		m_pointer = Algorithms<NodePointer>::prev_node(m_pointer);
		return *this;
	}

	auto operator--(int) -> Iterator {
		Iterator temp(*this);
		operator--();
		return *temp;
	}

	auto operator==(Iterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator const & y) const -> bool {
		return !operator==(y);
	}

private:
	explicit Iterator(NodePointer pointer) noexcept : m_pointer(pointer) {
	}

private:
	NodePointer m_pointer;
}; // class Iterator<TNodePointer>

template< typename TNodePointer >
class ConstIterator : public IteratorWithCategory< ReadableTag, BidirectionalTraversalTag > {
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = PointerTraits<TNodePointer>;

	using Node = typename NodePointerTraits::Element;

	using BasicNode = typename Node::Base;

	using BasicNodePointer = typename NodePointerTraits::template Rebind<BasicNode>;

	template< typename, typename, typename >
	friend class BR::BinaryTree;

public:
	struct Category : public IteratorTag, public ReadableTag, public BidirectionalTraversalTag {};

	using Element = typename Node::Element;

	using Pointer = typename NodePointerTraits::template Rebind<Element const>;

	using Reference = Element const &;

	using Difference = typename NodePointerTraits::Difference;

	ConstIterator() noexcept : m_pointer(nullptr) {
	}

	ConstIterator(Iterator<NodePointer> iterator) noexcept : m_pointer(iterator.m_pointer) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return NodePointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> ConstIterator & {
		m_pointer = Algorithms<NodePointer>::next_node(m_pointer);
		return *this;
	}

	auto operator++(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator++();
		return temp;
	}

	auto operator--() -> ConstIterator & {
		m_pointer = Algorithms<NodePointer>::prev_node(m_pointer);
		return *this;
	}

	auto operator--(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator--();
		return *temp;
	}

	auto operator==(ConstIterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(ConstIterator const & y) const -> bool {
		return !operator==(y);
	}

	auto operator==(Iterator<NodePointer> const  & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator<NodePointer> const  & y) const -> bool {
		return !operator==(y);
	}

private:
	explicit ConstIterator(NodePointer pointer) noexcept : m_pointer(pointer) {
	}

private:
	NodePointer m_pointer;
}; // class ConstIterator<TNodePointer>

template< typename TNodePointer >
inline auto operator==(Iterator<TNodePointer> const & x, ConstIterator<TNodePointer> const & y) -> bool {
	return y == x;
}

template< typename TNodePointer >
auto operator!=(Iterator<TNodePointer> const & x, ConstIterator<TNodePointer> const & y) -> bool {
	return y != x;
}

template< typename TElement, typename TComparator, typename TAllocator >
class Base {

public:
	using Element = TElement;

	using Comparator = TComparator;

	using Allocator = TAllocator;

protected:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using VoidPointer = typename AllocatorTraits::VoidPointer;

	using Node = BinaryTree::Node<Element, VoidPointer>;

	using NodeAllocator = typename AllocatorTraits::template Rebind<Node>;

	using NodeAllocatorTraits = BR::AllocatorTraits<NodeAllocator>;

	using NodePointer = typename NodeAllocatorTraits::Pointer;

	using NodePointerTraits = PointerTraits<NodePointer>;

	using BasicNode = typename Node::Base;

	using BasicNodeAllocator = typename AllocatorTraits::template Rebind<BasicNode>;

	using BasicNodeAllocatorTraits = BR::AllocatorTraits<BasicNodeAllocator>;

	using BasicNodePointer = typename BasicNodeAllocatorTraits::Pointer;

	using BasicNodePointerTraits = PointerTraits<BasicNodePointer>;

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
	using NodeDestructor = BinaryTree::NodeDestructor<NodeAllocator>;

	using NodeHolder = UniquePointer< Node, NodeDestructor >;

	using Algorithms = BinaryTree::Algorithms<NodePointer>;

protected:
	Base() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) : m_impl(0) {
		Algorithms::init_header(m_header());
	}

	explicit Base(Allocator const & allocator) : m_impl(0, NodeAllocator(allocator)) {
		Algorithms::init_header(m_header());
	}

	Base(Comparator const & comparator, Allocator const & allocator = Allocator{}) : m_impl(0, NodeAllocator(allocator), comparator) {
		Algorithms::init_header(m_header());
	}

	Base(Base && tree) noexcept(BooleanAnd< HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<NodeAllocator> >{}) : m_impl(move(tree.m_impl)) {
		if (m_size() == 0) {
			Algorithms::init_header(m_header());
		} else {
			m_header()->parent->parent = m_header();
			Algorithms::init_header(tree.m_header());
			tree.m_size() = 0;
		}
	}

	Base(Base && tree, Allocator const & allocator): m_impl(0, NodeAllocator(allocator), tree.m_comparator()) {
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

	~Base() {
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
		return static_cast<NodePointer>(PointerTraits<BasicNodePointer>::make_pointer(const_cast<BasicNode &>(m_impl.template get<BasicNode>())));
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

	void m_copy_assign_allocator(Base const & tree) {
		m_copy_assign_allocator(tree, typename NodeAllocatorTraits::IsPropagateOnContainerCopyAssignment{});
	}

	void m_move_assign(Base & tree) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<NodeAllocator>, HasNothrowMoveAssignment<Comparator> >{}) {
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
			Algorithms::insert_commit(m_header(), node, data);
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
			Algorithms::insert_commit(m_header(), node, data);
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
		typename Algorithms::InsertCommitData data;
		Algorithms::insert_equal_upper_bound_check(m_header(), node, m_comparator(), data);
		Algorithms::insert_commit(m_header(), node, data);
		++m_size();
		return node;
	}

	auto m_insert_equal(NodePointer hint, NodeHolder holder) -> NodePointer {
		auto result = m_insert_equal(hint, holder.get());
		holder.release();
		return result;
	}

	auto m_insert_equal(NodePointer hint, NodePointer node) -> NodePointer {
		typename Algorithms::InsertCommitData data;
		Algorithms::insert_equal_check(m_header(), hint, node, m_comparator(), data);
		Algorithms::insert_commit(m_header(), node, data);
		++m_size();
		return node;
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

	void m_swap(Base & tree) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsAlwaysEqual, IsNothrowSwappable<Comparator> >{}) {
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
	void m_copy_assign_allocator(Base const & tree, BooleanTrue) {
		if (m_allocator() != tree.m_allocator()) {
			m_clear();
		}
		m_allocator() = tree.m_allocator();
	}

	void m_copy_assign_allocator(Base const & tree, BooleanFalse) {
	}

	void m_move_assign(Base & tree, BooleanTrue) noexcept(BooleanAnd< HasNothrowMoveAssignment<NodeAllocator>, HasNothrowMoveAssignment<Comparator> >{}) {
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

	void m_move_assign(Base & tree, BooleanFalse) {
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

	void m_destroy_subtree(NodePointer const & root) {
		for (auto node = root; node != nullptr; ) {
			auto const node_left = node->left;
			auto const node_right = node->right;
			auto & allocator = m_allocator();
			NodeAllocatorTraits::destroy(allocator, address_of(node->element));
			NodeAllocatorTraits::deallocate(allocator, node, 1);
			m_destroy_subtree(node_left);
			node = node_right;
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
}; // class Base< TElement, TComparator, TAllocator >

} // namespace BinaryTree
} // namespace Container
} // namespace Detail

inline namespace Container {

template< typename TElement, typename TComparator, typename TAllocator >
class BinaryTree : private Detail::Container::BinaryTree::Base< TElement, TComparator, TAllocator >,
	public Enumerable<
		BinaryTree< TElement, TComparator, TAllocator >,
		typename Detail::Container::BinaryTree::Base< TElement, TComparator, TAllocator >::Iterator,
		typename Detail::Container::BinaryTree::Base< TElement, TComparator, TAllocator >::ConstIterator
	>
{

public:
	/**
	 * @brief Element
	 */
	using Element = TElement;

	/**
	 * @brief Comparator
	 */
	using Comparator = TComparator;

	/**
	 * @brief Allocator
	 */
	using Allocator = TAllocator;

private:
	using Base = Detail::Container::BinaryTree::Base< TElement, TComparator, TAllocator >;

public:
	/**
	 * @brief Reference
	 */
	using Reference = typename Base::Reference;

	/**
	 * @brief ConstReference
	 */
	using ConstReference = typename Base::ConstReference;

	/**
	 * @brief Pointer
	 */
	using Pointer = typename Base::Pointer;

	/**
	 * @brief ConstPointer
	 */
	using ConstPointer = typename Base::ConstPointer;

	/**
	 * @brief Difference
	 */
	using Difference = typename Base::Difference;

	/**
	 * @brief Size
	 */
	using Size = typename Base::Size;

	/**
	 * @brief Iterator
	 */
	using Iterator = typename Base::Iterator;

	/**
	 * @brief ConstIterator
	 */
	using ConstIterator = typename Base::ConstIterator;

	/**
	 * @brief ReverseIterator
	 */
	using ReverseIterator = BR::ReverseIterator<Iterator>;

	/**
	 * @brief ConstReverseIterator
	 */
	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

private:
	using NodePointer = typename Base::NodePointer;

	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

	using NodeDestructor = typename Base::NodeDestructor;

	using NodeHolder = typename Base::NodeHolder;

public:
	/**
	 * @name 构造函数
	 */
	///@{
	/**
	 *
	 * @return
	 */
	BinaryTree() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) : Base() {
	}

	/**
	 *
	 * @param allocator
	 * @return
	 */
	explicit BinaryTree(Allocator const & allocator) : Base(allocator) {
	}

	/**
	 *
	 * @param comparator
	 * @param allocator
	 * @return
	 */
	explicit BinaryTree(Comparator const & comparator, Allocator const & allocator = Allocator{}) : Base(comparator, allocator) {
	}

	/**
	 *
	 * @param tree
	 * @return
	 */
	BinaryTree(BinaryTree const & tree) : Base(tree.m_comparator(), Allocator(NodeAllocatorTraits::select_on_container_copy_construction(tree.m_allocator()))) {
		insert_equal(tree.begin(), tree.end());
	}

	/**
	 *
	 * @param tree
	 * @param allocator
	 * @return
	 */
	BinaryTree(BinaryTree const & tree, Allocator const & allocator) : Base(tree.m_comparator(), allocator) {
		insert_equal(tree.begin(), tree.end());
	}

	/**
	 *
	 * @param tree
	 * @return
	 */
	BinaryTree(BinaryTree && tree) noexcept(BooleanAnd< HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<NodeAllocator> >{}) : Base(move(tree)) {
	}

	/**
	 *
	 * @param tree
	 * @param allocator
	 * @return
	 */
	BinaryTree(BinaryTree && tree, Allocator const & allocator) : Base(move(tree), allocator) {
	}

	/**
	 *
	 * @tparam TIterator
	 * @param f
	 * @param l
	 * @param allocator
	 * @return
	 */
	template< typename TIterator >
	BinaryTree(TIterator f, TIterator l, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : BinaryTree(f, l, Comparator{}, allocator) {
	}

	/**
	 *
	 * @tparam TIterator
	 * @param f
	 * @param l
	 * @param comparator
	 * @param allocator
	 * @return
	 */
	template< typename TIterator >
	BinaryTree(TIterator f, TIterator l, Comparator comparator, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : Base(comparator, allocator) {
		insert_equal(f, l);
	}


	BinaryTree(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(allocator) {
		insert_equal(list.begin(), list.end());
	}
	///@}

	~BinaryTree() = default;

	/**
	 * @name 成员
	 */
	///@{
	auto allocator() const noexcept -> Allocator {
		return Allocator(this->m_allocator());
	}

	auto comparator() const noexcept -> Comparator {
		return this->m_comparator();
	}
	///@}

	/**
	 * @name 迭代器
	 */
	///@{
	/**
	 * @brief begin
	 */
	auto begin() noexcept -> Iterator {
		return Iterator(this->m_begin());
	}

	/**
	 * @brief begin
	 */
	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(this->m_begin());
	}

	/**
	 * @brief const begin
	 */
	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	/**
	 * @brief end
	 */
	auto end() noexcept -> Iterator {
		return Iterator(this->m_end());
	}

	/**
	 * @brief end
	 */
	auto end() const noexcept -> ConstIterator {
		return ConstIterator(this->m_end());
	}

	/**
	 * @brief const end
	 */
	auto cend() const noexcept -> ConstIterator {
		return end();
	}

	/**
	 * @brief reverse begin
	 */
	auto rbegin() noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	/**
	 * @brief reverse begin
	 */
	auto rbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(end());
	}

	/**
	 * @brief const reverse begin
	 */
	auto crbegin() const noexcept -> ConstReverseIterator {
		return rbegin();
	}

	/**
	 * @brief reverse end
	 */
	auto rend() noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	/**
	 * @brief reverse end
	 */
	auto rend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(begin());
	}

	/**
	 * @brief const reverse end
	 */
	auto crend() const noexcept -> ConstReverseIterator {
		return rend();
	}
	///@}

	/**
	 * @name 容量
	 */
	///@{
	/**
	 * @brief empty
	 */
	auto empty() const noexcept -> bool {
		return size() == 0;
	}

	/**
	 * @brief size
	 */
	auto size() const noexcept -> Size {
		return this->m_size();
	}

	/**
	 * @brief max size
	 */
	auto max_size() const noexcept -> Size {
		return NodeAllocatorTraits::max_size(this->m_allocator());
	}
	///@}

	/**
	 * @name 比较
	 */
	///@{
	auto operator==(BinaryTree const & y) const -> bool {
		return size() == y.size() && equal(begin(), end(), y.begin(), y.end());
	}

	auto operator!=(BinaryTree const & y) const -> bool {
		return !operator==(y);
	}

	auto operator<(BinaryTree const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}

	auto operator>(BinaryTree const & y) const -> bool {
		return y.operator<(*this);
	}

	auto operator<=(BinaryTree const & y) const -> bool {
		return !y.operator<(*this);
	}

	auto operator>=(BinaryTree const & y) const -> bool {
		return !operator<(y);
	}
	///@}

	/**
	 * @name 赋值操作
	 */
	///@{

	//@{
	/**
	 * copy assignment
	 * @param tree
	 * @return
	 */
	auto operator=(BinaryTree const & tree) -> BinaryTree & {
		if (this != &tree) {
			this->m_comparator() = tree.m_comparator();
			this->m_copy_assign_allocator(tree);
			assign_equal(tree.begin(), tree.end());
		}
		return *this;
	}

	auto assign(BinaryTree const & tree) -> BinaryTree & {
		return *this = tree;
	}
	//@}

	//@{
	/**
	 * move assignment
	 * @param tree
	 * @return
	 */
	auto operator=(BinaryTree && tree) noexcept(
		BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator>, HasNothrowMoveAssignment<Comparator> >{}
	) -> BinaryTree & {
		this->m_move_assign(tree);
		return *this;
	}

	auto assign(BinaryTree && tree) -> BinaryTree & {
		return *this = move(tree);
	}
	//@}

	/**
	 * @tparam TIterator
	 * @param first
	 * @param last
	 * @return
	 */
	template< typename TIterator >
	auto assign_unique(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, BinaryTree & > {
		this->m_assign_unique(first, last);
		return *this;
	}

	/**
	 * @tparam TIterator
	 * @param first
	 * @param last
	 * @return
	 */
	template< typename TIterator >
	auto assign_equal(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, BinaryTree & > {
		this->m_assign_equal(first, last);
		return *this;
	}
	///@}

	/**
	 * @name 查找（首个）匹配的元素
	 */
	///@{
	auto find(Element const & element) -> Iterator {
		return Iterator(this->m_find(element));
	}

	template< typename TKey >
	auto find(TKey const & key) -> Iterator {
		return Iterator(this->m_find(key));
	}

	auto find(Element const & element) const -> ConstIterator {
		return ConstIterator(this->m_find(element));
	}

	template< typename TKey >
	auto find(TKey const & key) const -> ConstIterator {
		return ConstIterator(this->m_find(key));
	}
	///@}

	/**
	 * @name 查找下界
	 */
	///@{
	auto lower_bound(Element const & element) -> Iterator {
		return Iterator(this->m_lower_bound(element));
	}

	template< typename TKey >
	auto lower_bound(TKey const & key) -> Iterator {
		return Iterator(this->m_lower_bound(key));
	}

	auto lower_bound(Element const & element) const -> ConstIterator {
		return ConstIterator(this->m_lower_bound(element));
	}

	template< typename TKey >
	auto lower_bound(TKey const & key) const -> ConstIterator  {
		return ConstIterator(this->m_lower_bound(key));
	}
	///@}

	/**
	 * @name 查找上界
	 */
	///@{
	auto upper_bound(Element const & element) -> Iterator {
		return Iterator(this->m_upper_bound(element));
	}

	template< typename TKey >
	auto upper_bound(TKey const & key) -> Iterator {
		return Iterator(this->m_upper_bound(key));
	}

	auto upper_bound(Element const & element) const -> ConstIterator {
		return ConstIterator(this->m_upper_bound(element));
	}

	template< typename TKey >
	auto upper_bound(TKey const & key) const -> ConstIterator {
		return ConstIterator(this->m_upper_bound(key));
	}

	/**
	 * @name 查找边界
	 * @return < lower_bound(e), upper_bound(e) >
	 */
	///@{
	auto equal_range(Element const & element) -> Pair< Iterator, Iterator > {
		auto range = this->m_equal_range(element);
		return make_pair(Iterator(range.first), Iterator(range.second));
	}

	template< typename TKey >
	auto equal_range(TKey const & key) -> Pair< Iterator, Iterator > {
		auto range = this->m_equal_range(key);
		return make_pair(Iterator(range.first), Iterator(range.second));
	}

	auto equal_range(Element const & element) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_equal_range(element);
		return make_pair(ConstIterator(range.first), ConstIterator(range.second));
	}

	template< typename TKey >
	auto equal_range(TKey const & key) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_equal_range(key);
		return make_pair(ConstIterator(range.first), ConstIterator(range.second));
	}
	///@}

	/**
	 * @name 查找边界
	 * @return < lower_bound(e), upper_bound(e) >
	 */
	///@{
	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator > {
		auto range = this->m_bounded_range(lower_key, upper_key, left_closed, right_closed);
		return make_pair(Iterator(range.first), Iterator(range.second));
	}

	template< typename TKey >
	auto bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator > {
		auto range = this->m_bounded_range(lower_key, upper_key, left_closed, right_closed);
		return make_pair(Iterator(range.first), Iterator(range.second));
	}

	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_bounded_range(lower_key, upper_key, left_closed, right_closed);
		return make_pair(ConstIterator(range.first), ConstIterator(range.second));
	}

	template< typename TKey >
	auto bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_bounded_range(lower_key, upper_key, left_closed, right_closed);
		return make_pair(ConstIterator(range.first), ConstIterator(range.second));
	}
	///@}

	/**
	 * @name 计数
	 */
	///@{
	auto count(Element const & element) const -> Size {
		return this->m_count(element);
	}

	template< typename TKey >
	auto count(TKey const & key) const -> Size {
		return this->m_count(key);
	}
	///@}

	/**
	 * @name 添加（唯一）
	 */
	///@{
	template< typename ... TArgs >
	auto emplace_unique(TArgs && ... args) -> Pair< Iterator, bool > {
		auto result = this->m_insert_unique(this->m_construct_node(forward<TArgs>(args)...));
		return Pair< Iterator, bool >(Iterator(result.first), result.second);
	}

	auto insert_unique(Element const & element) -> Pair< Iterator, bool > {
		auto result = this->m_insert_unique(this->m_construct_node(element));
		return Pair< Iterator, bool >(Iterator(result.first), result.second);
	}

	auto insert_unique(Element && element) -> Pair< Iterator, bool > {
		auto result = this->m_insert_unique(this->m_construct_node(move(element)));
		return Pair< Iterator, bool >(Iterator(result.first), result.second);
	}

	template< typename TValue >
	auto insert_unique(TValue && value) -> Pair< Iterator, bool > {
		auto result = this->m_insert_unique(this->m_construct_node(forward<TValue>(value)));
		return Pair< Iterator, bool >(Iterator(result.first), result.second);
	}

	template< typename ... TArgs >
	auto emplace_unique_hint(ConstIterator hint, TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert_unique(hint.m_pointer, this->m_construct_node(forward<TArgs>(args)...)));
	}

	auto insert_unique(ConstIterator hint, Element const & element) -> Iterator {
		return Iterator(this->m_insert_unique(hint.m_pointer, this->m_construct_node(element)));
	}

	auto insert_unique(ConstIterator hint, Element && element) -> Iterator {
		return Iterator(this->m_insert_unique(hint.m_pointer, this->m_construct_node(move(element))));
	}

	template< typename TValue >
	auto insert_unique(ConstIterator hint, TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Iterator > {
		return Iterator(this->m_insert_unique(hint.m_pointer, this->m_construct_node(forward<TValue>(value))));
	}

	template< typename TIterator >
	auto insert_unique(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, BinaryTree & > {
		if (this->empty()) {
			auto  end = this->end();
			for (; first != last; ++first) {
				this->m_insert_unique(end, this->m_construct_node(*first));
			}
		} else {
			for (; first != last; ++first) {
				this->m_insert_unique(this->m_construct_node(*first));
			}
		}
		return *this;
	}
	///@}

	/**
	 * @name 添加（可重复）
	 */
	///@{
	template< typename ... TArgs >
	auto emplace_equal(TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert_equal(this->m_construct_node(forward<TArgs>(args)...)));
	}

	auto insert_equal(Element const & element) -> Iterator {
		return Iterator(this->m_insert_equal(this->m_construct_node(element)));
	}

	auto insert_equal(Element && element) -> Iterator {
		return Iterator(this->m_insert_equal(this->m_construct_node(move(element))));
	}

	template< typename TValue >
	auto insert_equal(TValue && value) -> Iterator {
		return Iterator(this->m_insert_equal(this->m_construct_node(forward<TValue>(value))));
	}

	template< typename ... TArgs >
	auto emplace_equal_hint(ConstIterator hint, TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert_equal(hint.m_pointer, this->m_construct_node(forward<TArgs>(args)...)));
	}

	auto insert_equal(ConstIterator hint, Element const & element) -> Iterator {
		return Iterator(this->m_insert_equal(hint.m_pointer, this->m_construct_node(element)));
	}

	auto insert_equal(ConstIterator hint, Element && element) -> Iterator {
		return Iterator(this->m_insert_equal(hint.m_pointer, this->m_construct_node(move(element))));
	}

	template< typename TValue >
	auto insert_equal(ConstIterator hint, TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Iterator > {
		return Iterator(this->m_insert_equal(hint.m_pointer, this->m_construct_node(forward<TValue>(value))));
	}

	template< typename TIterator >
	auto insert_equal(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, BinaryTree & > {
		auto end = this->m_end();
		for (; first != last; ++first) {
			this->m_insert_equal(end, this->m_construct_node(*first));
		}
		return *this;
	}
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	/**
	 * @brief clear
	 * @return
	 */
	auto clear() noexcept -> BinaryTree & {
		this->m_clear();
		return *this;
	}

	/**
	 * @brief erase
	 * @param position Iterator to the element to remove.
	 * @return Iterator following the removed element.
	 */
	auto erase(ConstIterator position) -> Iterator {
		return Iterator(this->m_erase(position.m_pointer));
	}

	/**
	 * @brief erase
	 * @param first,last Range of elements to remove.
	 * @return Iterator following the last removed element.
	 */
	auto erase(ConstIterator first, ConstIterator last) -> Iterator {
		auto f = first.m_pointer, l = last.m_pointer;
		for(; f != l;) {
			f = this->m_erase(f);
		}
		return Iterator(f);
	}

	/**
	 * @brief erase
	 * @param element The elements to remove.
	 * @return Number of elements removed.
	 */
	auto erase(Element const & element) -> Size {
		auto range = this->m_equal_range(element);
		Size n = 0;
		for(; range.first != range.second; ++n) {
			range.first = this->m_erase(range.first);
		}
		return n;
	}
	///@}

	void swap(BinaryTree & tree) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsAlwaysEqual, IsNothrowSwappable<Comparator> >{}) {
		this->m_swap(tree);
	}

}; // class BinaryTree< TElement, TComparator, TAllocator >

} // inline namespace Container

} // namespace BR
