/**
 * @file
 * @brief ForwardList
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/enumerate/enumerable.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/iterator/move_iterator.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/allocator_destructor.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/remove_const.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Container {

template< typename TElement, typename TAllocator = Allocator<TElement> >
class ForwardList;

template< typename TElement, typename TAllocator >
inline void swap(ForwardList< TElement, TAllocator> & x, ForwardList< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}

} // namespace Container



namespace Detail {
namespace Container {
namespace ForwardList {

template< typename TElement, typename TVoidPointer >
struct Node;

template< typename TNodePointer >
struct BasicNode;

template< typename TElement, typename TVoidPointer >
using HeadNode = BasicNode< typename PointerTraits<TVoidPointer>::template Rebind< Node<TElement, TVoidPointer> > >;

template< typename TNodePointer >
struct BasicNode {
	using NodePointer = TNodePointer;

	BasicNode() : next(nullptr) {
	}

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
class Iterator : public IteratorWithCategory< ReadableTag, WritableTag, ForwardTraversalTag > {
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = BR::PointerTraits<NodePointer>;

	using Node = typename NodePointerTraits::Element;

	template< typename TElement, typename TAllocator >
	friend class BR::ForwardList;

	template< typename TNodeConstPointer >
	friend class ConstIterator;

public:
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
class ConstIterator : public IteratorWithCategory< ReadableTag, ForwardTraversalTag > {
private:
	using NodeConstPointer = TNodeConstPointer;

	using NodeConstPointerTraits = PointerTraits<NodeConstPointer>;

	using Node = RemoveConst< typename NodeConstPointerTraits::Element >;

	using NodePointer = typename NodeConstPointerTraits::template Rebind<Node>;

	template< typename TElement, typename TAllocator >
	friend class BR::ForwardList;

public:
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
		++(*this);
		return *temp;
	}

	auto operator==(ConstIterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(ConstIterator const & y) const -> bool {
		return !(*this == y);
	}

	auto operator==(Iterator<NodePointer> const  & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator<NodePointer> const  & y) const -> bool {
		return !(*this == y);
	}

private:
	explicit ConstIterator(NodeConstPointer pointer) noexcept : m_pointer(pointer) {}

private:
	NodeConstPointer m_pointer;
}; // class ConstIterator<TNodeConstPointer>

template< typename TElement, typename TAllocator >
class Base {
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

	using NodeConstPointer = typename NodeAllocatorTraits::Pointer;

	using HeadNode = ForwardList::HeadNode< Element, VoidPointer >;

	using HeadNodeAllocator = typename AllocatorTraits::template Rebind<HeadNode>;

	using HeadNodeAllocatorTraits = BR::AllocatorTraits<HeadNodeAllocator>;

	using HeadNodePointer = typename HeadNodeAllocatorTraits::Pointer;

	using HeadNodePointerTraits = PointerTraits<HeadNodePointer>;

public:
	using Reference = Element &;

	using ConstReference = Element const &;

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using Size = typename AllocatorTraits::Size;

	using Difference = typename AllocatorTraits::Difference;

	using Iterator = ForwardList::Iterator<NodePointer>;

	using ConstIterator = ForwardList::ConstIterator<NodeConstPointer>;

protected:
	Base() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) : m_impl() {
	}

	explicit Base(Allocator const & allocator) : m_impl(NodeAllocator(allocator)) {
	}

	Base(Base && list) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : m_impl(move(list.m_impl)) {
		list.m_head()->next = nullptr;
	}

	Base(Base && list, Allocator const & allocator) : m_impl(NodeAllocator(allocator)) {
		if (m_allocator() == list.m_allocator()) {
			m_head()->next = list.m_head()->next;
			list.m_head()->next = nullptr;
		}
	}

	~Base() {
		m_clear();
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
		BooleanOr<
			BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<NodeAllocator>
		>{}
	) {
		using BR::swap;
		m_swap_allocator(m_allocator(), list.m_allocator());
		swap(m_head()->next, list.m_head()->next);
	}

private:
	Base(Base const &) = delete;

	auto operator=(Base const &) -> Base & = delete;

	void m_copy_assign_allocator(Base const & list, BooleanTrue) {
		if (m_allocator() != list.m_allocator()) {
			m_clear();
		}
		m_allocator() = list.m_allocator();
	}

	void m_copy_assign_allocator(Base const & list, BooleanFalse) noexcept {
	}

	void m_move_assign_allocator(Base & list, BooleanTrue) noexcept(HasNothrowMoveAssignment<NodeAllocator>{}) {
		m_allocator() = move(list.m_allocator());
	}

	void m_move_assign_allocator(Base & list, BooleanFalse) noexcept {
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y) noexcept(
		BooleanOr<
			BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<NodeAllocator>
		>{}
	) {
		m_swap_allocator(x, y, typename NodeAllocatorTraits::IsPropagateOnContainerSwap{});
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanFalse) noexcept {
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanTrue) noexcept(IsNothrowSwappable<NodeAllocator>{}) {
		using BR::swap;
		swap(x, y);
	}

protected:
	Tuple< NodeAllocator, HeadNode > m_impl;

}; // class Base< TElement, TAllocator >

template< typename TElement, typename TAllocator >
void Base< TElement, TAllocator >::m_clear() noexcept {
	auto & allocator = m_allocator();
	for (auto pointer = m_head()->next; pointer != nullptr;) {
		auto next = pointer->next;
		NodeAllocatorTraits::destroy(allocator, address_of(pointer->element));
		NodeAllocatorTraits::deallocate(allocator, pointer, 1);
		pointer = next;
	}
	m_head()->next = nullptr;
}

} // namespace ForwardList
} // namespace Container
} // namespace Detail

/**
 * @brief 单向链表
 * @tparam TElement 元素类型
 * @tparam TAllocator 分配器类型
 */
template< typename TElement, typename TAllocator >
class ForwardList : private Detail::Container::ForwardList::Base< TElement, TAllocator >,
	public Enumerable<
		ForwardList<TElement, TAllocator>,
		typename Detail::Container::ForwardList::Base< TElement, TAllocator >::Iterator,
		typename Detail::Container::ForwardList::Base< TElement, TAllocator >::ConstIterator
	> {

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
	using Base = Detail::Container::ForwardList::Base< Element, Allocator >;

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
	ForwardList() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) {
	}

	/**
	 * @brief 默认构造函数，指定分配器
	 * @param[in] allocator 分配器
	 */
	explicit ForwardList(Allocator const & allocator) : Base(allocator) {
	}

	/**
	 * @brief 复制构造函数
	 * @param[in] list 源容器
	 */
	ForwardList(ForwardList const & list) : Base(Allocator(NodeAllocatorTraits::select_on_container_copy_construction(list.m_allocator()))) {
		insert_after(chead(), list.begin(), list.end());
	}

	/**
	 * @brief 复制构造函数，指定分配器
	 * @param[in] list 源容器
	 * @param[in] allocator 分配器
	 */
	ForwardList(ForwardList const & list, Allocator const & allocator) : Base(allocator) {
		insert_after(chead(), list.begin(), list.end());
	}

	/**
	 * @brief 移动构造函数
	 * @param[in,out] list 源容器
	 */
	ForwardList(ForwardList && list) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : Base(move(list)) {
	}

	/**
	 * @brief 移动构造函数，指定分配器
	 * @param[in,out] list 源容器
	 * @param[in] allocator 分配器
	 */
	ForwardList(ForwardList && list, Allocator const & allocator) : Base(move(allocator)){
		if (this->m_allocator() != list.m_allocator()) {
			insert_after(chead(), make_move_iterator(list.begin()), make_move_iterator(list.end()));
		}
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以默认值初始化
	 * @param[in] count 容器大小
	 * @param[in] allocator 分配器
	 */
	explicit ForwardList(Size count, Allocator const & allocator = Allocator{}) : Base(allocator){
		m_prepare_after(this->m_head(), count);
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以给定值初始化
	 * @param[in] element 用于初始化的元素
	 * @param[in] size 容器大小
	 * @param[in] allocator 分配器
	 */
	ForwardList(Element const & element, Size size, Allocator const & allocator = Allocator{}) : Base(allocator) {
		insert_after(chead(), element, size);
	}

	/**
	 * @brief 从给定区间中的值构造
	 * @tparam TIterator 迭代器类型
	 * @param[in] f,l 给定区间
	 * @param[in] allocator 分配器
	 */
	template< typename TIterator >
	ForwardList(TIterator f, TIterator l, Allocator const & allocator = Allocator{}, EnableIf< IsInputIterator<TIterator> > * = nullptr) : Base(allocator) {
		insert_after(chead(), f, l);
	}

	/**
	 * @brief 从初始化列表构造
	 * @param[in] list 初始化列表
	 * @param[in] allocator 分配器
	 */
	ForwardList(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(allocator) {
		insert_after(chead(), list.begin(), list.end());
	}
	///@}

	~ForwardList() = default;

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
	///@}

	/**
	 * @name 迭代器
	 */
	///@{
	/**
	 * @brief begin
	 */
	auto begin() noexcept -> Iterator {
		return Iterator(this->m_head()->next);
	}

	/**
	 * @brief begin
	 */
	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(this->m_head()->next);
	}

	/**
	 * @brief end
	 */
	auto end() noexcept -> Iterator {
		return Iterator(nullptr);
	}

	/**
	 * @brief end
	 */
	auto end() const noexcept -> ConstIterator {
		return ConstIterator(nullptr);
	}

	/**
	 * @brief const begin
	 */
	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	/**
	 * @brief const end
	 */
	auto cend() const noexcept -> ConstIterator {
		return end();
	}

	/**
	 * @brief iterator before begin
	 */
	auto head() noexcept -> Iterator {
		return Iterator(this->m_head());
	}

	/**
	 * @brief iterator before begin
	 */
	auto head() const noexcept -> ConstIterator {
		return ConstIterator(this->m_head());
	}

	/**
	 * @brief const head
	 */
	auto chead() const noexcept -> ConstIterator {
		return head();
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
	auto empty() const noexcept -> bool {
		return this->m_head()->next == nullptr;
	}

	/**
	 * @brief max size
	 */
	auto max_size() const noexcept -> Size {
		return NodeAllocatorTraits::max_size(this->m_allocator());
	}

	auto resize(Size n) -> ForwardList &;

	auto resize(Size n, Element const & x) -> ForwardList &;
	///@}

	/**
	 * @name 比较
	 */
	///@{
	auto operator==(ForwardList const & y) const -> bool {
		return equal(begin(), end(), y.begin(), y.end());
	}

	auto operator!=(ForwardList const & y) const -> bool {
		return !operator==(y);
	}

	auto operator<(ForwardList const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}

	auto operator>(ForwardList const & y) const -> bool {
		return y.operator<(*this);
	}

	auto operator<=(ForwardList const & y) const -> bool {
		return !y.operator<(*this);
	}

	auto operator>=(ForwardList const & y) const -> bool {
		return !operator<(y);
	}
	///@}

	/**
	 * @name 赋值操作
	 */
	///@{
	/**
	 * @brief 复制赋值运算
	 * @param[in] list 源容器
	 */
	auto operator=(ForwardList const & list) -> ForwardList & {
		if (this != &list) {
			this->m_copy_assign_allocator(list);
			assign(list.begin(), list.end());
		}
		return *this;
	}

	/**
	 * @brief 移动赋值运算
	 * @param[in,out] list 源容器
	 */
	auto operator=(ForwardList && list) noexcept(
		BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator> >{}
	) -> ForwardList & {
		m_move_assign(list, typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment{});
		return *this;
	}

	/**
	 * @brief 以初始化列表赋值
	 * @param[in] list 初始化列表
	 */
	auto operator=(InitializerList<Element> list) -> ForwardList & {
		return assign(list.begin(), list.end());
	}

	/**
	 * @brief 设置容器内容为 count 个给定元素的副本
	 * @param[in] element 迭代器区间
	 * @param[in] count 迭代器区间
	 */
	auto assign(Element const & element, Size count) -> ForwardList &;

	/**
	 * @brief 以迭代器区间赋值
	 * @param[in] f,l 迭代器区间
	 */
	template< typename TIterator >
	auto assign(TIterator f, TIterator l) -> EnableIf< IsInputIterator<TIterator>, ForwardList & >;
	///@}

	/**
	 * @name 添加性操作
	 */
	///@{
	template< typename ... TArgs >
	auto emplace_front(TArgs && ... args) -> ForwardList &;

	template< typename ... TArgs >
	auto emplace_after(ConstIterator p, TArgs && ... args) -> Iterator;

	auto insert_front(Element const & x) -> ForwardList & {
		return emplace_front(x);
	}

	auto insert_front(Element && x) -> ForwardList & {
		return emplace_front(move(x));
	}

	auto insert_after(ConstIterator p, Element const & x) -> Iterator {
		return emplace_after(p, x);
	}

	auto insert_after(ConstIterator p, Element && x) -> Iterator {
		return emplace_after(p, move(x));
	}

	auto insert_after(ConstIterator p, Element const & x, Size size) -> Iterator;

	template< typename TIterator >
	auto insert_after(ConstIterator p, TIterator f, TIterator l) -> EnableIf< IsInputIterator<TIterator>, Iterator >;

	auto insert_after(ConstIterator p, InitializerList<Element> l) -> Iterator {
		return insert_after(p, l.begin(), l.end());
	}
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	auto clear() noexcept -> ForwardList & {
		this->m_clear();
		return *this;
	}

	auto erase_front() -> ForwardList &;

	auto erase_after(ConstIterator position) -> Iterator;

	auto erase_after(ConstIterator f, ConstIterator l) -> Iterator;

	void remove(Element const & element);

	template< typename TUnaryPredicate >
	void remove_if(TUnaryPredicate && predicate);
	///@}

	/**
	 * @name splice
	 */
	///@{
	void splice_after(ConstIterator p, ForwardList & other);

	void splice_after(ConstIterator p, ForwardList & other, ConstIterator i);

	void splice_after(ConstIterator p, ForwardList & other, ConstIterator f, ConstIterator l);

	void splice_after(ConstIterator p, ForwardList && other) {
		splice_after(p, other);
	}

	void splice_after(ConstIterator p, ForwardList && other, ConstIterator i) {
		splice_after(p, other, i);
	}

	void splice_after(ConstIterator p, ForwardList && other, ConstIterator f, ConstIterator l) {
		splice_after(p, other, f, l);
	}
	///@}

	/**
	 * @name 杂项
	 */
	///@{
	void unique() {
		unique(Equal<Element>{});
	}

	template< typename TBinaryPredicate >
	void unique(TBinaryPredicate && predicate);

	auto merge(ForwardList & list) -> ForwardList & {
		return merge(list, Less<Element>{});
	}

	template< typename TComparator >
	auto merge(ForwardList & list, TComparator && comparator) -> ForwardList & {
		if (this != &list) {
			this->m_head()->next = m_merge(this->m_head()->next, list.m_head()->next, comparator);
			list.m_head()->next = nullptr;
		}
		return *this;
	}

	auto merge(ForwardList && list) -> ForwardList & {
		return merge(list, Less<Element>{});
	}

	template< typename TComparator >
	auto merge(ForwardList && list, TComparator && comparator) -> ForwardList & {
		return merge(list, move(comparator));
	}

	auto sort() -> ForwardList & {
		return sort(Less<Element>{});
	}

	template< typename TComparator >
	auto sort(TComparator && comparator) -> ForwardList & {
		this->m_head()->next = m_sort(this->m_head()->next, distance(begin(), end()), comparator);
		return *this;
	}

	void swap(ForwardList & other) noexcept(
		BooleanOr<
			BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<NodeAllocator>
		>{}
	) {
		this->m_swap(other);
	}

	auto reverse() noexcept -> ForwardList &;
	///@}

private:
	void m_prepare_after(NodePointer position, Size size) {
		if (size > 0) {
			using Deleter = AllocatorDestructor<NodeAllocator>;
			auto & allocator = this->m_allocator();
			UniquePointer< Node, Deleter > node(nullptr, Deleter(allocator, 1));
			for (auto pointer = position; size > 0; --size, pointer = pointer->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element));
				node->next = nullptr;
				pointer->next = node.release();
			}
		}
	}

	void m_move_assign(ForwardList & list, BooleanTrue) noexcept(HasNothrowMoveAssignment<Allocator>{}) {
		clear();
		this->m_move_assign_allocator(list);
		this->m_head()->next = list.m_head()->next;
		list.m_head()->next = nullptr;
	}

	void m_move_assign(ForwardList & list, BooleanFalse) {
		if (this->m_allocator() == list.m_allocator()) {
			m_move_assign(list, BooleanTrue());
		} else {
			assign(make_move_iterator(list.begin()), make_move_iterator(list.end()));
		}
	}

	template< typename TComparator >
	static auto m_merge(NodePointer f1, NodePointer f2, TComparator & comparator) -> NodePointer;

	template< typename TComparator >
	static auto m_sort(NodePointer f1, Difference size, TComparator & comparator) -> NodePointer;

}; // class ForwardList< TElement, TAllocator >

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::assign(Element const & x, Size n) -> ForwardList & {
	auto i = head(), j = next(i), e = end();
	for (; j != e && n > 0; --n, ++i, ++j) {
		*j = x;
	}
	if (j == e) {
		insert_after(i, x, n);
	} else {
		erase_after(i, e);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
auto ForwardList< TElement, TAllocator >::assign(TIterator f, TIterator l) -> EnableIf< ForwardList::IsInputIterator<TIterator>, ForwardList & > {
	auto i = head(), j = next(i), e = end();
	for (; j != e && f != l; ++i, (void)++j, ++f) {
		*j = *f;
	}
	if (j == e) {
		insert_after(i, f, l);
	} else {
		erase_after(i, e);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto ForwardList< TElement, TAllocator >::emplace_front(TArgs && ... args) -> ForwardList & {
	using Deleter = AllocatorDestructor<NodeAllocator>;
	auto & allocator = this->m_allocator();
	UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
	NodeAllocatorTraits::construct(allocator, address_of(node->element), forward<TArgs>(args)...);
	node->next = this->m_head()->next;
	this->m_head()->next = node.release();
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto ForwardList< TElement, TAllocator >::emplace_after(ConstIterator p, TArgs && ... args) -> Iterator {
	using Deleter = AllocatorDestructor<NodeAllocator>;
	auto & allocator = this->m_allocator();
	UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
	NodeAllocatorTraits::construct(allocator, address_of(node->element), forward<TArgs>(args)...);
	auto const pointer = p.m_pointer;
	node->next = pointer->next;
	pointer->next = node.release();
	return Iterator(pointer->next);
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::insert_after(ConstIterator p, Element const & element, Size size) -> Iterator {
	auto r = p.m_pointer;
	if (size > 0) {
		using Deleter = AllocatorDestructor<NodeAllocator>;
		auto & allocator = this->m_allocator();
		UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
		NodeAllocatorTraits::construct(allocator, address_of(node->element), element);
		auto first = node.release();
		auto last = first;
		try {
			for (; size-- > 0; last = last->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element), element);
				last->next = node.release();
			}
		} catch (...) {
			while (first != nullptr) {
				auto next = first->next;
				NodeAllocatorTraits::destroy(allocator, address_of((first->element)));
				NodeAllocatorTraits::deallocate(allocator, first, 1);
				first = next;
			}
			throw;
		}
		last->next = r->next;
		r->next = first;
		r = last;
	}
	return Iterator(r);
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
auto ForwardList< TElement, TAllocator >::insert_after(ConstIterator p, TIterator f, TIterator l) -> EnableIf< ForwardList::IsInputIterator<TIterator>, Iterator > {
	auto r = p.m_pointer;
	if (f != l) {
		using Deleter = AllocatorDestructor<NodeAllocator>;
		auto & allocator = this->m_allocator();
		UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
		NodeAllocatorTraits::construct(allocator, address_of(node->element), *f);
		auto first = node.release(), last = first;
		try {
			for (++f; f != l; ++f, (void)(last = last->next)) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element), *f);
				last->next = node.release();
			}
		} catch (...) {
			while (first != nullptr) {
				auto next = first->next;
				NodeAllocatorTraits::destroy(allocator, address_of((first->element)));
				NodeAllocatorTraits::deallocate(allocator, first, 1);
				first = next;
			}
			throw;
		}
		last->next = r->next;
		r->next = first;
		r = last;
	}
	return Iterator(r);
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::erase_front() -> ForwardList & {
	auto & allocator = this->m_allocator();
	auto p = this->m_head()->next;
	this->m_head()->next = p->next;
	NodeAllocatorTraits::destroy(allocator, address_of(p->element));
	NodeAllocatorTraits::deallocate(allocator, p, 1);
	return *this;
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::erase_after(ConstIterator p) -> Iterator {
	auto r = p.m_pointer;
	auto n = r->next;
	r->next = n->next;
	auto & allocator = this->m_allocator();
	NodeAllocatorTraits::destroy(allocator, address_of((n->element)));
	NodeAllocatorTraits::deallocate(allocator, n, 1);
	return Iterator(r->next);
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::erase_after(ConstIterator f, ConstIterator l) -> Iterator {
	auto e = l.m_pointer;
	if (f != l) {
		auto p = f.m_pointer, n = p->next;
		if (n != e) {
			p->next = e;
			auto & allocator = this->m_allocator();
			do {
				p = n->next;
				NodeAllocatorTraits::destroy(allocator, address_of((n->element)));
				NodeAllocatorTraits::deallocate(allocator, n, 1);
				n = p;
			} while (n != e);
		}
	}
	return Iterator(e);
}

template< typename TElement, typename TAllocator >
void ForwardList< TElement, TAllocator >::remove(Element const & x) {
	for (auto i = head(), e = end(); i.m_pointer->next != nullptr;) {
		if (i.m_pointer->next->element == x) {
			auto j = next(i, 2);
			for (; j != e && *j == x; ++j) {}
			erase_after(i, j);
			if (j == e) {
				break;
			}
			i = j;
		} else {
			++i;
		}
	}
}

template< typename TElement, typename TAllocator >
template< typename TUnaryPredicate>
void ForwardList< TElement, TAllocator >::remove_if(TUnaryPredicate && predicate) {
	for (auto i = head(), e = end(); i.m_pointer->next != nullptr;) {
		if (predicate(i.m_pointer->next->element)) {
			auto j = next(i, 2);
			for (; j != e && predicate(*j); ++j) {}
			erase_after(i, j);
			if (j == e) {
				break;
			}
			i = j;
		} else {
			++i;
		}
	}
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::resize(Size n) -> ForwardList & {
	Size c = 0;
	auto p = head(), i = begin(), e = end();
	for (; i != e && c < n; ++p, ++i, ++c) {}
	if (i != e) {
		erase_after(p, e);
	} else {
		m_prepare_after(i.m_pointer, n - c);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::resize(Size n, Element const & x) -> ForwardList & {
	Size c = 0;
	auto p = head(), i = begin(), e = end();
	for (; i != e && c < n; ++p, ++i, ++c) {}
	if (i != e) {
		erase_after(p, e);
	} else {
		n -= c;
		if (n > 0) {
			using Deleter = AllocatorDestructor<NodeAllocator>;
			auto & allocator = this->m_allocator();
			UniquePointer< Node, Deleter > node(nullptr, Deleter(allocator, 1));
			for (auto pointer = i.m_pointer; n > 0; --n, pointer = pointer->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element), x);
				node->next = nullptr;
				pointer->next = node.release();
			}
		}
	}
	return *this;
}

template< typename TElement, typename TAllocator >
void ForwardList< TElement, TAllocator >::splice_after(ConstIterator p, ForwardList & other) {
	if (!other.empty()) {
		if (p.m_pointer->next != nullptr) {
			auto i = other.chead();
			for (; i.m_pointer->next != nullptr; ++i) {}
			i.m_pointer->next = p.m_pointer->next;
		}
		p.m_pointer->next = other.m_head()->next;
		other.m_head()->next = nullptr;
	}
}

template< typename TElement, typename TAllocator >
void ForwardList< TElement, TAllocator >::splice_after(ConstIterator p, ForwardList & other, ConstIterator i) {
	auto j = next(i);
	if (p != i && p != j) {
		i.m_pointer->next = j.m_pointer->next;
		j.m_pointer->next = p.m_pointer->next;
		p.m_pointer->next = j.m_pointer;
	}
}

template< typename TElement, typename TAllocator >
void ForwardList< TElement, TAllocator >::splice_after(ConstIterator p, ForwardList & other, ConstIterator f, ConstIterator l) {
	if (f != l && p != f) {
		auto i = f;
		for (; i.m_pointer->next != l.m_pointer; ++i) {}
		if (f != i) {
			i.m_pointer->next = p.m_pointer->next;
			p.m_pointer->next = f.m_pointer->next;
			f.m_pointer->next = l.m_pointer;
		}
	}
}

template< typename TElement, typename TAllocator >
template< typename TBinaryPredicate>
void ForwardList< TElement, TAllocator >::unique(TBinaryPredicate && predicate) {
	for (auto i = begin(), e = end(); i != e;) {
		auto j = next(i);
		for (; j != e && predicate(*i, *j); ++j) {}
		if (i.m_pointer->next != j.m_pointer) {
			erase_after(i, j);
		}
		i = j;
	}
}

template< typename TElement, typename TAllocator >
template< typename TComparator >
auto ForwardList< TElement, TAllocator >::m_merge(NodePointer f1, NodePointer f2, TComparator & comparator) -> NodePointer {
	if (f1 == nullptr) {
		return f2;
	}
	if (f2 == nullptr) {
		return f1;
	}
	NodePointer r;
	if (comparator(f2->element, f1->element)) {
		auto t = f2;
		for (; t->next != nullptr && comparator(t->next->element, f1->element); t = t->next) {}
		r = f2;
		f2 = t->next;
		t->next = f1;
	} else {
		r = f1;
	}
	auto p = f1;
	for (f1 = f1->next; f1 != nullptr && f2 != nullptr; f1 = f1->next) {
		if (comparator(f2->element, f1->element)) {
			NodePointer t = f2;
			for (; t->next != nullptr && comparator(t->next->element, f1->element); t = t->next) {}
			p->next = f2;
			f2 = t->next;
			t->next = f1;
		}
		p = f1;
	}
	if (f2 != nullptr) {
		p->next = f2;
	}
	return r;
}

template< typename TElement, typename TAllocator >
template< typename TComparator >
auto ForwardList< TElement, TAllocator >::m_sort(NodePointer f1, Difference size, TComparator & comparator) -> NodePointer {
	switch (size) {
		case 0:
		case 1:
			return f1;
		case 2:
			if (comparator(f1->next->element, f1->element)) {
				NodePointer t = f1->next;
				t->next = f1;
				f1->next = nullptr;
				f1 = t;
			}
			return f1;
		default:
			break;
	}
	auto sz1 = size / 2;
	auto sz2 = size - sz1;
	auto t = next(Iterator(f1), sz1 - 1).m_pointer;
	NodePointer f2 = t->next;
	t->next = nullptr;
	return m_merge(m_sort(f1, sz1, comparator), m_sort(f2, sz2, comparator), comparator);
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::reverse() noexcept -> ForwardList & {
	auto p = this->m_head()->next;
	if (p != nullptr) {
		auto f = p->next;
		for (p->next = nullptr; f != nullptr;) {
			auto t = f->next;
			f->next = p;
			p = f;
			f = t;
		}
		this->m_head()->next = p;
	}
	return *this;
}

} // namespace BR