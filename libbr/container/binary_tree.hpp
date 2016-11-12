/**
 * @file
 * @brief RBTree
 * @author Bromine0x23
 * @since 2016/5/11
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/detail/binary_tree.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename TElement, typename TComparator = Less<TElement>, typename TAllocator = Allocator<TElement> >
class BinaryTree;

namespace Detail {
namespace Container {
namespace BinaryTree {

template< typename TElement, typename TVoidPointer >
struct Node;

template< typename TNodePointer >
struct BasicNode;

template< typename TElement, typename TVoidPointer >
using HeadNode = BasicNode< typename PointerTraits<TVoidPointer>::template Rebind< Node<TElement, TVoidPointer> > >;

template< typename TNodePointer >
struct BasicNode {
	using NodePointer = TNodePointer;

	using BasicNodePointer = typename PointerTraits<NodePointer>::template Rebind<BasicNode>;

	BasicNode() : parent(nullptr), left(self()), right(self()) {
	}

	auto self() -> NodePointer {
		return static_cast<NodePointer>(PointerTraits<BasicNodePointer>::make_pointer(*this));
	}

	NodePointer parent;
	NodePointer left;
	NodePointer right;
};

template< typename TElement, typename TVoidPointer >
struct Node : public HeadNode< TElement, TVoidPointer > {
	using Element = TElement;

	Element element;
};

} // namespace BinaryTree
} // namespace Container
} // namespace Detail


template< typename TElement, typename TComparator, typename TAllocator >
class BinaryTree : private Detail::Container::BinaryTree::Base< TElement, TComparator, TAllocator > {

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
	using Base = Detail::Container::BinaryTree::Base< TElement, TComparator, TAllocator >;

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

public:
	BinaryTree() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) {
	}

	explicit BinaryTree(Allocator const & allocator) : Base(allocator) {
	}

	explicit BinaryTree(Comparator const & comparator, Allocator const & allocator = Allocator{}) : Base(comparator, allocator) {
	}

	BinaryTree(BinaryTree const & tree);

	BinaryTree(BinaryTree const & tree, Allocator const & allocator);

	BinaryTree(BinaryTree && tree);

	BinaryTree(BinaryTree && tree, Allocator const & allocator);

	~BinaryTree() = default;


	auto operator=(BinaryTree const & tree) -> BinaryTree & {
		if (this != &tree) {
			this->m_comparator() = tree.m_comparator();
			this->m_copy_assign_allocator(tree);
			assign_multi(tree.begin(), tree.end());
		}
		return *this;
	}

	auto operator=(BinaryTree && tree) noexcept(
		BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator>, HasNothrowMoveAssignment<Comparator> >{}
	) -> BinaryTree & {
		m_move_assign(tree, typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment{});
		return *this;
	}

	auto operator=(InitializerList<Element> list) -> BinaryTree & {
		return assign_multi(list.begin(), list.end());
	}

	template< typename TInputIterator >
	auto assign_unique(TInputIterator first, TInputIterator last) -> BinaryTree &;

	template< typename TInputIterator >
	auto assign_multi(TInputIterator first, TInputIterator last) -> BinaryTree &;

	/**
	 * @name 成员
	 */
	///@{
	auto allocator() const noexcept -> Allocator {
		return Allocator(this->m_node_allocator());
	}

	auto comparator() const noexcept -> Comparator {
		return this->m_comparator();
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
	auto is_empty() const noexcept -> bool {
		return size() == 0;
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
		return AllocatorTraits::max_size();
	}
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
	 * @name 查找操作
	 */
	///@{
	auto count(Element const & element) const -> Size {
		return this->m_count(element);
	}

	template< typename TKey >
	auto count(TKey const & key) const -> Size {
		return this->m_count(key);
	}

	auto find(Element const & element) -> Iterator {
		return this->m_make_iterator(this->m_find(element));
	}

	template< typename TKey >
	auto find(TKey const & key) -> Iterator {
		return this->m_make_iterator(this->m_find(key));
	}

	auto find(Element const & element) const -> Iterator {
		return this->m_make_const_iterator(this->m_find(element));
	}

	template< typename TKey >
	auto find(TKey const & key) const -> Iterator {
		return this->m_make_const_iterator(this->m_find(key));
	}

	auto lower_bound(Element const & element) -> Iterator {
		return this->m_make_iterator(this->m_lower_bound(element));
	}

	template< typename TKey >
	auto lower_bound(TKey const & key) -> Iterator {
		return this->m_make_iterator(this->m_lower_bound(key));
	}

	auto lower_bound(Element const & element) const -> ConstIterator {
		return this->m_make_const_iterator(this->m_lower_bound(element));
	}

	template< typename TKey >
	auto lower_bound(TKey const & key) const -> ConstIterator  {
		return this->m_make_const_iterator(this->m_lower_bound(key));
	}

	auto upper_bound(Element const & element) -> Iterator {
		return this->m_make_iterator(this->m_upper_bound(element));
	}

	template< typename TKey >
	auto upper_bound(TKey const & key) -> Iterator {
		return this->m_make_iterator(this->m_upper_bound(key));
	}

	auto upper_bound(Element const & element) const -> ConstIterator {
		return this->m_make_const_iterator(this->m_upper_bound(element));
	}

	template< typename TKey >
	auto upper_bound(TKey const & key) const -> ConstIterator {
		return this->m_make_const_iterator(this->m_upper_bound(key));
	}

	auto equal_range(Element const & element) -> Pair< Iterator, Iterator > {
		auto range = this->m_equal_range(element);
		return make_pair(this->m_make_iterator(range.first), this->m_make_iterator(range.second));
	}

	template< typename TKey >
	auto equal_range(TKey const & key) -> Pair< Iterator, Iterator > {
		auto range = this->m_equal_range(key);
		return make_pair(this->m_make_iterator(range.first), this->m_make_iterator(range.second));
	}

	auto equal_range(Element const & element) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_equal_range(element);
		return make_pair(this->m_make_const_iterator(range.first), this->m_make_const_iterator(range.second));
	}

	template< typename TKey >
	auto equal_range(TKey const & key) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_equal_range(key);
		return make_pair(this->m_make_const_iterator(range.first), this->m_make_const_iterator(range.second));
	}
	///@}

	/**
	 * @name 添加操作
	 */
	///@{
	template< typename ... TArgs >
	auto emplace_unique(TArgs && ... args) -> Pair< Iterator, bool >;

	template< typename ... TArgs >
	auto emplace_multi(TArgs && ... args) -> Iterator;

	template< typename ... TArgs >
	auto emplace_hint_unique(ConstIterator hint, TArgs && ... args) -> Iterator;

	template< typename ... TArgs >
	auto emplace_hint_multi(ConstIterator hint, TArgs && ... args) -> Iterator;
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	auto clear() noexcept -> BinaryTree &;

	auto erase(Iterator position) -> Iterator;

	auto erase(ConstIterator position) -> Iterator;

	auto erase(ConstIterator first, ConstIterator last) -> Iterator;

	auto erase(Element const & element) -> Size;
	///@}

}; // class BinaryTree< TElement, TComparator, TAllocator >

} // namespace BR
