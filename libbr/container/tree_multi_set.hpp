/**
 * @file
 * @brief TreeMultiSet
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/container/rb_tree.hpp>
#include <libbr/enumerate/enumerable.hpp>
#include <libbr/exception/index_exception.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/operators/decrementable.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/incrementable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_callable.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/is_final.hpp>
#include <libbr/type_traits/is_input_iterator.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Container {

/**
 *
 * @tparam TElement
 * @tparam TComparator
 * @tparam TAllocator
 * @tparam TTree
 * @tparam TOtherTreeArgs
 */
template<
	typename TElement,
	typename TComparator = Less<TElement>,
	typename TAllocator = Allocator<TElement>,
	template< typename, typename, typename, typename ...> class TTree = RBTree,
	typename ... TOtherTreeArgs
>
class TreeMultiSet;

template< typename TElement, typename TComparator, typename TAllocator, template< typename, typename, typename, typename ...> class TTree, typename ... TOtherTreeArgs >
inline void swap(TreeMultiSet<TElement, TComparator, TAllocator, TTree, TOtherTreeArgs...> & x, TreeMultiSet<TElement, TComparator, TAllocator, TTree, TOtherTreeArgs...> & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}

} // namespace Container



namespace Detail {
namespace Container {
namespace TreeMultiSet {

template< typename TTreeIterator >
class Iterator;

template< typename TTreeIterator >
class ConstIterator;

template< typename TTreeIterator >
class Iterator :
	public BasicIterator,
	public EqualityComparable< Iterator<TTreeIterator> >,
	public Incrementable< Iterator<TTreeIterator> >,
	public Decrementable< Iterator<TTreeIterator> >
{
private:
	using TreeIterator = TTreeIterator;

public:
	using Category = typename TreeIterator::Category;

	using Element = typename TreeIterator::Element;

	using Pointer = typename TreeIterator::Pointer;

	using Reference = typename TreeIterator::Reference;

	using Difference = typename TreeIterator::Difference;

private:
	template<typename, typename, typename, template< typename, typename, typename, typename ...> class, typename ...>
	friend class BR::TreeMultiSet;

	template <typename>
	friend class ConstIterator;

public:
	Iterator() noexcept {}

	auto operator*() const -> Reference {
		return _iterator_.operator*();
	}

	auto operator->() const -> Pointer {
		return _iterator_.operator->();
	}

	auto operator++() -> Iterator & {
		++_iterator_;
		return *this;
	}

	auto operator--() -> Iterator & {
		--_iterator_;
		return *this;
	}

	auto operator==(Iterator const & y) const -> bool {
		return _iterator_ == y._iterator_;
	}

private:
	Iterator(TreeIterator iterator) noexcept : _iterator_(iterator) {}

private:
	TreeIterator _iterator_;
}; // class Iterator<TTreeIterator>

template< typename TTreeIterator >
class ConstIterator :
	public BasicIterator,
	public EqualityComparable< ConstIterator<TTreeIterator> >,
	public EqualityComparable< ConstIterator<TTreeIterator>, Iterator<TTreeIterator> >,
	public Incrementable< ConstIterator<TTreeIterator> >,
	public Decrementable< ConstIterator<TTreeIterator> >
{

private:
	using TreeIterator = TTreeIterator;

public:
	using Category = typename TreeIterator::Category;

	using Element = typename TreeIterator::Element;

	using Pointer = typename TreeIterator::Pointer;

	using Reference = typename TreeIterator::Reference;

	using Difference = typename TreeIterator::Difference;

private:
	template<typename, typename, typename, template< typename, typename, typename, typename ...> class, typename ...>
	friend class BR::TreeMultiSet;

public:
	ConstIterator() noexcept {
	}

	ConstIterator(Iterator<TreeIterator> iterator) noexcept : _iterator_(iterator._iterator_) {
	}

	auto operator*() const -> Reference {
		return _iterator_.operator*();
	}

	auto operator->() const -> Pointer {
		return _iterator_.operator->();
	}

	auto operator++() -> ConstIterator & {
		++_iterator_;
		return *this;
	}

	auto operator--() -> ConstIterator & {
		--_iterator_;
		return *this;
	}

	auto operator==(ConstIterator const & y) const -> bool {
		return _iterator_ == y._iterator_;
	}

	auto operator==(Iterator<TreeIterator> const  & y) const -> bool {
		return _iterator_ == y._iterator_;
	}

private:
	ConstIterator(TreeIterator iterator) noexcept : _iterator_(iterator) {
	}

private:
	TreeIterator _iterator_;
}; // class ConstIterator<TTreeIterator>

} // namespace TreeMultiSet
} // namespace Container
} // namespace Detail

inline namespace Container {

template<typename TElement, typename TComparator, typename TAllocator, template< typename, typename, typename, typename ...> class TTree, typename ... TOtherTreeArgs >
class TreeMultiSet:
	public Enumerable<
		TreeMultiSet< TElement, TComparator, TAllocator, TTree, TOtherTreeArgs... >,
		typename Detail::Container::TreeMultiSet::Iterator<
			typename TTree< TElement, TComparator, TAllocator, TOtherTreeArgs... >::Iterator
		>,
		typename Detail::Container::TreeMultiSet::ConstIterator<
			typename TTree< TElement, TComparator, TAllocator, TOtherTreeArgs... >::ConstIterator
		>
	> {

public:
	using Element    = TElement;
	using Comparator = TComparator;
	using Allocator  = TAllocator;

private:
	using Tree = TTree< Element, Comparator, Allocator, TOtherTreeArgs... >;

public:
	using Reference = typename Tree::Reference;

	using ConstReference = typename Tree::ConstReference;

	using Pointer = typename Tree::Pointer;

	using ConstPointer = typename Tree::ConstPointer;

	using Size = typename Tree::Size;

	using Difference = typename Tree::Difference;

	using Iterator = typename Detail::Container::TreeMultiSet::Iterator< typename Tree::Iterator >;

	using ConstIterator = typename Detail::Container::TreeMultiSet::ConstIterator< typename Tree::ConstIterator >;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

public:
	TreeMultiSet() noexcept(HasNothrowDefaultConstructor<Tree>{}): _tree_() {
	}

	explicit TreeMultiSet(Allocator const & allocator) : _tree_(allocator) {
	}

	explicit TreeMultiSet(Comparator const & comparator, Allocator const & allocator = Allocator{}) : _tree_(comparator, allocator) {
	}

	TreeMultiSet(TreeMultiSet const & set) : _tree_(set._tree_) {
		insert(set.begin(), set.end());
	}

	TreeMultiSet(TreeMultiSet const & set, Allocator const & allocator) : _tree_(set._tree_, allocator) {
	}

	TreeMultiSet(TreeMultiSet && set) noexcept(HasNothrowMoveConstructor<Tree>{}): _tree_(move(set._tree_)) {
	}

	TreeMultiSet(TreeMultiSet && set, Allocator const & allocator) : _tree_(move(set._tree_), allocator) {
	}

	template< typename TIterator >
	TreeMultiSet(TIterator first, TIterator last, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : _tree_(allocator) {
		insert(first, last);
	}

	template< typename TIterator >
	TreeMultiSet(TIterator first, TIterator last, Comparator const & comparator, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : _tree_(comparator, allocator) {
		insert(first, last);
	}

	TreeMultiSet(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : _tree_(allocator) {
		insert(list.begin(), list.end());
	}

	TreeMultiSet(InitializerList<Element> list, Comparator const & comparator, Allocator const & allocator = Allocator{}) : _tree_(comparator, allocator) {
		insert(list.begin(), list.end());
	}

	~TreeMultiSet() = default;

	auto operator=(TreeMultiSet const & set) -> TreeMultiSet & {
		_tree_ = set._tree_;
		return *this;
	}

	auto operator=(TreeMultiSet && set) noexcept(HasNothrowMoveAssignment<Tree>{}) -> TreeMultiSet & {
		_tree_ = move(set._tree_);
		return *this;
	}

	auto operator=(InitializerList<Element> list) -> TreeMultiSet & {
		_tree_.assign_equal(list.begin(), list.end());
		return *this;
	}

	auto allocator() const noexcept -> Allocator {
		return _tree_.allocator();
	}

	auto comparator() const noexcept -> Comparator {
		return _tree_.comparator();
	}

	auto begin() noexcept -> Iterator {
		return Iterator(_tree_.begin());
	}

	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(_tree_.begin());
	}

	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	auto end() noexcept -> Iterator {
		return Iterator(_tree_.end());
	}

	auto end() const noexcept -> ConstIterator {
		return ConstIterator(_tree_.end());
	}

	auto cend() const noexcept -> ConstIterator {
		return end();
	}

	auto rbegin() noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	auto rbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(end());
	}

	auto crbegin() const noexcept -> ConstReverseIterator {
		return rbegin();
	}

	auto rend() noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	auto rend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(begin());
	}

	auto crend() const noexcept -> ConstReverseIterator {
		return rend();
	}

	auto empty() const noexcept -> bool {
		return _tree_.empty();
	}

	auto size() const noexcept -> Size {
		return _tree_.size();
	}

	auto max_size() const noexcept -> Size {
		return _tree_.max_size();
	}

	auto operator==(TreeMultiSet const & y) const -> bool {
		return _tree_.operator==(y._tree_);
	}

	auto operator!=(TreeMultiSet const & y) const -> bool {
		return !operator==(y);
	}

	auto operator<(TreeMultiSet const & y) const -> bool {
		return _tree_.operator<(y._tree_);
	}

	auto operator>(TreeMultiSet const & y) const -> bool {
		return y.operator<(*this);
	}

	auto operator<=(TreeMultiSet const & y) const -> bool {
		return !y.operator<(*this);
	}

	auto operator>=(TreeMultiSet const & y) const -> bool {
		return !operator<(y);
	}

	auto find(Element const & element) -> Iterator {
		return Iterator(_tree_.find(element));
	}

	template< typename TOtherKey >
	auto find(TOtherKey const & key) -> Iterator {
		return Iterator(_tree_.find(key));
	}

	auto find(Element const & element) const -> ConstIterator {
		return ConstIterator(_tree_.find(element));
	}

	template< typename TOtherKey >
	auto find(TOtherKey const & key) const -> ConstIterator {
		return ConstIterator(_tree_.find(key));
	}

	auto lower_bound(Element const & element) -> Iterator {
		return Iterator(_tree_.lower_bound(element));
	}

	template< typename TOtherKey >
	auto lower_bound(TOtherKey const & key) -> Iterator {
		return Iterator(_tree_.lower_bound(key));
	}

	auto lower_bound(Element const & element) const -> ConstIterator {
		return ConstIterator(_tree_.lower_bound(element));
	}

	template< typename TOtherKey >
	auto lower_bound(TOtherKey const & key) const -> ConstIterator  {
		return ConstIterator(_tree_.lower_bound(key));
	}

	auto upper_bound(Element const & element) -> Iterator {
		return Iterator(_tree_.upper_bound(element));
	}

	template< typename TOtherKey >
	auto upper_bound(TOtherKey const & key) -> Iterator {
		return Iterator(_tree_.upper_bound(key));
	}

	auto upper_bound(Element const & element) const -> ConstIterator {
		return ConstIterator(_tree_.upper_bound(element));
	}

	template< typename TOtherKey >
	auto upper_bound(TOtherKey const & key) const -> ConstIterator {
		return ConstIterator(_tree_.upper_bound(key));
	}

	auto equal_range(Element const & element) -> Pair< Iterator, Iterator > {
		auto pair = _tree_.equal_range(element);
		return Pair< Iterator, Iterator >(pair.template get<0>(), pair.template get<1>());
	}

	template< typename TOtherKey >
	auto equal_range(TOtherKey const & key) -> Pair< Iterator, Iterator > {
		auto pair = _tree_.equal_range(key);
		return Pair< Iterator, Iterator >(pair.template get<0>(), pair.template get<1>());
	}

	auto equal_range(Element const & element) const -> Pair< ConstIterator, ConstIterator > {
		auto pair = _tree_.equal_range(element);
		return Pair< ConstIterator, ConstIterator >(pair.template get<0>(), pair.template get<1>());
	}

	template< typename TOtherKey >
	auto equal_range(TOtherKey const & key) const -> Pair< ConstIterator, ConstIterator > {
		auto pair = _tree_.equal_range(key);
		return Pair< ConstIterator, ConstIterator >(pair.template get<0>(), pair.template get<1>());
	}

	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator > {
		auto pair = _tree_.bounded_range(lower_key, upper_key, left_closed, right_closed);
		return Pair< Iterator, Iterator >(pair.template get<0>(), pair.template get<1>());
	}

	template< typename TOtherKey >
	auto bounded_range(TOtherKey const & lower_key, TOtherKey const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator > {
		auto pair = _tree_.bounded_range(lower_key, upper_key, left_closed, right_closed);
		return Pair< Iterator, Iterator >(pair.template get<0>(), pair.template get<1>());
	}

	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator > {
		auto pair = _tree_.bounded_range(lower_key, upper_key, left_closed, right_closed);
		return Pair< ConstIterator, ConstIterator >(pair.template get<0>(), pair.template get<1>());
	}

	template< typename TOtherKey >
	auto bounded_range(TOtherKey const & lower_key, TOtherKey const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator > {
		auto pair = _tree_.bounded_range(lower_key, upper_key, left_closed, right_closed);
		return Pair< ConstIterator, ConstIterator >(pair.template get<0>(), pair.template get<1>());
	}

	auto exist(Element const & element) const -> bool {
		return _tree_.find(element) != _tree_.cend();
	}

	template< typename TOtherKey >
	auto exist(TOtherKey const & key) const -> bool {
		return _tree_.find(key) != _tree_.cend();
	}

	template< typename ... TArgs >
	auto emplace(TArgs &&... args) -> Iterator {
		return Iterator(_tree_.emplace_equal(forward<TArgs>(args)...));
	}

	auto insert(Element const & element) -> Iterator {
		return Iterator(_tree_.insert_equal(element));
	}

	auto insert(Element && element) -> Iterator {
		return Iterator(_tree_.insert_equal(move(element)));
	}

	template< typename TOtherElement >
	auto insert(TOtherElement && element) -> EnableIf< IsConstructible<Element, TOtherElement>, Iterator > {
		return Iterator(_tree_.insert_equal(forward<TOtherElement>(element)));
	}

	template< typename ... TArgs >
	auto emplace_hint(ConstIterator hint, TArgs &&... args) -> Iterator {
		return Iterator(_tree_.emplace_equal_hint(hint._iterator_, forward<TArgs>(args)...));
	}

	auto insert(ConstIterator hint, Element const & element) -> Iterator {
		return Iterator(_tree_.insert_equal(hint._iterator_, element));
	}

	auto insert(ConstIterator hint, Element && element) -> Iterator {
		return Iterator(_tree_.insert_equal(hint._iterator_, move(element)));
	}

	template< typename TOtherElement >
	auto insert(ConstIterator hint, TOtherElement && element) -> EnableIf< IsConstructible<Element, TOtherElement>, Iterator > {
		return Iterator(_tree_.insert_equal(hint._iterator_, forward<TOtherElement>(element)));
	}

	template< typename TIterator >
	auto insert(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> > {
		_tree_.insert_equal(first, last);
	}

	template< typename TOtherComparator >
	void merge(TreeMultiSet<TElement, TOtherComparator, TAllocator, TTree, TOtherTreeArgs...> & set) {
		_tree_.merge_equal(set._tree_);
	}

	auto erase(ConstIterator position) -> Iterator {
		return Iterator(_tree_.erase(position._iterator_));
	}

	auto erase(ConstIterator first, ConstIterator last) -> Iterator {
		return Iterator(_tree_.erase(first._iterator_, last._iterator_));
	}

	auto erase(Element const & element) -> Size {
		return _tree_.erase(element);
	}

	void clear() noexcept {
		_tree_.clear();
	}

	void swap(TreeMultiSet & set) noexcept(IsNothrowSwappable<Tree>{}) {
		_tree_.swap(set._tree_);
	}

private:
	Tree _tree_;

}; // class TreeMultiSet<TElement, TComparator, TAllocator, TTree, TOtherTreeArgs...>

} // namespace Container

} // namespace BR

