#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/move.hpp>
#include <libbr/algorithm/move_backward.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/container/detail/allocator_helpers.hpp>
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
class DequeBlock;

template< typename TElement, typename TAllocator >
inline void swap(DequeBlock< TElement, TAllocator> & x, DequeBlock< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}



template< typename TElement, typename TAllocator >
class DequeBlock {

public:
	using Element = TElement;

	using Allocator = TAllocator;

private:
	using Self = DequeBlock;

public:
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
	DequeBlock() noexcept(HasNothrowDefaultConstructor<Allocator>{}) : m_impl(nullptr, nullptr, nullptr, nullptr) {
	}

	explicit DequeBlock(Allocator & allocator) : m_impl(nullptr, nullptr, nullptr, nullptr, allocator) {
	}

	explicit DequeBlock(Allocator const & allocator) : m_impl(nullptr, nullptr, nullptr, nullptr, allocator) {
	}

	DequeBlock(Size capacity, Size start, Allocator & allocator) : m_impl(nullptr, nullptr, nullptr, nullptr, allocator) {
		storage_begin() = capacity != 0 ? AllocatorTraits::allocate(allocator, capacity) : nullptr;
		begin() = end() = storage_begin() + start;
		storage_end() = storage_begin() + capacity;
	}

	DequeBlock(Self && other) noexcept(HasNothrowMoveConstructor<Allocator>{}) : m_impl(move(other.m_impl)) {
		other.storage_begin() = other.begin() = other.end() = other.storage_end() = nullptr;
	}

	DequeBlock(Self && other, Allocator const & allocator) : m_impl(allocator) {
		if (allocator == other.m_allocator()) {
			storage_begin() = other.storage_begin();
			begin() = other.begin();
			end() = other.end();
			storage_end() = other.storage_end();
			other.storage_begin() = other.begin() = other.end() = other.storage_end() = nullptr;
		} else {
			Size capacity = other.size();
			storage_begin() = AllocatorTraits::allocate(allocator(), capacity);
			begin() = end() = storage_begin();
			storage_end() = storage_begin() + capacity;
			construct_at_end(make_move_iterator(other.begin()), make_move_iterator(other.end()));
		}
	}

	~DequeBlock() {
		clear();
		if (storage_begin() != nullptr) {
			AllocatorTraits::deallocate(allocator(), storage_begin(), capacity());
		}
	}

	auto operator=(Self && other) noexcept(
		BooleanOr<
			BooleanAnd<
				typename AllocatorTraits::IsPropagateOnContainerMoveAssignment,
				HasNothrowMoveAssignment<Allocator>
			>,
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment >
		>{}
	) -> Self & {
		clear();
		clamp();
		storage_begin() = other.storage_begin();
		begin() = other.begin();
		end() = other.end();
		storage_end() = other.storage_end();
		move_allocator(other);
		return *this;
	}

	auto storage_begin() noexcept -> Pointer & {
		return m_impl.template get<0>();
	}

	auto storage_begin() const noexcept -> Pointer const & {
		return m_impl.template get<0>();
	}

	auto begin() noexcept -> Pointer & {
		return m_impl.template get<1>();
	}

	auto begin() const noexcept -> Pointer const & {
		return m_impl.template get<1>();
	}

	auto end() noexcept -> Pointer & {
		return m_impl.template get<2>();
	}

	auto end() const noexcept -> Pointer const & {
		return m_impl.template get<2>();
	}

	auto storage_end() noexcept -> Pointer & {
		return m_impl.template get<3>();
	}

	auto storage_end() const noexcept -> Pointer const & {
		return m_impl.template get<3>();
	}

	auto allocator() noexcept -> Allocator & {
		return m_impl.template get<Allocator &>();
	}

	auto allocator() const noexcept -> Allocator const & {
		return m_impl.template get<Allocator &>();
	}

	auto front_spare() const -> Size {
		return static_cast<Size>(begin() - storage_begin());
	}

	auto back_spare() const -> Size {
		return static_cast<Size>(storage_end() - end());
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

	auto empty() const -> bool {
		return begin() == end();
	}

	auto size() const -> Size {
		return static_cast<Size>(end() - begin());
	}

	auto capacity() const -> Size {
		return static_cast<Size>(storage_end() - storage_begin());
	}

	void clear() noexcept {
		destruct_at_end(begin());
	}

	void reserve(Size count) {
		if (capacity() < count) {
			using BR::swap;
			Self buffer(count, 0, allocator());
			buffer.construct_at_end(make_move_iterator(begin()), make_move_iterator(end()));
			m_swap_without_allocator(buffer);
		}
	}

	void clamp() noexcept {
		if (size() < capacity()) {
			BR_TRY {
				using BR::swap;
				Self buffer(size(), 0, allocator());
				buffer.construct_at_end(make_move_iterator(begin()), make_move_iterator(end()));
				end() = begin() + size();
				m_swap_without_allocator(buffer);
			} BR_CATCH(...) {
				BR_RETHROW;
			}
		}
	}

	template< typename ... TArgs>
	void emplace_front(TArgs && ... args) {
		if (begin() == storage_begin()) {
			if (end() < storage_end()) {
				Difference difference = storage_end() - end();
				difference = (difference + 1) / 2;
				begin() = move_backward(begin(), end(), end() + difference);
				end() += difference;
			} else {
				Size capacity = max<Size>(2 * static_cast<Size>(storage_end() - storage_begin()), 1);
				Self buffer(capacity, (capacity + 3) / 4, allocator());
				buffer.construct_at_end(make_move_iterator(begin()), make_move_iterator(end()));
				m_swap_without_allocator(buffer);
			}
		}
		AllocatorTraits::construct(allocator(), PointerTraits::to_raw(begin() - 1), forward<TArgs>(args)...);
		--begin();
	}

	template< typename ... TArgs>
	void emplace_back(TArgs && ... args) {
		if (end() == storage_end()) {
			if (storage_begin() < begin()) {
				Difference difference = begin() - storage_begin();
				difference = (difference + 1) / 2;
				end() = move(begin(), end(), begin() - difference);
				begin() -= difference;
			} else {
				Size capacity = max<Size>(2 * static_cast<Size>(storage_end() - storage_begin()), 1);
				Self buffer(capacity, capacity / 4, allocator());
				buffer.construct_at_end(make_move_iterator(begin()), make_move_iterator(end()));
				m_swap_without_allocator(buffer);
			}
		}
		AllocatorTraits::construct(allocator(), PointerTraits::to_raw(end()), forward<TArgs>(args)...);
		++end();
	}

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
		destruct_at_begin(begin() + 1);
	}

	void erase_back() {
		destruct_at_end(end() - 1);
	}

	void swap(Self & other) noexcept(
		BooleanOr<
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<Allocator>
		>{}
	) {
		using BR::swap;
		m_swap_without_allocator(other);
		swap_allocator(allocator(), other.allocator());
	}

	void construct_at_end(Size count) {
		do {
			AllocatorTraits::construct(allocator(), PointerTraits::to_raw(end()));
			++end();
			--count;
		} while (count > 0);
	}

	void construct_at_end(Element const & element, Size count) {
		do {
			AllocatorTraits::construct(allocator(), PointerTraits::to_raw(end()), element);
			++end();
			--count;
		} while (count > 0);
	}

	template< typename TIterator >
	void construct_at_end(TIterator first, TIterator last) {
		m_construct_at_end(first, last, typename IteratorTraits<TIterator>::Category{});
	}

	void destruct_at_begin(Pointer new_begin) {
		m_destruct_at_begin(new_begin, HasTrivialDestructor<Element>{});
	}

	void destruct_at_end(Pointer new_end) {
		m_destruct_at_end(new_end, HasTrivialDestructor<Element>{});
	}

private:
	template< typename TSinglePassIterator >
	void m_construct_at_end(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		for (; first != last; ++first) {
			if (end() == storage_end()) {
				auto old_cap = storage_end() - storage_begin();
				auto new_cap = max<Size>(2 * old_cap, 8);
				Self buffer(new_cap, 0, allocator());
				for (auto p = begin(); p != end(); ++p, ++buffer.end()) {
					AllocatorTraits::construct(buffer.allocator(), PointerTraits::to_raw(buffer.end()), move(*p));
				}
				swap(buffer);
			}
			AllocatorTraits::construct(allocator(), PointerTraits::to_raw(end()), *first);
			++end();
		}
	}

	template< typename TForwardIterator >
	void m_construct_at_end(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		for (; first != last; ++first) {
			AllocatorTraits::construct(allocator(), PointerTraits::to_raw(end()), *first);
			++end();
		}
	}

	void m_destruct_at_begin(Pointer new_begin, BooleanTrue) {
		begin() = new_begin;
	}

	void m_destruct_at_begin(Pointer new_begin, BooleanFalse) {
		for (; begin() != new_begin;) {
			AllocatorTraits::destroy(allocator(), PointerTraits::to_raw(begin()++));
		}
	}

	void m_destruct_at_end(Pointer new_end, BooleanTrue) {
		end() = new_end;
	}

	void m_destruct_at_end(Pointer new_end, BooleanFalse) {
		for (; new_end != end(); ) {
			AllocatorTraits::destroy(allocator(), PointerTraits(--end()));
		}
	}

	void m_swap_without_allocator(Self & other) {
		using BR::swap;
		swap(storage_begin(), other.storage_begin());
		swap(begin(), other.begin());
		swap(end(), other.end());
		swap(storage_end(), other.storage_end());
	}

private:
	DequeBlock(Self const &) = delete;

	auto operator=(DequeBlock const &) -> DequeBlock & = delete;

private:
	// storage_begin, begin, end, storage_end, allocator
	Tuple< Pointer, Pointer, Pointer, Pointer, Allocator & > m_impl;
}; // class DequeBlock< TElement, TAllocator >

} // namespace Container
} // namespace Detail
} // namespace BR