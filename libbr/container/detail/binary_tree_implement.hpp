#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/algorithm/lexicographical_compare.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_input_iterator.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace BinaryTree {

using BR::Pair;

template< template< typename, typename, typename, typename...> class TBasic, typename TElement, typename TComparator, typename TAllocator, typename... TClassArgs >
class Implement :
	protected TBasic< TElement, TComparator, TAllocator, TClassArgs... >,
	public EqualityComparable< Implement<TBasic, TElement, TComparator, TAllocator, TClassArgs...> >,
	public LessThanComparable< Implement<TBasic, TElement, TComparator, TAllocator, TClassArgs...> >
{
private:
	using Base = TBasic< TElement, TComparator, TAllocator, TClassArgs... >;

public:
	using Element = typename Base::Element;

	using Comparator = typename Base::Comparator;

	using Allocator = typename Base::Allocator;

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

protected:
	using NodeAllocator = typename Base::NodeAllocator;

	using NodeAllocatorTraits = typename Base::NodeAllocatorTraits;

	using NodePointer = typename Base::NodePointer;

public:
	Implement() noexcept(BooleanAnd< HasNothrowDefaultConstructor<Comparator>, HasNothrowDefaultConstructor<NodeAllocator> >{}) : Base() {
	}

	explicit Implement(Allocator const & allocator) : Base(allocator) {
	}

	explicit Implement(Comparator const & comparator, Allocator const & allocator = Allocator{}) : Base(comparator, allocator) {
	}

	Implement(Implement const & tree) : Base(tree.m_comparator(), Allocator(NodeAllocatorTraits::select_on_container_copy_construction(tree.m_allocator()))) {
		insert_equal(tree.begin(), tree.end());
	}

	Implement(Implement const & tree, Allocator const & allocator) : Base(tree.m_comparator(), allocator) {
		insert_equal(tree.begin(), tree.end());
	}

	Implement(Implement && tree) noexcept(BooleanAnd< HasNothrowMoveConstructor<Comparator>, HasNothrowMoveConstructor<NodeAllocator> >{}) : Base(move(tree)) {
	}

	Implement(Implement && tree, Allocator const & allocator) : Base(move(tree), allocator) {
	}

	template< typename TIterator >
	Implement(TIterator f, TIterator l, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : Implement(f, l, Comparator{}, allocator) {
	}

	template< typename TIterator >
	Implement(TIterator f, TIterator l, Comparator const & comparator, EnableIf< IsInputIterator<TIterator>, Allocator const & > allocator = Allocator{}) : Base(comparator, allocator) {
		insert_equal(f, l);
	}

	Implement(InitializerList<Element> list, Allocator const & allocator = Allocator{}) : Base(allocator) {
		insert_equal(list.begin(), list.end());
	}

	~Implement() = default;

	auto operator=(Implement const & tree) -> Implement & {
		if (this != &tree) {
			this->m_comparator() = tree.m_comparator();
			this->m_copy_assign_allocator(tree);
			assign_equal(tree.begin(), tree.end());
		}
		return *this;
	}

	auto assign(Implement const & tree) -> Implement & {
		return *this = tree;
	}

	auto operator=(Implement && tree) noexcept(
		BooleanAnd< typename NodeAllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssignment<Allocator>, HasNothrowMoveAssignment<Comparator> >{}
	) -> Implement & {
		this->m_move_assign(tree);
		return *this;
	}

	auto assign(Implement && tree) -> Implement & {
		return *this = move(tree);
	}

	template< typename TIterator >
	auto assign_unique(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, Implement & > {
		this->m_assign_unique(first, last);
		return *this;
	}

	template< typename TIterator >
	auto assign_equal(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, Implement & > {
		this->m_assign_equal(first, last);
		return *this;
	}

	void swap(Implement & tree) noexcept(BooleanAnd< typename NodeAllocatorTraits::IsAlwaysEqual, IsNothrowSwappable<Comparator> >{}) {
		this->m_swap(tree);
	}

	auto allocator() const noexcept -> Allocator {
		return Allocator(this->m_allocator());
	}

	auto comparator() const noexcept -> Comparator {
		return this->m_comparator();
	}

	auto begin() noexcept -> Iterator {
		return Iterator(this->m_begin());
	}

	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(this->m_begin());
	}

	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	auto end() noexcept -> Iterator {
		return Iterator(this->m_end());
	}

	auto end() const noexcept -> ConstIterator {
		return ConstIterator(this->m_end());
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
		return size() == 0;
	}

	auto size() const noexcept -> Size {
		return this->m_size();
	}

	auto max_size() const noexcept -> Size {
		return NodeAllocatorTraits::max_size(this->m_allocator());
	}

	auto operator==(Implement const & y) const -> bool {
		return size() == y.size() && equal(begin(), end(), y.begin(), y.end());
	}

	auto operator<(Implement const & y) const -> bool {
		return lexicographical_compare(begin(), end(), y.begin(), y.end());
	}

	auto find(Element const & element) -> Iterator {
		return Iterator(this->m_find(element));
	}

	template< typename TKey >
	auto find(TKey const & key) -> Iterator {
		return Iterator(this->m_find(key));
	}

	auto find(Element const & element) const -> ConstIterator {
		return ConstIterator(this->m_find(element));
	}

	template< typename TKey >
	auto find(TKey const & key) const -> ConstIterator {
		return ConstIterator(this->m_find(key));
	}

	auto lower_bound(Element const & element) -> Iterator {
		return Iterator(this->m_lower_bound(element));
	}

	template< typename TKey >
	auto lower_bound(TKey const & key) -> Iterator {
		return Iterator(this->m_lower_bound(key));
	}

	auto lower_bound(Element const & element) const -> ConstIterator {
		return ConstIterator(this->m_lower_bound(element));
	}

	template< typename TKey >
	auto lower_bound(TKey const & key) const -> ConstIterator  {
		return ConstIterator(this->m_lower_bound(key));
	}

	auto upper_bound(Element const & element) -> Iterator {
		return Iterator(this->m_upper_bound(element));
	}

	template< typename TKey >
	auto upper_bound(TKey const & key) -> Iterator {
		return Iterator(this->m_upper_bound(key));
	}

	auto upper_bound(Element const & element) const -> ConstIterator {
		return ConstIterator(this->m_upper_bound(element));
	}

	template< typename TKey >
	auto upper_bound(TKey const & key) const -> ConstIterator {
		return ConstIterator(this->m_upper_bound(key));
	}

	auto equal_range(Element const & element) -> Pair< Iterator, Iterator > {
		auto range = this->m_equal_range(element);
		return make_pair(Iterator(range.first), Iterator(range.second));
	}

	template< typename TKey >
	auto equal_range(TKey const & key) -> Pair< Iterator, Iterator > {
		auto range = this->m_equal_range(key);
		return make_pair(Iterator(range.first), Iterator(range.second));
	}

	auto equal_range(Element const & element) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_equal_range(element);
		return make_pair(ConstIterator(range.first), ConstIterator(range.second));
	}

	template< typename TKey >
	auto equal_range(TKey const & key) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_equal_range(key);
		return make_pair(ConstIterator(range.first), ConstIterator(range.second));
	}

	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator > {
		auto range = this->m_bounded_range(lower_key, upper_key, left_closed, right_closed);
		return make_pair(Iterator(range.first), Iterator(range.second));
	}

	template< typename TKey >
	auto bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed = true, bool right_closed = true) -> Pair< Iterator, Iterator > {
		auto range = this->m_bounded_range(lower_key, upper_key, left_closed, right_closed);
		return make_pair(Iterator(range.first), Iterator(range.second));
	}

	auto bounded_range(Element const & lower_key, Element const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_bounded_range(lower_key, upper_key, left_closed, right_closed);
		return make_pair(ConstIterator(range.first), ConstIterator(range.second));
	}

	template< typename TKey >
	auto bounded_range(TKey const & lower_key, TKey const & upper_key, bool left_closed = true, bool right_closed = true) const -> Pair< ConstIterator, ConstIterator > {
		auto range = this->m_bounded_range(lower_key, upper_key, left_closed, right_closed);
		return make_pair(ConstIterator(range.first), ConstIterator(range.second));
	}

	auto count(Element const & element) const -> Size {
		return this->m_count(element);
	}

	template< typename TKey >
	auto count(TKey const & key) const -> Size {
		return this->m_count(key);
	}

	template< typename... TArgs >
	auto emplace_unique(TArgs && ... args) -> Pair< Iterator, bool > {
		auto result = this->m_insert_unique(this->m_construct_node(forward<TArgs>(args)...));
		return Pair< Iterator, bool >(Iterator(result.first), result.second);
	}

	auto insert_unique(Element const & element) -> Pair< Iterator, bool > {
		auto result = this->m_insert_unique(this->m_construct_node(element));
		return Pair< Iterator, bool >(Iterator(result.first), result.second);
	}

	auto insert_unique(Element && element) -> Pair< Iterator, bool > {
		auto result = this->m_insert_unique(this->m_construct_node(move(element)));
		return Pair< Iterator, bool >(Iterator(result.first), result.second);
	}

	template< typename TValue >
	auto insert_unique(TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Pair< Iterator, bool > > {
		auto result = this->m_insert_unique(this->m_construct_node(forward<TValue>(value)));
		return Pair< Iterator, bool >(Iterator(result.first), result.second);
	}

	template< typename ... TArgs >
	auto emplace_unique_hint(ConstIterator hint, TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert_unique(hint.m_pointer, this->m_construct_node(forward<TArgs>(args)...)));
	}

	auto insert_unique(ConstIterator hint, Element const & element) -> Iterator {
		return Iterator(this->m_insert_unique(hint.m_pointer, this->m_construct_node(element)));
	}

	auto insert_unique(ConstIterator hint, Element && element) -> Iterator {
		return Iterator(this->m_insert_unique(hint.m_pointer, this->m_construct_node(move(element))));
	}

	template< typename TValue >
	auto insert_unique(ConstIterator hint, TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Iterator > {
		return Iterator(this->m_insert_unique(hint.m_pointer, this->m_construct_node(forward<TValue>(value))));
	}

	template< typename TIterator >
	auto insert_unique(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> > {
		if (this->empty()) {
			auto end = this->m_end();
			for (; first != last; ++first) {
				this->m_insert_unique(end, this->m_construct_node(*first));
			}
		} else {
			for (; first != last; ++first) {
				this->m_insert_unique(this->m_construct_node(*first));
			}
		}
	}

	template< typename... TArgs >
	auto emplace_equal(TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert_equal(this->m_construct_node(forward<TArgs>(args)...)));
	}

	auto insert_equal(Element const & element) -> Iterator {
		return Iterator(this->m_insert_equal(this->m_construct_node(element)));
	}

	auto insert_equal(Element && element) -> Iterator {
		return Iterator(this->m_insert_equal(this->m_construct_node(move(element))));
	}

	template< typename TValue >
	auto insert_equal(TValue && value) -> Iterator {
		return Iterator(this->m_insert_equal(this->m_construct_node(forward<TValue>(value))));
	}

	template< typename... TArgs >
	auto emplace_equal_hint(ConstIterator hint, TArgs && ... args) -> Iterator {
		return Iterator(this->m_insert_equal(hint.m_pointer, this->m_construct_node(forward<TArgs>(args)...)));
	}

	auto insert_equal(ConstIterator hint, Element const & element) -> Iterator {
		return Iterator(this->m_insert_equal(hint.m_pointer, this->m_construct_node(element)));
	}

	auto insert_equal(ConstIterator hint, Element && element) -> Iterator {
		return Iterator(this->m_insert_equal(hint.m_pointer, this->m_construct_node(move(element))));
	}

	template< typename TValue >
	auto insert_equal(ConstIterator hint, TValue && value) -> EnableIf< IsConstructible<Element, TValue>, Iterator > {
		return Iterator(this->m_insert_equal(hint.m_pointer, this->m_construct_node(forward<TValue>(value))));
	}

	template< typename TIterator >
	auto insert_equal(TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator> > {
		auto end = this->m_end();
		for (; first != last; ++first) {
			this->m_insert_equal(end, this->m_construct_node(*first));
		}
	}

	template< typename TOtherComparator >
	void merge_unique(Implement< TBasic, TElement, TOtherComparator, TAllocator, TClassArgs... > & tree) {
		this->m_merge_unique(tree);
	}

	template< typename TOtherComparator >
	void merge_equal(Implement< TBasic, TElement, TOtherComparator, TAllocator, TClassArgs... > & tree) {
		this->m_merge_equal(tree);
	}

	auto erase(ConstIterator position) -> Iterator {
		return Iterator(this->m_erase(position.m_pointer));
	}

	auto erase(ConstIterator first, ConstIterator last) -> Iterator {
		auto f = first.m_pointer, l = last.m_pointer;
		for(; f != l;) {
			f = this->m_erase(f);
		}
		return Iterator(f);
	}

	auto erase(Element const & element) -> Size {
		auto range = this->m_equal_range(element);
		Size n = 0;
		for(; range.first != range.second; ++n) {
			range.first = this->m_erase(range.first);
		}
		return n;
	}

	template< typename TKey >
	auto erase(TKey const & key) -> Size {
		auto range = this->m_equal_range(key);
		Size n = 0;
		for(; range.first != range.second; ++n) {
			range.first = this->m_erase(range.first);
		}
		return n;
	}

	void clear() noexcept {
		this->m_clear();
	}

protected:
	static auto make_iterator(NodePointer pointer) -> Iterator {
		return Iterator(pointer);
	}

	static auto make_const_iterator(NodePointer pointer) -> ConstIterator {
		return ConstIterator(pointer);
	}

	static auto unwrap_iterator(Iterator iterator) {
		return iterator.m_pointer;
	}

}; // Implement< TBasic, TElement, TComparator, TAllocator, TArgs... >

} // namespace BinaryTree
} // namespace Container
} // namespace Detail
} // namespace BR

