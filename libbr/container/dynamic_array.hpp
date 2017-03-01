/**
 * @file
 * @brief DynamicArray
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/detail/dynamic_array_basic.hpp>
#include <libbr/enumerate/enumerable.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_input_iterator.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Container {

/**
 * @brief Dynamic array
 * @tparam TElement The type of the elements.
 * @tparam TAllocator An allocator used to acquire/release memory and to construct/destroy the elements in that memory.
 */
template< typename TElement, typename TAllocator = Allocator<TElement> >
class DynamicArray;

template< typename TElement, typename TAllocator >
inline void swap(DynamicArray< TElement, TAllocator> & x, DynamicArray< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}

} // namespace Container



inline namespace Container {

template< typename TElement, typename TAllocator >
class DynamicArray :
	private Detail::Container::DynamicArray::Basic< TElement, TAllocator >,
	public Enumerable<
		DynamicArray<TElement, TAllocator>,
		typename Detail::Container::DynamicArray::Basic< TElement, TAllocator >::Iterator,
		typename Detail::Container::DynamicArray::Basic< TElement, TAllocator >::ConstIterator
	>,
	public EqualityComparable< DynamicArray<TElement, TAllocator> >,
	public LessThanComparable< DynamicArray<TElement, TAllocator> >
{

public:
	using Element = TElement;

	using Allocator = TAllocator;

private:
	using Self = DynamicArray;

	using Base = Detail::Container::DynamicArray::Basic< Element, Allocator >;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
	/**
	 * @brief Element &
	 */
	using Reference = Element &;

	/**
	 * @brief Element const &
	 */
	using ConstReference = Element const &;

	using Pointer = typename Base::Pointer;

	using ConstPointer = typename Base::ConstPointer;

	using Difference = typename Base::Difference;

	using Size = typename Base::Size;

	using Iterator = typename Base::Iterator;

	using ConstIterator = typename Base::ConstIterator;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

	static_assert(IsSame< typename Allocator::Element, Element >{}, "`Allocator::Value` must be same type as `Element`");
public:
	/**
	 * @name Constructor
	 */
	///@{
	/**
	 * @brief Default constructor.
	 */
	DynamicArray() noexcept (HasNothrowDefaultConstructor<Allocator>{}) {
	}

	/**
	 * @brief Default constructor.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	explicit DynamicArray(Allocator const & allocator) noexcept : Base(allocator) {
	}

	/**
	 * @brief Copy constructor.
	 * @param other Another container to be used as source to initialize the elements of the container with.
	 */
	DynamicArray(Self const & other) : Base(Allocator(AllocatorTraits::select_on_container_copy_construction(other.m_allocator()))) {
		this->m_allocate_construct(other.m_begin(), other.m_end());
	}

	/**
	 * @brief Copy constructor.
	 * @param other Another container to be used as source to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	DynamicArray(Self const & other, Allocator const & allocator) : Base(allocator) {
		this->m_allocate_construct(other.m_begin(), other.m_end());
	}

	/**
	 * @brief Move constructor.
	 * @param other Another container to be used as source to initialize the elements of the container with.
	 */
	DynamicArray(Self && other) noexcept : Base(move(other)) {
	}

	/**
	 * @brief Move constructor.
	 * @param other Another container to be used as source to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	DynamicArray(Self && other, Allocator const & allocator) : Base(move(other), allocator) {
	}

	/**
	 * @brief Constructs the container with \p count default-constructed instances of Element.
	 * @param count The size of the container.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	explicit DynamicArray(Size count, Allocator const & allocator = Allocator{}) {
		if (count > 0) {
			this->m_allocate(count);
			this->m_construct_at_end(count);
		}
	}

	/**
	 * @brief Constructs the container with \p count copies of elements with value \p element.
	 * @param element The value to initialize elements of the container with.
	 * @param count The size of the container.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	DynamicArray(ConstReference element, Size count, Allocator const & allocator = Allocator{}) {
		if (count > 0) {
			this->m_allocate(count);
			this->m_construct_at_end(element, count);
		}
	}

	/**
	 * @brief Constructs the container with the contents of the range \f$ [first, last) \f$.
	 * @tparam TIterator Iterator type.
	 * @param first,last The range to copy the elements from.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	template< typename TIterator >
	DynamicArray(TIterator first, TIterator last, Allocator const & allocator = Allocator{}, EnableIf< IsInputIterator<TIterator> > * = nullptr) : Base(allocator) {
		this->m_allocate_construct(first, last);
	}

	/**
	 * @brief Constructs the container with the contents of the initializer list \p list.
	 * @param list Initializer list to initialize the elements of the container with.
	 * @param allocator Allocator to use for all memory allocations of this container.
	 */
	DynamicArray(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(allocator) {
		this->m_allocate_construct(list.begin(), list.end());
	}
	///@}

	/**
	 * @name Destructor
	 */
	///@{
	/**
	 * @brief Destructor.
	 */
	~DynamicArray() = default;
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
		return this->m_allocator();
	}

	/**
	 * @brief Access specified element.
	 * @param index Position of the element to return.
	 * @return Reference to the requested element.
	 */
	auto operator[](Size index) -> Reference {
		BR_ASSERT(index < size());
		return this->m_begin()[index];
	}

	/**
	 * @brief Access specified element.
	 * @param index Position of the element to return.
	 * @return Reference to the requested element.
	 */
	auto operator[](Size index) const -> ConstReference {
		BR_ASSERT(index < size());
		return this->m_begin()[index];
	}

	/**
	 * @brief Access specified element with bounds checking.
	 * @param index Position of the element to return.
	 * @throw IndexException
	 * @return Reference to the requested element.
	 */
	auto at(Size index) -> Reference {
		if (index >= size()) {
			throw_index_exception("DynamicArray::at(Size)");
		}
		return this->m_begin()[index];
	}

	/**
	 * @brief Access specified element with bounds checking.
	 * @param index Position of the element to return.
	 * @throw IndexException \f$ !(index < size()) \f$
	 * @return Reference to the requested element.
	 */
	auto at(Size index) const -> ConstReference {
		if (index >= size()) {
			throw_index_exception("DynamicArray::at(Size)");
		}
		return this->m_begin()[index];
	}

	/**
	 * @brief Access the first element.
	 * @return Reference to the first element.
	 */
	auto front() -> Reference {
		return *this->m_begin();
	}

	/**
	 * @brief Access the first element.
	 * @return Reference to the first element.
	 */
	auto front() const -> ConstReference {
		return *this->m_begin();
	}

	/**
	 * @brief Access the last element.
	 * @return Reference to the last element.
	 */
	auto back() -> Reference {
		return *(this->m_end() - 1);
	}

	/**
	 * @brief Access the last element.
	 * @return Reference to the last element.
	 */
	auto back() const -> ConstReference {
		return *(this->m_end() - 1);
	}

	/**
	 * @brief Direct access to the underlying array.
	 * @return Pointer to the underlying element storage. For non-empty containers, returns &front()
	 */
	auto data() noexcept -> Element * {
		return PointerTraits<Pointer>::to_raw(this->m_begin());
	}

	/**
	 * @brief Direct access to the underlying array.
	 * @return Pointer to the underlying element storage. For non-empty containers, returns &front()
	 */
	auto data() const noexcept -> Element const * {
		return PointerTraits<Pointer>::to_raw(this->m_begin());
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
	auto empty() const noexcept -> Boolean {
		return this->m_empty();
	}

	/**
	 * @brief Returns the number of elements.
	 * @return The number of elements in the container.
	 */
	auto size() const noexcept -> Size {
		return this->m_size();
	}

	/**
	 * @brief Returns the number of elements that the container has currently allocated space for.
	 * @return Capacity of the currently allocated storage.
	 */
	auto capacity() const noexcept -> Size {
		return this->m_capacity();
	}

	/**
	 * @brief Returns the maximum possible number of element.
	 * @return Maximum possible number of element.
	 */
	auto max_size() const noexcept -> Size {
		return this->m_max_size();
	}

	/**
	 * @brief Reserves storage.
	 * @param new_capacity new capacity of the container.
	 */
	void reserve(Size new_capacity) {
		this->m_reserve(new_capacity);
	}

	/**
	 * @brief Reduces memory usage by freeing unused memory.
	 */
	void clamp() noexcept {
		this->m_clamp();
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
	auto operator==(Self const & y) const -> bool {
		return size() == y.size() && equal(begin(), end(), y.begin(), y.end());
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
		this->m_assign(other);
		return *this;
	}

	/**
	 * @brief Move assignment.
	 * @param other Data source container.
	 * @return \c *this
	 */
	auto operator=(Self && other) noexcept(
		BooleanOr< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment, typename AllocatorTraits::IsAlwaysEqual >{}
	) -> Self & {
		this->m_assign(move(other));
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
	 * @brief Constructs element in-place.
	 * @tparam TArgs Type of \p args
	 * @param position Iterator before which the new element will be constructed.
	 * @param args Arguments to forward to the constructor of the element.
	 * @return Iterator pointing to the emplaced element.
	 */
	template< typename ... TArgs >
	auto emplace(ConstIterator position, TArgs && ... args) -> Iterator {
		return Iterator(this->m_emplace(position - cbegin(), forward<TArgs>(args)...));
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
		return Iterator(this->m_insert(position - this->m_begin(), element, count));
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
		return Iterator(this->m_insert(position - this->m_begin(), first, last));
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
	 * @brief Constructs an element in-place at the end.
	 * @tparam TArgs Type of \p args
	 * @param args Arguments to forward to the constructor of the element.
	 * @return A reference to the inserted element.
	 */
	template< typename ... TArgs >
	auto emplace_back(TArgs && ... args) -> Reference {
		this->m_emplace_back(forward<TArgs>(args)...);
		return back();
	}

	/**
	 * @brief Inserts an element to the end.
	 * @param element Element value to insert.
	 */
	void insert_back(Element const & element) {
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
	 * @brief Removes the element at \p position.
	 * @param position Iterator to the element to remove.
	 * @return Iterator following the removed element, or \c end() if the iterator \p position refers to the last element.
	 */
	auto erase(ConstIterator position) -> Iterator {
		return Iterator(this->m_erase(position - cbegin()));
	}

	/**
	 * @brief Removes the elements in the range \f$ [first, last) \f$ .
	 * @param first,last Range of elements to remove.
	 * @return Iterator following the last removed element.
	 */
	auto erase(ConstIterator first, ConstIterator last) -> Iterator {
		return Iterator(this->m_erase(first - cbegin(), last - first));
	}

	/**
	 * @brief Removes the last element.
	 */
	void erase_back() {
		this->m_destruct_at_end(this->m_end() - 1);
	}

	/**
	 * @brief Clears the contents.
	 */
	void clear() noexcept {
		this->m_clear();
	}
	///@}

	/**
	 * @name Miscellaneous
	 */
	///@{
	/**
	 * @brief Swaps the contents.
	 * @param other Container to exchange the contents with.
	 */
	void swap(Self & other) noexcept(
		BooleanOr< BooleanNot< typename AllocatorTraits::IsPropagateOnContainerSwap >, IsNothrowSwappable<Allocator> >{}
	) {
		this->m_swap(other);
	}
	///@}
}; // class DynamicArray< TElement, TAllocator >

} // namespace Container

} // namespace BR