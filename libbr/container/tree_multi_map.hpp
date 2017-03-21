/**
 * @file
 * @brief TreeMultiMap
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/container/rb_tree.hpp>
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
 * @tparam TKey
 * @tparam TValue
 * @tparam TKeyComparator
 * @tparam TAllocator
 * @tparam TTree
 * @tparam TOtherTreeArgs
 */
template<
	typename TKey,
	typename TValue,
	typename TKeyComparator = Less<TKey>,
	typename TAllocator = Allocator< Pair<TKey, TValue> >,
	template< typename, typename, typename, typename ...> class TTree = RBTree,
	typename ... TOtherTreeArgs
>
class TreeMultiMap;

template< typename TKey, typename TValue, typename TKeyComparator, typename TAllocator, template< typename, typename, typename, typename ...> class TTree, typename ... TOtherTreeArgs >
inline void swap(TreeMultiMap<TKey, TValue, TKeyComparator, TAllocator, TTree, TOtherTreeArgs...> & x, TreeMultiMap<TKey, TValue, TKeyComparator, TAllocator, TTree, TOtherTreeArgs...> & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}

} // namespace Container



namespace Detail {
namespace Container {
namespace TreeMultiMap {

template<typename TKey, class TPair, class TKeyComparator, bool = BooleanAnd< IsEmpty<TKeyComparator>, NotFinal<TKeyComparator> >{} >
class Comparator : private TKeyComparator {
private:
	using KeyComparator = TKeyComparator;

public:
	Comparator() noexcept(HasNothrowDefaultConstructor<KeyComparator>{}): KeyComparator() {}

	Comparator(KeyComparator comparator) noexcept(HasNothrowCopyConstructor<KeyComparator>{}) : KeyComparator(comparator) {}

	auto key_comparator() const noexcept -> KeyComparator const & {
		return *this;
	}

	auto operator()(TPair const & x, TPair const & y) const -> bool {
		return key_comparator()(x.template get<0>(), y.template get<0>());
	}

	auto operator()(TKey const & x, TPair const & y) const -> bool {
		return key_comparator()(x, y.template get<0>());
	}

	auto operator()(TPair const & x, TKey const & y) const -> bool {
		return key_comparator()(x.template get<0>(), y);
	}

	void swap(Comparator & comparator) noexcept (IsNothrowSwappable<KeyComparator>{}) {
		using BR::swap;
		swap(static_cast<KeyComparator &>(*this), static_cast<KeyComparator &>(comparator));
	}

	template< typename TOtherKey >
	auto operator()(TOtherKey const & x, TPair const & y) const -> EnableIf< IsCallable< KeyComparator, TOtherKey const &, TPair const & >, bool > {
		return key_comparator()(x, y.template get<0>());
	}

	template< typename TOtherKey >
	auto operator()(TPair const & x, TOtherKey const & y) const -> EnableIf< IsCallable< KeyComparator, TPair const &, TOtherKey const & >, bool > {
		return key_comparator()(x.template get<0>(), y);
	}
};

template<typename TKey, class TPair, class TKeyComparator >
class Comparator< TKey, TPair, TKeyComparator, false > {
private:
	using KeyComparator = TKeyComparator;

public:
	Comparator() noexcept(HasNothrowDefaultConstructor<KeyComparator>{}): _comparator_() {}

	Comparator(KeyComparator comparator) noexcept(HasNothrowCopyConstructor<KeyComparator>{}) : _comparator_(comparator) {}

	auto key_comparator() const noexcept -> KeyComparator const & {
		return _comparator_;
	}

	auto operator()(TPair const & x, TPair const & y) const -> bool {
		return key_comparator()(x.template get<0>(), y.template get<0>());
	}

	auto operator()(TKey const & x, TPair const & y) const -> bool {
		return key_comparator()(x, y.template get<0>());
	}

	auto operator()(TPair const & x, TKey const & y) const -> bool {
		return key_comparator()(x.template get<0>(), y);
	}

	void swap(Comparator & comparator) noexcept (IsNothrowSwappable<KeyComparator>{}) {
		using BR::swap;
		swap(_comparator_, comparator._comparator_);
	}

	template< typename TOtherKey >
	auto operator()(TOtherKey const & x, TPair const & y) const -> EnableIf< IsCallable< KeyComparator, TOtherKey const &, TPair const & >, bool > {
		return key_comparator()(x, y.template get<0>());
	}

	template< typename TOtherKey >
	auto operator()(TPair const & x, TOtherKey const & y) const -> EnableIf< IsCallable< KeyComparator, TPair const &, TOtherKey const & >, bool > {
		return key_comparator()(x.template get<0>(), y);
	}

private:
	KeyComparator _comparator_;
};

template<typename TKey, class TPair, class TKeyComparator, bool b >
inline void swap(Comparator<TKey, TPair, TKeyComparator, b> & x, Comparator<TKey, TPair, TKeyComparator, b> & y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

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
	template<typename, typename, typename, typename, template< typename, typename, typename, typename ...> class, typename ...>
	friend class BR::TreeMultiMap;

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
	template<typename, typename, typename, typename, template< typename, typename, typename, typename ...> class, typename ...>
	friend class BR::TreeMultiMap;

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

} // namespace TreeMultiMap
} // namespace Container
} // namespace Detail

inline namespace Container {

template<typename TKey, typename TValue, typename TKeyComparator, typename TAllocator, template< typename, typename, typename, typename ...> class TTree, typename ... TOtherTreeArgs>
class TreeMultiMap :
	public Enumerable<
		TreeMultiMap< TKey, TValue, TKeyComparator, TAllocator, TTree, TOtherTreeArgs... >,
		typename Detail::Container::TreeMultiMap::Iterator<
			typename TTree< Pair<TKey, TValue>, Detail::Container::TreeMultiMap::Comparator< TKey, Pair<TKey, TValue>, TKeyComparator >, TAllocator, TOtherTreeArgs... >::Iterator
		>,
		typename Detail::Container::TreeMultiMap::ConstIterator<
			typename TTree< Pair<TKey, TValue>, Detail::Container::TreeMultiMap::Comparator< TKey, Pair<TKey, TValue>, TKeyComparator >, TAllocator, TOtherTreeArgs... >::ConstIterator
		>
	>,
	public EqualityComparable< TreeMultiMap< TKey, TValue, TKeyComparator, TAllocator, TTree, TOtherTreeArgs... > >,
	public LessThanComparable< TreeMultiMap< TKey, TValue, TKeyComparator, TAllocator, TTree, TOtherTreeArgs... > >
{

public:
	using Key           = TKey;
	using Value         = TValue;
	using KeyComparator = TKeyComparator;
	using Allocator     = TAllocator;
	using Element       = Pair<Key, Value>;

private:
	using Comparator = Detail::Container::TreeMultiMap::Comparator< Key, Element, KeyComparator >;

	using Tree = TTree< Element, Comparator, Allocator, TOtherTreeArgs... >;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
	using Reference = typename Tree::Reference;

	using ConstReference = typename Tree::ConstReference;

	using Pointer = typename Tree::Pointer;

	using ConstPointer = typename Tree::ConstPointer;

	using Size = typename Tree::Size;

	using Difference = typename Tree::Difference;

	using Iterator = typename Detail::Container::TreeMultiMap::Iterator< typename Tree::Iterator >;

	using ConstIterator = typename Detail::Container::TreeMultiMap::ConstIterator< typename Tree::ConstIterator >;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

	class ElementComparator : public BinaryFunctor< Element, Element > {
		friend class TreeMultiMap;

	public:
		auto operator()(Element const & x, Element const & y) const -> bool {
			return _key_comparator_(x.template get<0>(), y.template get<0>());
		}

	protected:
		ElementComparator(KeyComparator key_comparator) : _key_comparator_(key_comparator) {
		}

	protected:
		KeyComparator _key_comparator_;
	};

public:
	TreeMultiMap() noexcept(HasNothrowDefaultConstructor<Tree>{}): _tree_(Comparator()) {
	}

	explicit TreeMultiMap(Allocator const & allocator) : _tree_(typename Tree::Allocator(allocator)) {
	}

	explicit TreeMultiMap(KeyComparator const & comparator, Allocator const & allocator = Allocator{}) : _tree_(Comparator(comparator), typename Tree::Allocator(allocator)) {
	}

	TreeMultiMap(TreeMultiMap const & map) : _tree_(map._tree_) {
		insert(map.begin(), map.end());
	}

	TreeMultiMap(TreeMultiMap const & map, Allocator const & allocator) : _tree_(map._tree_, typename Tree::Allocator(allocator)) {
	}

	TreeMultiMap(TreeMultiMap && map) noexcept(HasNothrowMoveConstructor<Tree>{}): _tree_(move(map._tree_)) {
	}

	TreeMultiMap(TreeMultiMap && map, Allocator const & allocator) : _tree_(move(map._tree_), typename Tree::Allocator(allocator)) {
	}

	template< typename TIterator >
	TreeMultiMap(TIterator first, TIterator last, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : _tree_(typename Tree::Allocator(allocator)) {
		insert(first, last);
	}

	template< typename TIterator >
	TreeMultiMap(TIterator first, TIterator last, KeyComparator const & comparator, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : _tree_(Comparator(comparator), typename Tree::Allocator(allocator)) {
		insert(first, last);
	}

	TreeMultiMap(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : _tree_(typename Tree::Allocator(allocator)) {
		insert(list.begin(), list.end());
	}

	TreeMultiMap(InitializerList<Element> list, KeyComparator const & comparator, Allocator const & allocator = Allocator{}) : _tree_(Comparator(comparator), typename Tree::Allocator(allocator)) {
		insert(list.begin(), list.end());
	}

	auto operator=(TreeMultiMap const & map) -> TreeMultiMap & {
		_tree_ = map._tree_;
		return *this;
	}

	auto operator=(TreeMultiMap && map) noexcept(HasNothrowMoveAssignment<Tree>{}) -> TreeMultiMap & {
		_tree_ = move(map._tree_);
		return *this;
	}

	auto operator=(InitializerList<Element> list) -> TreeMultiMap & {
		_tree_.assign_equal(list.begin(), list.end());
		return *this;
	}

	auto allocator() const noexcept -> Allocator {
		return _tree_.allocator();
	}

	auto element_comparator() const noexcept -> ElementComparator {
		return ElementComparator(_tree_.comparator().key_comparator());
	}

	auto key_comparator() const noexcept -> KeyComparator {
		return _tree_.comparator().key_comparator();
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

	auto operator==(TreeMultiMap const & y) const -> bool {
		return _tree_.operator==(y._tree_);
	}

	auto operator<(TreeMultiMap const & y) const -> bool {
		return _tree_.operator<(y._tree_);
	}

	auto find(Key const & key) -> Iterator {
		return Iterator(_tree_.find(key));
	}

	template< typename TOtherKey >
	auto find(TOtherKey const & key) -> Iterator {
		return Iterator(_tree_.find(key));
	}

	auto find(Key const & key) const -> ConstIterator {
		return ConstIterator(_tree_.find(key));
	}

	template< typename TOtherKey >
	auto find(TOtherKey const & key) const -> ConstIterator {
		return ConstIterator(_tree_.find(key));
	}

	auto lower_bound(Key const & key) -> Iterator {
		return Iterator(_tree_.lower_bound(key));
	}

	template< typename TOtherKey >
	auto lower_bound(TOtherKey const & key) -> Iterator {
		return Iterator(_tree_.lower_bound(key));
	}

	auto lower_bound(Key const & key) const -> ConstIterator {
		return ConstIterator(_tree_.lower_bound(key));
	}

	template< typename TOtherKey >
	auto lower_bound(TOtherKey const & key) const -> ConstIterator  {
		return ConstIterator(_tree_.lower_bound(key));
	}

	auto upper_bound(Key const & key) -> Iterator {
		return Iterator(_tree_.upper_bound(key));
	}

	template< typename TOtherKey >
	auto upper_bound(TOtherKey const & key) -> Iterator {
		return Iterator(_tree_.upper_bound(key));
	}

	auto upper_bound(Key const & key) const -> ConstIterator {
		return ConstIterator(_tree_.upper_bound(key));
	}

	template< typename TOtherKey >
	auto upper_bound(TOtherKey const & key) const -> ConstIterator {
		return ConstIterator(_tree_.upper_bound(key));
	}

	auto equal_range(Key const & key) -> Pair< Iterator, Iterator > {
		auto pair = _tree_.equal_range(key);
		return Pair< Iterator, Iterator >(pair.template get<0>(), pair.template get<1>());
	}

	template< typename TOtherKey >
	auto equal_range(TOtherKey const & key) -> Pair< Iterator, Iterator > {
		auto pair = _tree_.equal_range(key);
		return Pair< Iterator, Iterator >(pair.template get<0>(), pair.template get<1>());
	}

	auto equal_range(Key const & key) const -> Pair< ConstIterator, ConstIterator > {
		auto pair = _tree_.equal_range(key);
		return Pair< ConstIterator, ConstIterator >(pair.template get<0>(), pair.template get<1>());
	}

	template< typename TOtherKey >
	auto equal_range(TOtherKey const & key) const -> Pair< ConstIterator, ConstIterator > {
		auto pair = _tree_.equal_range(key);
		return Pair< ConstIterator, ConstIterator >(pair.template get<0>(), pair.template get<1>());
	}

	auto bounded_range(Key const & lower_key, Key const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator > {
		auto pair = _tree_.bounded_range(lower_key, upper_key, left_closed, right_closed);
		return Pair< Iterator, Iterator >(pair.template get<0>(), pair.template get<1>());
	}

	template< typename TOtherKey >
	auto bounded_range(TOtherKey const & lower_key, TOtherKey const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator > {
		auto pair = _tree_.bounded_range(lower_key, upper_key, left_closed, right_closed);
		return Pair< Iterator, Iterator >(pair.template get<0>(), pair.template get<1>());
	}

	auto bounded_range(Key const & lower_key, Key const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator > {
		auto pair = _tree_.bounded_range(lower_key, upper_key, left_closed, right_closed);
		return Pair< ConstIterator, ConstIterator >(pair.template get<0>(), pair.template get<1>());
	}

	template< typename TOtherKey >
	auto bounded_range(TOtherKey const & lower_key, TOtherKey const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator > {
		auto pair = _tree_.bounded_range(lower_key, upper_key, left_closed, right_closed);
		return Pair< ConstIterator, ConstIterator >(pair.template get<0>(), pair.template get<1>());
	}

	auto count(Key const & key) const -> Size {
		return _tree_.count(key);
	}

	template< typename TOtherKey >
	auto count(TOtherKey const & key) const -> Size {
		return _tree_.count(key);
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

	template< typename TOtherKeyComparator >
	void merge(TreeMultiMap<TKey, TValue, TOtherKeyComparator, TAllocator, TTree, TOtherTreeArgs...> & map) {
		_tree_.merge_equal(map._tree_);
	}

	auto erase(ConstIterator position) -> Iterator {
		return Iterator(_tree_.erase(position._iterator_));
	}

	auto erase(ConstIterator first, ConstIterator last) -> Iterator {
		return Iterator(_tree_.erase(first._iterator_, last._iterator_));
	}

	auto erase(Key const & key) -> Size {
		return _tree_.erase(key);
	}

	void clear() noexcept {
		_tree_.clear();
	}

	void swap(TreeMultiMap & map) noexcept(IsNothrowSwappable<Tree>{}) {
		_tree_.swap(map._tree_);
	}

private:
	Tree _tree_;

}; // class TreeMultiMap<TKey, TValue, TKeyComparator, TAllocator, TTree, TOtherTreeArgs...>

} // namespace Container

} // namespace BR