/**
 * @file
 * @brief RBTree
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/binary_tree_implement.hpp>
#include <libbr/container/detail/binary_tree_basic.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/enumerate/enumerable.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/has_default_constructor.hpp>
#include <libbr/type_traits/has_move_assignment.hpp>
#include <libbr/type_traits/has_move_constructor.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_input_iterator.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
inline namespace Container {

/**
 * @brief binary tree
 * @tparam TElement
 * @tparam TComparator
 * @tparam TAllocator
 */
template< typename TElement, typename TComparator = Less<TElement>, typename TAllocator = Allocator<TElement> >
class BinaryTree :
	public Detail::Container::BinaryTree::Implement< Detail::Container::BinaryTree::Basic<TElement, TComparator, TAllocator> >,
	public Enumerable<
		BinaryTree< TElement, TComparator, TAllocator >,
		typename Detail::Container::BinaryTree::Basic< TElement, TComparator, TAllocator >::Iterator,
		typename Detail::Container::BinaryTree::Basic< TElement, TComparator, TAllocator >::ConstIterator
	>
{
public:
	/**
	 * @brief Element
	 */
	using Element = TElement;

	/**
	 * @brief Comparator
	 */
	using Comparator = TComparator;

	/**
	 * @brief Allocator
	 */
	using Allocator = TAllocator;

private:
	using Base = Detail::Container::BinaryTree::Implement< Detail::Container::BinaryTree::Basic<TElement, TComparator, TAllocator> >;

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
	using ReverseIterator = typename Base::ReverseIterator;

	/**
	 * @brief ConstReverseIterator
	 */
	using ConstReverseIterator = typename Base::ConstReverseIterator;

private:
	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

public:
	/**
	 * @name 构造函数
	 */
	///@{
	/**
	 *
	 * @return
	 */
	BinaryTree() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) : Base() {
	}

	/**
	 *
	 * @param allocator
	 * @return
	 */
	explicit BinaryTree(Allocator const & allocator) : Base(allocator) {
	}

	/**
	 *
	 * @param comparator
	 * @param allocator
	 * @return
	 */
	explicit BinaryTree(Comparator const & comparator, Allocator const & allocator = Allocator{}) : Base(comparator, allocator) {
	}

	/**
	 *
	 * @param tree
	 * @return
	 */
	BinaryTree(BinaryTree const & tree) : Base(tree) {
	}

	/**
	 *
	 * @param tree
	 * @param allocator
	 * @return
	 */
	BinaryTree(BinaryTree const & tree, Allocator const & allocator) : Base(tree, allocator) {
	}

	/**
	 *
	 * @param tree
	 * @return
	 */
	BinaryTree(BinaryTree && tree) noexcept(BooleanAnd< HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<NodeAllocator> >{}) : Base(move(tree)) {
	}

	/**
	 *
	 * @param tree
	 * @param allocator
	 * @return
	 */
	BinaryTree(BinaryTree && tree, Allocator const & allocator) : Base(move(tree), allocator) {
	}

	/**
	 *
	 * @tparam TIterator
	 * @param f
	 * @param l
	 * @param allocator
	 * @return
	 */
	template< typename TIterator >
	BinaryTree(TIterator f, TIterator l, Allocator const & allocator = Allocator{}) : Base(f, l, allocator) {
	}

	/**
	 *
	 * @tparam TIterator
	 * @param f
	 * @param l
	 * @param comparator
	 * @param allocator
	 * @return
	 */
	template< typename TIterator >
	BinaryTree(TIterator f, TIterator l, Comparator comparator, Allocator const & allocator = Allocator{}) : Base(f, l, comparator, allocator) {
	}


	/**
	 *
	 * @param list
	 * @param allocator
	 */
	BinaryTree(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(list, allocator) {
	}
	///@}

	/**
	 * @brief 析构函数
	 */
	~BinaryTree() = default;

	/**
	 * @name 赋值操作
	 */
	///@{
	/**
	 * @brief copy assignment
	 * @param tree
	 * @return
	 */
	auto operator=(BinaryTree const & tree) -> BinaryTree & {
		Base::operator=(tree);
		return *this;
	}

	/**
	 * @brief copy assignment
	 * @param tree
	 * @return
	 */
	auto assign(BinaryTree const & tree) -> BinaryTree & {
		return *this = tree;
	}

	/**
	 * @brief move assignment
	 * @param tree
	 * @return
	 */
	auto operator=(BinaryTree && tree) noexcept(
		BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator>, HasNothrowMoveAssignment<Comparator> >{}
	) -> BinaryTree & {
		Base::operator=(move(tree));
		return *this;
	}

	/**
	 * @brief move assignment
	 * @param tree
	 * @return
	 */
	auto assign(BinaryTree && tree) -> BinaryTree & {
		return *this = move(tree);
	}

	/**
	 * @brief assign_unique
	 * @tparam TIterator
	 * @param first
	 * @param last
	 * @return
	 */
	template< typename TIterator >
	auto assign_unique(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, BinaryTree & > {
		Base::assign_unique(first, last);
		return *this;
	}

	/**
	 * @brief assign_equal
	 * @tparam TIterator
	 * @param first
	 * @param last
	 * @return
	 */
	template< typename TIterator >
	auto assign_equal(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, BinaryTree & > {
		Base::assign_equal(first, last);
		return *this;
	}
	///@}

	/**
	 * @brief swap
	 * @param tree
	 */
	void swap(BinaryTree & tree) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsAlwaysEqual, IsNothrowSwappable<Comparator> >{}) {
		Base::swap(tree);
	}

#if defined(BR_DOXYGEN)
	/**
	 *  @name 成员
	 */
	///@{
	/**
	 * @brief get allocator
	 * @return allocator
	 */
	auto allocator() const noexcept -> Allocator;

	/**
	 * @brief get comparator
	 * @return comparator
	 */
	auto comparator() const noexcept -> Comparator;
	///@}

	/**
	 * @name 迭代器
	 */
	///@{
	/**
	 * @brief begin
	 */
	auto begin() noexcept -> Iterator;

	/**
	 * @brief begin
	 */
	auto begin() const noexcept -> ConstIterator;

	/**
	 * @brief const begin
	 */
	auto cbegin() const noexcept -> ConstIterator;

	/**
	 * @brief end
	 */
	auto end() noexcept -> Iterator;

	/**
	 * @brief end
	 */
	auto end() const noexcept -> ConstIterator;

	/**
	 * @brief const end
	 */
	auto cend() const noexcept -> ConstIterator;

	/**
	 * @brief reverse begin
	 */
	auto rbegin() noexcept -> ReverseIterator;

	/**
	 * @brief reverse begin
	 */
	auto rbegin() const noexcept -> ConstReverseIterator;

	/**
	 * @brief const reverse begin
	 */
	auto crbegin() const noexcept -> ConstReverseIterator;

	/**
	 * @brief reverse end
	 */
	auto rend() noexcept -> ReverseIterator;

	/**
	 * @brief reverse end
	 */
	auto rend() const noexcept -> ConstReverseIterator;

	/**
	 * @brief const reverse end
	 */
	auto crend() const noexcept -> ConstReverseIterator;
	///@}

	/**
	 * @name 容量
	 */
	///@{
	/**
	 * @brief empty
	 */
	auto empty() const noexcept -> bool;

	/**
	 * @brief size
	 */
	auto size() const noexcept -> Size;

	/**
	 * @brief max size
	 */
	auto max_size() const noexcept -> Size;
	///@}

	/**
	 * @name 比较
	 */
	///@{
	/**
	 * @brief x == y
	 * @param y
	 * @return x == y
	 */
	auto operator==(BinaryTree const & y) const -> bool;

	/**
	 * @brief x != y
	 * @param y
	 * @return x != y
	 */
	auto operator!=(BinaryTree const & y) const -> bool;

	/**
	 * @brief x < y
	 * @param y
	 * @return x < y
	 */
	auto operator<(BinaryTree const & y) const -> bool;

	/**
	 * @brief x > y
	 * @param y
	 * @return x > y
	 */
	auto operator>(BinaryTree const & y) const -> bool;

	/**
	 * @brief x <= y
	 * @param y
	 * @return x <= y
	 */
	auto operator<=(BinaryTree const & y) const -> bool;

	/**
	 * @brief x >= y
	 * @param y
	 * @return x >= y
	 */
	auto operator>=(BinaryTree const & y) const -> bool;
	///@}

	/**
	 * @name 查找元素
	 */
	///@{
	/**
	 * @brief find(element)
	 * @param element
	 * @return
	 */
	auto find(Element const & element) -> Iterator;

	/**
	 * @brief find(element)
	 * @param element
	 * @return
	 */
	auto find(Element const & element) const -> ConstIterator;

	/**
	 * @brief find(key)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto find(TKey const & key) -> Iterator;

	/**
	 * @brief find(key)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto find(TKey const & key) const -> ConstIterator;
	///@}

	/**
	 * @name 查找下界
	 */
	///@{
	/**
	 * @brief lower_bound(element)
	 * @param element
	 * @return
	 */
	auto lower_bound(Element const & element) -> Iterator;

	/**
	 * @brief lower_bound(element)
	 * @param element
	 * @return
	 */
	auto lower_bound(Element const & element) const -> ConstIterator;

	/**
	 * @brief lower_bound(key)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto lower_bound(TKey const & key) -> Iterator;

	/**
	 * @brief lower_bound(key)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto lower_bound(TKey const & key) const -> ConstIterator;
	///@}

	/**
	 * @name 查找上界
	 */
	///@{
	/**
	 * @brief upper_bound(element)
	 * @param element
	 * @return
	 */
	auto upper_bound(Element const & element) -> Iterator;

	/**
	 * @brief upper_bound(element)
	 * @param element
	 * @return
	 */
	auto upper_bound(Element const & element) const -> ConstIterator;

	/**
	 * @brief upper_bound(key)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto upper_bound(TKey const & key) -> Iterator;

	/**
	 * @brief upper_bound(key)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto upper_bound(TKey const & key) const -> ConstIterator;
	///@}

	/**
	 * @name 查找区间
	 */
	///@{
	/**
	 * @brief equal_range(element)
	 * @param element
	 * @return
	 */
	auto equal_range(Element const & element) -> Pair< Iterator, Iterator >;

	/**
	 * @brief equal_range(element)
	 * @param element
	 * @return
	 */
	auto equal_range(Element const & element) const -> Pair< ConstIterator, ConstIterator >;

	/**
	 * @brief equal_range(key)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto equal_range(TKey const & key) -> Pair< Iterator, Iterator >;

	/**
	 * @brief equal_range(key)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto equal_range(TKey const & key) const -> Pair< ConstIterator, ConstIterator >;
	///@}

	/**
	 * @name 查找边界
	 */
	///@{
	/**
	 * @brief bounded_range(lower_key, upper_key, left_closed = true, right_closed = true)
	 * @param lower_key
	 * @param upper_key
	 * @param left_closed
	 * @param right_closed
	 * @return
	 */
	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator >;

	/**
	 * @brief bounded_range(lower_key, upper_key, left_closed = true, right_closed = true)
	 * @param lower_key
	 * @param upper_key
	 * @param left_closed
	 * @param right_closed
	 * @return
	 */
	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator >;

	/**
	 * @brief bounded_range(lower_key, upper_key, left_closed = true, right_closed = true)
	 * @tparam TKey
	 * @param lower_key
	 * @param upper_key
	 * @param left_closed
	 * @param right_closed
	 * @return
	 */
	template< typename TKey >
	auto bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator >;

	/**
	 * @brief bounded_range(lower_key, upper_key, left_closed = true, right_closed = true)
	 * @tparam TKey
	 * @param lower_key
	 * @param upper_key
	 * @param left_closed
	 * @param right_closed
	 * @return
	 */
	template< typename TKey >
	auto bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator >;
	///@}

	/**
	 * @name 计数
	 */
	///@{
	/**
	 * @brief count(element)
	 * @param element
	 * @return
	 */
	auto count(Element const & element) const -> Size;

	/**
	 * @brief count(element)
	 * @tparam TKey
	 * @param key
	 * @return
	 */
	template< typename TKey >
	auto count(TKey const & key) const -> Size;
	///@}

	/**
	 * @name 添加（唯一）
	 */
	///@{
	/**
	 * @brief emplace_unique(args...)
	 * @tparam TArgs
	 * @param args
	 * @return
	 */
	template< typename ... TArgs >
	auto emplace_unique(TArgs && ... args) -> Pair< Iterator, bool >;

	/**
	 * @brief insert_unique(element)
	 * @param element
	 * @return
	 */
	auto insert_unique(Element const & element) -> Pair< Iterator, bool >;

	/**
	 * @brief insert_unique(element)
	 * @param element
	 * @return
	 */
	auto insert_unique(Element && element) -> Pair< Iterator, bool >;

	/**
	 * @brief insert_unique(value)
	 * @tparam TValue
	 * @param value
	 * @return
	 */
	template< typename TValue >
	auto insert_unique(TValue && value) -> Pair< Iterator, bool >;

	/**
	 * @brief emplace_unique_hint(hint, args...)
	 * @tparam TArgs
	 * @param hint
	 * @param args
	 * @return
	 */
	template< typename ... TArgs >
	auto emplace_unique_hint(ConstIterator hint, TArgs && ... args) -> Iterator;

	/**
	 * @brief insert_unique(hint, element)
	 * @param hint
	 * @param element
	 * @return
	 */
	auto insert_unique(ConstIterator hint, Element const & element) -> Iterator;

	/**
	 * @brief insert_unique(hint, element)
	 * @param hint
	 * @param element
	 * @return
	 */
	auto insert_unique(ConstIterator hint, Element && element) -> Iterator;

	/**
	 * @brief insert_unique(hint, value)
	 * @tparam TValue
	 * @param hint
	 * @param value
	 * @return
	 */
	template< typename TValue >
	auto insert_unique(ConstIterator hint, TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Iterator >;

	/**
	 * @brief insert_unique(first, last)
	 * @tparam TIterator
	 * @param first
	 * @param last
	 * @return
	 */
	template< typename TIterator >
	auto insert_unique(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> >;
	///@}

	/**
	 * @name 添加（可重复）
	 */
	///@{
	/**
	 * @brief emplace_equal(args...)
	 * @tparam TArgs
	 * @param args
	 * @return
	 */
	template< typename ... TArgs >
	auto emplace_equal(TArgs && ... args) -> Iterator;

	/**
	 * @brief insert_equal(element)
	 * @param element
	 * @return
	 */
	auto insert_equal(Element const & element) -> Iterator;

	/**
	 * @brief insert_equal(element)
	 * @param element
	 * @return
	 */
	auto insert_equal(Element && element) -> Iterator;

	/**
	 * @brief insert_equal(value)
	 * @tparam TValue
	 * @param value
	 * @return
	 */
	template< typename TValue >
	auto insert_equal(TValue && value) -> Iterator;

	/**
	 * @brief emplace_equal_hint(hint, args...)
	 * @tparam TArgs
	 * @param hint
	 * @param args
	 * @return
	 */
	template< typename ... TArgs >
	auto emplace_equal_hint(ConstIterator hint, TArgs && ... args) -> Iterator;

	/**
	 * @brief insert_equal(hint, element)
	 * @param hint
	 * @param element
	 * @return
	 */
	auto insert_equal(ConstIterator hint, Element const & element) -> Iterator;

	/**
	 * @brief insert_equal(hint, element)
	 * @param hint
	 * @param element
	 * @return
	 */
	auto insert_equal(ConstIterator hint, Element && element) -> Iterator;

	/**
	 * @brief insert_equal(hint, value)
	 * @tparam TValue
	 * @param hint
	 * @param value
	 * @return
	 */
	template< typename TValue >
	auto insert_equal(ConstIterator hint, TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Iterator >;

	/**
	 * @brief insert_equal(first, last)
	 * @tparam TIterator
	 * @param first
	 * @param last
	 * @return
	 */
	template< typename TIterator >
	auto insert_equal(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> >;
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	/**
	 * @brief erase
	 * @param position Iterator to the element to remove.
	 * @return Iterator following the removed element.
	 */
	auto erase(ConstIterator position) -> Iterator;

	/**
	 * @brief erase
	 * @param first,last Range of elements to remove.
	 * @return Iterator following the last removed element.
	 */
	auto erase(ConstIterator first, ConstIterator last) -> Iterator;

	/**
	 * @brief erase
	 * @param element The elements to remove.
	 * @return Number of elements removed.
	 */
	auto erase(Element const & element) -> Size;
	///@}

	/**
	 * @brief clear()
	 */
	void clear() noexcept;
#endif // defined(BR_DOXYGEN)
};

} // inline namespace Container
} // namespace BR
