#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/memory/pointer_traits.hpp>

namespace BR {

inline namespace Container {

template< typename TElement, typename TAllocator >
class DList;

} // inline namespace Container

namespace Detail {
namespace Container {
namespace DList {

template< typename TNodePointer >
class Iterator;

template< typename TNodePointer >
class ConstIterator;

template< typename TNodePointer >
class Iterator : public IteratorWithCategory< ReadableTag, WritableTag, BidirectionalTraversalTag > {
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = BR::PointerTraits<NodePointer>;

	using Node = typename NodePointerTraits::Element;

	template< typename, typename >
	friend class BR::DList;

	template< typename >
	friend class ConstIterator;

public:
	using Element = typename Node::Element;

	using Pointer = typename NodePointerTraits::template Rebind<Element>;

	using Reference = Element &;

	using Difference = typename NodePointerTraits::Difference;

private:
	using PointerTraits = BR::PointerTraits<Pointer>;

public:
	Iterator() noexcept : m_pointer(nullptr) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return PointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> Iterator & {
		m_pointer = m_pointer->next;
		return *this;
	}

	auto operator++(int) -> Iterator {
		Iterator temp(*this);
		operator++();
		return temp;
	}

	auto operator--() -> Iterator & {
		m_pointer = m_pointer->prev;
		return *this;
	}

	auto operator--(int) -> Iterator {
		Iterator temp(*this);
		operator--();
		return temp;
	}

	auto operator==(Iterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator const & y) const -> bool {
		return !operator==(y);
	}

private:
	explicit Iterator(NodePointer pointer) noexcept : m_pointer(pointer) {
	}

private:
	NodePointer m_pointer;
}; // class Iterator<TNodePointer>

template< typename TNodePointer >
class ConstIterator : public IteratorWithCategory< ReadableTag, BidirectionalTraversalTag > {
private:
	using NodePointer = TNodePointer;

	using NodePointerTraits = BR::PointerTraits<NodePointer>;

	using Node = typename NodePointerTraits::Element;

	template< typename, typename >
	friend class BR::DList;

public:
	using Element = typename Node::Element;

	using Pointer = typename NodePointerTraits::template Rebind<Element const>;

	using Reference = Element const &;

	using Difference = typename NodePointerTraits::Difference;

private:
	using PointerTraits = BR::PointerTraits<Pointer>;

public:
	ConstIterator() noexcept : m_pointer(nullptr) {
	}

	ConstIterator(Iterator<NodePointer> iterator) noexcept : m_pointer(iterator.m_pointer) {
	}

	auto operator*() const -> Reference {
		return m_pointer->element;
	}

	auto operator->() const -> Pointer {
		return PointerTraits::make_pointer(m_pointer->element);
	}

	auto operator++() -> ConstIterator & {
		m_pointer = m_pointer->next;
		return *this;
	}

	auto operator++(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator++();
		return *temp;
	}

	auto operator--() -> ConstIterator & {
		m_pointer = m_pointer->prev;
		return *this;
	}

	auto operator--(int) -> ConstIterator {
		ConstIterator temp(*this);
		operator--();
		return *temp;
	}

	auto operator==(ConstIterator const & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(ConstIterator const & y) const -> bool {
		return !operator==(y);
	}

	auto operator==(Iterator<NodePointer> const  & y) const -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(Iterator<NodePointer> const  & y) const -> bool {
		return !operator==(y);
	}

private:
	explicit ConstIterator(NodePointer pointer) noexcept : m_pointer(pointer) {}

private:
	NodePointer m_pointer;
}; // class ConstIterator<TNodeConstPointer>

template< typename TNodePointer >
inline auto operator==(Iterator<TNodePointer> const & x, ConstIterator<TNodePointer> const & y) -> bool {
	return y == x;
}

template< typename TNodePointer >
inline auto operator!=(Iterator<TNodePointer> const & x, ConstIterator<TNodePointer> const & y) -> bool {
	return y != x;
}

} // namespace DList
} // namespace Container
} // namespace Detail

} // namespace BR