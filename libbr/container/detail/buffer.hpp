#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/move.hpp>
#include <libbr/algorithm/move_backward.hpp>
#include <libbr/container/tuple.hpp>
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
namespace Detail {
namespace Container {

template< typename TElement, typename TAllocator >
class Buffer;

template< typename TElement, typename TAllocator >
class Buffer {

protected:
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

	template< typename TElement, typename TAllocator >
	friend class BR::DynamicArray;

	using PointerTraits = BR::PointerTraits<Pointer>;

public:
	Buffer() noexcept(HasNothrowDefaultConstructor<Allocator>{}) : m_imp(nullptr, nullptr, nullptr, nullptr) {
	}

	explicit Buffer(Allocator & allocator) : m_imp(nullptr, nullptr, nullptr, nullptr, allocator) {
	}

	explicit Buffer(Allocator const & allocator) : m_imp(nullptr, nullptr, nullptr, nullptr, allocator) {
	}

	Buffer(Size capacity, Size start, Allocator & allocator) : m_imp(allocator) {
		storage_begin() = capacity != 0 ? AllocatorTraits::allocate(m_allocator(), capacity) : nullptr;
		begin() = end() = storage_begin() + start;
		storage_end() = storage_begin() + capacity;
	}

	Buffer(Buffer && buffer) noexcept(HasNothrowMoveConstructor<Allocator>{}) : m_imp(move(buffer.m_imp)) {
		buffer.storage_begin() = buffer.begin() = buffer.end() = buffer.storage_end() = nullptr;
	}

	Buffer(Buffer && buffer, Allocator const & allocator) : m_imp(allocator) {
		if (allocator == buffer.m_allocator()) {
			storage_begin() = buffer.storage_begin();
			begin() = buffer.begin();
			end() = buffer.end();
			storage_end() = buffer.storage_end();
			buffer.storage_begin() = buffer.begin() = buffer.end() = buffer.storage_end() = nullptr;
		} else {
			Size capacity = buffer.size();
			storage_begin() = AllocatorTraits::allocate(m_allocator(), capacity);
			begin() = end() = storage_begin();
			storage_end() = storage_begin() + capacity;
			construct_at_end(make_move_iterator(buffer.begin()), make_move_iterator(buffer.end()));
		}
	}

	~Buffer() {
		clear();
		if (storage_begin() != nullptr) {
			AllocatorTraits::allocate(m_allocator(), storage_begin(), capacity());
		}
	}

	auto operator=(SplitBuffer && buffer) noexcept(
		BooleanOr<
			BooleanAnd<
				typename AllocatorTraits::IsPropagateOnContainerMoveAssignment,
				HasNothrowMoveAssign<Allocator>
			>,
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment >
		>{}
	) -> SplitBuffer & {
		clear();
		clamp();
		storage_begin() = buffer.storage_begin();
		begin() = buffer.begin();
		end() = buffer.end();
		storage_end() = buffer.storage_end();
		m_move_assign_allocator(buffer);
		return *this;
	}

	auto is_empty() const -> bool {
		return begin() == end();
	}

	auto size() const -> Size {
		return static_cast<Size>(end() - begin());
	}

	auto capacity() const -> Size {
		return static_cast<Size>(end_storage() - begin_storage());
	}

	auto front_spare() const -> Size {
		return static_cast<Size>(begin() - begin_storage());
	}

	auto back_spare() const -> Size {
		return static_cast<Size>(end_storage() - end());
	}

	auto front() -> Reference {
		return *begin();
	}

	auto front() const -> ConstReference {
		return *begin();
	}

	auto back() -> Reference {
		return *(end() - 1);
	}

	auto back() const -> ConstReference {
		return *(end() - 1);
	}

	void clear() noexcept {
		m_destruct_at_end(begin());
	}

	void reserve(Size count);

	void clamp() noexcept;

	template< typename ... TArgs>
	void emplace_front(TArgs && ... args);

	template< typename ... TArgs>
	void emplace_back(TArgs && ... args);

	void insert_front(Element const & x) {
		emplace_front(x);
	}

	void insert_front(Element && x) {
		emplace_front(move(x));
	}

	void insert_back(Element const & x) {
		emplace_back(x);
	}

	void insert_back(Element && x) {
		emplace_back(move(x));
	}

	void erase_front() {
		m_destruct_at_begin(begin() + 1);
	}

	void erase_back() {
		m_destruct_at_end(end() - 1);
	}

	void swap(Buffer & buffer) noexcept(
		BooleanOr<
			BooleanNot< AllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<Allocator>
		>{}
	) {
		using BR::swap;
		swap(storage_begin(), buffer.storage_begin());
		swap(begin(), buffer.begin());
		swap(end(), buffer.end());
		swap(storage_end(), buffer.storage_end());
		m_swap_allocator(m_allocator(), buffer.m_allocator());
	}

	void construct_at_end(Size n);

	void construct_at_end(Size n, Element const & x);

	template< typename TIterator >
	void construct_at_end(TIterator first, TIterator last) {
		construct_at_end(first, last, typename IteratorTraits<TIterator>::Category{});
	}

	void destruct_at_begin(Pointer new_begin) {
		destruct_at_begin(new_begin, HasTrivialDestructor<Element>{});
	}

	void destruct_at_end(Pointer new_end) {
		destruct_at_end(new_begin, HasTrivialDestructor<Element>{});
	}

protected:
	auto m_storage_begin() noexcept -> Pointer & {
		return m_imp.get<0>();
	}

	auto m_storage_begin() noexcept -> Pointer const & {
		return m_imp.get<0>();
	}

	auto m_begin() noexcept -> Pointer & {
		return m_imp.get<1>();
	}

	auto m_begin() noexcept -> Pointer const & {
		return m_imp.get<1>();
	}

	auto m_end() noexcept -> Pointer & {
		return m_imp.get<2>();
	}

	auto m_end() noexcept -> Pointer const & {
		return m_imp.get<2>();
	}

	auto m_storage_end() noexcept -> Pointer & {
		return m_imp.get<3>();
	}

	auto m_storage_end() noexcept -> Pointer const & {
		return m_imp.get<3>();
	}

	auto m_allocator() noexcept -> Allocator & {
		return m_imp.get<Allocator>();
	}

	auto m_allocator() const noexcept -> Allocator const & {
		return m_imp.get<Allocator>();
	}

	void m_move_assign_allocator(Buffer & buffer) noexcept(
		BooleanOr<
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment >,
			HasNothrowMoveAssignment<Allocator>
		>{}
	) {
		m_move_assign_allocator(buffer, typename AllocatorTraits::IsPropagateOnContainerMoveAssignment{});
	}

private:
	template< typename TIterator >
	void m_construct_at_end(TIterator first, TIterator last, SinglePassTraversalTag);

	template< typename TIterator >
	void m_construct_at_end(TIterator first, TIterator last, ForwardTraversalTag);

	void m_destruct_at_begin(Pointer new_begin, BooleanTrue);

	void m_destruct_at_begin(Pointer new_begin, BooleanFalse);

	void m_destruct_at_end(Pointer new_end, BooleanTrue);

	void m_destruct_at_end(Pointer new_end, BooleanFalse);

	void m_move_assign_allocator(Buffer & buffer, BooleanTrue) noexcept(HasNothrowMoveAssign<Allocator>{}) {
		m_allocator() = move(other.m_allocator());
	}

	void m_move_assign_allocator(Buffer & buffer, BooleanFalse) noexcept {
	}

	static void m_swap_allocator(Allocator & x, Allocator & y) noexcept(
		BooleanOr<
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<Allocator>
		>{}
	) {
		m_swap_allocator(x, y, typename AllocatorTraits::IsPropagateOnContainerSwap{});
	}

	static void m_swap_allocator(Allocator & x, Allocator & y, BooleanFalse) noexcept {
	}

	static void m_swap_allocator(Allocator & x, Allocator & y, BooleanTrue) noexcept(IsNothrowSwappable<Allocator>{}) {
		using BR::swap;
		swap(x, y);
	}

private:
	// storage_begin, begin, end, storage_end, allocator
	Tuple< Pointer, Pointer, Pointer, Pointer, Allocator > m_imp;

private:
	Buffer(Buffer const &) = delete;

	auto operator=(SplitBuffer const &) -> SplitBuffer & = delete;
}; // class Buffer< TElement, TAllocator >

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::construct_at_end(Size n) {
	auto & allocator = m_allocator();
	do {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(end()));
		++end();
		--n;
	} while (n > 0);
}

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::construct_at_end(Size n, Element const & x) {
	auto & allocator = m_allocator();
	do {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(end()), x);
		++end();
		--n;
	} while (n > 0);
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
void Buffer< TElement, TAllocator >::m_construct_at_end(TIterator first, TIterator last, SinglePassTraversalTag) {
	auto & allocator = m_allocator();
	for (; first != last; ++first) {
		if (end() == storage_end()) {
			auto old_cap = storage_end() - storage_begin();
			auto new_cap = max<Size>(2 * old_cap, 8);
			Buffer buffer(new_cap, 0, allocator);
			for (auto p = begin(); p != end(); ++p, ++buffer.end()) {
				AllocatorTraits::construct(buffer.m_allocator(), PointerTraits::to_raw(buffer.end()), move(*p));
			}
			swap(buffer);
		}
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(end()), *first);
		++m_end();
	}
}

template< typename TElement, typename TAllocator >
template< typename TIterator >
void Buffer< TElement, TAllocator >::m_construct_at_end(TIterator first, TIterator last, ForwardTraversalTag) {
	auto & allocator = m_allocator();
	for (; first != last; ++first) {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(end()), *first);
		++end();
	}
}

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::m_destruct_at_begin(Pointer new_begin, BooleanTrue) {
	begin() = new_begin;
}

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::m_destruct_at_begin(Pointer new_begin, BooleanFalse) {
	for (; begin() != new_begin;) {
		AllocatorTraits::destroy(m_allocator(), PointerTraits::to_raw(begin()++));
	}
}

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::m_destruct_at_end(Pointer new_end, BooleanTrue) {
	end() = new_end;
}

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::m_destruct_at_end(Pointer new_end, BooleanFalse) {
	for (; new_end != end(); ) {
		AllocatorTraits::destroy(m_allocator(), PointerTraits(--end()));
	}
}

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::reserve(Size count) {
	if (capacity() < count) {
		using BR::swap;
		Buffer< Element, Allocator & > buffer(count, 0, m_allocator());
		buffer.construct_at_end(make_move_iterator(begin()), make_move_iterator(end()));
		swap(storage_begin(), buffer.storage_begin());
		swap(begin(), buffer.begin());
		swap(end(), buffer.end());
		swap(storage_end(), buffer.storage_end());
	}
}

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::clamp() noexcept {
	if (size() < capacity()) {
#if !defined(BR_NO_EXCEPTIONS)
		try {
#endif
		using BR::swap;
		Buffer< Element, Allocator & > buffer(size(), 0, m_allocator());
		buffer.construct_at_end(make_move_iterator(begin()), make_move_iterator(end()));
		end() = begin() + size();
		swap(storage_begin(), buffer.storage_begin());
		swap(begin(), buffer.begin());
		swap(end(), buffer.end());
		swap(storage_end(), buffer.storage_end());
#if !defined(BR_NO_EXCEPTIONS)
		} catch (...) {
		}
#endif
	}
}
template< typename TElement, typename TAllocator >
template< typename ... TArgs>
void Buffer< TElement, TAllocator >::emplace_front(TArgs && ... args) {
	if (begin() == storage_begin()) {
		if (end() < storage_end()) {
			Difference difference = storage_end() - end();
			difference = (difference + 1) / 2;
			begin() = move_backward(begin(), end(), end() + difference);
			end() += difference;
		} else {
			Size capacity = max<Size>(2 * static_cast<Size>(storage_end() - storage_begin()), 1);
			Buffer< Element, Allocator & > buffer(capacity, (capacity + 3) / 4, m_allocator());
			buffer.construct_at_end(make_move_iterator(begin()), make_move_iterator(end()));
			swap(storage_begin(), buffer.storage_begin());
			swap(begin(), buffer.begin());
			swap(end(), buffer.end());
			swap(storage_end(), buffer.storage_end());
		}
	}
	AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(begin() - 1), forward<TArgs>(args)...);
	--begin();
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs>
void Buffer< TElement, TAllocator >::emplace_back(TArgs && ... args) {
	if (end() == storage_end()) {
		if (storage_begin() < begin()) {
			Difference difference = begin() - storage_begin();
			difference = (difference + 1) / 2;
			end() = move(begin(), end(), begin() - difference);
			begin() -= difference;
		} else {
			Size capacity = max<Size>(2 * static_cast<Size>(storage_end() - storage_begin()), 1);
			Buffer< Element, Allocator & > buffer(capacity, capacity / 4, allocator());
			buffer.construct_at_end(make_move_iterator(begin()), make_move_iterator(end()));
			swap(storage_begin(), buffer.storage_begin());
			swap(begin(), buffer.begin());
			swap(end(), buffer.end());
			swap(storage_end(), buffer.storage_end());
		}
	}
	AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(end()), forward<TArgs>(args)...);
	++end();
}

} // namespace Container
} // namespace Detail
} // namespace BR