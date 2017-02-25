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
#include <libbr/functional/equal_to.hpp>
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
 * @brief Circular double-linked  list。
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
	 * @brief Constructs the container with the contents of the range \f$ [first, last) \f$.
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
	 * @name Destructor
	 */
	///@{
	/**
	 * @brief Destructor.
	 */
	~List() = default;
	///@}

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

	/**
	 * @brief Access the last element.
	 * @return Reference to the last element.
	 */
	auto back() -> Reference {
		return this->m_header()->prev->element;
	}

	/**
	 * @brief Access the last element.
	 * @return Reference to the last element.
	 */
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
	 * @brief Returns a reverse iterator to the beginning.
	 * @return Reverse iterator to the first element.
	 */
	auto rbegin() noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	/**
	 * @brief Returns a reverse iterator to the beginning.
	 * @return Reverse iterator to the first element.
	 */
	auto rbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(end());
	}

	/**
	 * @brief Returns a reverse iterator to the beginning.
	 * @return Reverse iterator to the first element.
	 */
	auto crbegin() const noexcept -> ConstReverseIterator {
		return rbegin();
	}

	/**
	 * @brief Returns a reverse iterator to the end.
	 * @return Reverse iterator to the element following the last element.
	 */
	auto rend() noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	/**
	 * @brief Returns a reverse iterator to the end.
	 * @return Reverse iterator to the element following the last element.
	 */
	auto rend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(begin());
	}

	/**
	 * @brief Returns a reverse iterator to the end.
	 * @return Reverse iterator to the element following the last element.
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
	 * @retval true The container is empty.
	 * @retval false Otherwise.
	 */
	auto empty() const noexcept -> bool {
		return this->m_size() == 0;
	}

	/**
	 * @brief Returns the number of elements.
	 * @return The number of elements in the container.
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
		this->m_assign(element, count);
	}

	/**
	 * @brief Replaces the contents with copies of those in the range \f$ [first, last) \f$.
	 * @param first,last The range to copy the elements from.
	 * @return \c *this
	 */
	template< typename TIterator >
	auto assign(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> > {
		this->m_assign(first, last);
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
	 * @name Insertion
	 */
	///@{
	/**
	 * @brief Constructs element in-place.
	 * @tparam TArgs Type of \p args
	 * @param position Iterator before which the new element will be constructed.
	 * @param args Arguments to forward to the constructor of the element.
	 * @return Iterator pointing to the emplaced element.
	 */
	template< typename ... TArgs >
	auto emplace(ConstIterator position, TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert(position.m_pointer, this->m_construct_node(forward<TArgs>(args)...)));
	}

	/**
	 * @brief Constructs an element in-place at the beginning.
	 * @tparam TArgs Type of \p args
	 * @param args Arguments to forward to the constructor of the element.
	 * @return A reference to the inserted element.
	 */
	template< typename ... TArgs >
	auto emplace_front(TArgs && ... args) -> Reference {
		return *emplace(cbegin(), forward<TArgs>(args)...);
	}

	/**
	 * @brief Constructs an element in-place at the end.
	 * @tparam TArgs Type of \p args
	 * @param args Arguments to forward to the constructor of the element.
	 * @return A reference to the inserted element.
	 */
	template< typename ... TArgs >
	auto emplace_back(TArgs && ... args) -> Reference {
		return *emplace(cend(), forward<TArgs>(args)...);
	}

	/**
	 * @brief Inserts \p element before \p position.
	 * @param position Iterator after which the content will be inserted.
	 * @param element Element value to insert.
	 * @return Iterator to the inserted \p element.
	 */
	auto insert(ConstIterator position, Element const & element) -> Iterator {
		return emplace(position, element);
	}

	/**
	 * @brief Inserts \p element before \p position.
	 * @param position Iterator after which the content will be inserted.
	 * @param element Element value to insert.
	 * @return Iterator to the inserted \p element.
	 */
	auto insert(ConstIterator position, Element && element) -> Iterator {
		return emplace(position, move(element));
	}

	/**
	 * @brief Inserts \p count copies of the \p element before \p position.
	 * @param position Iterator after which the content will be inserted, can be the end() iterator.
	 * @param element Element value to insert.
	 * @param count Number of copies to insert.
	 * @return Iterator to the first element inserted, or \p position if <code>count == 0</code>.
	 */
	auto insert(ConstIterator position, Element const & element, Size count) -> Iterator {
		return Iterator(this->m_insert(position.m_pointer, element, count));
	}

	/**
	 * @brief Inserts elements from range \f$ [first, last) \f$ before \p position.
	 * @tparam TIterator Type of \p first and \p last.
	 * @param position Iterator after which the content will be inserted, can be the end() iterator.
	 * @param first,last The range of elements to insert, can't be iterators into container for which insert is called
	 * @return Iterator to the first element inserted, or \p position if <code>first == last</code>.
	 */
	template< typename TIterator >
	auto insert(ConstIterator position, TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, Iterator > {
		return Iterator(this->m_insert(position.m_pointer, first, last));
	}

	/**
	 * @brief Inserts elements from initializer \p list ilist before \p position.
	 * @param position Iterator after which the content will be inserted, can be the end() iterator.
	 * @param list Initializer list to insert the values from.
	 * @return Iterator to the first element inserted, or pos if ilist is empty.
	 */
	auto insert(ConstIterator position, InitializerList<Element> list) -> Iterator {
		return insert(position, list.begin(), list.end());
	}

	/**
	 * @brief Inserts an element to the beginning.
	 * @param element Element value to insert.
	 */
	void insert_front(Element const & element) {
		emplace_front(element);
	}

	/**
	 * @brief Inserts an element to the beginning.
	 * @param element Element value to insert.
	 */
	void insert_front(Element && element) {
		emplace_front(move(element));
	}

	/**
	 * @brief Inserts an element to the end.
	 * @param element Element value to insert.
	 */
	void insert_back(Element const & element){
		emplace_back(element);
	}

	/**
	 * @brief Inserts an element to the end.
	 * @param element Element value to insert.
	 */
	void insert_back(Element && element) {
		emplace_back(move(element));
	}
	///@}

	/**
	 * @name Deletion
	 */
	///@{
	/**
	 * @brief Removes the first element.
	 */
	void erase_front() {
		erase(cbegin());
	}

	/**
	 * @brief Removes the element at \p position.
	 * @param position Iterator to the element to remove.
	 * @return Iterator following the removed element, or \c end() if the iterator \p position refers to the last element.
	 */
	auto erase(ConstIterator position) -> Iterator {
		return Iterator(this->m_erase(position.m_pointer));
	}

	/**
	 * @brief Removes the elements in the range \f$ [first, last) \f$ .
	 * @param first,last Range of elements to remove.
	 * @return Iterator following the last removed element.
	 */
	auto erase(ConstIterator first, ConstIterator last) -> Iterator {
		return Iterator(this->m_erase(first.m_pointer, last.m_pointer));
	}

	/**
	 * @brief Removes the last element.
	 */
	void erase_back() {
		erase(--cend());
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
	void remove(ConstReference element) {
		return remove_if(EqualTo<Element>(element));
	}

	/**
	 * @brief Removes all elements for which predicate \p predicate returns true.
	 * @tparam TUnaryPredicate Type of unary predicate.
	 * @param predicate Unary predicate which returns \c ​true if the element should be removed.
	 */
	template< typename TUnaryPredicate >
	void remove_if(TUnaryPredicate predicate) {
		this->m_remove(predicate);
	}
	///@}

	/**
	 * @name splice
	 */
	///@{
	/**
	 * @brief Moves elements from another List
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 */
	void splice(ConstIterator position, List & other) {
		this->m_splice(position.m_pointer, other);
	}

	/**
	 * @brief Moves elements from another List
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param i Iterator preceding the iterator to the element to move from other to \c *this.
	 */
	void splice(ConstIterator position, List & other, ConstIterator i) {
		this->m_splice(position.m_pointer, other, i.m_pointer);
	}

	/**
	 * @brief Moves elements from another List
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param first,last The range of elements to move from other to \c *this.
	 */
	void splice(ConstIterator position, List & other, ConstIterator first, ConstIterator last) {
		this->m_splice(position.m_pointer, other, first.m_pointer, last.m_pointer);
	}

	/**
	 * @brief Moves elements from another List
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 */
	void splice(ConstIterator position, List && other) {
		splice(position, other);
	}

	/**
	 * @brief Moves elements from another List
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param i Iterator preceding the iterator to the element to move from other to \c *this.
	 */
	void splice(ConstIterator position, List && other, ConstIterator i) {
		splice(position, other, i);
	}

	/**
	 * @brief Moves elements from another List
	 * @param position Element after which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param first,last The range of elements to move from other to \c *this.
	 */
	void splice(ConstIterator position, List && other, ConstIterator first, ConstIterator last) {
		splice(position, other, first, last);
	}
	///@}

	/**
	 * @name Miscellaneous
	 */
	///@{
	/**
	 * @brief Removes consecutive duplicate elements.
	 */
	void unique() {
		unique(Equal<Element>{});
	}

	/**
	 * @brief Removes consecutive duplicate elements.
	 * @tparam TBinaryPredicate Type of \p predicate.
	 * @param predicate Binary predicate which returns ​true if the elements should be treated as equal.
	 */
	template< typename TBinaryPredicate >
	void unique(TBinaryPredicate predicate) {
		this->m_unique(predicate);
	}

	/**
	 * @brief Merges two sorted lists into one.
	 * @param list Another container to merge.
	 */
	void merge(List & list) {
		merge(list, Less<Element>{});
	}

	/**
	 * @brief Merges two sorted lists into one.
	 * @tparam TComparator Type of \p comparator
	 * @param list Another container to merge.
	 * @param comparator Binary predicate which returns ​true if the first argument is less than (i.e. is ordered before) the second.
	 */
	template< typename TComparator >
	void merge(List & list, TComparator comparator) {
		this->m_merge(list, comparator);
	}

	/**
	 * @brief Merges two sorted lists into one.
	 * @param list Another container to merge.
	 */
	void merge(List && list) {
		merge(list);
	}

	/**
	 * @brief Merges two sorted lists into one.
	 * @tparam TComparator Type of \p comparator
	 * @param list Another container to merge.
	 * @param comparator Binary predicate which returns ​true if the first argument is less than (i.e. is ordered before) the second.
	 */
	template< typename TComparator >
	void merge(List && list, TComparator comparator) {
		merge(list, comparator);
	}

	/**
	 * @brief Sorts the elements.
	 */
	void sort() {
		sort(Less<Element>{});
	}

	/**
	 * @brief Sorts the elements.
	 * @tparam TComparator Type of \p comparator
	 * @param comparator Binary predicate which returns ​true if the first argument is less than (i.e. is ordered before) the second.
	 */
	template< typename TComparator >
	void sort(TComparator comparator) {
		this->m_sort(comparator);
	}

	/**
	 * @brief Swaps the contents.
	 * @param other Container to exchange the contents with.
	 */
	void swap(List & other) noexcept(BooleanOr< BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >, IsNothrowSwappable<NodeAllocator> >{}) {
		this->m_swap(other);
	}

	/**
	 * @brief Reverses the order of the elements.
	 */
	void reverse() {
		this->m_reverse();
	}
	///@}

}; // class List< TElement, TAllocator >

} // inline namespace Container

} // namespace BR