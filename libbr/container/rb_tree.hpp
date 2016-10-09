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
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_operate/map_cv.hpp>
#include <libbr/type_operate/remove_const.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename TElement, typename TComparator = Less<TElement>, typename TAllocator = Allocator<TElement> >
class RBTree;



namespace Detail {
namespace Container {
namespace RBTree {

template< typename TNodePointer >
inline bool node_is_left_child(TNodePointer p) noexcept {
	BR_ASSERT(p != nullptr);
	return p == p->parent->left;
}

template< typename TNodePointer >
auto node_left_most(TNodePointer p) noexcept -> TNodePointer {
	BR_ASSERT(p != nullptr);
	while (p->left != nullptr) {
		p = p->left;
	}
	return p;
}

template< typename TNodePointer >
auto node_right_most(TNodePointer p) noexcept -> TNodePointer {
	BR_ASSERT(p != nullptr);
	while (p->right != nullptr) {
		p = p->right;
	}
	return p;
}

template< typename TNodePointer >
auto node_next(TNodePointer p) noexcept -> TNodePointer {
	if (p->right != nullptr) {
		return node_left_most(p->right);
	}
	while (!node_is_left_child(p)) {
		p = p->parent;
	}
	return p->parent;
}

template< typename TNodePointer >
auto node_prev(TNodePointer p) noexcept -> TNodePointer {
	if (p->left != nullptr) {
		return node_right_most(p->left);
	}
	while (node_is_left_child(p)) {
		p = p->parent;
	}
	return p->parent;
}

template< typename TNodePointer >
void tree_left_rotate(TNodePointer & root, TNodePointer x) noexcept {
	auto y = x->right;
	x->right = y->left;
	if (x->right != nullptr) {
		x->right->parent = x;
	}
	y->parent = x->parent;
	if (x == root) {
		root = y;
	} else if (node_is_left_child(x)) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template< typename TNodePointer >
void tree_left_rotate(TNodePointer x) noexcept {
	auto y = x->right;
	x->right = y->left;
	if (x->right != nullptr) {
		x->right->parent = x;
	}
	y->parent = x->parent;
	if (node_is_left_child(x)) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template< typename TNodePointer >
void tree_right_rotate(TNodePointer & root, TNodePointer x) noexcept {
	auto y = x->left;
	x->left = y->right;
	if (x->left != nullptr) {
		x->left->parent = x;
	}
	y->parent = x->parent;
	if (x == root) {
		root = y;
	} else if (node_is_left_child(x)) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}

template< typename TNodePointer >
void tree_right_rotate(TNodePointer x) noexcept {
	auto y = x->left;
	x->left = y->right;
	if (x->left != nullptr) {
		x->left->parent = x;
	}
	y->parent = x->parent;
	if (node_is_left_child(x)) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}

template< typename TNodePointer >
void tree_balance_after_insert(TNodePointer root, TNodePointer x) noexcept {
	x->is_black = x == root;
	while (x != root && !x->parent->is_black) {
		if (node_is_left_child(x->parent)) {
			auto y = x->parent->parent->right;
			if (y != nullptr && !y->is_black) {
				x = x->parent;
				x->is_black = true;
				x = x->parent;
				x->is_black = x == root;
				y->is_black = true;
			} else {
				if (!node_is_left_child(x)) {
					x = x->parent;
					tree_left_rotate(x);
				}
				x = x->parent;
				x->is_black = true;
				x = x->parent;
				x->is_black = false;
				tree_right_rotate(x);
				break;
			}
		} else {
			auto y = x->parent->parent->left;
			if (y != nullptr && !y->is_black) {
				x = x->parent;
				x->is_black = true;
				x = x->parent;
				x->is_black = x == root;
				y->is_black = true;
			} else {
				if (node_is_left_child(x)) {
					x = x->parent;
					tree_right_rotate(x);
				}
				x = x->parent;
				x->is_black = true;
				x = x->parent;
				x->is_black = false;
				tree_left_rotate(x);
				break;
			}
		}
	}
}

template< typename TNodePointer >
void tree_remove(TNodePointer root, TNodePointer z) noexcept {

}

template< typename TNodePointer >
struct BasicNode;

template< typename TVoidPointer >
struct RBNode;

template< typename TElement, typename TVoidPointer >
struct Node;

template< typename TVoidPointer >
using HeadNode = BasicNode< typename PointerTraits<TVoidPointer>::template Rebind< BasicNode<TVoidPointer> > >;

template< typename TNodePointer >
struct BasicNode {
	using NodePointer = TNodePointer;

	BasicNode() noexcept : parent(nullptr), left(nullptr), right(nullptr) {
	}

	NodePointer parent;
	NodePointer left;
	NodePointer right;
};

template< typename TVoidPointer >
struct RBNode : public HeadNode<TVoidPointer> {
	using Base = HeadNode<TVoidPointer>;

	using VoidPointer = TVoidPointer;

	using VoidPointerTraits = PointerTraits<TVoidPointer>;

	using Pointer = typename VoidPointerTraits::template Rebind<RBNode>;

	using ConstPointer = typename VoidPointerTraits::template Rebind<RBNode const>;

	RBNode() noexcept : is_black(false) {
	}

	bool is_black;
};

template< typename TElement, typename TVoidPointer >
struct Node : public RBNode<TVoidPointer> {
	using Base = RBNode<TVoidPointer>;

	using Element = TElement;

	template< typename ... TArgs >
	explicit Node(TArgs && ... args) : element(forward<TArgs>(args)...) {
	}

	Element element;
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

	using RBNode = typename Node::Base;

	using RBNodePointer = typename NodePointerTraits::template Rebind<RBNode>;

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
		m_pointer = static_cast<NodePointer>(node_next(static_cast<RBNodePointer>(m_pointer)));
		return *this;
	}

	auto operator++(int) -> Iterator {
		Iterator temp(*this);
		operator++();
		return *temp;
	}

	auto operator--() -> Iterator & {
		m_pointer = static_cast<NodePointer>(node_prev(static_cast<RBNodePointer>(m_pointer)));
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

template< typename TNodeConstPointer >
class ConstIterator : BasicIterator {
private:
	using NodeConstPointer = TNodeConstPointer;

	using NodeConstPointerTraits = PointerTraits<NodeConstPointer>;

	using NodeConst = typename NodeConstPointerTraits::Element;

	using Node = RemoveConst<NodeConst>;

	using NodePointer = typename NodeConstPointerTraits::template Rebind<Node>;

	using RBNodeConst =  MapCV< NodeConst, typename Node::Base >;

	using RBNodeConstPointer = typename NodeConstPointerTraits::template Rebind<RBNodeConst>;

public:
	struct Category : public IteratorTag, public ReadableTag, public BidirectionalTraversalTag {};

	using Element = typename Node::Element;

	using Pointer = typename NodeConstPointerTraits::template Rebind<Element const>;

	using Reference = Element const &;

	using Difference = typename NodeConstPointerTraits::Difference;

	ConstIterator() noexcept : m_pointer(nullptr) {
	}

	ConstIterator(Iterator<NodePointer> iterator) noexcept : m_pointer(iterator.m_pointer) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return NodeConstPointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> ConstIterator & {
		m_pointer = static_cast<NodeConstPointer>(node_next(static_cast<RBNodeConstPointer>(m_pointer)));
		return *this;
	}

	auto operator++(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator++();
		return *temp;
	}

	auto operator--() -> ConstIterator & {
		m_pointer = static_cast<NodeConstPointer>(node_prev(static_cast<RBNodeConstPointer>(m_pointer)));
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
	NodeConstPointer m_pointer;
}; // class ConstIterator<TNodeConstPointer>

template< typename TElement, typename TComparator, typename TAllocator >
class Base {
protected:
	using Element = TElement;

	using Comparator = TComparator;

	using Allocator = TAllocator;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using VoidPointer = typename AllocatorTraits::VoidPointer;

	using Node = RBTree::Node< Element, VoidPointer >;

	using NodeAllocator = typename AllocatorTraits::template Rebind<Node>;

	using NodeAllocatorTraits = BR::AllocatorTraits<NodeAllocator>;

	using NodePointer = typename NodeAllocatorTraits::Pointer;

	using NodeConstPointer = typename NodeAllocatorTraits::Pointer;

	using BasicNode = typename Node::Base;

	using BasicNodePointer = typename BasicNode::Pointer;

	using BasicNodeConstPointer = typename BasicNode::Pointer;

	using HeadNode = RBTree::HeadNode<VoidPointer>;

	using HeadNodeAllocator = typename AllocatorTraits::template Rebind<HeadNode>;

	using HeadNodeAllocatorTraits = BR::AllocatorTraits<HeadNodeAllocator>;

	using HeadNodePointer = typename HeadNodeAllocatorTraits::Pointer;

	using HeadNodePointerTraits = PointerTraits<HeadNodePointer>;

	using Reference = Element &;

	using ConstReference = Element const &;

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using Size = typename AllocatorTraits::Size;

	using Difference = typename AllocatorTraits::Difference;

	using Iterator = RBTree::Iterator<NodePointer>;

	using ConstIterator = RBTree::ConstIterator<NodePointer>;

protected:
	Base() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) : m_imp(0) {
		m_initialize();
	}

	explicit Base(Allocator const & allocator) : m_imp(0, NodeAllocator(allocator)) {
		m_initialize();
	}

	Base(Comparator const & comparator, Allocator const & allocator = Allocator{}) : m_imp(0, NodeAllocator(allocator), comparator) {
		m_initialize();
	}

	~Base();

protected:
	auto m_size() noexcept -> Size & {
		return m_imp.template get<Size>();
	}

	auto m_size() const noexcept -> Size const & {
		return m_imp.template get<Size>();
	}

	auto m_allocator() noexcept -> NodeAllocator & {
		return m_imp.template get<NodeAllocator>();
	}

	auto m_allocator() const noexcept -> NodeAllocator const & {
		return m_imp.template get<NodeAllocator>();
	}

	auto m_comparator() noexcept -> Comparator & {
		return m_imp.template get<Comparator>();
	}

	auto m_comparator() const noexcept -> Comparator const & {
		return m_imp.template get<Comparator>();
	}

	auto m_head() noexcept -> NodePointer {
		return static_cast<NodePointer>(HeadNodePointerTraits::make_pointer(m_imp.template get<HeadNode>()));
	}

	auto m_head() const noexcept -> NodeConstPointer {
		return static_cast<NodeConstPointer>(HeadNodePointerTraits::make_pointer(const_cast<HeadNode &>(m_imp.template get<HeadNode>())));
	}

	auto m_root() noexcept -> NodePointer {
		return m_head()->parent;
	}

	auto m_root() const noexcept -> NodeConstPointer {
		return m_head()->parent;
	}

	auto m_left_most() noexcept -> NodePointer {
		return m_head()->left;
	}

	auto m_left_most() const noexcept -> NodeConstPointer {
		return m_head()->left;
	}

	auto m_right_most() noexcept -> NodePointer {
		return m_head()->right;
	}

	auto m_right_most() const noexcept -> NodeConstPointer {
		return m_head()->right;
	}

	auto m_begin() noexcept -> NodePointer {
		return m_left_most();
	}

	auto m_begin() const noexcept -> NodeConstPointer {
		return m_left_most();
	}

	auto m_end() noexcept -> NodePointer {
		return m_head();
	}

	auto m_end() const noexcept -> NodeConstPointer {
		return m_head();
	}

	bool m_is_empty() const noexcept {
		return m_size() == 0;
	}

private:
	void m_initialize() noexcept {
		m_head()->parent = nullptr;
		m_head()->left = m_head()->right = m_head();
	}

private:
	Tuple< Size, NodeAllocator, Comparator, HeadNode > m_imp;

}; // class Base< TElement, TComparator, TAllocator >

} // namespace RBTree
} // namespace Container
} // namespace Detail

template< typename TElement, typename TComparator, typename TAllocator >
class RBTree : private Detail::Container::RBTree::Base< TElement, TComparator, TAllocator > {

protected:
	using Element = TElement;

	using Comparator = TComparator;

	using Allocator = TAllocator;

private:
	using Base = Detail::Container::RBTree::Base< TElement, TComparator, TAllocator >;

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
	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

	template< typename TIterator >
	using IsInputIterator = BooleanAnd<
		IsConvertible< typename IteratorTraits<TIterator>::Category, ReadableTag >,
		IsConvertible< typename IteratorTraits<TIterator>::Category, SinglePassTraversalTag >
	>;

public:
	RBTree() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) {
	}

	explicit RBTree(Allocator const & allocator) : Base(allocator) {
	}

	explicit RBTree(Comparator const & comparator, Allocator const & allocator = Allocator{}) : Base(comparator, allocator) {
	}

	RBTree(RBTree const & tree);

	RBTree(RBTree const & tree, Allocator const & allocator);

	RBTree(RBTree && tree);

	RBTree(RBTree && tree, Allocator const & allocator);

	template< typename TInputIterator >
	RBTree(TInputIterator f, TInputIterator l, Comparator const & comparator = Comparator{}, Allocator const & allocator = Allocator{}, EnableIf< IsInputIterator<TInputIterator> > * = nullptr) : Base(comparator, allocator) {
	}

	template< typename TInputIterator >
	RBTree(TInputIterator f, TInputIterator l, Allocator const & allocator = Allocator{}, EnableIf< IsInputIterator<TInputIterator> > * = nullptr) : RBTree(f, l, Comparator{}, allocator) {
	}

	RBTree(InitializerList<Element> l, Comparator const & comparator = Comparator{}, Allocator const & allocator = Allocator{}) : Base(comparator, allocator) {
	}

	RBTree(InitializerList<Element> l, Allocator const & allocator = Allocator{}) : RBTree(l, Comparator{}, allocator) {
	}

	~RBTree() = default;

	/**
	 * @name 成员
	 */
	///@{
	auto allocator() const noexcept -> Allocator {
		return Allocator(this->m_allocator());
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
	 * @brief is empty
	 */
	auto is_empty() const noexcept -> bool {
		return this->m_is_empty();
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
	auto operator==(RBTree const & y) const -> bool {
		return size() == y.size() && equal(begin(), end(), y.begin(), y.end());
	}

	auto operator!=(RBTree const & y) const -> bool {
		return !operator==(y);
	}

	auto operator<(RBTree const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}

	auto operator>(RBTree const & y) const -> bool {
		return y.operator<(*this);
	}

	auto operator<=(RBTree const & y) const -> bool {
		return !y.operator<(*this);
	}

	auto operator>=(RBTree const & y) const -> bool {
		return !operator<(y);
	}
	///@}

	/**
	 * @name 赋值操作
	 */
	///@{
	auto operator=(RBTree const &) -> RBTree &;

	auto operator=(RBTree &&) -> RBTree &;

	auto operator=(InitializerList<Element> l) -> RBTree &;
	///@}

	/**
	 * @name 添加操作
	 */
	///@{
	template< typename ... TArgs >
	auto emplace(TArgs && ... args) -> Pair< Iterator, bool >;

	template< typename ... TArgs >
	auto emplace_hint(ConstIterator hint, TArgs && ... args) -> Pair< Iterator, bool >;


	auto insert(Element const & element) -> Pair< Iterator, bool >;
	///@}


	/**
	 * @name 删除操作
	 */
	///@{
	auto clear() noexcept -> RBTree &;

	auto erase(ConstIterator pos) -> Iterator;

	auto erase(ConstIterator first, ConstIterator last) -> Iterator;

	auto erase(Element const & key) -> Iterator;
	///@}

}; // class RBTree< TElement, TComparator, TAllocator >

} // namespace BR