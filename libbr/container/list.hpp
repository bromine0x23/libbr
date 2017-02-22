/**
 * @file
 * @brief List
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/detail/allocator_helpers.hpp>
#include <libbr/container/detail/list_basic.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/enumerate/enumerable.hpp>
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
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Container {

/**
 * @brief 双向链表
 * @tparam TElement 元素类型
 * @tparam TAllocator 分配器类型
 */
template< typename TElement, typename TAllocator = Allocator<TElement> >
class List;

template< typename TElement, typename TAllocator >
inline void swap(List< TElement, TAllocator > & x, List< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

} // inline namespace Container



inline namespace Container {

template< typename TElement, typename TAllocator >
class List :
	private Detail::Container::List::Basic< TElement, TAllocator >,
	public Enumerable<
		List<TElement, TAllocator>,
		typename Detail::Container::List::Basic< TElement, TAllocator >::Iterator,
		typename Detail::Container::List::Basic< TElement, TAllocator >::ConstIterator
	>,
	public EqualityComparable< List<TElement, TAllocator> >,
	public LessThanComparable< List<TElement, TAllocator> >
{
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
	using Base = Detail::Container::List::Basic< Element, Allocator >;

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
	List(List const & list) : Base(Allocator(NodeAllocatorTraits::select_on_container_copy_construction(list.m_allocator()))) {
		insert(begin(), list.begin(), list.end());
	}

	/**
	 * @brief 复制构造函数，指定分配器
	 * @param[in] list 源容器
	 * @param[in] allocator 分配器
	 */
	List(List const & list, Allocator const & allocator) : Base(allocator) {
		insert(begin(), list.begin(), list.end());
	}

	/**
	 * @brief 移动构造函数
	 * @param[in,out] list 源容器
	 */
	List(List && list) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : Base(Allocator(move(list.m_allocator()))) {
		splice(end(), list);
	}

	/**
	 * @brief 移动构造函数，指定分配器
	 * @param[in,out] list 源容器
	 * @param[in] allocator 分配器
	 */
	List(List && list, Allocator const & allocator) : Base(allocator) {
		if (allocator == list.m_allocator()) {
			splice(end(), list);
		} else {
			assign(make_move_iterator(list.begin()), make_move_iterator(list.end()));
		}
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以默认值初始化
	 * @param[in] n 容器大小
	 * @param[in] allocator 分配器
	 */
	explicit List(Size n, Allocator const & allocator = Allocator{}) : Base(allocator) {
		for (; n > 0; --n) {
			emplace_back();
		}
	}

	/**
	 * @brief 构造具有指定长度的容器，元素以给定值初始化
	 * @param[in] x 用于初始化的元素
	 * @param[in] n 容器大小
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
	List(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(allocator) {
		for (auto i = list.begin(), e = list.end(); i != e; ++i) {
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
		return this->m_header()->next->element;
	}

	auto front() const -> ConstReference {
		return this->m_header()->next->element;
	}

	auto back() -> Reference {
		return this->m_header()->prev->element;
	}

	auto back() const -> ConstReference {
		return this->m_header()->prev->element;
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
	auto empty() const noexcept -> bool {
		return this->m_size() == 0;
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

	/**
	 * resize
	 *
	 * @param new_size new size
	 * @return
	 */
	auto resize(Size new_size) -> List & {
		this->m_resize(new_size);
		return *this;
	}

	/**
	 * resize
	 *
	 * @param new_size new size
	 * @param x element to fill
	 * @return
	 */
	auto resize(Size new_size, Element const & x) -> List & {
		this->m_resize(new_size, x);
		return *this;
	}
	///@}

	/**
	 * @name 比较
	 */
	///@{
	auto operator==(List const & y) const -> bool {
		return size() == y.size() && equal(begin(), end(), y.begin(), y.end());
	}

	auto operator<(List const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}
	///@}

	/**
	 * @name 赋值操作
	 */
	///@{
	/**
	 * @brief 复制运算
	 * @param[in] list 源链表
	 * @return
	 */
	auto operator=(List const & list) -> List & {
		if (this != &list) {
			this->m_copy_assign_allocator(list);
			assign(list.begin(), list.end());
		}
		return *this;
	}

	/**
	 * @brief copy assignment
	 * @param list
	 * @return
	 */
	auto assign(List const & list) -> List & {
		return *this = list;
	}

	/**
	 * @brief 移动运算
	 * @param[in] list 源链表
	 * @return
	 */
	auto operator=(List && list) noexcept(
		BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator> >{}
	) -> List & {
		this->m_move_assign(list);
		return *this;
	}

	/**
	 * @brief 从初始化列表复制
	 * @param[in] list 初始化列表
	 */
	auto operator=(InitializerList<Element> list) -> List & {
		assign(list.begin(), list.end());
		return *this;
	}

	/**
	 * @brief 从初始化列表复制
	 * @param[in] list 初始化列表
	 */
	auto assign(InitializerList<Element> list) -> List & {
		assign(list.begin(), list.end());
		return *this;
	}

	/**
	 * @brief 设置容器内容为 count 个给定元素的副本
	 * @param[in] x 作为副本的元素
	 * @param[in] n 鸽术
	 */
	auto assign(Element const & x, Size n) -> List & {
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

	/**
	 * @brief 以迭代器区间赋值
	 * @param[in] f,l 迭代器区间
	 */
	template< typename TIterator >
	auto assign(TIterator f, TIterator l) -> EnableIf< IsInputIterator<TIterator>, List & > {
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
	///@}

	/**
	 * @name 添加性操作
	 */
	///@{
	/**
	 * @brief 从参数构造对象并添加到指定位置
	 * @tparam TArgs
	 * @param postion
	 * @param args
	 * @return
	 */
	template< typename ... TArgs >
	auto emplace(ConstIterator postion, TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert(postion.m_pointer, this->m_construct_node(forward<TArgs>(args)...)));
	}

	/**
	 * @brief 从参数构造对象并添加到头部
	 * @tparam TArgs
	 * @param args
	 * @return
	 */
	template< typename ... TArgs >
	auto emplace_front(TArgs && ... args) -> Reference {
		return *emplace(cbegin(), forward<TArgs>(args)...);
	}

	/**
	 * @brief 从参数构造对象并添加到尾部
	 * @tparam TArgs
	 * @param args
	 * @return
	 */
	template< typename ... TArgs >
	auto emplace_back(TArgs && ... args) -> Reference {
		return *emplace(cend(), forward<TArgs>(args)...);
	}

	/**
	 *
	 * @param position
	 * @param element
	 * @return
	 */
	auto insert(ConstIterator position, Element const & element) -> Iterator {
		return emplace(position, element);
	}

	/**
	 *
	 * @param position
	 * @param element
	 * @return
	 */
	auto insert(ConstIterator position, Element && element) -> Iterator {
		return emplace(position, move(element));
	}

	/**
	 *
	 * @param position
	 * @param element
	 * @param n
	 * @return
	 */
	auto insert(ConstIterator position, Element const & element, Size n) -> Iterator {
		return Iterator(this->m_insert(position.m_pointer, element, n));
	}

	/**
	 *
	 * @tparam TIterator
	 * @param position
	 * @param first
	 * @param last
	 * @return
	 */
	template< typename TIterator >
	auto insert(ConstIterator position, TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, Iterator > {
		return Iterator(this->m_insert(position.m_pointer, first, last));
	}

	/**
	 *
	 * @param position
	 * @param list
	 * @return
	 */
	auto insert(ConstIterator position, InitializerList<Element> list) -> Iterator {
		return insert(position, list.begin(), list.end());
	}

	/**
	 *
	 * @param element
	 * @return
	 */
	void insert_front(Element const & element) {
		emplace_front(element);
	}

	/**
	 *
	 * @param element
	 * @return
	 */
	void insert_front(Element && element) {
		emplace_front(move(element));
	}

	/**
	 *
	 * @param element
	 * @return
	 */
	void insert_back(Element const & element){
		emplace_back(element);
	}

	/**
	 *
	 * @param element
	 * @return
	 */
	void insert_back(Element && element) {
		emplace_back(move(element));
	}
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	auto clear() noexcept -> List & {
		this->m_clear();
	}

	void erase_front() {
		erase(cbegin());
	}

	auto erase(ConstIterator position) -> Iterator {
		return Iterator(this->m_erase(position.m_pointer));
	}

	auto erase(ConstIterator first, ConstIterator last) -> Iterator {
		return Iterator(this->m_erase(first.m_pointer, last.m_pointer));
	}

	void erase_back() {
		erase(cend());
	}

	auto remove(ConstReference x) -> List & {
		return remove_if([&x](ConstReference y){ return x == y; });
	}

	template< typename TUnaryPredicate >
	auto remove_if(TUnaryPredicate && predicate) -> List & {
		this->m_remove(predicate);
		return *this;
	}
	///@}

	/**
	 * @name splice
	 */
	///@{
	auto splice(ConstIterator p, List & other) -> List & {
		this->m_splice(p.m_pointer, other);
		return *this;
	}

	auto splice(ConstIterator p, List & other, ConstIterator i) -> List & {
		this->m_splice(p.m_pointer, other, i.m_pointer);
		return *this;
	}

	auto splice(ConstIterator p, List & other, ConstIterator f, ConstIterator l) -> List & {
		this->m_splice(p.m_pointer, other, f.m_pointer, l.m_pointer);
		return *this;
	}

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
	auto unique(TBinaryPredicate predicate) -> List & {
		for (auto i = begin(), e = end(); i != e;) {
			auto j = i;
			for (++j; j != e && predicate(*i, *j); ++j) {}
			if (++i != j) {
				i = erase(i, j);
			}
		}
		return *this;
	}

	template< typename TComparator >
	auto merge(List & other, TComparator comparator) -> List & {
		this->m_merge(other, comparator);
		return *this;
	}

	auto merge(List & other) -> List & {
		return merge(other, Less<Element>{});
	}

	template< typename TComparator >
	auto merge(List && other, TComparator comparator) -> List & {
		return merge(other, comparator);
	}

	auto merge(List && other) -> List & {
		return merge(other);
	}

	template< typename TComparator >
	auto sort(TComparator comparator) -> List & {
		this->m_sort(comparator);
		return *this;
	}

	auto sort() -> List & {
		return sort(Less<Element>{});
	}

	void swap(List & other) noexcept(BooleanOr< BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >, IsNothrowSwappable<NodeAllocator> >{}) {
		this->m_swap(other);
	}

	auto reverse() -> List & {
		this->m_reverse();
		return *this;
	}
	///@}

}; // class List< TElement, TAllocator >

} // inline namespace Container

} // namespace BR