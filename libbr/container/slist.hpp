/**
 * @file
 * @brief SList
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/detail/slist_basic.hpp>
#include <libbr/enumerate/enumerable.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/functional/equal_to.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/iterator/move_iterator.hpp>
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
#include <libbr/type_traits/is_input_iterator.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Container {

/**
 * @brief Linear singly-linked list。
 * @tparam TElement The type of the elements.
 * @tparam TAllocator An allocator used to acquire/release memory and to construct/destroy the elements in that memory.
 */
template< typename TElement, typename TAllocator = Allocator<TElement> >
class SList;

/**
 * @brief Specializes the BR::swap algorithm for SList
 * @tparam TElement,TAllocator Template arguments of SList.
 * @param x,y Containers whose contents to swap.
 */
template< typename TElement, typename TAllocator >
inline void swap(SList< TElement, TAllocator> & x, SList< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}

} // namespace Container



inline namespace Container {

template< typename TElement, typename TAllocator >
class SList :
	private Detail::Container::SList::Basic< TElement, TAllocator >,
	public Enumerable<
		SList<TElement, TAllocator>,
		typename Detail::Container::SList::Basic< TElement, TAllocator >::Iterator,
		typename Detail::Container::SList::Basic< TElement, TAllocator >::ConstIterator
	>,
	public EqualityComparable< SList<TElement, TAllocator> >,
	public LessThanComparable< SList<TElement, TAllocator> >
{

public:
	/**
	 * TElement
	 */
	using Element = TElement;

	/**
	 * TAllocator
	 */
	using Allocator = TAllocator;

private:
	using Self = SList;

	using Base = Detail::Container::SList::Basic< Element, Allocator >;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using Node = typename Base::Node;

	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

	using NodePointer = typename Base::NodePointer;

public:
	/**
	 * Element &
	 */
	using Reference = Element &;

	/**
	 * Element const &
	 */
	using ConstReference = Element const &;

	/**
	 * BR::AllocatorTraits<Allocator>::Pointer
	 */
	using Pointer = typename Base::Pointer;

	/**
	 * BR::AllocatorTraits<Allocator>::ConstPointer
	 */
	using ConstPointer = typename Base::ConstPointer;

	using Difference = typename Base::Difference;

	using Size = typename Base::Size;

	/**
	 * A forward iterator to Element
	 */
	using Iterator = typename Base::Iterator;

	/**
	 * A forward iterator to Element const
	 */
	using ConstIterator = typename Base::ConstIterator;

public:
	/**
	 * @name Constructor
	 */
	///@{
	/**
	 * @brief Default constructor.
	 */
	SList() noexcept(HasNothrowDefaultConstructor<NodeAllocator>{}) {
	}

	/**
	 * @brief Default constructor.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	explicit SList(Allocator const & allocator) : Base(allocator) {
	}

	/**
	 * @brief Copy constructor.
	 * @param list Another container to be used as source to initialize the elements of the container with.
	 */
	SList(Self const & list) : Base(Allocator(NodeAllocatorTraits::select_on_container_copy_construction(list.m_allocator()))) {
		insert_after(before_cbegin(), list.begin(), list.end());
	}

	/**
	 * @brief Copy constructor.
	 * @param list Another container to be used as source to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	SList(Self const & list, Allocator const & allocator) : Base(allocator) {
		insert_after(before_cbegin(), list.begin(), list.end());
	}

	/**
	 * @brief Move constructor.
	 * @param list Another container to be used as source to initialize the elements of the container with.
	 */
	SList(Self && list) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : Base(Allocator(move(list.m_allocator()))) {
		splice_after(before_cbegin(), move(list));
	}

	/**
	 * @brief Move constructor.
	 * @param list Another container to be used as source to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	SList(Self && list, Allocator const & allocator) : Base(move(allocator)) {
		if (this->m_allocator() == list.m_allocator()) {
			splice_after(before_cbegin(), move(list));
		} else {
			insert_after(before_cbegin(), make_move_iterator(list.begin()), make_move_iterator(list.end()));
		}
	}

	/**
	 * @brief Constructs the container with \p count default-constructed instances of Element.
	 * @param count The size of the container.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	explicit SList(Size count, Allocator const & allocator = Allocator{}) : Base(allocator) {
		this->m_prepare_after(this->m_header(), count);
	}

	/**
	 * @brief Constructs the container with \p count copies of elements with value \p element.
	 * @param element The value to initialize elements of the container with.
	 * @param count The size of the container.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	SList(Element const & element, Size count, Allocator const & allocator = Allocator{}) : Base(allocator) {
		insert_after(before_cbegin(), element, count);
	}

	/**
	 * @brief Constructs the container with the contents of the range \f$ [first, last) \f$.
	 * @tparam TIterator Iterator type.
	 * @param first,last The range to copy the elements from.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	template< typename TIterator >
	SList(TIterator first, TIterator last, Allocator const & allocator = Allocator{}, EnableIf< IsInputIterator<TIterator> > * = nullptr) : Base(allocator) {
		insert_after(before_cbegin(), first, last);
	}

	/**
	 * @brief Constructs the container with the contents of the initializer list \p list.
	 * @param list Initializer list to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	SList(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(allocator) {
		insert_after(before_cbegin(), list.begin(), list.end());
	}
	///@}

	/**
	 * @name Destructor
	 */
	///@{
	/**
	 * @brief Destructor.
	 */
	~SList() = default;
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
		return this->m_begin()->element;
	}

	/**
	 * @brief Access the first element.
	 * @return Reference to the first element.
	 */
	auto front() const -> ConstReference {
		return this->m_begin()->element;
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
	 * @brief Returns an iterator to the element before beginning.
	 * @return Iterator to the element before the first element.
	 */
	auto before_begin() noexcept -> Iterator {
		return Iterator(this->m_header());
	}

	/**
	 * @brief Returns an iterator to the element before beginning.
	 * @return Iterator to the element before the first element.
	 */
	auto before_begin() const noexcept -> ConstIterator {
		return ConstIterator(this->m_header());
	}

	/**
	 * @brief Returns an iterator to the element before beginning.
	 * @return Iterator to the element before the first element.
	 */
	auto before_cbegin() const noexcept -> ConstIterator {
		return before_begin();
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
		return this->m_begin() == this->m_end();
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
	 * @name Compare
	 */
	///@{
	/**
	 * @brief Check equality.
	 * @param y Another containers to compare.
	 * @return \c true if the contents of the containers are equal, \c false otherwise.
	 */
	auto operator==(SList const & y) const -> bool {
		return equal(begin(), end(), y.begin(), y.end());
	}

	/**
	 * @brief Lexicographically less comparision.
	 * @param y Another containers to compare.
	 * @return \c true if the contents of this container are lexicographically less than the contents of \p y, \c false otherwise.
	 */
	auto operator<(Self const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}
	///@}

	/**
	 * @name Assignment
	 */
	///@{
	/**
	 * @brief Copy assignment.
	 * @param other Data source container.
	 * @return \c *this
	 */
	auto operator=(Self const & other) -> Self & {
		if (this != &other) {
			this->m_copy_assign_allocator(other);
			assign(other.begin(), other.end());
		}
		return *this;
	}

	/**
	 * @brief Move assignment.
	 * @param other Data source container.
	 * @return \c *this
	 */
	auto operator=(Self && other) noexcept(typename AllocatorTraits::IsAlwaysEqual{}) -> Self & {
		this->m_move_assign(other);
		return *this;
	}

	/**
	 * @brief Replaces the contents with the elements from the initializer list \p list.
	 * @param list Initializer list to copy the values from.
	 * @return \c *this
	 */
	auto operator=(InitializerList<Element> list) -> Self & {
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
	 * @brief Constructs an element in-place at the beginning.
	 * @tparam TArgs Type of arguments.
	 * @param args Arguments to forward to the constructor of the element.
	 * @return A reference to the inserted element.
	 */
	template< typename ... TArgs >
	auto emplace_front(TArgs && ... args) -> Reference {
		return *emplace_after(before_begin(), forward<TArgs>(args)...);
	}

	/**
	 * @brief Constructs elements in-place after an element.
	 * @tparam TArgs Type of arguments.
	 * @param position  Iterator before which the new element will be constructed.
	 * @param args Arguments to forward to the constructor of the element.
	 * @return Iterator to the new element.
	 */
	template< typename ... TArgs >
	auto emplace_after(ConstIterator position, TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert_after(position.m_pointer, this->m_construct_node(forward<TArgs>(args)...)));
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
	 * @brief Inserts \p element after \p position.
	 * @param position Iterator before which the content will be inserted.
	 * @param element Element value to insert.
	 * @return Iterator to the inserted element.
	 */
	auto insert_after(ConstIterator position, Element const & element) -> Iterator {
		return emplace_after(position, element);
	}

	/**
	 * @brief Inserts \p element after \p position.
	 * @param position Iterator before which the content will be inserted.
	 * @param element Element value to insert.
	 * @return Iterator to the inserted element.
	 */
	auto insert_after(ConstIterator position, Element && element) -> Iterator {
		return emplace_after(position, move(element));
	}

	/**
	 * @brief Inserts \p count copies of the \p element after \p position.
	 * @param position Iterator before which the content will be inserted.
	 * @param element Element value to insert.
	 * @param count Number of copies to insert.
	 * @return Iterator to the last element inserted, or \p position if \code count == 0 \endcode.
	 */
	auto insert_after(ConstIterator position, Element const & element, Size count) -> Iterator {
		return Iterator(this->m_insert_after(position.m_pointer, element, count));
	}

	/**
	 * @brief Inserts elements from range \f$ [first, last) \f$ after \p position.
	 * @tparam TIterator Type of \p first and \p last.
	 * @param position Iterator before which the content will be inserted.
	 * @param first,last The range of elements to insert.
	 * @return Iterator to the last element inserted, or \p position if \code first == last \endcode.
	 */
	template< typename TIterator >
	auto insert_after(ConstIterator position, TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, Iterator > {
		return Iterator(this->m_insert_after(position.m_pointer, first, last));
	}

	/**
	 * @brief Inserts elements from initializer \p list ilist after \p position.
	 * @param position Iterator before which the content will be inserted.
	 * @param list Initializer list to insert the values from.
	 * @return Iterator to the last element inserted, or \p position if \p list is empty.
	 */
	auto insert_after(ConstIterator position, InitializerList<Element> list) -> Iterator {
		return insert_after(position, list.begin(), list.end());
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
		erase_after(before_cbegin());
	}

	/**
	 * @brief Removes the element following \p position.
	 * @param position Iterator to the element before the element to remove.
	 * @return Iterator to the element following the erased one, or \c end() if no such element exists.
	 */
	auto erase_after(ConstIterator position) -> Iterator {
		return Iterator(this->m_erase_after(position.m_pointer));
	}

	/**
	 * @brief Removes the elements in the range \f$ (first, last) \f$.
	 * @param first,last Range of elements to remove.
	 * @return Iterator to the element following the erased one, or \c end() if no such element exists.
	 */
	auto erase_after(ConstIterator first, ConstIterator last) -> Iterator {
		return Iterator(this->m_erase_after(first.m_pointer, last.m_pointer));
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
	void remove(Element const & element) {
		return remove_if(EqualTo<Element>(element));
	}

	/**
	 * @brief Removes all elements for which predicate \p predicate returns true.
	 * @tparam TUnaryPredicate Type of \p predicate.
	 * @param predicate Unary predicate which returns \c ​true if the element should be removed.
	 */
	template< typename TUnaryPredicate >
	void remove_if(TUnaryPredicate && predicate) {
		this->m_remove(predicate);
	}
	///@}

	/**
	 * @name Splice
	 */
	///@{
	/**
	 * @brief Moves elements from another SList
	 * @param position Element before which the content will be inserted.
	 * @param other Another container to move the content from.
	 */
	void splice_after(ConstIterator position, Self & other) {
		this->m_splice_after(position.m_pointer, other);
	}

	/**
	 * @brief Moves elements from another SList
	 * @param position Element before which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param i Iterator preceding the iterator to the element to move from other to \c *this.
	 */
	void splice_after(ConstIterator position, Self & other, ConstIterator i) {
		this->m_splice_after(position.m_pointer, other, i.m_pointer);
	}

	/**
	 * @brief Moves elements from another SList
	 * @param position Element before which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param first,last The range of elements to move from other to \c *this.
	 */
	void splice_after(ConstIterator position, Self & other, ConstIterator first, ConstIterator last) {
		this->m_splice_after(position.m_pointer, other, first.m_pointer, last.m_pointer);
	}

	/**
	 * @brief Moves elements from another SList
	 * @param position Element before which the content will be inserted.
	 * @param other Another container to move the content from.
	 */
	void splice_after(ConstIterator position, Self && other) {
		splice_after(position, other);
	}

	/**
	 * @brief Moves elements from another SList
	 * @param position Element before which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param i Iterator preceding the iterator to the element to move from other to \c *this.
	 */
	void splice_after(ConstIterator position, Self && other, ConstIterator i) {
		splice_after(position, other, i);
	}

	/**
	 * @brief Moves elements from another SList
	 * @param position Element before which the content will be inserted.
	 * @param other Another container to move the content from.
	 * @param first,last The range of elements to move from other to \c *this.
	 */
	void splice_after(ConstIterator position, Self && other, ConstIterator first, ConstIterator last) {
		splice_after(position, other, first, last);
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
	void merge(Self & list) {
		merge(list, Less<Element>{});
	}

	/**
	 * @brief Merges two sorted lists into one.
	 * @tparam TComparator Type of \p comparator
	 * @param list Another container to merge.
	 * @param comparator Binary predicate which returns ​true if the first argument is less than (i.e. is ordered before) the second.
	 */
	template< typename TComparator >
	void merge(Self & list, TComparator comparator) {
		if (this != &list) {
			this->m_merge(list, comparator);
		}
	}

	/**
	 * @brief Merges two sorted lists into one.
	 * @param list Another container to merge.
	 */
	void merge(Self && list) {
		merge(list, Less<Element>{});
	}

	/**
	 * @brief Merges two sorted lists into one.
	 * @tparam TComparator Type of \p comparator
	 * @param list Another container to merge.
	 * @param comparator Binary predicate which returns ​true if the first argument is less than (i.e. is ordered before) the second.
	 */
	template< typename TComparator >
	void merge(Self && list, TComparator comparator) {
		if (this != &list) {
			this->m_merge(list, comparator);
		}
	}

	/**
	 * @brief Sorts the elements.
	 */
	void sort() {
		return sort(Less<Element>{});
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
	void swap(Self & other) noexcept(typename AllocatorTraits::IsAlwaysEqual{}) {
		this->m_swap(other);
	}

	/**
	 * @brief Reverses the order of the elements.
	 */
	void reverse() noexcept {
		this->m_reverse();
	}
	///@}

}; // class SList< TElement, TAllocator >

} // namespace Container

} // namespace BR