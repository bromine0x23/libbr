/**
 * @file
 * @brief Deque
 * @author Bromine0x23
 * @since 2015/11/19
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/move_backward.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/iterator/move_iterator.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/has_trivial_destructor.hpp>
#include <libbr/type_traits/is_nothrow_swappable.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

template< typename TElement, typename TAllocator = Allocator<TElement> >
class Deque;

namespace Detail {
namespace Container {
namespace Deque {

template< typename TElement, typename TAllocator >
class Chunk {

public:
	using Element = TElement;

	using Allocator = TAllocator;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using Reference = Element &;

	using ConstReference = Element const &;

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using Difference = typename AllocatorTraits::Difference;

	using Size = typename AllocatorTraits::Size;

	using Iterator = Pointer;

	using ConstIterator = ConstPointer;

private:
	using PointerTraits = BR::PointerTraits<Pointer>;

public:

	Chunk() noexcept(HasNothrowDefaultConstructor<Allocator>::value) : m_impl() {
	}

	explicit Chunk(Allocator const & allocator) : m_impl(allocator) {
	}

	Chunk(Size capacity, Size start, Allocator const & allocator) : m_impl(allocator) {
		m_storage_begin() = capacity != 0 ? AllocatorTraits::allocate(m_allocator(), capacity) : nullptr;
		m_begin() = m_end() = m_storage_begin() + start;
		m_storage_end() = m_storage_begin() + capacity;
	}

	Chunk(Chunk && chunk) noexcept(HasNothrowMoveConstructor<Allocator>::value) : m_impl(move(chunk.m_impl)) {
		chunk.m_storage_begin() = chunk.m_begin() = chunk.m_end() = chunk.m_storage_end() = nullptr;
	}

	Chunk(Chunk && chunk, Allocator const & allocator) : m_impl(allocator) {
		if (m_allocator() == chunk.m_allocator()) {
			m_storage_begin() = chunk.m_storage_begin();
			m_begin() = chunk.m_begin();
			m_end() = chunk.m_end();
			m_storage_end() = chunk.m_storage_end();
			chunk.m_storage_begin() = chunk.m_begin() = chunk.m_end() = chunk.m_storage_end() = nullptr;
		} else {
			auto capacity = chuck.size();
			m_storage_begin() = AllocatorTraits::allocate(m_allocator(), capacity);
			m_begin() = m_end() = m_storage_begin();
			m_storage_end() = m_storage_begin() + capacity;
			m_construct_at_end(make_move_iterator(chuck.begin()), make_move_iterator(chuck.end()));
		}
	}

	~Chunk() {
		clear();
		if (m_storage_begin() != nullptr) {
			AllocatorTraits::deallocate(m_allocator(), m_storage_begin(), capacity());
		}
	}

	auto operator=(Chunk && chunk) noexcept(
		BooleanOr<
			BooleanAnd< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment, HasNothrowMoveAssign<Allocator> >,
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment >
		>::value
	) -> Chunk & {
		clear();
		clamp();
		m_storage_begin() = chunk.m_storage_begin();
		m_begin() = chunk.m_begin();
		m_end() = chunk.m_end();
		m_storage_end() = chunk.m_storage_end();
		m_move_assign_allocator(chunk, typename AllocatorTraits::IsPropagateOnContainerMoveAssignment());
		chunk.m_storage_begin() = chunk.m_begin() = chunk.m_end() = chunk.m_storage_end() = nullptr;
		return *this;
	}

	auto begin() noexcept -> Iterator {
		return m_begin();
	}

	auto begin() const noexcept -> ConstIterator {
		return m_begin();
	}

	auto end() noexcept -> Iterator {
		return m_end();
	}

	auto end() const noexcept -> ConstIterator {
		return m_end();
	}

	auto is_empty() const -> bool {
		return m_begin() == m_end();
	}

	auto size() const -> Size {
		return static_cast<Size>(m_end() - m_begin());
	}

	auto capacity() const -> Size {
		return static_cast<Size>(m_end_storage() - m_begin_storage());
	}

	auto front_spare() const -> Size {
		return static_cast<Size>(m_begin() - m_begin_storage());
	}

	auto back_spare() const -> Size {
		return static_cast<Size>(m_end_storage() - m_end());
	}

	auto front() -> Reference {
		return *m_begin();
	}

	auto front() const -> ConstReference {
		return *m_begin();
	}

	auto back() -> Reference {
		return *(m_end() - 1);
	}

	auto back() const -> ConstReference {
		return *(m_end() - 1);
	}

	void clear() noexcept {
		m_destruct_at_end(m_begin());
	}

	void reserve(Size n) {
		if (n < capacity()) {
			Chuck chuck(n, 0, m_allocator());
			chuck.m_construct_at_end(make_move_iterator(m_begin()), make_move_iterator(m_end()));
			swap(m_storage_begin(), other.m_storage_begin());
			swap(m_begin(), other.m_begin());
			swap(m_end(), other.m_send());
			swap(m_storage_end(), other.m_storage_end());
		}
	}

	void clamp() {
		if (capacity() > size()) {
			try {
				Chuck chuck(size(), 0, m_allocator());
				chuck.m_construct_at_end(make_move_iterator(m_begin()), make_move_iterator(m_end()));
				t.m_end() = t.m_begin() + (m_end() - m_begin());
				swap(m_storage_begin(), other.m_storage_begin());
				swap(m_begin(), other.m_begin());
				swap(m_end(), other.m_send());
				swap(m_storage_end(), other.m_storage_end());
			} catch (...) {
			}
		}
	}

	template< typename ... TArgs >
	auto emplace_front(TArgs && ... args) -> Chunk &;

	auto add_front(Element const & x) -> Chunk & {
		return emplace_front(x);
	}

	auto add_front(Element && x) -> Chunk & {
		return emplace_front(move(x));
	}

	template< typename ... TArgs >
	auto emplace_back(TArgs && ... args) -> Chunk &;

	auto add_back(Element const & x) -> Chunk & {
		return emplace_back(x);
	}

	auto add_back(Element && x) -> Chunk & {
		return emplace_back(move(x));
	}

	void erase_front() {
		m_destruct_at_begin(m_begin() + 1);
	}

	void erase_back() {
		m_destruct_at_end(m_end() - 1);
	}

	void swap(Chunk & other) noexcept(
		BooleanOr<
			BooleanNot< AllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<Allocator>
		>::value
	) {
		using BR::swap;
		swap(m_storage_begin(), other.m_storage_begin());
		swap(m_begin(), other.m_begin());
		swap(m_end(), other.m_send());
		swap(m_storage_end(), other.m_storage_end());
		m_swap_allocator(m_allocator(), other.m_allocator(), typename AllocatorTraits::IsPropagateOnContainerSwap());
	}

private:
	auto m_allocator() noexcept -> Allocator & {
		return m_impl.get<0>();
	}

	auto m_allocator() const noexcept -> Allocator const & {
		return m_impl.get<0>();
	}

	auto m_storage_begin() noexcept -> Pointer & {
		return m_impl.get<1>();
	}

	auto m_storage_begin() noexcept -> Pointer const & {
		return m_impl.get<1>();
	}

	auto m_begin() noexcept -> Pointer & {
		return m_impl.get<2>();
	}

	auto m_begin() noexcept -> Pointer const & {
		return m_impl.get<2>();
	}

	auto m_end() noexcept -> Pointer & {
		return m_impl.get<3>();
	}

	auto m_end() noexcept -> Pointer const & {
		return m_impl.get<3>();
	}

	auto m_storage_end() noexcept -> Pointer & {
		return m_impl.get<4>();
	}

	auto m_storage_end() noexcept -> Pointer const & {
		return m_impl.get<4>();
	}

	void m_construct_at_end(Size n);

	void m_construct_at_end(Size n, Element const & x);

	template< typename TIterator >
	void m_construct_at_end(TIterator first, TIterator last) {
		m_construct_at_end(first, last, IteratorTraits<TIterator>::category());
	}

	template< typename TIterator >
	void m_construct_at_end(TIterator first, TIterator last, SinglePassTraversalTag);

	template< typename TIterator >
	void m_construct_at_end(TIterator first, TIterator last, ForwardTraversalTag);

	void m_destruct_at_begin(Pointer new_begin) {
		m_destruct_at_begin(new_begin, HasTrivialDestructor<Element>());
	}

	void m_destruct_at_begin(Pointer new_begin, BooleanTrue) {
		m_begin() = new_begin;
	}

	void m_destruct_at_begin(Pointer new_begin, BooleanFalse) {
		for (; m_begin() != new_begin;) {
			AllocatorTraits::destroy(m_allocator(), PointerTraits::to_raw(m_begin()++));
		}
	}

	void m_destruct_at_end(Pointer new_end) {
		m_destruct_at_end(new_begin, BooleanFalse());
	}

	void m_destruct_at_end(Pointer new_end, BooleanTrue) {
		m_end() = new_end;
	}

	void m_destruct_at_end(Pointer new_end, BooleanFalse) {
		for (; m_end() != new_end;) {
			AllocatorTraits::destroy(m_allocator(), PointerTraits(--m_end()));
		}
	}

	void m_move_assign_allocator(Chunk & other, BooleanTrue) noexcept(HasNothrowMoveAssign<Allocator>::value) {
		m_allocator() = move(other.m_allocator());
	}

	void m_move_assign_allocator(Chunk & other, BooleanFalse) noexcept {
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanTrue) noexcept(IsNothrowSwappable<NodeAllocator>()) {
		using BR::swap;
		swap(x, y);
	}

	static void m_swap_allocator(NodeAllocator & x, NodeAllocator & y, BooleanFalse) noexcept {
	}

private:
	// allocator, storage_begin, begin, end, storage_end
	Tuple< Allocator, Pointer, Pointer, Pointer, Pointer > m_impl;

private:
	Chunk(Chunk const &) = delete;

	auto operator=(Chunk const &) -> Chunk & = delete;
}; // class Chunk< TElement, TAllocator >

template< typename TElement, typename TAllocator >
void Chunk< TElement, TAllocator >::m_construct_at_end(Size n) {
	auto & allocator = m_allocator();
	do {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()));
		++m_end();
		--n;
	} while (n > 0);
}

template< typename TElement, typename TAllocator >
void Chunk< TElement, TAllocator >::m_construct_at_end(Size n, Element const & x) {
	auto & allocator = m_allocator();
	do {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()), x);
		++m_end();
		--n;
	} while (n > 0);
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
void Chunk< TElement, TAllocator >::m_construct_at_end(TIterator first, TIterator last, SinglePassTraversalTag) {
	auto & allocator = m_allocator();
	for (; first != last; ++first) {
		if (m_end() == m_storage_end()) {
			auto old_cap = m_storage_end() - m_storage_begin();
			auto new_cap = max<Size>(2 * old_cap, 8);
			Chunk buffer(new_cap, 0, allocator);
			for (auto p = m_begin(); p != m_end(); ++p, ++buffer.m_end()) {
				AllocatorTraits::construct(buffer.m_allocator(), PointerTraits::to_raw(buffer.m_end()), move(*p));
			}
			swap(buffer);
		}
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()), *first);
		++m_end();
	}
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
void Chunk< TElement, TAllocator >::m_construct_at_end(TIterator first, TIterator last, ForwardTraversalTag) {
	auto & allocator = m_allocator();
	for (; first != last; ++first) {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()), *first);
		++m_end();
	}
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto Chunk< TElement, TAllocator >::emplace_front(TArgs && ... args) -> Chunk {
	if (m_storage_begin() == m_begin()) {
		if (m_end() < m_storage_end()) {
			auto d = (back_spare() + 1) / 2;
			m_begin() = move_backward(m_begin(), m_end(), m_end() + static_cast<Difference>(d));
			m_end() += d;
		} else {
			auto c = max<Size>(2 * capacity(), 1);
			Chuck chuck(c, (c + 3) / 4, m_allocator());
			chuck.m_construct_at_end(make_move_iterator(m_begin()), make_move_iterator(m_end()));
			swap(m_storage_begin(), other.m_storage_begin());
			swap(m_begin(), other.m_begin());
			swap(m_end(), other.m_send());
			swap(m_storage_end(), other.m_storage_end());
		}
	}
	AllocatorTraits::construct(m_allocator(), PointerTraits ::to_raw(m_begin() - 1), forward<TArgs>(args)...);
	--m_begin();
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto Chunk< TElement, TAllocator >::emplace_back(TArgs && ... args) -> Chunk & {
	if (m_storage_end() == m_end()) {
		if (m_storage_begin() < m_begin()) {
			auto d = (front_spare() + 1) / 2;
			m_end() = move(m_begin(), m_end(), m_begin() - static_cast<Difference>(d));
			m_begin -= d;
		} else {
			auto c = max<Size>(2 * capacity(), 1);
			Chuck chuck(c, c / 4, m_allocator());
			chuck.m_construct_at_end(make_move_iterator(m_begin()), make_move_iterator(m_end()));
			swap(m_storage_begin(), other.m_storage_begin());
			swap(m_begin(), other.m_begin());
			swap(m_end(), other.m_send());
			swap(m_storage_end(), other.m_storage_end());
		}
	}
	AllocatorTraits::construct(m_allocator(), PointerTraits ::to_raw(m_end()), forward<TArgs>(args)...);
	++m_end();
	return *this;
};

template< typename TElement, typename TPointer >
class Iterator : public BasicIterator {

};

template< typename TElement, typename TPointer >
class ConstIterator : public BasicIterator {

};

template< typename TElement, typename TAllocator >
class Base {
protected:
	using Element = TElement;

	using Allocator = TAllocator;

	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

	using Reference = Element &;

	using ConstReference = Element const &;

	using Size = typename AllocatorTraits::Size;

	using Difference = typename AllocatorTraits::Difference;

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

	using PointerAllocator = typename AllocatorTraits::template Rebind<Pointer>;

	using PointerAllocatorTraits = BR::AllocatorTraits<PointerAllocator>;

	using MapPointer = typename PointerAllocatorTraits::Pointer;

	using ConstPointerAllocator = typename AllocatorTraits::template Rebind<ConstPointer>;

	using ConstPointerAllocatorTraits = BR::AllocatorTraits<ConstPointerAllocator>;

	using MapConstPointer = typename ConstPointerAllocatorTraits::Pointer;

	using Map = Chuck< Pointer, PointerAllocator >;

	static constexpr Difference chuck_size = sizeof(Element) < 0x100 ? 0x1000 / sizeof(Element) : 0x10;

private:
	Base(Base const & queue) = delete;
	Base& operator=(Base const & queue) = delete;

}; // class Base< TElement, TAllocator >

} // namespace Deque
} // namespace Container
} // namespace Detail

} // namespace BR