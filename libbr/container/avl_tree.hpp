/**
 * @file
 * @brief AVLTree
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/detail/binary_tree_implement.hpp>
#include <libbr/container/detail/avl_tree_basic.hpp>
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
 * @brief avl tree
 * @tparam TElement
 * @tparam TComparator
 * @tparam TAllocator
 */
template< typename TElement, typename TComparator = Less<TElement>, typename TAllocator = Allocator<TElement> >
class AVLTree;

template< typename TElement, typename TComparator, typename TAllocator >
inline void swap(AVLTree<TElement, TComparator, TAllocator> & x, AVLTree<TElement, TComparator, TAllocator> & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}



template< typename TElement, typename TComparator, typename TAllocator >
class AVLTree :
	public Detail::Container::BinaryTree::Implement< Detail::Container::AVLTree::Basic, TElement, TComparator, TAllocator >,
	public Enumerable<
		AVLTree< TElement, TComparator, TAllocator >,
		typename Detail::Container::AVLTree::Basic< TElement, TComparator, TAllocator >::Iterator,
		typename Detail::Container::AVLTree::Basic< TElement, TComparator, TAllocator >::ConstIterator
	>
{
public:
	/// @copydoc BR::Container::BinaryTree::Element
	using Element = TElement;

	/// @copydoc BR::Container::BinaryTree::Comparator
	using Comparator = TComparator;

	/// @copydoc BR::Container::BinaryTree::Allocator
	using Allocator = TAllocator;

private:
	using Base = Detail::Container::BinaryTree::Implement< Detail::Container::AVLTree::Basic, TElement, TComparator, TAllocator >;

public:
	/// @copydoc BR::Container::BinaryTree::Reference
	using Reference = typename Base::Reference;

	/// @copydoc BR::Container::BinaryTree::ConstReference
	using ConstReference = typename Base::ConstReference;

	/// @copydoc BR::Container::BinaryTree::Pointer
	using Pointer = typename Base::Pointer;

	/// @copydoc BR::Container::BinaryTree::ConstPointer
	using ConstPointer = typename Base::ConstPointer;

	/// @copydoc BR::Container::BinaryTree::Difference
	using Difference = typename Base::Difference;

	/// @copydoc BR::Container::BinaryTree::Size
	using Size = typename Base::Size;

	/// @copydoc BR::Container::BinaryTree::Iterator
	using Iterator = typename Base::Iterator;

	/// @copydoc BR::Container::BinaryTree::ConstIterator
	using ConstIterator = typename Base::ConstIterator;

	/// @copydoc BR::Container::BinaryTree::ReverseIterator
	using ReverseIterator = typename Base::ReverseIterator;

	/// @copydoc BR::Container::BinaryTree::ConstReverseIterator
	using ConstReverseIterator = typename Base::ConstReverseIterator;

private:
	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

public:
	/**
	 * @name 构造函数
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::BinaryTree()
	AVLTree() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) : Base() {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(Allocator const &)
	explicit AVLTree(Allocator const & allocator) : Base(allocator) {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(Comparator const &, Allocator const &)
	explicit AVLTree(Comparator const & comparator, Allocator const & allocator = Allocator{}) : Base(comparator, allocator) {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(BinaryTree const &)
	AVLTree(AVLTree const & tree) : Base(tree) {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(BinaryTree const &, Allocator const &)
	AVLTree(AVLTree const & tree, Allocator const & allocator) : Base(tree, allocator) {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(BinaryTree &&)
	AVLTree(AVLTree && tree) noexcept(BooleanAnd< HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<NodeAllocator> >{}) : Base(move(tree)) {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(BinaryTree &&, Allocator const &)
	AVLTree(AVLTree && tree, Allocator const & allocator) : Base(move(tree), allocator) {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(TIterator f, TIterator l, Allocator const &)
	template< typename TIterator >
	AVLTree(TIterator f, TIterator l, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : Base(f, l, allocator) {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(TIterator f, TIterator l, Comparator, Allocator const &)
	template< typename TIterator >
	AVLTree(TIterator f, TIterator l, Comparator const & comparator, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : Base(f, l, comparator, allocator) {
	}

	/// @copydoc BR::Container::BinaryTree::BinaryTree(InitializerList<Element>, Allocator const &)
	AVLTree(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(list, allocator) {
	}
	///@}

	/**
	 * @name 赋值操作
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::operator=(BinaryTree const &)
	auto operator=(AVLTree const & tree) -> AVLTree & {
		Base::operator=(tree);
		return *this;
	}

	/// @copydoc BR::Container::BinaryTree::assign(BinaryTree const &)
	auto assign(AVLTree const & tree) -> AVLTree & {
		return *this = tree;
	}

	/// @copydoc BR::Container::BinaryTree::operator=(BinaryTree &&)
	auto operator=(AVLTree && tree) noexcept(
		BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator>, HasNothrowMoveAssignment<Comparator> >{}
	) -> AVLTree & {
		Base::operator=(move(tree));
		return *this;
	}

	/// @copydoc BR::Container::BinaryTree::assign(BinaryTree &&)
	auto assign(AVLTree && tree) -> AVLTree & {
		return *this = move(tree);
	}

	/// @copydoc BR::Container::BinaryTree::assign_unique(TIterator, TIterator)
	template< typename TIterator >
	auto assign_unique(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, AVLTree & > {
		Base::assign_unique(first, last);
		return *this;
	}

	/// @copydoc BR::Container::BinaryTree::assign_equal(TIterator, TIterator)
	template< typename TIterator >
	auto assign_equal(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, AVLTree & > {
		Base::assign_equal(first, last);
		return *this;
	}
	///@}

	/// @copydoc BR::Container::BinaryTree::swap(BinaryTree &)
	void swap(AVLTree & tree) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsAlwaysEqual, IsNothrowSwappable<Comparator> >{}) {
		Base::swap(tree);
	}

#if defined(BR_DOXYGEN)
	/**
	 *  @name 成员
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::allocator() const
	auto allocator() const noexcept -> Allocator;

	/// @copydoc BR::Container::BinaryTree::comparator() const
	auto comparator() const noexcept -> Comparator;
	///@}

	/**
	 * @name 迭代器
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::begin()
	auto begin() noexcept -> Iterator;

	/// @copydoc BR::Container::BinaryTree::begin() const
	auto begin() const noexcept -> ConstIterator;

	/// @copydoc BR::Container::BinaryTree::cbegin() const
	auto cbegin() const noexcept -> ConstIterator;

	/// @copydoc BR::Container::BinaryTree::end()
	auto end() noexcept -> Iterator;

	/// @copydoc BR::Container::BinaryTree::end() const
	auto end() const noexcept -> ConstIterator;

	/// @copydoc BR::Container::BinaryTree::cend() const
	auto cend() const noexcept -> ConstIterator;

	/// @copydoc BR::Container::BinaryTree::rbegin()
	auto rbegin() noexcept -> ReverseIterator;

	/// @copydoc BR::Container::BinaryTree::rbegin() const
	auto rbegin() const noexcept -> ConstReverseIterator;

	/// @copydoc BR::Container::BinaryTree::crbegin() const
	auto crbegin() const noexcept -> ConstReverseIterator;

	/// @copydoc BR::Container::BinaryTree::rend()
	auto rend() noexcept -> ReverseIterator;

	/// @copydoc BR::Container::BinaryTree::rend() const
	auto rend() const noexcept -> ConstReverseIterator;

	/// @copydoc BR::Container::BinaryTree::crend() const
	auto crend() const noexcept -> ConstReverseIterator;
	///@}

	/**
	 * @name 容量
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::empty() const
	auto empty() const noexcept -> bool;

	/// @copydoc BR::Container::BinaryTree::size() const
	auto size() const noexcept -> Size;

	/// @copydoc BR::Container::BinaryTree::max_size() const
	auto max_size() const noexcept -> Size;
	///@}

	/**
	 * @name 比较
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::operator==(BinaryTree const &) const
	auto operator==(SplayTree const & y) const -> bool;

	/// @copydoc BR::Container::BinaryTree::operator!=(BinaryTree const &) const
	auto operator!=(SplayTree const & y) const -> bool;

	/// @copydoc BR::Container::BinaryTree::operator<(BinaryTree const &) const
	auto operator<(SplayTree const & y) const -> bool;

	/// @copydoc BR::Container::BinaryTree::operator>(BinaryTree const &) const
	auto operator>(SplayTree const & y) const -> bool;

	/// @copydoc BR::Container::BinaryTree::operator<=(BinaryTree const &) const
	auto operator<=(SplayTree const & y) const -> bool;

	/// @copydoc BR::Container::BinaryTree::operator>=(BinaryTree const &) const
	auto operator>=(SplayTree const & y) const -> bool;
	///@}

	/**
	 * @name 查找元素
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::find(Element const &)
	auto find(Element const & element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::find(Element const &) const
	auto find(Element const & element) const -> ConstIterator;

	/// @copydoc BR::Container::BinaryTree::find(TKey const &)
	template< typename TKey >
	auto find(TKey const & key) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::find(TKey const &) const
	template< typename TKey >
	auto find(TKey const & key) const -> ConstIterator;
	///@}

	/**
	 * @name 查找下界
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::lower_bound(Element const &)
	auto lower_bound(Element const & element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::lower_bound(Element const &) const
	auto lower_bound(Element const & element) const -> ConstIterator;

	/// @copydoc BR::Container::BinaryTree::lower_bound(TKey const &)
	template< typename TKey >
	auto lower_bound(TKey const & key) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::lower_bound(TKey const &) const
	template< typename TKey >
	auto lower_bound(TKey const & key) const -> ConstIterator;
	///@}

	/**
	 * @name 查找上界
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::upper_bound(Element const &)
	auto upper_bound(Element const & element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::upper_bound(Element const &) const
	auto upper_bound(Element const & element) const -> ConstIterator;

	/// @copydoc BR::Container::BinaryTree::upper_bound(TKey const &)
	template< typename TKey >
	auto upper_bound(TKey const & key) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::upper_bound(TKey const &) const
	template< typename TKey >
	auto upper_bound(TKey const & key) const -> ConstIterator;
	///@}

	/**
	 * @name 查找区间
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::equal_range(Element const &)
	auto equal_range(Element const & element) -> Pair< Iterator, Iterator >;

	/// @copydoc BR::Container::BinaryTree::equal_range(Element const &) const
	auto equal_range(Element const & element) const -> Pair< ConstIterator, ConstIterator >;

	/// @copydoc BR::Container::BinaryTree::equal_range(TKey const &)
	template< typename TKey >
	auto equal_range(TKey const & key) -> Pair< Iterator, Iterator >;

	/// @copydoc BR::Container::BinaryTree::equal_range(TKey const &) const
	template< typename TKey >
	auto equal_range(TKey const & key) const -> Pair< ConstIterator, ConstIterator >;
	///@}

	/**
	 * @name 查找边界
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::bounded_range(Element const &, Element const &, bool, bool)
	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator >;

	/// @copydoc BR::Container::BinaryTree::bounded_range(Element const &, Element const &, bool, bool) const
	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator >;

	/// @copydoc BR::Container::BinaryTree::bounded_range(TKey const &, TKey const &, bool, bool)
	template< typename TKey >
	auto bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator >;

	/// @copydoc BR::Container::BinaryTree::bounded_range(TKey const &, TKey const &, bool, bool) const
	template< typename TKey >
	auto bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator >;
	///@}

	/**
	 * @name 计数
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::count(Element const &) const
	auto count(Element const & element) const -> Size;

	/// @copydoc BR::Container::BinaryTree::count(TKey const &) const
	template< typename TKey >
	auto count(TKey const & key) const -> Size;
	///@}

	/**
	 * @name 添加（唯一）
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::emplace_unique(TArgs &&)
	template< typename... TArgs >
	auto emplace_unique(TArgs &&... args) -> Pair< Iterator, bool >;

	/// @copydoc BR::Container::BinaryTree::insert_unique(Element const &)
	auto insert_unique(Element const & element) -> Pair< Iterator, bool >;

	/// @copydoc BR::Container::BinaryTree::insert_unique(Element &&)
	auto insert_unique(Element && element) -> Pair< Iterator, bool >;

	/// @copydoc BR::Container::BinaryTree::insert_unique(TValue &&)
	template< typename TValue >
	auto insert_unique(TValue && value) -> Pair< Iterator, bool >;

	/// @copydoc BR::Container::BinaryTree::emplace_unique_hint(ConstIterator, TArgs &&)
	template< typename ... TArgs >
	auto emplace_unique_hint(ConstIterator hint, TArgs && ... args) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_unique(ConstIterator, Element const &)
	auto insert_unique(ConstIterator hint, Element const & element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_unique(ConstIterator, Element &&)
	auto insert_unique(ConstIterator hint, Element && element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_unique(ConstIterator, TValue &&)
	template< typename TValue >
	auto insert_unique(ConstIterator hint, TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Iterator >;

	/// @copydoc BR::Container::BinaryTree::insert_unique(TIterator, TIterator)
	template< typename TIterator >
	auto insert_unique(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> >;
	///@}

	/**
	 * @name 添加（可重复）
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::emplace_equal(TArgs &&)
	template< typename ... TArgs >
	auto emplace_equal(TArgs && ... args) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_equal(Element const &)
	auto insert_equal(Element const & element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_equal(Element &&)
	auto insert_equal(Element && element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_equal(TValue &&)
	template< typename TValue >
	auto insert_equal(TValue && value) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::emplace_equal_hint(ConstIterator, TArgs &&)
	template< typename ... TArgs >
	auto emplace_equal_hint(ConstIterator hint, TArgs && ... args) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_equal(ConstIterator, Element const &)
	auto insert_equal(ConstIterator hint, Element const & element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_equal(ConstIterator, Element &&)
	auto insert_equal(ConstIterator hint, Element && element) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::insert_equal(ConstIterator, TValue &&)
	template< typename TValue >
	auto insert_equal(ConstIterator hint, TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Iterator >;

	/// @copydoc BR::Container::BinaryTree::insert_equal(TIterator, TIterator)
	template< typename TIterator >
	auto insert_equal(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> >;
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	/// @copydoc BR::Container::BinaryTree::erase(ConstIterator)
	auto erase(ConstIterator position) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::erase(ConstIterator, ConstIterator)
	auto erase(ConstIterator first, ConstIterator last) -> Iterator;

	/// @copydoc BR::Container::BinaryTree::erase(Element const &)
	auto erase(Element const & element) -> Size;

	/// @copydoc BR::Container::BinaryTree::erase(TKey const &)
	template< typename TKey >
	auto erase(TKey const & key) -> Size;
	///@}

	/// @copydoc BR::Container::BinaryTree::clear()
	void clear() noexcept;
#endif // defined(BR_DOXYGEN)
}; // class AVLTree<TElement, TComparator, TAllocator>

} // namespace Container
} // namespace BR