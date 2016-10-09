/**
 * @file
 * @brief List
 * @author Bromine0x23
 * @since 2015/11/17
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/move_iterator.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/iterator/prev.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_destructor.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename TElement, typename TAllocator = Allocator<TElement> >
class List;

template< typename TElement, typename TAllocator >
inline void swap(List< TElement, TAllocator > & x, List< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}



namespace Detail {
namespace Container {
namespace List {

template< typename TNodePointer >
struct BasicNode;

template< typename TElement, typename TVoidPointer >
struct Node;

template< typename TElement, typename TVoidPointer >
using HeadNode = BasicNode< typename PointerTraits<TVoidPointer>::template Rebind< Node<TElement, TVoidPointer> > >;

template< typename TNodePointer >
struct BasicNode {
	using NodePointer = TNodePointer;

	using BasicNodePointer = typename PointerTraits<NodePointer>::template Rebind<BasicNode>;

	BasicNode() : prev(self()), next(self()) {
	}

	auto self() -> NodePointer {
		return static_cast<NodePointer>(PointerTraits<BasicNodePointer>::make_pointer(*this));
	}

	NodePointer prev;
	NodePointer next;
};

template< typename TElement, typename TVoidPointer >
struct Node : public HeadNode< TElement, TVoidPointer > {
	using Element = TElement;

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

	template< typename TElement, typename TAllocator >
	friend class BR::List;

	template< typename TNodeConstPointer >
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
		m_pointer = m_pointer->next;
		return *this;
	}

	auto operator++(int) -> Iterator {
		Iterator temp(*this);
		operator++();
		return *temp;
	}

	auto operator--() -> Iterator & {
		m_pointer = m_pointer->prev;
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

	using Node = RemoveConst< typename NodeConstPointerTraits::Element >;

	using NodePointer = typename NodeConstPointerTraits::template Rebind<Node>;

	template< typename TElement, typename TAllocator >
	friend class BR::List;

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
		m_pointer = m_pointer->next;
		return *this;
	}

	auto operator++(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator++();
		return *temp;
	}

	auto operator--() -> ConstIterator & {
		m_pointer = m_pointer->prev;
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
	explicit ConstIterator(NodePointer pointer) noexcept : m_pointer(pointer) {}

private:
	NodeConstPointer m_pointer;
}; // class ConstIterator<TNodeConstPointer>

template< typename TElement, typename TAllocator >
class Base {
protected:
	using Element = TElement;

	using Allocator = TAllocator;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using VoidPointer = typename AllocatorTraits::VoidPointer;

	using Node = List::Node< Element, VoidPointer >;

	using NodeAllocator = typename AllocatorTraits::template Rebind<Node>;

	using NodeAllocatorTraits = BR::AllocatorTraits<NodeAllocator>;

	using NodePointer = typename NodeAllocatorTraits::Pointer;

	using NodeConstPointer = typename NodeAllocatorTraits::Pointer;

	using HeadNode = List::HeadNode< Element, VoidPointer >;

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

	using Iterator = List::Iterator<NodePointer>;

	using ConstIterator = List::ConstIterator<NodePointer>;

protected:
	Base() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) : m_impl(0) {
	}

	Base(Allocator const & allocator) : m_impl(0, NodeAllocator(allocator)) {
	}

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

	auto m_head() noexcept -> NodePointer {
		return static_cast<NodePointer>(HeadNodePointerTraits::make_pointer(m_impl.template get<HeadNode>()));
	}

	auto m_head() const noexcept -> NodeConstPointer {
		return static_cast<NodeConstPointer>(HeadNodePointerTraits::make_pointer(const_cast<HeadNode &>(m_impl.template get<HeadNode>())));
	}

	bool m_is_empty() const noexcept {
		return m_size() == 0;
	}

	auto m_begin() noexcept -> NodePointer {
		return m_head()->next;
	}

	auto m_begin() const noexcept -> NodeConstPointer {
		return m_head()->next;
	}

	auto m_end() noexcept -> NodePointer {
		return m_head();
	}

	auto m_end() const noexcept -> NodeConstPointer {
		return m_head();
	}

	void m_copy_assign_allocator(Base const & list) {
		m_copy_assign_allocator(list, typename NodeAllocatorTraits::IsPropagateOnContainerCopyAssignment{});
	}

	void m_move_assign_allocator(Base & list) noexcept(
		BooleanOr<
			BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment >,
			HasNothrowMoveAssignment<NodeAllocator>
		>{}
	) {
		m_move_assign_allocator(list, typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment{});
	}

	void m_clear() noexcept;

	void m_swap(Base & list) noexcept(
		BooleanOr< BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >, IsNothrowSwappable<NodeAllocator> >{}
	);

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y) noexcept(
		BooleanOr<
			BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<NodeAllocator>
		>{}
	) {
		m_swap_allocator(x, y, typename NodeAllocatorTraits::IsPropagateOnContainerSwap{});
	}

	static void m_link_nodes(NodePointer p, NodePointer f, NodePointer l);

	static void m_unlink_nodes(NodePointer f, NodePointer l) noexcept {
		f->prev->next = l->next;
		l->next->prev = f->prev;
	}

	void m_insert_nodes_at_front(NodePointer f, NodePointer l);

	void m_insert_nodes_at_back(NodePointer f, NodePointer l);

private:
	void m_copy_assign_allocator(Base const & list, BooleanFalse) {
	}

	void m_copy_assign_allocator(Base const & list, BooleanTrue) {
		if (m_allocator() != list.m_allocator()) {
			m_clear();
		}
		m_allocator() = list.m_allocator();
	}

	void m_move_assign_allocator(Base & list, BooleanFalse) noexcept {
	}

	void m_move_assign_allocator(Base & list, BooleanTrue) noexcept(HasNothrowMoveAssignment<NodeAllocator>{}) {
		m_allocator() = move(list.m_allocator());
	}

	void m_swap_fix() {
		if (m_size() == 0) {
			m_head()->next = m_head()->prev = m_head()->self();
		} else {
			m_head()->prev->next = m_head()->next->prev = m_head()->self();
		}
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanFalse) noexcept {
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanTrue) noexcept(IsNothrowSwappable<NodeAllocator>{}) {
		using BR::swap;
		swap(x, y);
	}

protected:
	Tuple< Size, NodeAllocator, HeadNode > m_impl;

}; // class Base< TElement, TAllocator >

template< typename TElement, typename TAllocator >
void Base< TElement, TAllocator >::m_clear() noexcept {
	if (!m_is_empty()) {
		auto & allocator = m_allocator();
		auto f = m_begin(), l = m_end();
		m_unlink_nodes(f, l->prev);
		m_size() = 0;
		for (; f != l;) {
			auto node = f;
			f = f->next;
			NodeAllocatorTraits::destroy(allocator, address_of(node->element));
			NodeAllocatorTraits::deallocate(allocator, node, 1);
		}
	}
}

template< typename TElement, typename TAllocator >
void Base< TElement, TAllocator >::m_link_nodes(NodePointer p, NodePointer f, NodePointer l) {
	p->prev->next = f;
	f->prev = p->prev;
	p->prev = l;
	l->next = p;
}

template< typename TElement, typename TAllocator >
void Base< TElement, TAllocator >::m_insert_nodes_at_front(NodePointer f, NodePointer l) {
	f->prev = m_head()->self();
	l->next = m_head()->next;
	l->next->prev = l;
	this->m_head()->next = f;
}

template< typename TElement, typename TAllocator >
void Base< TElement, TAllocator >::m_insert_nodes_at_back(NodePointer f, NodePointer l) {
	l->next = m_head()->self();
	f->prev = m_head()->prev;
	f->prev->next = f;
	this->m_head()->prev = l;
}

template< typename TElement, typename TAllocator >
void Base< TElement, TAllocator >::m_swap(Base & list) noexcept(
	BooleanOr< BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >, IsNothrowSwappable<NodeAllocator> >{}
) {
	using BR::swap;
	m_swap_allocator(m_allocator(), list.m_allocator());
	swap(m_head()->next, list.m_head()->next);
	swap(m_head()->prev, list.m_head()->prev);
	swap(m_size(), list.m_size());
	m_swap_fix();
	list.m_swap_fix();
}

} // namespace List
} // namespace Container
} // namespace Detail

/**
 * @brief 双向链表
 * @tparam TElement 元素类型
 * @tparam TAllocator 分配器类型
 */
template< typename TElement, typename TAllocator >
class List : private Detail::Container::List::Base< TElement, TAllocator > {
public:
	/**
	 * @brief 元素类型
	 */
	using Element = TElement;

	/**
	 * @brief 分配器类型
	 */
	using Allocator = TAllocator;

private:
	using Base = Detail::Container::List::Base< Element, Allocator >;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using Node = typename Base::Node;

	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

	using NodePointer = typename Base::NodePointer;

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
	template< typename TIterator >
	using IsInputIterator = BooleanAnd<
		IsConvertible< typename IteratorTraits<TIterator>::Category, ReadableTag >,
		IsConvertible< typename IteratorTraits<TIterator>::Category, SinglePassTraversalTag >
	>;

public:
	/**
	 * @name 构造函数
	 */
	///@{
	/**
	 * @brief 默认构造函数
	 */
	List() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) {
	}

	/**
	 * @brief 默认构造函数，指定分配器
	 * @param[in] allocator 分配器
	 */
	explicit List(Allocator const & allocator) : Base(allocator) {
	}

	/**
	 * @brief 复制构造函数
	 * @param[in] list 源容器
	 */
	List(List const & other) : Base(Allocator(NodeAllocatorTraits::select_on_container_copy_construction(other.m_allocator()))) {
		for (auto i = other.begin(), e = other.end(); i != e; ++i) {
			insert_back(*i);
		}
	}

	/**
	 * @brief 复制构造函数，指定分配器
	 * @param[in] list 源容器
	 * @param[in] allocator 分配器
	 */
	List(List const & other, Allocator const & allocator) : Base(allocator) {
		for (auto i = other.begin(), e = other.end(); i != e; ++i) {
			insert_back(*i);
		}
	}

	/**
	 * @brief 移动构造函数
	 * @param[in,out] list 源容器
	 */
	List(List && other) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : Base(Allocator(move(other.m_allocator()))) {
		splice(end(), other);
	}

	/**
	 * @brief 移动构造函数，指定分配器
	 * @param[in,out] list 源容器
	 * @param[in] allocator 分配器
	 */
	List(List && other, Allocator const & allocator) : Base(allocator) {
		if (allocator == other.m_allocator()) {
			splice(end(), other);
		} else {
			assign(make_move_iterator(other.begin()), make_move_iterator(other.end()));
		}
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以默认值初始化
	 * @param[in] count 容器大小
	 * @param[in] allocator 分配器
	 */
	explicit List(Size n, Allocator const & allocator = Allocator{}) : Base(allocator) {
		for (; n > 0; --n) {
			emplace_back();
		}
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以给定值初始化
	 * @param[in] element 用于初始化的元素
	 * @param[in] size 容器大小
	 * @param[in] allocator 分配器
	 */
	List(ConstReference x, Size n, Allocator const & allocator = Allocator{}) : Base(allocator) {
		for (; n > 0; --n) {
			emplace_back(x);
		}
	}

	/**
	 * @brief 从给定区间中的值构造
	 * @tparam TIterator 迭代器类型
	 * @param[in] f,l 给定区间
	 * @param[in] allocator 分配器
	 */
	template< typename TIterator >
	List(TIterator f, TIterator l, Allocator const & allocator = Allocator{}, EnableIf< IsInputIterator<TIterator> > * = nullptr) : Base(allocator) {
		for (; f != l; ++f) {
			emplace_back(*f);
		}
	}

	/**
	 * @brief 从初始化列表构造
	 * @param[in] list 初始化列表
	 * @param[in] allocator 分配器
	 */
	List(InitializerList<Element> l, Allocator const & allocator = Allocator{}) : Base(allocator) {
		for (auto i = l.begin(), e = l.end(); i != e; ++i) {
			emplace_back(*i);
		}
	}
	///@}

	~List() = default;

	/**
	 * @name 成员
	 */
	///@{
	auto allocator() const noexcept -> Allocator {
		return Allocator(this->m_allocator());
	}

	auto front() -> Reference {
		return this->m_head()->next->element;
	}

	auto front() const -> ConstReference {
		return this->m_head()->next->element;
	}

	auto back() -> Reference {
		return this->m_head()->prev->element;
	}

	auto back() const -> ConstReference {
		return this->m_head()->prev->element;
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
	 * @brief begin
	 */
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

	auto resize(Size n) -> List &;

	auto resize(Size n, Element const & x) -> List &;
	///@}

	/**
	 * @name 比较
	 */
	///@{
	auto operator==(List const & y) const -> bool {
		return size() == y.size() && equal(begin(), end(), y.begin(), y.end());
	}

	auto operator!=(List const & y) const -> bool {
		return !operator==(y);
	}

	auto operator<(List const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}

	auto operator>(List const & y) const -> bool {
		return y.operator<(*this);
	}

	auto operator<=(List const & y) const -> bool {
		return !y.operator<(*this);
	}

	auto operator>=(List const & y) const -> bool {
		return !operator<(y);
	}
	///@}

	/**
	 * @name 赋值操作
	 */
	///@{
	/**
	 * @brief 复制运算
	 * @param[in] string 源链表
	 */
	auto operator=(List const & other) -> List & {
		if (this != &other) {
			this->m_copy_assign_allocator(other);
			assign(other.begin(), other.end());
		}
		return *this;
	}

	/**
	 * @brief 移动运算
	 * @param[in] list 源链表
	 */
	auto operator=(List && other) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator> >{}) -> List & {
		m_move_assign(other, typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment{});
		return *this;
	}

	/**
	 * @brief 从初始化列表复制
	 * @param[in] list 初始化列表
	 */
	auto operator=(InitializerList<Element> l) -> List & {
		assign(l.begin(), l.end());
		return *this;
	}

	/**
	 * @brief 设置容器内容为 count 个给定元素的副本
	 * @param[in] element 迭代器区间
	 * @param[in] count 迭代器区间
	 */
	auto assign(Element const & x, Size n) -> List &;

	/**
	 * @brief 以迭代器区间赋值
	 * @param[in] f,l 迭代器区间
	 */
	template< typename TIterator >
	auto assign(TIterator f, TIterator l) -> EnableIf< IsInputIterator<TIterator>, List & >;
	///@}

	/**
	 * @name 添加性操作
	 */
	///@{
	/**
	 * @brief 从参数构造对象并添加到指定位置
	 */
	template< typename ... TArgs >
	auto emplace(ConstIterator p, TArgs && ... args) -> Iterator;

	/**
	 * @brief 从参数构造对象并添加到头部
	 */
	template< typename ... TArgs >
	auto emplace_front(TArgs && ... args) -> List &;

	/**
	 * @brief 从参数构造对象并添加到尾部
	 */
	template< typename ... TArgs >
	auto emplace_back(TArgs && ... args) -> List &;

	auto insert(ConstIterator p, Element const & x) -> Iterator {
		return emplace(p, x);
	}

	auto insert(ConstIterator p, Element && x) -> Iterator {
		return emplace(p, move(x));
	}

	auto insert(ConstIterator p, Element const & x, Size s) -> Iterator;

	template< typename TIterator >
	auto insert(ConstIterator p, TIterator f, TIterator l) -> EnableIf< IsInputIterator<TIterator>, Iterator >;

	auto insert(ConstIterator p, InitializerList<Element> l) -> Iterator {
		return insert(p, l.begin(), l.end());
	}

	auto insert_front(Element const & x) -> List & {
		return emplace_front(x);
	}

	auto insert_front(Element && x) -> List & {
		return emplace_front(move(x));
	}

	auto insert_back(Element const & x) -> List & {
		return emplace_back(x);
	}

	auto insert_back(Element && x) -> List & {
		return emplace_back(move(x));
	}
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	auto clear() noexcept -> List & {
		this->m_clear();
	}

	auto erase_front() -> List &;

	auto erase(ConstIterator p) -> Iterator;

	auto erase(ConstIterator f, ConstIterator l) -> Iterator;

	auto erase_back() -> List &;

	auto remove(Element const & x) -> List &;

	template< typename TUnaryPredicate >
	auto remove_if(TUnaryPredicate && predicate) -> List &;
	///@}

	/**
	 * @name splice
	 */
	///@{
	auto splice(ConstIterator p, List & other) -> List &;

	auto splice(ConstIterator p, List & other, ConstIterator i) -> List &;

	auto splice(ConstIterator p, List & other, ConstIterator f, ConstIterator l) -> List &;

	auto splice(ConstIterator p, List && other) -> List & {
		return splice(p, other);
	}

	auto splice(ConstIterator p, List && other, ConstIterator i) -> List & {
		return splice(p, other, i);
	}

	auto splice(ConstIterator p, List && other, ConstIterator f, ConstIterator l) -> List & {
		return splice(p, other, f, l);
	}
	///@}

	/**
	 * @name 杂项
	 */
	///@{
	auto unique() -> List & {
		return unique(Equal<Element>{});
	}

	template< typename TBinaryPredicate >
	auto unique(TBinaryPredicate && predicate) -> List &;

	template< typename TComparator >
	auto merge(List & other, TComparator && comparator) -> List &;

	auto merge(List & other) -> List & {
		return merge(other, Less<Element>{});
	}

	template< typename TComparator >
	auto merge(List && other, TComparator && comparator) -> List & {
		return merge(other, comparator);
	}

	auto merge(List && other) -> List & {
		return merge(other);
	}

	template< typename TComparator >
	auto sort(TComparator && comparator) -> List & {
		m_sort(begin(), end(), this->m_size(), comparator);
		return *this;
	}

	auto sort() -> List & {
		return sort(Less<Element>{});
	}

	void swap(List & other) noexcept(BooleanOr< BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >, IsNothrowSwappable<NodeAllocator> >{}) {
		this->m_swap(other);
	}

	auto reverse() -> List &;
	///@}

private:
	auto m_iterator_at(Size n) -> Iterator {
		return n <= this->m_size() / 2 ? next(begin(), n) : prev(end(), this->m_size() - n);
	}

	void m_move_assign(List & list, BooleanTrue) noexcept(HasNothrowMoveAssignment<Allocator>{}) {
		clear();
		this->m_move_assign_allocator(list);
		splice(end(), list);
	}

	void m_move_assign(List & list, BooleanFalse) {
		if (this->m_allocator() != list.m_allocator()) {
			assign(make_move_iterator(list.begin()), make_move_iterator(list.end()));
		} else {
			m_move_assign(list, BooleanTrue{});
		}
	}

	template< typename TComparator >
	auto m_sort(Iterator f1, Iterator e2, Size n, TComparator & comparator) -> Iterator;

}; // class List< TElement, TAllocator >

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::assign(Element const & x, Size n) -> List & {
	auto i = begin(), e = end();
	for (; n > 0 && i != e; --n, ++i) {
		*i = x;
	}
	if (i == e) {
		insert(e, x, n);
	} else {
		erase(i, e);
	}
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
auto List< TElement, TAllocator >::assign(TIterator f, TIterator l) -> EnableIf< List::IsInputIterator<TIterator>, List & > {
	auto i = begin(), e = end();
	for (; f != l && i != e; ++f, ++i) {
		*i = *f;
	}
	if (i == e) {
		insert(e, f, l);
	} else {
		erase(i, e);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto List< TElement, TAllocator >::emplace(ConstIterator p, TArgs && ... args) -> Iterator {
	using Deleter = AllocatorDestructor<NodeAllocator>;
	auto & allocator = this->m_allocator();
	UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
	node->prev = nullptr;
	NodeAllocatorTraits::construct(allocator, address_of(node->element), forward<TArgs>(args)...);
	this->m_link_nodes(p.m_pointer, node.get(), node.get());
	++this->m_size();
	return Iterator(node.release());
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto List< TElement, TAllocator >::emplace_front(TArgs && ... args) -> List & {
	using Deleter = AllocatorDestructor<NodeAllocator>;
	auto & allocator = this->m_allocator();
	UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
	NodeAllocatorTraits::construct(allocator, address_of(node->element), forward<TArgs>(args)...);
	this->m_insert_nodes_at_front(node.get(), node.get());
	++this->m_size();
	node.release();
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto List< TElement, TAllocator >::emplace_back(TArgs && ... args) -> List & {
	using Deleter = AllocatorDestructor<NodeAllocator>;
	auto & allocator = this->m_allocator();
	UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
	NodeAllocatorTraits::construct(allocator, address_of(node->element), forward<TArgs>(args)...);
	this->m_insert_nodes_at_back(node.get(), node.get());
	++this->m_size();
	node.release();
	return *this;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::insert(ConstIterator p, Element const & x, Size n) -> Iterator {
	auto r = p.m_pointer;
	if (n > 0) {
		using Deleter = AllocatorDestructor<NodeAllocator>;
		auto & allocator = this->m_allocator();
		UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
		node->prev = nullptr;
		NodeAllocatorTraits::construct(allocator, address_of(node->element), x);
		r = node.release();
		auto last = r;
#if !defined(BR_NO_EXCEPTIONS)
		try {
#endif
			for (Size i = 1; i < n; ++i, last = last->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element), x);
				last->next = node.get();
				node->prev = last;
				node.release();
			}
#if !defined(BR_NO_EXCEPTIONS)
		} catch (...) {
			for (; last != nullptr;) {
				auto prev = last->prev;
				NodeAllocatorTraits::destroy(allocator, address_of(last->element));
				NodeAllocatorTraits::deallocate(allocator, last, 1);
				last = prev;
			}
			throw;
		}
#endif
		this->m_link_nodes(p.m_pointer, r, last);
		this->m_size() += n;
	}
	return Iterator(r);
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
auto List< TElement, TAllocator >::insert(ConstIterator p, TIterator f, TIterator l) -> EnableIf< List::IsInputIterator<TIterator>, Iterator > {
	auto r = p.m_pointer;
	if (f != l) {
		using Deleter = AllocatorDestructor<NodeAllocator>;
		Size n = 0;
		auto & allocator = this->m_allocator();
		UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
		node->prev = nullptr;
		NodeAllocatorTraits::construct(allocator, address_of(node->element), *f);
		r = node.release();
		auto last = r;
#if !defined(BR_NO_EXCEPTIONS)
		try {
#endif
			for (++f, (void)++n; f != l; ++f, (void)++n, last = last->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element), *f);
				last->next = node.get();
				node->prev = last;
				node.release();
			}
#if !defined(BR_NO_EXCEPTIONS)
		} catch (...) {
			for (; last != nullptr;) {
				auto prev = last->prev;
				NodeAllocatorTraits::destroy(allocator, address_of(last->element));
				NodeAllocatorTraits::deallocate(allocator, last, 1);
				last = prev;
			}
			throw;
		}
#endif
		this->m_link_nodes(p.m_pointer, r, last);
		this->m_size() += n;
	}
	return Iterator(r);
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::erase_front() -> List & {
	BR_ASSERT(!is_empty());
	auto & allocator = this->m_allocator();
	auto n = this->m_head()->next;
	this->m_unlink_nodes(n, n);
	--this->m_size();
	NodeAllocatorTraits::destroy(allocator, address_of(n->element));
	NodeAllocatorTraits::deallocate(allocator, n, 1);
	return *this;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::erase(ConstIterator p) -> Iterator {
	BR_ASSERT(p != end());
	auto & allocator = this->m_allocator();
	auto n = p.m_pointer;
	auto r = n->next;
	this->m_unlink_nodes(n, n);
	--this->m_size();
	NodeAllocatorTraits::destroy(allocator, address_of(n->element));
	NodeAllocatorTraits::deallocate(allocator, n, 1);
	return Iterator(r);
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::erase(ConstIterator f, ConstIterator l) -> Iterator {
	if (f != l) {
		auto allocator = this->m_allocator();
		this->m_unlink_nodes(f.m_pointer, l.m_pointer->prev);
		while (f != l) {
			auto n = f.m_pointer;
			++f;
			--this->m_size();
			NodeAllocatorTraits::destroy(allocator, address_of(n->element));
			NodeAllocatorTraits::deallocate(allocator, n, 1);
		}
	}
	return Iterator(l.m_pointer);
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::erase_back() -> List & {
	BR_ASSERT(!is_empty());
	auto & allocator = this->m_allocator();
	auto n = this->m_head()->prev;
	this->m_unlink_nodes(n, n);
	--this->m_size();
	NodeAllocatorTraits::destroy(allocator, address_of(n->element));
	NodeAllocatorTraits::deallocate(allocator, n, 1);
	return *this;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::remove(Element const & x) -> List & {
	List deleted_nodes;
	auto e = end();
	for (auto i = cbegin(); i != e;) {
		if (*i == x) {
			auto j = next(i);
			for (; j != e && *j == x; ++j) {}
			deleted_nodes.splice(deleted_nodes.end(), *this, i, j);
			i = j;
			if (i != e) {
				++i;
			}
		} else {
			++i;
		}
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename TUnaryPredicate >
auto List< TElement, TAllocator >::remove_if(TUnaryPredicate && predicate) -> List & {
	List deleted_nodes;
	for (auto i = cbegin(), e = end(); i != e;) {
		if (predicate(*i)) {
			auto j = next(i);
			for (; j != e && predicate(*j); ++j) {}
			deleted_nodes.splice(deleted_nodes.end(), *this, i, j);
			i = j;
			if (i != e) {
				++i;
			}
		} else {
			++i;
		}
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::resize(Size n) -> List & {
	if (n < this->m_size()) {
		erase(m_iterator_at(n), end());
	} else if (n > this->m_size()) {
		using Deleter = AllocatorDestructor<NodeAllocator>;
		n -= this->m_size();
		auto & allocator = this->m_allocator();
		UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
		node->prev = nullptr;
		NodeAllocatorTraits::construct(allocator, address_of(node->element));
		auto first = node.release();
		auto last = first;
#if !defined(BR_NO_EXCEPTIONS)
		try {
#endif
			for (Size i = 1; i < n; ++i, last = last->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element));
				last->next = node.get();
				node->prev = last;
				node.release();
			}
#if !defined(BR_NO_EXCEPTIONS)
		} catch (...) {
			for (; last != nullptr;) {
				auto prev = last->prev;
				NodeAllocatorTraits::destroy(allocator, address_of(last->element));
				NodeAllocatorTraits::deallocate(allocator, last, 1);
				last = prev;
			}
			throw;
		}
#endif
		this->m_insert_nodes_at_back(first, last);
		this->m_size() += n;
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::resize(Size n, Element const & x) -> List & {
	if (n < this->m_size()) {
		erase(m_iterator_at(n), end());
	} else if (n > this->m_size()) {
		using Deleter = AllocatorDestructor<NodeAllocator>;
		n -= this->m_size();
		auto & allocator = this->m_allocator();
		UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
		node->prev = nullptr;
		NodeAllocatorTraits::construct(allocator, address_of(node->element), x);
		auto first = node.release();
		auto last = first;
#if !defined(BR_NO_EXCEPTIONS)
		try {
#endif
			for (Size i = 1; i < n; ++i, last = last->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element), x);
				last->next = node.get();
				node->prev = last;
				node.release();
			}
#if !defined(BR_NO_EXCEPTIONS)
		} catch (...) {
			for (; last != nullptr;) {
				auto prev = last->prev;
				NodeAllocatorTraits::destroy(allocator, address_of(last->element));
				NodeAllocatorTraits::deallocate(allocator, last, 1);
				last = prev;
			}
			throw;
		}
#endif
		this->m_insert_nodes_at_back(first, last);
		this->m_size() += n;
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::splice(ConstIterator p, List & other) -> List & {
	if (!other.is_empty()) {
		auto f = other.m_head()->next;
		auto l = other.m_head()->prev;
		this->m_unlink_nodes(f, l);
		this->m_link_nodes(p.m_pointer, f, l);
		this->m_size() += other.m_size();
		other.m_size() = 0;
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::splice(ConstIterator p, List & other, ConstIterator i) -> List & {
	if (p.m_pointer != i.m_pointer && p.m_pointer != i.m_pointer->next) {
		auto f = i.m_pointer;
		this->m_unlink_nodes(f, f);
		this->m_link_nodes(p.m_pointer, f, f);
		--other.m_size();
		++this->m_size();
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::splice(ConstIterator p, List & other, ConstIterator f, ConstIterator l) -> List & {
	if (f != l) {
		if (this != &other) {
			Size n = distance(f, l);
			other.m_size() -= n;
			this->m_size() += n;
		}
		auto first = f.m_pointer;
		auto last = l.m_pointer->prev;
		this->m_unlink_nodes(first, last);
		this->m_link_nodes(p.m_pointer, first, last);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename TBinaryPredicate >
auto List< TElement, TAllocator >::unique(TBinaryPredicate && predicate) -> List & {
	for (auto i = begin(), e = end(); i != e;) {
		auto j = next(i);
		for (; j != e && predicate(*i, *j); ++j) {}
		if (++i != j) {
			i = erase(i, j);
		}
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename TComparator >
auto List< TElement, TAllocator >::merge(List & other, TComparator && comparator) -> List & {
	if (this != &other) {
		auto f0 = begin(), l0 = end();
		auto f1 = other.begin(), l1 = other.end();
		for (;f0 != l0 && f1 != l1;) {
			if (comparator(*f1, *f0)) {
				Size n = 1;
				auto m1 = next(f1);
				for (; m1 != l1 && comparator(*m1, *f0); ++m1, ++n) {}
				this->m_size() += n;
				other.m_size() -= n;
				auto f = f1.m_pointer, l = m1.m_pointer->prev;
				f1 = m1;
				this->m_unlink_nodes(f, l);
				auto m0 = next(f0);
				this->m_link_nodes(f1.m_pointer, f, l);
				f0 = m0;
			} else {
				++f0;
			}
		}
		splice(l0, other);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename TComparator >
auto List< TElement, TAllocator >::m_sort(Iterator f1, Iterator e2, Size n, TComparator & comparator) -> Iterator {
	switch (n) {
		case 0:
		case 1:
			return f1;
		case 2:
			if (comparator(*--e2, *f1)) {
				auto f = e2.m_pointer;
				this->m_unlink_nodes(f, f);
				this->m_link_nodes(f1.m_pointer, f, f);
				return e2;
			}
			return f1;
	}
	auto half_n = n / 2;
	auto e1 = next(f1, half_n);
	auto r = f1 = m_sort(f1, e1, half_n, comparator);
	auto f2 = e1 = m_sort(e1, e2, n - half_n, comparator);
	if (comparator(*f2, *f1)) {
		auto m2 = next(f2);
		for (; m2 != e2 && comparator(*m2, *f1); ++m2) {
		}
		auto f = f2.m_pointer;
		auto l = m2.m_pointer->prev;
		r = f2;
		e1 = f2 = m2;
		this->m_unlink_nodes(f, l);
		m2 = next(f1);
		this->m_link_nodes(f1.m_pointer, f, l);
		f1 = m2;
	} else {
		++f1;
	}
	while (f1 != e1 && f2 != e2) {
		if (comparator(*f2, *f1)) {
			auto m2 = next(f2);
			for (; m2 != e2 && comparator(*m2, *f1); ++m2) {}
			auto f = f2.m_pointer;
			auto l = m2.m_pointer->prev;
			if (e1 == f2) {
				e1 = m2;
			}
			f2 = m2;
			this->m_unlink_nodes(f, l);
			m2 = next(f1);
			this->m_link_nodes(f1.m_pointer, f, l);
			f1 = m2;
		} else {
			++f1;
		}
	}
	return r;
}

template< typename TElement, typename TAllocator >
auto List< TElement, TAllocator >::reverse() -> List & {
	using BR::swap;
	if (this->m_size() > 1) {
		auto e = end();
		for (auto i = begin(); i != e; i.m_pointer = i.m_pointer->prev) {
			swap(i.m_pointer->prev, i.m_pointer->next);
		}
		swap(e.m_pointer->prev, e.m_pointer->next);
	}
}

} // namespace BR