/**
 * @file
 * @brief SplitBuffer
 * @author Bromine0x23
 * @since 2015/11/19
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_operate/bool.hpp>
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
class SplitBuffer;

template< typename TElement, typename TAllocator >
class SplitBuffer {

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

	SplitBuffer() noexcept(HasNothrowDefaultConstructor<Allocator>::value);

	explicit SplitBuffer(Allocator & allocator);

	explicit SplitBuffer(Allocator const & allocator);

	SplitBuffer(Size capacity, Size start, Allocator & allocator);

	SplitBuffer(SplitBuffer && buffer) noexcept(HasNothrowMoveConstructor<Allocator>::value);

	SplitBuffer(SplitBuffer && buffer, Allocator const & allocator);

	~SplitBuffer();

	auto operator=(SplitBuffer && buffer) noexcept(
		BooleanOr<
			BooleanAnd<
				typename AllocatorTraits::IsPropagateOnContainerMoveAssignment,
				HasNothrowMoveAssign<Allocator>
			>,
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment >
		>
	) -> SplitBuffer &;

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

	void reserve(Size n);

	void clamp();

	void add_front(Element const & x);

	void add_front(Element && x);

	void add_back(Element const & x);

	void add_back(Element && x);

	template< typename ... TArgs>
	void emplace_back(TArgs && ... args);

	void erase_front() {
		m_destruct_at_begin(m_begin() + 1);
	}

	void erase_back() {
		m_destruct_at_end(m_end() - 1);
	}

	void swap(SplitBuffer & other) noexcept(
		BooleanOr<
			BooleanNot< AllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<Allocator>
		>::value
	);

private:
	auto m_storage_begin() noexcept -> Pointer & {
		return m_impl.get<0>();
	}

	auto m_storage_begin() noexcept -> Pointer const & {
		return m_impl.get<0>();
	}

	auto m_begin() noexcept -> Pointer & {
		return m_impl.get<1>();
	}

	auto m_begin() noexcept -> Pointer const & {
		return m_impl.get<1>();
	}

	auto m_end() noexcept -> Pointer & {
		return m_impl.get<2>();
	}

	auto m_end() noexcept -> Pointer const & {
		return m_impl.get<2>();
	}

	auto m_storage_end() noexcept -> Pointer & {
		return m_impl.get<3>();
	}

	auto m_storage_end() noexcept -> Pointer const & {
		return m_impl.get<3>();
	}

	auto m_allocator() noexcept -> Allocator & {
		return m_impl.get<4>();
	}

	auto m_allocator() const noexcept -> Allocator const & {
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

	void m_destruct_at_begin(Pointer new_begin, BooleanTrue);

	void m_destruct_at_begin(Pointer new_begin, BooleanFalse);

	void m_destruct_at_end(Pointer new_end) {
		m_destruct_at_begin(new_begin, BooleanFalse());
	}

	void m_destruct_at_end(Pointer new_end, BooleanTrue);

	void m_destruct_at_end(Pointer new_end, BooleanFalse);

	void m_move_assign_allocator(SplitBuffer & other, BooleanTrue) noexcept(HasNothrowMoveAssign<Allocator>::value) {
		m_allocator() = move(other.m_allocator());
	}

	_LIBCPP_INLINE_VISIBILITY
	void m_move_assign_allocator(SplitBuffer & other, BooleanFalse) noexcept {
	}

private:
	// storage_begin, begin, end, storage_end, allocator
	Tuple< Pointer, Pointer, Pointer, Pointer, Allocator > m_impl;

private:
	SplitBuffer(SplitBuffer const &) = delete;

	auto operator=(SplitBuffer const &) -> SplitBuffer & = delete;
}; // class SplitBuffer< TElement, TAllocator >

template< typename TElement, typename TAllocator >
void SplitBuffer< TElement, TAllocator >::m_construct_at_end(Size n) {
	auto & allocator = m_allocator();
	do {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()));
		++m_end();
		--n;
	} while (n > 0);
}

template< typename TElement, typename TAllocator >
void SplitBuffer< TElement, TAllocator >::m_construct_at_end(Size n, Element const & x) {
	auto & allocator = m_allocator();
	do {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()), x);
		++m_end();
		--n;
	} while (n > 0);
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
void SplitBuffer< TElement, TAllocator >::m_construct_at_end(TIterator first, TIterator last, SinglePassTraversalTag) {
	auto & allocator = m_allocator();
	for (; first != last; ++first) {
		if (m_end() == m_storage_end()) {
			auto old_cap = m_storage_end() - m_storage_begin();
			auto new_cap = max<Size>(2 * old_cap, 8);
			SplitBuffer buffer(new_cap, 0, allocator);
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
void SplitBuffer< TElement, TAllocator >::m_construct_at_end(TIterator first, TIterator last, ForwardTraversalTag) {
	auto & allocator = m_allocator();
	for (; first != last; ++first) {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()), *first);
		++m_end();
	}
}

template< typename TElement, typename TAllocator >
void SplitBuffer< TElement, TAllocator >::m_destruct_at_begin(Pointer new_begin, BooleanTrue) {
	m_begin() = new_begin;
}

template< typename TElement, typename TAllocator >
void SplitBuffer< TElement, TAllocator >::m_destruct_at_begin(Pointer new_begin, BooleanFalse) {
	for (; m_begin() != new_begin;) {
		AllocatorTraits::destroy(m_allocator(), PointerTraits::to_raw(m_begin()++));
	}
}

template< typename TElement, typename TAllocator >
void SplitBuffer< TElement, TAllocator >::m_destruct_at_end(Pointer new_end, BooleanTrue) {
	m_end() = new_end;
}

template< typename TElement, typename TAllocator >
void SplitBuffer< TElement, TAllocator >::m_destruct_at_end(Pointer new_end, BooleanFalse) {
	for (new_end != m_end()) {
		AllocatorTraits::destroy(m_allocator(), PointerTraits(--m_end()));
	}
}

} // namespace BR