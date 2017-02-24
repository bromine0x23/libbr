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
#include <libbr/container/detail/list_basic.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/enumerate/enumerable.hpp>
#include <libbr/iterator/move_iterator.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Container {

/**
 * @brief Double-linked list。
 * @tparam TElement The type of the elements.
 * @tparam TAllocator An allocator used to acquire/release memory and to construct/destroy the elements in that memory.
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
	using Element = TElement;

	using Allocator = TAllocator;

private:
	using Base = Detail::Container::List::Basic< Element, Allocator >;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using Node = typename Base::Node;

	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

	using NodePointer = typename Base::NodePointer;

public:
	using Reference = typename Base::Reference;

	using ConstReference = typename Base::ConstReference;

	using Pointer = typename Base::Pointer;

	using ConstPointer = typename Base::ConstPointer;

	using Difference = typename Base::Difference;

	using Size = typename Base::Size;

	using Iterator = typename Base::Iterator;

	using ConstIterator = typename Base::ConstIterator;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

private:
	template< typename TIterator >
	using IsInputIterator = BooleanAnd<
		IsConvertible< typename IteratorTraits<TIterator>::Category, ReadableTag >,
		IsConvertible< typename IteratorTraits<TIterator>::Category, SinglePassTraversalTag >
	>;

public:
	/**
	 * @name Constructor
	 */
	///@{
	/**
	 * @brief Default constructor.
	 */
	List() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) {
	}

	/**
	 * @brief Default constructor.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	explicit List(Allocator const & allocator) : Base(allocator) {
	}

	/**
	 * @brief Copy constructor.
	 * @param list Another container to be used as source to initialize the elements of the container with.
	 */
	List(List const & list) : Base(Allocator(NodeAllocatorTraits::select_on_container_copy_construction(list.m_allocator()))) {
		insert(begin(), list.begin(), list.end());
	}

	/**
	 * @brief Copy constructor.
	 * @param list Another container to be used as source to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	List(List const & list, Allocator const & allocator) : Base(allocator) {
		insert(begin(), list.begin(), list.end());
	}

	/**
	 * @brief Move constructor.
	 * @param list Another container to be used as source to initialize the elements of the container with.
	 */
	List(List && list) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : Base(Allocator(move(list.m_allocator()))) {
		splice(end(), move(list));
	}

	/**
	 * @brief Move constructor.
	 * @param list Another container to be used as source to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	List(List && list, Allocator const & allocator) : Base(allocator) {
		if (this->m_allocator() == list.m_allocator()) {
			splice(end(), move(list));
		} else {
			assign(make_move_iterator(list.begin()), make_move_iterator(list.end()));
		}
	}

	/**
	 * @brief Constructs the container with \p count default-constructed instances of Element.
	 * @param count The size of the container.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	explicit List(Size count, Allocator const & allocator = Allocator{}) : Base(allocator) {
		for (; count > 0; --count) {
			emplace_back();
		}
	}

	/**
	 * @brief Constructs the container with \p count copies of elements with value \p element.
	 * @param element The value to initialize elements of the container with.
	 * @param count The size of the container.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	List(ConstReference element, Size count, Allocator const & allocator = Allocator{}) : Base(allocator) {
		for (; count > 0; --count) {
			emplace_back(element);
		}
	}

	/**
	 * @brief Constructs the container with the contents of the range \c [first,last).
	 * @tparam TIterator Iterator type.
	 * @param first,last The range to copy the elements from.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	template< typename TIterator >
	List(TIterator first, TIterator last, Allocator const & allocator = Allocator{}, EnableIf< IsInputIterator<TIterator> > * = nullptr) : Base(allocator) {
		for (; first != last; ++first) {
			emplace_back(*first);
		}
	}

	/**
	 * @brief Constructs the container with the contents of the initializer list \p list.
	 * @param list Initializer list to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	List(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(allocator) {
		for (auto i = list.begin(), e = list.end(); i != e; ++i) {
			emplace_back(*i);
		}
	}
	///@}

	/**
	 * @brief Destructor
	 */
	~List() = default;

	/**
	 * @name Member
	 */
	///@{
	/**
	 * @brief Returns the associated allocator.
	 * @return The associated allocator.
	 */
	auto allocator() const noexcept -> Allocator {
		return Allocator(this->m_allocator());
	}

	/**
	 * @brief Access the first element.
	 * @return Reference to the first element.
	 */
	auto front() -> Reference {
		return this->m_header()->next->element;
	}

	/**
	 * @brief Access the first element.
	 * @return Reference to the first element.
	 */
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
	 * @name Iterator
	 */
	///@{
	/**
	 * @brief Returns an iterator to the beginning.
	 * @return Iterator to the first element.
	 */
	auto begin() noexcept -> Iterator {
		return Iterator(this->m_begin());
	}

	/**
	 * @brief Returns an iterator to the beginning.
	 * @return Iterator to the first element.
	 */
	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(this->m_begin());
	}

	/**
	 * @brief Returns an iterator to the beginning.
	 * @return Iterator to the first element.
	 */
	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	/**
	 * @brief Returns an iterator to the end
	 * @return Iterator to the element following the last element.
	 */
	auto end() noexcept -> Iterator {
		return Iterator(this->m_end());
	}

	/**
	 * @brief Returns an iterator to the end
	 * @return Iterator to the element following the last element.
	 */
	auto end() const noexcept -> ConstIterator {
		return ConstIterator(this->m_end());
	}

	/**
	 * @brief Returns an iterator to the end
	 * @return Iterator to the element following the last element.
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
	 * @name Capacity
	 */
	///@{
	/**
	 * @brief Checks whether the container is empty.
	 * @return \c true if the container is empty, \c false otherwise.
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
	 * @brief Returns the maximum possible number of element.
	 * @return Maximum possible number of element.
	 */
	auto max_size() const noexcept -> Size {
		return NodeAllocatorTraits::max_size(this->m_allocator());
	}

	/**
	 * @brief Changes the number of elements stored.
	 * @param new_size New size of the container.
	 */
	void resize(Size new_size) {
		this->m_resize(new_size);
	}

	/**
	 * @brief Changes the number of elements stored.
	 * @param new_size New size of the container.
	 * @param element The value to initialize the new elements with.
	 */
	void resize(Size new_size, Element const & element) {
		this->m_resize(new_size, element);
	}
	///@}

	/**
	 * @name 比较
	 */
	///@{
	/**
	 * @brief Check equality.
	 * @param y Another containers to compare.
	 * @return \c true if the contents of the containers are equal, \c false otherwise.
	 */
	auto operator==(List const & y) const -> bool {
		return size() == y.size() && equal(begin(), end(), y.begin(), y.end());
	}

	/**
	 * @brief Lexicographically less comparision.
	 * @param y Another containers to compare.
	 * @return \c true if the contents of this container are lexicographically less than the contents of \p y, \c false otherwise.
	 */
	auto operator<(List const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}
	///@}

	/**
	 * @name Assignment
	 */
	///@{
	/**
	 * @brief Copy assignment.
	 * @param list Data source container.
	 * @return \c *this
	 */
	auto operator=(List const & list) -> List & {
		if (this != &list) {
			this->m_copy_assign_allocator(list);
			assign(list.begin(), list.end());
		}
		return *this;
	}

	/**
	 * @brief Move assignment.
	 * @param list Data source container.
	 * @return \c *this
	 */
	auto operator=(List && list) noexcept(
		BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator> >{}
	) -> List & {
		this->m_move_assign(list);
		return *this;
	}

	/**
	 * @brief Replaces the contents with the elements from the initializer list \p list.
	 * @param list Initializer list to copy the values from.
	 * @return \c *this
	 */
	auto operator=(InitializerList<Element> list) -> List & {
		assign(list.begin(), list.end());
		return *this;
	}

	/**
	 * @brief Replaces the contents with \p count copies of value \p element
	 * @param element The value to initialize elements of the container with.
	 * @param count The new size of the container.
	 * @return \c *this
	 */
	void assign(Element const & element, Size count) {
		auto i = begin(), e = end();
		for (; count > 0 && i != e; --count, ++i) {
			*i = element;
		}
		if (i == e) {
			insert(e, element, count);
		} else {
			erase(i, e);
		}
	}

	/**
	 * @brief Replaces the contents with copies of those in the range \c [first,last).
	 * @param first,last The range to copy the elements from.
	 * @return \c *this
	 */
	template< typename TIterator >
	auto assign(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> > {
		auto i = begin(), e = end();
		for (; first != last && i != e; ++first, ++i) {
			*i = *first;
		}
		if (i == e) {
			insert(e, first, last);
		} else {
			erase(i, e);
		}
	}

	/**
	 * @brief Replaces the contents with the elements from the initializer list \p list.
	 * @param list Initializer list to copy the values from.
	 * @return \c *this
	 */
	void assign(InitializerList<Element> list) {
		assign(list.begin(), list.end());
	}
	///@}

	/**
	 * @name 添加性操作
	 */
	///@{
	/**
	 * @brief 从参数构造对象并添加到指定位置
	 * @tparam TArgs
	 * @param position
	 * @param args
	 * @return
	 */
	template< typename ... TArgs >
	auto emplace(ConstIterator position, TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert(position.m_pointer, this->m_construct_node(forward<TArgs>(args)...)));
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
	 * @brief Inserts elements after an element.
	 * @param position Iterator after which the content will be inserted.
	 * @param element Element value to insert.
	 * @return Iterator to the inserted element.
	 */
	auto insert(ConstIterator position, Element const & element) -> Iterator {
		return emplace(position, element);
	}

	/**
	 * @brief Inserts elements after an element.
	 * @param position Iterator after which the content will be inserted.
	 * @param element Element value to insert.
	 * @return Iterator to the inserted element.
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

	/**
	 * @brief Clears the contents.
	 */
	void clear() noexcept {
		this->m_clear();
	}

	/**
	 * @brief Removes all elements that are equal to \p element.
	 * @param element Value of the elements to remove.
	 */
	void remove(ConstReference x) {
		return remove_if([&x](ConstReference y){ return x == y; });
	}

	/**
	 * @brief Removes all elements for which predicate \p predicate returns true.
	 * @tparam TUnaryPredicate Type of unary predicate.
	 * @param predicate Unary predicate which returns \c ​true if the element should be removed.
	 */
	template< typename TUnaryPredicate >
	void remove_if(TUnaryPredicate && predicate) {
		this->m_remove(predicate);
	}
	///@}

	/**
	 * @name splice
	 */
	///@{
	/**
	 * @brief Moves elements from another ForwardList
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 */
	void splice(ConstIterator position, List & other) {
		this->m_splice(position.m_pointer, other);
	}

	/**
	 * @brief Moves elements from another ForwardList
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param i Iterator preceding the iterator to the element to move from other to \c *this.
	 */
	void splice(ConstIterator position, List & other, ConstIterator i) {
		this->m_splice(position.m_pointer, other, i.m_pointer);
	}

	/**
	 * @brief Moves elements from another ForwardList
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param first,last The range of elements to move from other to \c *this.
	 */
	void splice(ConstIterator position, List & other, ConstIterator first, ConstIterator last) {
		this->m_splice(position.m_pointer, other, first.m_pointer, last.m_pointer);
	}

	/**
	 * @brief Moves elements from another ForwardList
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 */
	void splice(ConstIterator position, List && other) {
		splice(position, other);
	}

	/**
	 * @brief Moves elements from another ForwardList
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param i Iterator preceding the iterator to the element to move from other to \c *this.
	 */
	void splice(ConstIterator position, List && other, ConstIterator i) {
		splice(position, other, i);
	}

	/**
	 * @brief Moves elements from another ForwardList
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param first,last The range of elements to move from other to \c *this.
	 */
	void splice(ConstIterator position, List && other, ConstIterator first, ConstIterator last) {
		splice(position, other, first, last);
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