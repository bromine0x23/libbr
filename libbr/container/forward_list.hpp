#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/move_iterator.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_destructor.hpp>
#include <libbr/memory/scoped_pointer.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_pointer.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_traits/allocator_traits.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/type_traits/is_nothrow_default_constructible.hpp>
#include <libbr/type_traits/is_nothrow_move_assignable.hpp>
#include <libbr/type_traits/is_nothrow_move_constructible.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/type_traits/pointer_traits.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/initializer_list.hpp>
#include <libbr/utility/compressed_pair.hpp>

namespace BR {

template< typename TElement, typename TAllocator >
class ForwardList;

namespace Detail {
namespace ForwardList {

using namespace Iterator;
using namespace Memory;
using namespace TypeOperate;
using namespace TypeTraits;

template< typename TNodePointer >
struct BasicNode;

template< typename TElement, class TVoidPointer >
struct Node;

template< typename TNodePointer >
class Iterator;

template< typename TNodeConstPointer >
class ConstIterator;

template< typename TElement, typename TAllocator >
class Base;

template< typename TNodePointer >
struct BasicNode  {
	using Pointer = TNodePointer;

	HeadNode() : next(nullptr) {}

	Pointer next;
};

template< typename TElement, class TVoidPointer >
using HeadNode = BasicNode< PointerTraits<TVoidPointer>::Rebind< Node<TElement, TVoidPointer> > >;

template< typename TElement, class TVoidPointer >
struct Node : public HeadNode< TElement, TVoidPointer > {
	using Element = TElement;
	Element element;
};

template< typename TNodePointer >
class Iterator {
	using NodePointer = TNodePointer;
	using NodePointerTraits = PointerTraits<NodePointer>;

	template< typename TElement, typename TAllocator >
	friend class ForwardList;

	template< typename >
	friend class ConstIterator;

public:
	using Category   = ForwardIteratorTag;
	using Element    = typename NodePointerTraits::Element::Element;
	using Reference  = Element &;
	using Difference = typename NodePointerTraits::Difference;
	using Pointer    = typename NodePointerTraits::Rebind<Element>;

	Iterator() noexcept : m_pointer(nullptr) {}

	Reference operator*() const {
		return m_pointer->value;
	}

	Pointer operator->() const {
		return PointerTraits<Pointer>::make_pointer(m_pointer->value);
	}

	Iterator & operator++() {
		m_pointer = m_pointer->next;
		return *this;
	}

	Iterator & operator++(int) {
		Iterator temp(*this);
		++(*this);
		return *temp;
	}

	friend  bool operator==(Iterator const & x, Iterator const & y) {
		return x.m_pointer == y.m_pointer;
	}

	friend  bool operator!=(Iterator const & x, Iterator const & y) {
		return !(x == y);
	}

private:
	explicit Iterator(NodePointer pointer) noexcept : m_pointer(pointer) {}

private:
	TNodePointer m_pointer;
}; // class Iterator<TNodePointer>

template< typename TNodeConstPointer >
class ConstIterator {
	using NodeConstPointer       = TNodeConstPointer;
	using NodeConstPointerTraits = PointerTraits<NodeConstPointer>;
	using Node                   = RemoveConst< NodeConstPointerTraits::Element >;
	using NodePointer            = NodeConstPointerTraits::Rebind<Node>;

	template< typename TElement, typename TAllocator >
	friend class ForwardList;

public:
	using Category   = ForwardIteratorTag;
	using Element    = typename Node::Element;
	using Reference  = Element const &;
	using Difference = typename NodeConstPointerTraits::Difference;
	using Pointer    = typename NodeConstPointerTraits::Rebind<Element const>;

	ConstIterator() noexcept : m_pointer(nullptr) {}

	ConstIterator(Iterator<NodePointer> iterator) noexcept : m_pointer(iterator.m_pointer) {}

	Reference operator*() const {
		return m_pointer->value;
	}

	Pointer operator->() const {
		return PointerTraits<Pointer>::make_pointer(m_pointer->value);
	}

	Iterator & operator++() {
		m_pointer = m_pointer->next;
		return *this;
	}

	Iterator & operator++(int) {
		Iterator temp(*this);
		++(*this);
		return *temp;
	}

	friend  bool operator==(ConstIterator const & x, ConstIterator const & y) {
		return x.m_pointer == y.m_pointer;
	}

	friend  bool operator!=(ConstIterator const & x, ConstIterator const & y) {
		return !(x == y);
	}

private:
	explicit ConstIterator(NodePointer pointer) noexcept : m_pointer(pointer) {}

private:
	NodeConstPointer m_pointer;
}; // class ConstIterator<TNodeConstPointer>

template< typename TElement >
inline bool operator==(Iterator<TElement> const  & x, ConstIterator<TElement> const & y) {
	return x.node == y.node;
}

template<typename _Tp>
inline bool operator!=(Iterator<TElement> const  & x, ConstIterator<TElement> const & y) {
	return x.node != y.node;
}

template< typename TElement, typename TAllocator >
class Base {
protected:
	using Element   = TElement;
	using Allocator = TAllocator;

	using VoidPointer = typename AllocatorTraits<Allocator>::VoidPointer;

	using Node             = Node< Element , VoidPointer >;
	using NodeAllocator    = typename AllocatorTraits<Allocator>::Rebind<Node>;
	using NodeTraits       = AllocatorTraits<NodeAllocator>;
	using NodePointer      = typename NodeTraits::Pointer;
	using NodeConstPointer = typename NodeTraits::Pointer;

	using HeadNode          = HeadNode< Element, VoidPointer >;
	using HeadNodeAllocator = typename AllocatorTraits<Allocator>::Rebind<HeadNode>;
	using HeadNodeTraits    = AllocatorTraits<HeadNodeAllocator>;
	using HeadNodePointer   = typename HeadNodeTraits::Pointer;

	using Iterator = Iterator<NodePointer>;
	using ConstIterator = ConstIterator<NodePointer>;

public:
	Base(Base && list) noexcept(
		IsNothrowMoveConstructible<NodeAllocator>::value
	) : m_impl(move(list.m_impl)) {
		list.m_head()->next = nullptr;
	}

	Base(Base && list, Allocator const & allocator) : m_impl(HeadNode(), NodeAllocator(allocator)) {
		if (m_allocator() == list.m_allocator()) {
			m_head()->next = list.m_head()->next;
			list.m_head()->next = nullptr;
		}
	}

	~Base() {
		m_clear();
	}

	void swap(Base & list) noexcept(
		!NodeTraits::IsPropagateOnContainerSwap::value || IsNothrowSwappable<NodeAllocator>::value
	) {
		m_swap_allocator(m_allocator(), list.m_allocator());
		using swap;
		swap(m_head()->next, list.m_head()->next);
	}

protected:

	Base() noexcept(IsNothrowDefaultConstructible<NodeAllocator>::value) : m_impl(HeadNode()) {}

	Base(Allocator const & allocator) : m_impl(HeadNode(), NodeAllocator(allocator)) {}

	NodePointer m_head() noexcept {
		return static_cast<NodePointer>(PointerTraits<HeadNodePointer>::pointer_to(m_impl.first()));
	}

	NodeConstPointer m_head() const noexcept {
		return static_cast<NodeConstPointer>(PointerTraits<HeadNodePointer>::pointer_to(const_cast<HeadNode &>(m_impl.first())));
	}

	NodeAllocator & m_allocator() noexcept {
		return m_impl.second();
	}

	NodeAllocator const & m_allocator() const noexcept {
		return m_impl.second();
	}

	void m_copy_assign_allocate(Base const & list) {
		m_copy_assign_allocate(list, NodeTraits::IsPropagateOnContainerCopyAssignment());
	}

	void m_move_assign_allocate(Base & list) noexcept(
		!NodeTraits::IsPropagateOnContainerMoveAssignment::value || IsNothrowMoveAssignable<NodeAllocator>::value
	) {
		m_move_assign_allocate(list, NodeTraits::IsPropagateOnContainerMoveAssignment());
	}

	void m_clear() noexcept {
		NodeAllocator & allocator = m_allocator();
		for (NodePointer pointer = m_head()->next; pointer != nullptr;) {
			NodePointer next = pointer->next;
			NodeTraits::destroy(allocator, address_of(pointer->element));
			NodeTraits::deallocate(allocator, pointer, 1);
			pointer = next;
		}
		m_head()->next = nullptr;
	}

private:
	Base(Base const &) = delete;
	Base & operator=(Base const &) = delete;

	void m_copy_assign_allocate(Base const & list, BooleanFalse) {}

	void m_copy_assign_allocate(Base const & list, BooleanTrue) {
		if (m_allocator() != list.m_allocator()) {
			m_clear();
		}
		m_allocator() = list.m_allocator();
	}

	void m_move_assign_allocate(Base & list, BooleanFalse) noexcept {}

	void m_move_assign_allocate(Base & list, BooleanTrue) noexcept(
		IsNothrowMoveAssignable<NodeAllocator>::value
	) {
		m_allocator() = move(list.m_allocator());
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y) noexcept(
		!NodeTraits::IsPropagateOnContainerSwap::value || IsNothrowSwappable<NodeAllocator>::value
	) {
		swap_allocator(x, y, NodeTraits::IsPropagateOnContainerSwap());
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanFalse) noexcept {}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanTrue) noexcept(
		IsNothrowSwappable<NodeAllocator>::value
	) {
		using swap;
		swap(x, y);
	}

protected:
	CompressedPair< HeadNode, NodeAllocator > m_impl;

}; // class Base< TElement, TAllocator >

} // namespace ForwardList
} // namespace Detail

template< typename TElement, typename TAllocator = Memory::Allocator<TElement> >
class ForwardList : private Detail::ForwardList::Base< TElement, TAllocator > {

public:
	using Element = TElement;
	using Allocator = TAllocator;

private:
	using Base = Detail::ForwardList::Base< TElement, TAllocator >;
	using Node          = typename Base::Node;
	using NodeAllocator = typename Base::NodeAllocator;
	using NodePointer   = typename Base::NodePointer;
	using NodeTraits    = typename Base::NodeTraits;

public:
	using Reference      = AddLValueReference<Element>;
	using ConstReference = AddLValueReference< AddConst<Element> >;
	using Pointer        = typename AllocatorTraits<Allocator>::Pointer;
	using ConstPointer   = typename AllocatorTraits<Allocator>::ConstPointer;
	using Difference     = typename AllocatorTraits<Allocator>::Difference;
	using Size           = typename AllocatorTraits<Allocator>::Size;
	using Iterator       = typename Base::Iterator;
	using ConstIterator  = typename Base::ConstIterator;

	ForwardList() noexcept(TypeOperate::IsNothrowDefaultConstructible<NodeAllocator>::value) = default;

	explicit ForwardList(Allocator const & allocator) : Base(allocator) {};

	explicit ForwardList(Size capacity) {
		m_prepare_after(Base::m_head(), capacity);
	}

	explicit ForwardList(Size capacity, Allocator const & allocator) : Base(allocator), ForwardList(capacity) {}

	ForwardList(Size size, Element const & element) {
		insert_after(chead(), size, element);
	}

	ForwardList(Size size, Element const & element, Allocator const & allocator) : Base(allocator), ForwardList(size, element) {}

	template< typename TInputIterator >
	ForwardList(
		TInputIterator first,
		TInputIterator last,
		EnableIf<
			IsSame< IteratorCategory<TInputIterator>, Iterator::InputIteratorTag >
		> * = nullptr
	) {
		insert_after(chead(), first, last);
	}

	template< typename TInputIterator >
	ForwardList(
		TInputIterator first,
		TInputIterator last,
		Allocator const & allocator,
		EnableIf<
			IsSame< IteratorCategory<TInputIterator>, Iterator::InputIteratorTag >
		> * = nullptr
	) : Base(allocator), ForwardList(first, last) {}

	ForwardList(ForwardList const & list) : Base(Allocator(NodeTraits::select_on_container_copy_construction(list.m_allocator()))) {
		insert_after(chead(), list.begin(), list.end());
	}

	ForwardList(ForwardList const & list, Allocator const & allocator) : Base(allocator) {
		insert_after(chead(), list.begin(), list.end());
	}

	ForwardList(ForwardList && list) noexcept(is_nothrow_move_constructible<Base>::value) : base(move(list)) {}

	ForwardList(ForwardList && list, Allocator const & allocator) : Base(move(allocator)){
		if (Base::m_allocator() != list.m_allocator()) {
			insert_after(chead(), MoveIterator<Iterator>(list.begin()), MoveIterator<Iterator>(list.end()));
		}
	}

	ForwardList(InitializerList<Element> list) {
		insert_after(chead(), list.begin(), list.end());
	}

	ForwardList(InitializerList<Element> list, Allocator const & allocator) : Base(allocator), ForwardList(list) {}

	ForwardList & operator=(ForwardList const & list) {
		if (this != &list) {
			Base::m_copy_assign_allocate(list);
			assign(list.begin(), list.end());
		}
		return *this;
	}

	ForwardList & operator=(ForwardList && list) noexcept(
		BooleanAnd<
			NodeTraits::IsPropagateOnContainerMoveAssignment,
			IsNothrowMoveAssignable<Allocator>
		>::value
	) {
		m_move_assign(list, NodeTraits::IsPropagateOnContainerMoveAssignment());
		return *this;
	}

	ForwardList & operator=(InitializerList<Element> list) {
		assign(list.begin(), list.end());
		return *this;
	}

	template< class TInputIterator >
	EnableIf<
		IsSame< IteratorCategory<TInputIterator>, Iterator::InputIteratorTag >,
		ForwardList &
	> assign(TInputIterator first, TInputIterator last) {
		Iterator i = head();
		Iterator ni = next(i);
		Iterator e = end();
		for (; ni != e && first != last; ++i, ++ni, ++first) {
			*ni = *first;
		}
		if (ni == e) {
			insert_after(i, first, last);
		} else {
			erase_after(i, e);
		}
		return *this;
	}

	ForwardList & assign(Size size, Element const & element) {
		Iterator i = head();
		Iterator ni = next(i);
		Iterator e = end();
		for (; ni != e && size > 0; --size, ++i, ++ni) {
			*ni = element;
		}
		if (ni == e) {
			insert_after(i, size, element);
		} else {
			erase_after(i, e);
		}
		return *this;
	}

	ForwardList & assign(InitializerList<Element> list) {
		return assign(list.begin(), list.end());
	}

	Allocator get_allocator() const noexcept {
		return Allocator(Base::m_allocator());
	}

	Iterator begin() noexcept {
		return Iterator(Base::m_head()->next);
	}

	ConstIterator begin() const noexcept {
		return ConstIterator(Base::m_head()->next);
	}

	Iterator end() noexcept {
		return Iterator(nullptr);
	}

	ConstIterator end() const noexcept {
		return ConstIterator(nullptr);
	}

	ConstIterator cbegin() const noexcept {
		return ConstIterator(Base::m_head()->next);
	}

	ConstIterator cend() const noexcept {
		return ConstIterator(nullptr);
	}

	Iterator head() noexcept {
		return Iterator(Base::m_head());
	}

	ConstIterator head() const noexcept {
		return ConstIterator(Base::m_head());
	}

	ConstIterator chead() const noexcept {
		return ConstIterator(Base::m_head());
	}

	bool is_empty() const noexcept {
		return Base::m_head()->next == nullptr;
	}

	Size max_size() const noexcept {
		return TypeTraits::IntegerTraits<Size>::max();
	}

	Reference front() {
		return Base::m_head()->next->value;
	}

	ConstReference front() const {
		return Base::m_head()->next->value;
	}

	template< typename ... TArgs >
	void emplace_front(TArgs && ... args) {
		using Deleter = Memory::AllocatorDestructor<NodeAllocator>;
		NodeAllocator & allocator = Base::m_allocator();
		Memory::ScopedPointer< Node, Deleter > node(NodeTraits::allocate(allocator, 1), Deleter(allocator, 1));
		NodeTraits::construct(allocator, Memory::address_of(node->element), forward<TArgs>(args)...);
		node->next = Base::head->next;
		Base::head()->next = node.release();
	}

	void push_front(Element const & element) {
		emplace_front(element);
	}

	void push_front(Element && element) {
		emplace_front(move(element));
	}

	void pop_front() {
		NodeAllocator & allocator = Base::m_allocator();
		NodePointer pointer = Base::m_head()->next;
		Base::m_head()->next = pointer->next;
		NodeTraits::destroy(allocator, Memory::address_of(pointer->element));
		NodeTraits::deallocate(allocator, pointer, 1);
	}

	template< typename ... TArgs >
	Iterator emplace_after(ConstIterator position, TArgs && ... args) {
		using Deleter = Memory::AllocatorDestructor<NodeAllocator>;
		NodeAllocator & allocator = Base::m_allocator();
		Memory::ScopedPointer< Node, Deleter > node(NodeTraits::allocate(allocator, 1), Deleter(allocator, 1));
		NodeTraits::construct(allocator, Memory::address_of(node->element), forward<TArgs>(args)...);
		NodePointer const pos = position.m_pointer;
		node->next = pos->next;
		pos->next = node.release();
		return Iterator(pos->next);
	}

	Iterator insert_after(ConstIterator position, Element const & element) {
		return emplace_after(position, element);
	}

	Iterator insert_after(ConstIterator position, Element && element) {
		return emplace_after(position, move(element));
	}

	Iterator insert_after(ConstIterator position, Size size, Element const & element) {
		NodePointer pos = position.m_pointer;
		if (size > 0) {
			using Deleter = Memory::AllocatorDestructor<NodeAllocator>;
			NodeAllocator & allocator = Base::m_allocator();
			Memory::ScopedPointer< Node, Deleter > node(NodeTraits::allocate(allocator, 1), Deleter(allocator, 1));
			NodeTraits::construct(allocator, Memory::address_of(node->element), element);
			NodePointer first = node.release();
			NodePointer last = first;
			try {
				for (; size-- > 0; last = last->next) {
					node.reset(NodeTraits::allocate(allocator, 1));
					NodeTraits::construct(allocator, Memory::address_of(node->element), element);
					last->next = node.release();
				}
			} catch (...) {
				while (first != nullptr) {
					NodePointer next = first->next;
					NodeTraits::destroy(allocator, Memory::address_of((first->element)));
					NodeTraits::deallocate(allocator, frist, 1);
					first = next;
				}
				throw;
			}
			last->next = pos->next;
			pos->next = first;
			pos = last;
		}
		return Iterator(pos);
	}

	template< typename TInputIterator >
	EnableIf<
		IsSame< IteratorCategory<TInputIterator>, Iterator::InputIteratorTag >,
		TInputIterator
	> insert_after(ConstIterator position, TInputIterator first, TInputIterator last) {
		NodePointer pos = position.m_pointer;
		if (first != last) {
			using Deleter = Memory::AllocatorDestructor<NodeAllocator>;
			NodeAllocator & allocator = Base::m_allocator();
			Memory::ScopedPointer< Node, Deleter > node(NodeTraits::allocate(allocator, 1), Deleter(allocator, 1));
			NodeTraits::construct(allocator, Memory::address_of(node->element), *first);
			NodePointer first = node.release();
			NodePointer last = first;
			try {
				for (++first; first != last; ++first, last = last->next) {
					node.reset(NodeTraits::allocate(allocator, 1));
					NodeTraits::construct(allocator, Memory::address_of(node->element), element);
					last->next = node.release();
				}
			} catch (...) {
				while (first != nullptr) {
					NodePointer next = first->next;
					NodeTraits::destroy(allocator, Memory::address_of((first->element)));
					NodeTraits::deallocate(allocator, frist, 1);
					first = next;
				}
				throw;
			}
			last->next = pos->next;
			pos->next = first;
			pos = last;
		}
		return Iterator(pos);
	}

	iterator insert_after(ConstIterator pos, InitializerList<Element> list) {
		return insert_after(pos, list.begin(), list.end());
	}

	Iterator erase_after(ConstIterator position) {
		NodePointer p = position.m_pointer;
		NodePointer n = p->next;
		p->next = n->next;
		NodeAllocator & allocator = Base::m_allocator();
		NodeTraits::destroy(allocator, Memory::address_of((n->element)));
		NodeTraits::deallocate(allocator, n, 1);
		return Iterator(p->next);
	}

	Iterator erase_after(ConstIterator first, ConstIterator last) {
		NodePointer e = last.m_pointer;
		if (first != last) {
			NodePointer p = first.m_pointer;
			NodePointer n = p->next;
			if (n != e) {
				p->next = e;
				NodeAllocator & allocator = Base::m_allocator();
				do {
					p = n->next;
					NodeTraits::destroy(allocator, Memory::address_of((n->element)));
					NodeTraits::deallocate(allocator, n, 1);
					n = p;
				} while (n != e);
			}
		}
		return Iterator(e);
	}

	ForwardList & swap(ForwardList & list) noexcept(noexcept(Base::swap(list))) {
		Base::swap(list);
	}

	ForwardList & resize(Size size) {
		Size c = 0;
		Iterator i = head();
		Iterator ni = begin();
		Iterator e = end();
		for (; ni != e && c < size; ++i, ++ni, ++c) {}
		if (ni != e) {
			erase_after(i, e);
		} else {
			m_prepare_after(i.m_pointer, size - c);
		}
	}

	ForwardList & resize(Size size, Element const & element) {
		Size c = 0;
		Iterator i = head();
		Iterator ni = begin();
		Iterator e = end();
		for (; ni != e && c < size; ++i, ++ni, ++c) {}
		if (ni != e) {
			erase_after(i, e);
		} else {
			size -= c;
			if (size > 0) {
				using Deleter = Memory::AllocatorDestructor<NodeAllocator>;
				NodeAllocator & allocator = Base::m_allocator();
				Memory::ScopedPointer< Node, Deleter > node(nullptr, Deleter(allocator, 1));
				for (NodePointer pointer = i.m_pointer; size > 0; --size, pointer = pointer->next) {
					node.reset(NodeTraits::allocate(allocator, 1));
					NodeTraits::construct(allocator, Memory::address_of(node->element), element);
					node->next = nullptr;
					pointer->next = node.release();
				}
			}
		}
	}

	ForwardList & clear() noexcept {
		Base::clear();
	}

	void splice_after(ConstIterator p, ForwardList & list) {
		if (!list.is_empty()) {
			if (insert_position.m_pointer->next != nullptr) {
				ConstIterator i = list.head();
				while (i.m_pointer->next != nullptr) {
					++i;
				}
				i.m_pointer->next = p.m_pointer->next;
			}
			p.m_pointer->next = list.m_head()->next;
			list.m_head()->next = nullptr;
		}
	}

	void splice_after(ConstIterator p, ForwardList & list, ConstIterator e) {
		ConstIterator i = Iterator::next(e);
		if (p != e && p != i) {
			e.m_pointer->next = i.m_pointer->next;
			i.m_pointer->next = p.m_pointer->next;
			p.m_pointer->next = i.m_pointer;
		}
	}

	void splice_after(ConstIterator p, ForwardList & list, ConstIterator f, ConstIterator l) {
		if (f != l && p != f) {
			ConstIterator i = f;
			while (i.m_pointer->next != l.m_pointer) {
				++i;
			}
			if (f != i) {
				i.m_pointer->next = p.m_pointer->next;
				p.m_pointer->next = f.m_pointer->next;
				f.m_pointer->next = l.m_pointer;
			}
		}
	}

	void splice_after(ConstIterator p, ForwardList && list) {
		splice_after(p, list);
	}

	void splice_after(ConstIterator p, ForwardList && list, ConstIterator e) {
		splice_after(p, list, e);
	}

	void splice_after(ConstIterator p, ForwardList && list, ConstIterator f, ConstIterator l) {
		splice_after(p, x, f, l);
	}

	void remove(Element const & element) {
		// TODO: remove(equal<Element>());
	}

	template< typename TUnaryPredicate>
	void remove_if(TUnaryPredicate unary_predicate) {
		Iterator e = end();
		for (Iterator i = head(); i.m_pointer->next != nullptr;) {
			if (unary_predicate(i.m_pointer->next->element)) {
				Iterator j = Iterator::next(i, 2);
				for (; j != e && unary_predicate(*j); ++j) {}
				erase_after(i, j);
				if (j == e) {
					break;
				}
				i = j;
			}
			else {
				++i;
			}
		}
	}

	template< typename TBinaryPredicate>
	void unique(TBinaryPredicate binary_predicate) {
		for (Iterator i = begin(), e = end(); i != e;) {
			Iterator j = Iterator::next(i);
			for (; j != e && binary_predicate(*i, *j); ++j) {}
			if (i.m_pointer->next != j.m_pointer) {
				erase_after(i, j);
			}
			i = j;
		}
	}

	void unique() {
		// TODO: unique(__equal_to<Element>());
	}

	template< typename TComparator >
	void merge(ForwardList & list, TComparator comparator) {
		if (this != &list) {
			Base::m_head()->next = m_merge(Base::m_head()->next, list.m_head()->next, comparator);
			list.m_head()->next = nullptr;
		}
	}

	void merge(ForwardList & list) {
		// TODO: merge(list, __less<Element>());
	}

	template< typename TComparator >
	void merge(ForwardList && list, TComparator comparator) {
		merge(list, move(comparator));
	}

	void merge(ForwardList && list) {
		// TODO: merge(list, __less<Element>());
	}

	template< typename TComparator >
	void sort(Comparator comparator) {
		Base::m_head()->next = m_sort(base::m_head()->next, Iterator::distance(begin(), end()), comparator);
	}

	void sort() {
		// TODO: sort(__less<Element>());
	}

	void reverse() noexcept {
		NodePointer p = Base::m_head()->next;
		if (p != nullptr) {
			NodePointer f = p->next;
			p->next_ = nullptr;
			while (f != nullptr) {
				NodePointer t = f->next;
				f->next = p;
				p = f;
				f = t;
			}
			Base::m_head()->next = p;
		}
	}

private:
	void m_prepare_after(NodePointer position, Size size) {
		if (size > 0) {
			using Deleter = Memory::AllocatorDestructor<NodeAllocator>;
			NodeAllocator & allocator = Base::m_allocator();
			Memory::ScopedPointer< Node, Deleter > node(nullptr, Deleter(allocator, 1));
			for (NodePointer pointer = position; size > 0; --size, pointer = pointer->next) {
				node.reset(NodeTraits::allocate(allocator, 1));
				NodeTraits::construct(allocator, Memory::address_of(node->element));
				node->next = nullptr;
				pointer->next = node.release();
			}
		}
	}

	void m_move_assign(ForwardList & list, TypeOperate::BooleanTrue) noexcept(
		TypeOperate::IsNothrowMoveAssignable<Allocator>::value
	) {
		clear();
		Base::m_move_assign_allocate(list);
		Base::m_head()->next = list.m_head()->next;
		list.m_head()->next = nullptr;
	}


	void m_move_assign(ForwardList & list, TypeOperate::BooleanFalse ) {
		if (Base::m_allocator() == list.m_allocator()) {
			__move_assign(__x, true_type());
		} else {
			assign(Iterator::MoveIterator<Iterator>(list.begin()), Iterator::MoveIterator<Iterator>(list.end()));
		}
	}

	template< typename TComparator >
	static NodePointer m_merge(NodePointer f1, NodePointer f2, TComparator & comparator) {
		if (f1 == nullptr) {
			return f2;
		}
		if (f2 == nullptr) {
			return f1;
		}
		NodePointer r;
		if (comparator(f2->element, f1->element)) {
			NodePointer t = f2;
			for (; t->next != nullptr && comparator(t->next->element, f1->element); t = t->next) {}
			r = f2;
			f2 = t->next;
			t->next = f1;
		} else {
			r = f1;
		}
		NodePointer p = f1;
		f1 = f1->next;
		while (f1 != nullptr && f2 != nullptr) {
			if (comparator(f2->element, f1->element)) {
				NodePointer t = f2;
				for (; t->next != nullptr && comparator(t->next->element, f1->element); t = t->next) {}
				p->next = f2;
				f2 = t->next;
				t->next = f1;
			}
			p = f1;
			f1 = f1->next;
		}
		if (f2 != nullptr) {
			p->next = f2;
		}
		return r;
	}

	template< typename TComparator >
	static NodePointer m_sort(NodePointer f, Difference size, TComparator & comparator) {
		switch (size) {
			case 0:
			case 1:
				return f1;
			case 2:
				if (comparator(f1->next->element, f1->element)) {
					NodePointer t = f1->next;
					t->next = f1;
					f1->next = nullptr;
					f1 = t;
				}
				return f1;
		}
		Difference sz1 = size / 2;
		Difference sz2 = size - sz1;
		NodePointer t = Iterator::next(Iterator(f1), sz1 - 1).m_pointer;
		NodePointer f2 = t->next;
		t->next = nullptr;
		return m_merge(m_sort(f1, sz1, comparator), m_sort(f2, sz2, comparator), comparator);
	}

}; // class ForwardList< TElement, TAllocator >

template< typename TElement, typename TAllocator >
bool operator==(ForwardList< TElement, TAllocator > const & x, ForwardList< TElement, TAllocator > const & y) {
	using I = typename ForwardList< TElement, TAllocator >::ConstIterator;
	I ix = x.begin();
	I ex = x.end();
	I iy = y.begin();
	I ey = y.end();
	for (; ix != ex && iy != ey; ++ix, ++iy) {
		if (!(*ix == *iy)) {
			return false;
		}
	}
	return (ix == ex) == (iy == ey);
}

template< typename TElement, typename TAllocator >
inline bool operator!=(ForwardList< TElement, TAllocator > const & x, ForwardList< TElement, TAllocator > const & y) {
	return !(x == y);
}

template< typename TElement, typename TAllocator >
inline bool operator<(ForwardList< TElement, TAllocator > const & x, ForwardList< TElement, TAllocator > const & y) {
	// return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template< typename TElement, typename TAllocator >
inline bool operator>(ForwardList< TElement, TAllocator > const & x, ForwardList< TElement, TAllocator > const & y) {
	return y < x;
}

template< typename TElement, typename TAllocator >
inline bool operator>=(ForwardList< TElement, TAllocator > const & x, ForwardList< TElement, TAllocator > const & y) {
	return !(x < y);
}

template< typename TElement, typename TAllocator >
inline bool operator<=(ForwardList< TElement, TAllocator > const & x, ForwardList< TElement, TAllocator > const & y) {
	return !(y < x);
}

template< typename TElement, typename TAllocator >
inline void swap(
	ForwardList< TElement, TAllocator > const & x,
	ForwardList< TElement, TAllocator > const & y
) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}

} // namespace BR