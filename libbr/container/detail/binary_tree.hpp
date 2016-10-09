#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/has_default_constructor.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

namespace Detail {
namespace Container {
namespace BinaryTree {

struct NodeTraits {
	template< typename TVoidPointer >
	struct BasicNode {
		using NodePointer = typename PointerTraits<TVoidPointer>::template Rebind<BasicNode>;

		NodePointer parent, left, right;
	};

	template< typename TElement, typename TVoidPointer >
	struct Node : public BasicNode<TVoidPointer> {
		using Base = BasicNode<TVoidPointer>;

		using Element = TElement;

		Element element;
	};
};

struct Algorithms {
	template< typename TNodePointer >
	BR_CONSTEXPR_AFTER_CXX11 static bool is_header(TNodePointer const & node) noexcept {
		if (node->parent == nullptr) {
			return true;
		}
		auto left = node->left, right = node->right;
		return left != nullptr && right != nullptr && (left == right || left->parent != node || right->parent != node);
	}

	template< typename TNodePointer >
	static void init_header(TNodePointer const & header) noexcept {
		header->parent = nullptr;
		header->left = header->right = header;
	}

	template< typename TNodePointer >
	auto find_left_most(TNodePointer const & node) noexcept -> TNodePointer {
		for (; node->left != nullptr;) {
			node = static_cast<TNodePointer>(node->left);
		}
		return node;
	}

	template< typename TNodePointer >
	auto find_right_most(TNodePointer const & p) noexcept -> TNodePointer {
		for (; node->right != nullptr;) {
			node = static_cast<TNodePointer>(node->right);
		}
		return node;
	}

	template< typename TNodePointer >
	static auto prev_node(TNodePointer const & node) noexcept -> TNodePointer {
		if (is_header(node)) {
			return static_cast<TNodePointer>(node->right);
		} else {
			auto left = static_cast<TNodePointer>(node->left);
			if (left != nullptr) {
				return find_right_most(left);
			}
		}
		auto n = node;
		auto p = static_cast<TNodePointer>(n->parent);
		while (n == static_cast<TNodePointer>(p->left)) {
			n = p;
			p = static_cast<TNodePointer>(n->parent);
		}
		return p;
	}

	template< typename TNodePointer >
	static auto next_node(TNodePointer const & node) noexcept -> TNodePointer {
		auto right = static_cast<TNodePointer>(node->right);
		if (right != nullptr) {
			return find_left_most(right);
		}
		auto n = node;
		auto p = static_cast<TNodePointer>(n->parent);
		while (n == static_cast<TNodePointer>(p->right)) {
			n = p;
			p = static_cast<TNodePointer>(n->parent);
		}
		return static_cast<TNodePointer>(n->right) != p ? p : n;
	}

	template< typename TNodePointer >
	static void insert_at(TNodePointer const & header, TNodePointer const & new_node, TNodePointer const & parent, bool insert_left) noexcept {
		if (parent == header) {
			header->parent = header->left = header->right = new_node;
		} else if (insert_left) {
			parent->left = new_node;
			if (parent_node == static_cast<TNodePointer>(header->left)) {
				header->left = new_node;
			}
		} else {
			parent->right = new_node;
			if (parent_node == static_cast<TNodePointer>(header->right)) {
				header->right = new_node;
			}
		}
		new_node->parent = parent;
		new_node->left = new_node->right = nullptr;
	}

	template< typename TNodePointer, typename TKey, typename TComparator >
	static auto lower_bound(TNodePointer node, TNodePointer result, TKey const & key, TComparator comparator) noexcept -> TNodePointer {
		for (; node != nullptr;) {
			if (comparator(node->element, key)) {
				node = static_cast<TNodePointer>(node->right);
			} else {
				result = node;
				node = static_cast<TNodePointer>(node->left);
			}
		}
		return result;
	}

	template< typename TNodePointer, typename TKey, typename TComparator >
	static auto upper_bound(TNodePointer node, TNodePointer result, TKey const & key, TComparator comparator) noexcept -> TNodePointer {
		for (; node != nullptr;) {
			if (comparator(key, node->element)) {
				result = node;
				node = static_cast<TNodePointer>(node->left);
			} else {
				node = static_cast<TNodePointer>(node->right);
			}
		}
		return result;
	}

	template< typename TNodePointer, typename TKey, typename TComparator >
	static auto equal_range(TNodePointer node, TNodePointer result, TKey const & key, TComparator comparator) noexcept -> Pair< TNodePointer, TNodePointer > {
		for (; node != nullptr;) {
			if (comparator(node->element, key)) {
				node = static_cast<TNodePointer>(node->right);
			} else if (comparator(key, node->element)){
				result = node;
				node = static_cast<TNodePointer>(node->left);
			} else {
				return make_pair(
					lower_bound(static_cast<TNodePointer>(node->left), node, key, comparator),
					upper_bound(static_cast<TNodePointer>(node->right), result, key, comparator)
				);
			}
		}
		return make_pair(result, result);
	}

protected:
	template< typename TNodePointer >
	static void set_child(TNodePointer const & header, TNodePointer const & node, TNodePointer const & child, bool const at_left) noexcept {
		if (node == header) {
			header->parent = child;
		} else if (at_left) {
			node->left = child;
		} else {
			node->right = child;
		}
	}

	template< typename TNodePointer >
	static void rotate_left_no_parent_fix(TNodePointer const & node, TNodePointer const & right) noexcept {
		auto right_left = right->left;
		node->right = right_left;
		if (right_left != nullptr) {
			right_left->parent = node;
		}
		right->left = node;
		node->parent = right;
	}

	template< typename TNodePointer >
	static void rotate_left(TNodePointer const & header, TNodePointer const & node, TNodePointer const & parent, TNodePointer const & right) noexcept {
		auto const was_left = parent->left == node;
		rotate_left_no_parent_fix(node, right);
		right->parent = parent;
		set_child(header, parent, right, was_left);
	}

	template< typename TNodePointer >
	static void rotate_right_no_parent_fix(NodePointer const & node, NodePointer const & left) noexcept {
		auto left_right = left->right;
		node->left = left_right;
		if (left_right != nullptr) {
			left_right->parent = node;
		}
		left->right = node;
		node->parent = left;
	}

	template< typename TNodePointer >
	static void rotate_left(TNodePointer const & header, TNodePointer const & node, TNodePointer const & parent, TNodePointer const & left) noexcept {
		auto const was_left = parent->left == node;
		rotate_right_no_parent_fix(node, left);
		left->parent = parent;
		set_child(header, parent, left, was_left);
	}
};

template< typename TNodePointer >
class Iterator;

template< typename TNodeConstPointer >
class ConstIterator;

template< typename TNodePointer >
class Iterator : public BasicIterator {
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
		m_pointer = static_cast<NodePointer>(Algorithms::next_node(static_cast<BasicNodePointer>(m_pointer)));
		return *this;
	}

	auto operator++(int) -> Iterator {
		Iterator temp(*this);
		operator++();
		return *temp;
	}

	auto operator--() -> Iterator & {
		m_pointer = static_cast<NodePointer>(Algorithms::prev_node(static_cast<BasicNodePointer>(m_pointer)));
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
class ConstIterator : BasicIterator {
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = PointerTraits<TNodePointer>;

	using Node = typename NodePointerTraits::Element;

	using BasicNode = typename Node::Base;

	using BasicNodePointer = typename NodeConstPointerTraits::template Rebind<BasicNode>;

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
		m_pointer = static_cast<NodePointer>(Algorithms::next_node(static_cast<BasicNodePointer>(m_pointer)));
		return *this;
	}

	auto operator++(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator++();
		return *temp;
	}

	auto operator--() -> ConstIterator & {
		m_pointer = static_cast<NodePointer>(Algorithms::prev_node(static_cast<BasicNodePointer>(m_pointer)));
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

template< typename TElement, typename TComparator, typename TAllocator, typename TNodeTraits = NodeTraits >
class Base {

protected:
	using Element = TElement;

	using Comparator = TComparator;

	using Allocator = TAllocator;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using VoidPointer = typename AllocatorTraits::VoidPointer;

	using NodeTraits = TNodeTraits;

	using Node = typename NodeTraits::template Node<Element, VoidPointer>;

	using NodeAllocator = typename AllocatorTraits::template Rebind<Node>;

	using NodeAllocatorTraits = BR::AllocatorTraits<NodeAllocator>;

	using NodePointer = typename NodeAllocatorTraits::Pointer;

	using BasicNode = typename Node::Base;

	using BasicNodeAllocator = typename AllocatorTraits::template Rebind<BasicNode>;

	using BasicNodeAllocatorTraits = BR::AllocatorTraits<BasicNodeAllocator>;

	using BasicNodePointer = typename BasicNodeAllocatorTraits::Pointer;

	using BasicNodePointerTraits = PointerTraits<BasicNodePointer>;

	using Reference = Element &;

	using ConstReference = Element const &;

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using Size = typename AllocatorTraits::Size;

	using Difference = typename AllocatorTraits::Difference;

	using Iterator = RBTree::Iterator<NodePointer>;

	using ConstIterator = RBTree::ConstIterator<NodePointer>;

private:
	using NodeDestructor = AllocatorDestructor<NodeAllocator>;

	using NodeHolder = UniquePointer< Node, NodeDestructor >;

protected:
	Base() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) {
		Algorithms::init_header(m_header());
	}

	explicit Base(Allocator const & allocator) : m_imp(0, NodeAllocator(allocator)) {
		Algorithms::init_header(m_header());
	}

	Base(Comparator const & comparator, Allocator const & allocator = Allocator{}) : m_imp(0, NodeAllocator(allocator), comparator) {
		Algorithms::init_header(m_header());
	}

	~Base();

protected:
	auto m_size() noexcept -> Size & {
		return m_imp.get<Size>();
	}

	auto m_size() const noexcept -> Size const & {
		return m_imp.get<Size>();
	}

	auto m_node_allocator() noexcept -> NodeAllocator & {
		return m_imp.get<NodeAllocator>();
	}

	auto m_node_allocator() const noexcept -> NodeAllocator const & {
		return m_imp.get<NodeAllocator>();
	}

	auto m_comparator() noexcept -> Comparator & {
		return m_imp.get<Comparator>();
	}

	auto m_comparator() const noexcept -> Comparator const & {
		return m_imp.get<Comparator>();
	}

	auto m_header() const noexcept -> BasicNodePointer {
		return BasicNodePointerTraits::make_pointer(const_cast<HeadNode &>(m_imp.get<HeadNode>()));
	}

	auto m_root() const noexcept -> NodePointer {
		return static_cast<NodePointer>(m_header()->parent);
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
		return static_cast<NodePointer>(m_head());
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

	template< typename TKey >
	auto m_find(TKey const & key) const -> NodePointer {
		auto lower = m_lower_bound(element);
		return (lower == m_end() || m_comparator()(element, lower)) ? m_end() : lower;
	}

	template< typename TKey >
	auto m_lower_bound(TKey const & key) const -> NodePointer {
		return Algorithms::lower_bound(m_root(), static_cast<NodePointer>(m_header()), key, m_comparator());
	}

	template< typename TKey >
	auto m_upper_bound(TKey const & key) const -> NodePointer {
		return Algorithms::upper_bound(m_root(), static_cast<NodePointer>(m_header()), key, m_comparator());
	}

	template< typename TKey >
	auto m_equal_range(TKey const & key) const -> Pair< NodePointer, NodePointer > {
		return Algorithms::equal_range(m_root(), static_cast<NodePointer>(m_header()), key, m_comparator());
	}

	static auto m_make_iterator(NodePointer const & node) -> Iterator {
		return Iterator(node);
	}

	static auto m_make_iterator(NodePointer && node) -> Iterator {
		return Iterator(move(node));
	}

	static auto m_make_const_iterator(NodePointer const & node) -> ConstIterator {
		return ConstIterator(node);
	}

	static auto m_make_const_iterator(NodePointer && node) -> ConstIterator {
		return ConstIterator(move(node));
	}

private:

	auto m_emplace_unique_find(Element const & key) -> Pair< NodePointer, bool > {
		auto node = m_root();
		if (node != nullptr) {
			for (;;) {
				if (m_comparator(key, node->element)) {
					if (node->left != nullptr) {
						node = static_cast<NodePointer>(node->left);
					} else {
						return Pair{ static_cast<BasicNodePointer>(node), true };
					}
				} else if (m_comparator(node->element, key)) {
					if (node->right != nullptr) {
						node = static_cast<NodePointer>(node->right);
					} else {
						return make_pair(static_cast<BasicNodePointer>(node), true);
					}
				} else {
					return make_pair(static_cast<BasicNodePointer>(node), true);
				}
			}
		}
		return make_pair(m_end(), true);
	}

	template< typename ... TArgs >
	void m_emplace_unique(TArgs && ... args) -> Iterator {
		auto & node_allocator = this->m_node_allocator();
		NodeHolder holder(NodeAllocatorTraits::allocate(node_allocator, 1), NodeDestructor(node_allocator, 1));
		NodeAllocatorTraits::construct(allocator, address_of(node->element), forward<TArgs>(args)...);
		auto & child = m_find_equal(parent, holder->element);

		__node_holder __h(__node_traits::allocate(__na, 1), _Dp(__na));


		__node_holder __h = __construct_node(_VSTD::forward<_Args>(__args)...);
		__node_base_pointer __parent;
		__node_base_pointer& __child = __find_equal(__parent, __h->__value_);
		__node_pointer __r = static_cast<__node_pointer>(__child);
		bool __inserted = false;
		if (__child == nullptr)
		{
			__insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
			__r = __h.release();
			__inserted = true;
		}
	}

	void m_initialize() noexcept {
		m_head()->parent = nullptr;
		m_head()->left = m_head()->right = m_head();
	}

private:
	Tuple< Size, NodeAllocator, Comparator, BasicNode > m_imp;
};

} // namespace BinaryTree
} // namespace Container
} // namespace Detail
} // namespace BR