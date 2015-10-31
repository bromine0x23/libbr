/**
 * @file
 * @brief ForwardList
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/container/compressed_pair.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/move_iterator.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_destructor.hpp>
#include <libbr/memory/unique_pointer.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_const.hpp>
#include <libbr/type_traits/allocator_traits.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assign.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/type_traits/pointer_traits.hpp>
#include <libbr/utility/enumerator.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TElement, typename TAllocator >
class ForwardList;

namespace Detail {
namespace Container {
namespace ForwardList {

template< typename TNodePointer >
struct BasicNode {
	using NodePointer = TNodePointer;

	BasicNode() : next(nullptr) {
	}

	NodePointer next;
};

template< typename TElement, typename TVoidPointer >
struct Node;

template< typename TElement, typename TVoidPointer >
using HeadNode = BasicNode< typename PointerTraits<TVoidPointer>::template Rebind< Node<TElement, TVoidPointer> > >;

template< typename TElement, typename TVoidPointer >
struct Node : public HeadNode< TElement, TVoidPointer > {
	using Element = TElement;

	Element element;
};

template< typename TNodeConstPointer >
class ConstIterator;

template< typename TNodePointer >
class Iterator : public BasicIterator {
private:
	using NodePointer = TNodePointer;

	using PointerTraits = BR::PointerTraits<NodePointer>;

	using Node = typename PointerTraits::Element;

	template< typename TElement, typename TAllocator >
	friend class BR::ForwardList;

	template< typename TNodeConstPointer >
	friend class ConstIterator;

public:
	using Category = ForwardIteratorTag;

	using Element = typename Node::Element;

	using Pointer = typename PointerTraits::template Rebind<Element>;

	using Reference = Element &;

	using Difference = typename PointerTraits::Difference;

	Iterator() noexcept : m_pointer(nullptr) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return PointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> Iterator & {
		m_pointer = m_pointer->next;
		return *this;
	}

	auto operator++(int) -> Iterator & {
		Iterator temp(*this);
		++(*this);
		return *temp;
	}

	auto operator==(Iterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator const & y) const -> bool {
		return !(*this == y);
	}

private:
	explicit Iterator(NodePointer pointer) noexcept : m_pointer(pointer) {
	}

private:
	TNodePointer m_pointer;
}; // class Iterator<TNodePointer>

template< typename TNodeConstPointer >
class ConstIterator : BasicIterator {
private:
	using NodeConstPointer = TNodeConstPointer;

	using PointerTraits = BR::PointerTraits<NodeConstPointer>;

	using Node = RemoveConst< typename PointerTraits::Element >;

	using NodePointer = typename PointerTraits::template Rebind<Node>;

	template< typename TElement, typename TAllocator >
	friend class BR::ForwardList;

public:
	using Category = ForwardIteratorTag;

	using Element = typename Node::Element;

	using Pointer = typename PointerTraits::template Rebind<Element const>;

	using Reference = Element const &;

	using Difference = typename PointerTraits::Difference;

	ConstIterator() noexcept : m_pointer(nullptr) {
	}

	ConstIterator(Iterator<NodePointer> iterator) noexcept : m_pointer(iterator.m_pointer) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return PointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> ConstIterator & {
		m_pointer = m_pointer->next;
		return *this;
	}

	auto operator++(int) -> ConstIterator & {
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

	auto operator==(Iterator<TNodeConstPointer> const  & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator<TNodeConstPointer> const  & y) const -> bool {
		return !(*this == y);
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

	using Node = ForwardList::Node< Element, VoidPointer >;

	using NodeAllocator = typename AllocatorTraits::template Rebind<Node>;

	using NodeAllocatorTraits = BR::AllocatorTraits<NodeAllocator>;

	using NodePointer = typename NodeAllocatorTraits::Pointer;

	using NodeConstPointer = typename NodeAllocatorTraits::Pointer;

	using HeadNode = ForwardList::HeadNode< Element, VoidPointer >;

	using HeadNodeAllocator = typename AllocatorTraits::template Rebind<HeadNode>;

	using HeadNodeAllocatorTraits = BR::AllocatorTraits<HeadNodeAllocator>;

	using HeadNodePointer = typename HeadNodeAllocatorTraits::Pointer;

	using Iterator = ForwardList::Iterator<NodePointer>;

	using ConstIterator = ForwardList::ConstIterator<NodePointer>;

public:
	Base(Base && list) noexcept(HasNothrowMoveConstructor<NodeAllocator>()()) : m_impl(move(list.m_impl)) {
		list.m_head()->next = nullptr;
	}

	Base(Base && list, Allocator const & allocator) : m_impl(HeadNode(), NodeAllocator(allocator)) {
		if (m_allocator() == list.m_allocator()) {
			m_head()->next = list.m_head()->next;
			list.m_head()->next = nullptr;
		}
	}

	~Base() {
		m_clear();
	}

	void swap(Base & list) noexcept(
		BooleanOr<
			BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<NodeAllocator>
		>()()
	) {
		using BR::swap;
		m_swap_allocator(m_allocator(), list.m_allocator());
		swap(m_head()->next, list.m_head()->next);
	}

protected:

	Base() noexcept(HasNothrowDefaultConstructor<NodeAllocator>()) : m_impl(HeadNode()) {
	}

	Base(Allocator const & allocator) : m_impl(HeadNode(), NodeAllocator(allocator)) {
	}

	auto m_head() noexcept -> NodePointer {
		return static_cast<NodePointer>(PointerTraits<HeadNodePointer>::make_pointer(m_impl.first()));
	}

	auto m_head() const noexcept -> NodeConstPointer {
		return static_cast<NodeConstPointer>(PointerTraits<HeadNodePointer>::make_pointer(const_cast<HeadNode &>(m_impl.first())));
	}

	auto m_allocator() noexcept -> NodeAllocator & {
		return m_impl.second();
	}

	auto m_allocator() const noexcept -> NodeAllocator const & {
		return m_impl.second();
	}

	void m_copy_assign_allocate(Base const & list) {
		m_copy_assign_allocate(list, NodeAllocatorTraits::IsPropagateOnContainerCopyAssignment());
	}

	void m_move_assign_allocate(Base & list) noexcept(
		BooleanOr<
			BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment >,
			HasNothrowMoveAssign<NodeAllocator>
		>()
	) {
		m_move_assign_allocate(list, NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment());
	}

	void m_clear() noexcept {
		auto & allocator = m_allocator();
		for (auto pointer = m_head()->next; pointer != nullptr;) {
			auto next = pointer->next;
			NodeAllocatorTraits::destroy(allocator, address_of(pointer->element));
			NodeAllocatorTraits::deallocate(allocator, pointer, 1);
			pointer = next;
		}
		m_head()->next = nullptr;
	}

private:
	Base(Base const &) = delete;

	auto operator=(Base const &) -> Base & = delete;

	void m_copy_assign_allocate(Base const & list, BooleanFalse _dummy) {
	}

	void m_copy_assign_allocate(Base const & list, BooleanTrue _dummy) {
		if (m_allocator() != list.m_allocator()) {
			m_clear();
		}
		m_allocator() = list.m_allocator();
	}

	void m_move_assign_allocate(Base & list, BooleanFalse _dummy) noexcept {
	}

	void m_move_assign_allocate(Base & list, BooleanTrue _dummy) noexcept(HasNothrowMoveAssign<NodeAllocator>()) {
		m_allocator() = move(list.m_allocator());
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y) noexcept(
		BooleanOr<
			BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<NodeAllocator>
		>()
	) {
		swap_allocator(x, y, NodeAllocatorTraits::IsPropagateOnContainerSwap());
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanFalse _dummy) noexcept {
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanTrue _dummy) noexcept(IsNothrowSwappable<NodeAllocator>()) {
		using BR::swap;
		swap(x, y);
	}

protected:
	CompressedPair< HeadNode, NodeAllocator > m_impl;

}; // class Base< TElement, TAllocator >

} // namespace ForwardList
} // namespace Container
} // namespace Detail

/**
 * @brief 单向列表
 * @tparam TElement 元素类型
 * @tparam TAllocator 分配器类型
 */
template< typename TElement, typename TAllocator = Allocator<TElement> >
class ForwardList : private Detail::Container::ForwardList::Base< TElement, TAllocator > {

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
	using Base = Detail::Container::ForwardList::Base< TElement, TAllocator >;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using Node = typename Base::Node;

	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

	using NodePointer = typename Base::NodePointer;

public:
	/**
	 * @brief Reference
	 */
	using Reference = Element &;

	/**
	 * @brief ConstReference
	 */
	using ConstReference = Element const &;

	/**
	 * @brief Pointer
	 */
	using Pointer = typename AllocatorTraits::Pointer;

	/**
	 * @brief ConstPointer
	 */
	using ConstPointer = typename AllocatorTraits::ConstPointer;

	/**
	 * @brief Difference
	 */
	using Difference = typename AllocatorTraits::Difference;

	/**
	 * @brief Size
	 */
	using Size = typename AllocatorTraits::Size;

	/**
	 * @brief Iterator
	 */
	using Iterator = typename Base::Iterator;

	/**
	 * @brief ConstIterator
	 */
	using ConstIterator = typename Base::ConstIterator;

	/**
	 * @name 构造
	 */
	///@{
	/**
	 * @brief 默认构造函数
	 */
	ForwardList() = default;

	/**
	 * @brief 默认构造函数，指定分配器
	 * @param[in] allocator 分配器
	 */
	explicit ForwardList(Allocator const & allocator) : Base(allocator) {
	};

	/**
	 * @brief 复制构造函数
	 * @param[in] list 源容器
	 */
	ForwardList(ForwardList const & list) : Base(Allocator(NodeAllocatorTraits::select_on_container_copy_construction(list.m_allocator()))) {
		insert_after(chead(), list.each());
	}

	/**
	 * @brief 复制构造函数，指定分配器
	 * @param[in] list 源容器
	 * @param[in] allocator 分配器
	 */
	ForwardList(ForwardList const & list, Allocator const & allocator) : Base(allocator) {
		insert_after(chead(), list.each());
	}

	/**
	 * @brief 移动构造函数
	 * @param[in,out] list 源容器
	 */
	ForwardList(ForwardList && list) noexcept(HasNothrowMoveConstructor<Base>()) : Base(move(list)) {
	}

	/**
	 * @brief 移动构造函数，指定分配器
	 * @param[in,out] list 源容器
	 * @param[in] allocator 分配器
	 */
	ForwardList(ForwardList && list, Allocator const & allocator) : Base(move(allocator)){
		if (Base::m_allocator() != list.m_allocator()) {
			insert_after(chead(), make_enumerator(make_move_iterator(list.begin()), make_move_iterator(list.end())));
		}
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以默认值初始化
	 * @param[in] count 容器大小
	 */
	explicit ForwardList(Size count) {
		m_prepare_after(Base::m_head(), count);
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以默认值初始化，指定分配器
	 * @param[in] count 容器大小
	 * @param[in] allocator 分配器
	 */
	explicit ForwardList(Size count, Allocator const & allocator) : Base(allocator) {
		m_prepare_after(Base::m_head(), count);
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以给定值初始化
	 * @param[in] element 用于初始化的元素
	 * @param[in] count 容器大小
	 */
	ForwardList(Element const & element, Size size) {
		insert_after(chead(), element, size);
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以给定值初始化，指定分配器
	 * @param[in] element 用于初始化的元素
	 * @param[in] count 容器大小
	 * @param[in] allocator 分配器
	 */
	ForwardList(Element const & element, Size size, Allocator const & allocator) : Base(allocator) {
		insert_after(chead(), element, size);
	}

	/**
	 * @brief 从给定区间中的值构造
	 * @tparam TInputIterator 迭代器类型
	 * @param[in] enumerator 给定区间
	 */
	template< typename TInputIterator, typename _TDummy = EnableIf< typename IteratorTraits<TInputIterator>::IsInputIterator > >
	ForwardList(Enumerator<TInputIterator> enumerator) {
		insert_after(chead(), enumerator);
	}

	/**
	 * @brief 从给定区间中的值构造，指定分配器
	 * @tparam TInputIterator 迭代器类型
	 * @param[in] enumerator 给定区间
	 * @param[in] allocator 分配器
	 */
	template< typename TInputIterator, typename _TDummy = EnableIf< typename IteratorTraits<TInputIterator>::IsInputIterator > >
	ForwardList(Enumerator<TInputIterator> enumerator, Allocator const & allocator) : Base(allocator) {
		insert_after(chead(), enumerator);
	}

	/**
	 * @brief 从初始化列表构造
	 * @param[in] list 初始化列表
	 */
	ForwardList(InitializerList<Element> list) {
		insert_after(chead(), list.each());
	}

	/**
	 * @brief 从初始化列表构造，指定分配器
	 * @param[in] list 初始化列表
	 * @param[in] allocator 分配器
	 */
	ForwardList(InitializerList<Element> list, Allocator const & allocator) : Base(allocator) {
		insert_after(chead(), list.each());
	}
	///@}

	/**
	 * @brief 析构函数
	 */
	~ForwardList() = default;

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
			Base::m_copy_assign_allocate(list);
			assign(list.begin(), list.end());
		}
		return *this;
	}

	/**
	 * @brief 移动赋值运算
	 * @param[in,out] list 源容器
	 */
	auto operator=(ForwardList && list) noexcept(
		BooleanAnd<
			typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment,
			HasNothrowMoveAssign<Allocator>
		>()
	) -> ForwardList & {
		m_move_assign(list, NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment());
		return *this;
	}

	/**
	 * @brief 以迭代器区间赋值
	 * @param[in] enumerator 迭代器区间
	 * @see assign(Enumerator<TInputIterator> enumerator)
	 */
	template< typename TInputIterator, typename _TDummy = EnableIf< typename IteratorTraits<TInputIterator>::IsInputIterator > >
	auto operator=(Enumerator<TInputIterator> enumerator) -> ForwardList & {
		return assign(enumerator);
	}

	/**
	 * @brief 以初始化列表赋值
	 * @param[in] list 初始化列表
	 * @see assign(InitializerList<Element> list)
	 */
	auto operator=(InitializerList<Element> list) -> ForwardList & {
		return assign(list);
	}

	/**
	 * @brief 设置容器内容为 count 个给定元素的副本
	 * @param[in] element 迭代器区间
	 * @param[in] count 迭代器区间
	 */
	auto assign(Element const & element, Size count) -> ForwardList &;

	/**
	 * @brief 以迭代器区间赋值
	 * @param[in] enumerator 迭代器区间
	 */
	template< typename TInputIterator, typename _TDummy = EnableIf< typename IteratorTraits<TInputIterator>::IsInputIterator > >
	auto assign(Enumerator<TInputIterator> enumerator) -> ForwardList &;

	/**
	 * @brief 以初始化列表赋值
	 * @param[in] list 初始化列表
	 */
	auto assign(InitializerList<Element> list) -> ForwardList & {
		return assign(list.each());
	}
	///@}

	auto get_allocator() const noexcept -> Allocator {
		return Allocator(Base::m_allocator());
	}

	/**
	 * @name 迭代器
	 */
	///@{
	/**
	 * @brief begin
	 */
	auto begin() noexcept -> Iterator {
		return Iterator(Base::m_head()->next);
	}

	/**
	 * @brief begin
	 */
	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(Base::m_head()->next);
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
		return Iterator(Base::m_head());
	}

	/**
	 * @brief iterator before begin
	 */
	auto head() const noexcept -> ConstIterator {
		return ConstIterator(Base::m_head());
	}

	/**
	 * @brief const head
	 */
	auto chead() const noexcept -> ConstIterator {
		return head();
	}

	/**
	 * @brief each
	*/
	auto each() noexcept -> Enumerator<Iterator> {
		return make_enumerator(begin(), end());
	}

	template< typename TFunctor >
	auto each(TFunctor functor) noexcept -> ForwardList {
		each().each(functor);
		return *this;
	}

	/**
	 * @brief each
	*/
	auto each() const noexcept -> Enumerator<ConstIterator > {
		return make_enumerator(begin(), end());
	}

	template< typename TFunctor >
	auto each(TFunctor functor) const noexcept -> ForwardList {
		each().each(functor);
		return *this;
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
		return Base::m_head()->next == nullptr;
	}

	/**
	 * @brief max size
	 */
	auto max_size() const noexcept -> Size {
		return IntegerTraits<Size>::max();
	}
	///@}

	auto front() -> Reference {
		return Base::m_head()->next->value;
	}

	auto front() const -> ConstReference {
		return Base::m_head()->next->value;
	}

	template< typename ... TArgs >
	auto emplace_first(TArgs && ... args) -> ForwardList &;

	auto add_first(Element const & element) -> ForwardList & {
		return emplace_first(element);
	}

	auto add_first(Element && element) -> ForwardList & {
		return emplace_first(move(element));
	}

	auto remove_first() -> ForwardList &;

	template< typename ... TArgs >
	auto emplace_after(ConstIterator position, TArgs && ... args) -> Iterator ;

	auto insert_after(ConstIterator position, Element const & element) -> Iterator {
		return emplace_after(position, element);
	}

	auto insert_after(ConstIterator position, Element && element) -> Iterator {
		return emplace_after(position, move(element));
	}

	auto insert_after(ConstIterator position, Element const & element, Size size) -> Iterator;

	template< typename TInputIterator, typename _TDummy = EnableIf< typename IteratorTraits<TInputIterator>::IsInputIterator > >
	auto insert_after(ConstIterator position, Enumerator<TInputIterator> enumerator) -> Iterator;

	auto erase_after(ConstIterator position) -> Iterator;

	auto erase_after(Enumerator<ConstIterator> enumerator) -> Iterator;

	void swap(ForwardList & list) noexcept(noexcept(Base::swap(list))) {
		Base::swap(list);
	}

	auto resize(Size size) -> ForwardList &;

	auto resize(Size size, Element const & element) -> ForwardList &;

	auto clear() noexcept -> ForwardList & {
		Base::clear();
		return *this;
	}

	void splice_after(ConstIterator p, ForwardList & list);

	void splice_after(ConstIterator p, ForwardList & list, ConstIterator i);

	void splice_after(ConstIterator p, ForwardList & list, Enumerator<ConstIterator> e);

	void splice_after(ConstIterator p, ForwardList && list) {
		splice_after(p, list);
	}

	void splice_after(ConstIterator p, ForwardList && list, ConstIterator i) {
		splice_after(p, list, i);
	}

	void splice_after(ConstIterator p, ForwardList && list, Enumerator<ConstIterator> e) {
		splice_after(p, list, e);
	}

	void remove(Element const & element) {
		remove_if(Equal<Element>());
	}

	template< typename TUnaryPredicate >
	void remove_if(TUnaryPredicate predicate);

	void unique() {
		unique(Equal<Element>());
	}

	template< typename TBinaryPredicate >
	void unique(TBinaryPredicate predicate);

	auto merge(ForwardList & list) -> ForwardList & {
		return merge(list, Less<Element>());
	}

	template< typename TComparator >
	auto merge(ForwardList & list, TComparator comparator) -> ForwardList & {
		if (this != &list) {
			Base::m_head()->next = m_merge(Base::m_head()->next, list.m_head()->next, comparator);
			list.m_head()->next = nullptr;
		}
		return *this;
	}

	auto merge(ForwardList && list) -> ForwardList & {
		return merge(list, Less<Element>());
	}

	template< typename TComparator >
	auto merge(ForwardList && list, TComparator comparator) -> ForwardList & {
		return merge(list, move(comparator));
	}

	auto sort() -> ForwardList & {
		return sort(Less<Element>());
	}

	template< typename TComparator >
	auto sort(TComparator comparator) -> ForwardList & {
		Base::m_head()->next = m_sort(Base::m_head()->next, distance(begin(), end()), comparator);
		return *this;
	}

	auto reverse() noexcept -> ForwardList & {
		auto p = Base::m_head()->next;
		if (p != nullptr) {
			auto f = p->next;
			for (p->next = nullptr; f != nullptr;) {
				auto t = f->next;
				f->next = p;
				p = f;
				f = t;
			}
			Base::m_head()->next = p;
		}
		return *this;
	}

	auto operator==(ForwardList const & y) const -> bool {
		auto ix = begin(), ex = end(), iy = y.begin(), ey = y.end();
		for (; ix != ex && iy != ey; ++ix, ++iy) {
			if (!(*ix == *iy)) {
				return false;
			}
		}
		return (ix == ex) == (iy == ey);
	}

	auto operator!=(ForwardList const & y) const -> bool {
		return !(*this == y);
	}

	inline auto operator<(ForwardList const & y) const -> bool {
		return lexicographical_compare(each(), y.each());
	}

	inline auto operator>(ForwardList const & y) const -> bool {
		return y < *this;
	}

	inline auto operator>=(ForwardList const & y) const -> bool {
		return !(*this < y);
	}

	inline auto operator<=(ForwardList const & y) const -> bool {
		return !(y < *this);
	}

private:
	void m_prepare_after(NodePointer position, Size size) {
		if (size > 0) {
			using Deleter = AllocatorDestructor<NodeAllocator>;
			auto & allocator = Base::m_allocator();
			UniquePointer< Node, Deleter > node(nullptr, Deleter(allocator, 1));
			for (auto pointer = position; size > 0; --size, pointer = pointer->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element));
				node->next = nullptr;
				pointer->next = node.release();
			}
		}
	}

	void m_move_assign(ForwardList & list, BooleanTrue _dummy) noexcept(HasNothrowMoveAssign<Allocator>()) {
		clear();
		Base::m_move_assign_allocate(list);
		Base::m_head()->next = list.m_head()->next;
		list.m_head()->next = nullptr;
	}

	void m_move_assign(ForwardList & list, BooleanFalse _dummy) {
		if (Base::m_allocator() == list.m_allocator()) {
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
auto ForwardList< TElement, TAllocator >::assign(Element const & element, Size count) -> ForwardList & {
	auto i = head(), j = next(i), e = end();
	for (; j != e && count > 0; --count, ++i, ++j) {
		*j = element;
	}
	if (j == e) {
		insert_after(i, count, element);
	} else {
		erase_after(i, e);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename TInputIterator, typename _TDummy >
auto ForwardList< TElement, TAllocator >::assign(Enumerator<TInputIterator> enumerator) -> ForwardList & {
	auto f = enumerator.begin(), l = enumerator.end();
	auto i = head(), j = next(i), e = end();
	for (; j != e && f != l; ++i, (void)++j, ++f) {
		*j = *f;
	}
	if (j == e) {
		insert_after(i, make_enumerator(f, l));
	} else {
		erase_after(i, e);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto ForwardList< TElement, TAllocator >::emplace_first(TArgs && ... args) -> ForwardList & {
	using Deleter = AllocatorDestructor<NodeAllocator>;
	auto & allocator = Base::m_allocator();
	UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
	NodeAllocatorTraits::construct(allocator, address_of(node->element), forward<TArgs>(args)...);
	node->next = Base::m_head()->next;
	Base::m_head()->next = node.release();
	return *this;
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::remove_first() -> ForwardList & {
	auto & allocator = Base::m_allocator();
	auto pointer = Base::m_head()->next;
	Base::m_head()->next = pointer->next;
	NodeAllocatorTraits::destroy(allocator, address_of(pointer->element));
	NodeAllocatorTraits::deallocate(allocator, pointer, 1);
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto ForwardList< TElement, TAllocator >::emplace_after(ConstIterator position, TArgs && ... args) -> Iterator {
	using Deleter = AllocatorDestructor<NodeAllocator>;
	auto & allocator = Base::m_allocator();
	UniquePointer< Node, Deleter > node(NodeAllocatorTraits::allocate(allocator, 1), Deleter(allocator, 1));
	NodeAllocatorTraits::construct(allocator, address_of(node->element), forward<TArgs>(args)...);
	auto const pointer = position.m_pointer;
	node->next = pointer->next;
	pointer->next = node.release();
	return Iterator(pointer->next);
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::insert_after(ConstIterator position, Element const & element, Size size) -> Iterator {
	auto r = position.m_pointer;
	if (size > 0) {
		using Deleter = AllocatorDestructor<NodeAllocator>;
		auto & allocator = Base::m_allocator();
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
template< typename TInputIterator, typename _TDummy >
auto ForwardList< TElement, TAllocator >::insert_after(ConstIterator p, Enumerator<TInputIterator> enumerator) -> Iterator {
	auto r = p.m_pointer;
	auto f = enumerator.begin(), l = enumerator.end();
	if (f != l) {
		using Deleter = AllocatorDestructor<NodeAllocator>;
		auto & allocator = Base::m_allocator();
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
};

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::erase_after(ConstIterator position) -> Iterator {
	auto p = position.m_pointer;
	auto n = p->next;
	p->next = n->next;
	auto & allocator = Base::m_allocator();
	NodeAllocatorTraits::destroy(allocator, address_of((n->element)));
	NodeAllocatorTraits::deallocate(allocator, n, 1);
	return Iterator(p->next);
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::erase_after(Enumerator<ConstIterator> enumerator) -> Iterator {
	auto f = enumerator.begin(), l = enumerator.end();
	auto e = l.m_pointer;
	if (f != l) {
		auto p = f.m_pointer, n = p->next;
		if (n != e) {
			p->next = e;
			auto & allocator = Base::m_allocator();
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
auto ForwardList< TElement, TAllocator >::resize(Size count) -> ForwardList & {
	Size c = 0;
	auto p = head(), i = begin(), e = end();
	for (; i != e && c < count; ++p, ++i, ++c) {}
	if (i != e) {
		erase_after(p, e);
	} else {
		m_prepare_after(i.m_pointer, count - c);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto ForwardList< TElement, TAllocator >::resize(Size size, Element const & element) -> ForwardList & {
	Size c = 0;
	auto p = head(), i = begin(), e = end();
	for (; i != e && c < size; ++p, ++i, ++c) {}
	if (i != e) {
		erase_after(p, e);
	} else {
		size -= c;
		if (size > 0) {
			using Deleter = AllocatorDestructor<NodeAllocator>;
			auto & allocator = Base::m_allocator();
			UniquePointer< Node, Deleter > node(nullptr, Deleter(allocator, 1));
			for (auto pointer = i.m_pointer; size > 0; --size, pointer = pointer->next) {
				node.reset(NodeAllocatorTraits::allocate(allocator, 1));
				NodeAllocatorTraits::construct(allocator, address_of(node->element), element);
				node->next = nullptr;
				pointer->next = node.release();
			}
		}
	}
	return *this;
}

template< typename TElement, typename TAllocator >
void ForwardList< TElement, TAllocator >::splice_after(ConstIterator p, ForwardList & list) {
	if (!list.is_empty()) {
		if (p.m_pointer->next != nullptr) {
			auto i = list.chead();
			for (; i.m_pointer->next != nullptr; ++i) {}
			i.m_pointer->next = p.m_pointer->next;
		}
		p.m_pointer->next = list.m_head()->next;
		list.m_head()->next = nullptr;
	}
};

template< typename TElement, typename TAllocator >
void ForwardList< TElement, TAllocator >::splice_after(ConstIterator p, ForwardList & list, ConstIterator i) {
	auto j = next(i);
	if (p != i && p != j) {
		i.m_pointer->next = j.m_pointer->next;
		j.m_pointer->next = p.m_pointer->next;
		p.m_pointer->next = j.m_pointer;
	}
};

template< typename TElement, typename TAllocator >
void ForwardList< TElement, TAllocator >::splice_after(ConstIterator p, ForwardList & list, Enumerator<ConstIterator> e) {
	if (!e.is_empty()) {
		auto f = e.begin(), l = e.end();
		if (p != f) {
			auto i = f;
			for (; i.m_pointer->next != l.m_pointer; ++i) {}
			if (f != i) {
				i.m_pointer->next = p.m_pointer->next;
				p.m_pointer->next = f.m_pointer->next;
				f.m_pointer->next = l.m_pointer;
			}
		}
	}
};

template< typename TElement, typename TAllocator >
template< typename TUnaryPredicate>
void ForwardList< TElement, TAllocator >::remove_if(TUnaryPredicate predicate) {
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
template< typename TBinaryPredicate>
void ForwardList< TElement, TAllocator >::unique(TBinaryPredicate predicate) {
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
inline void swap(ForwardList< TElement, TAllocator> & x, ForwardList< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}

} // namespace BR