#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/move.hpp>
#include <libbr/algorithm/move_backward.hpp>
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
namespace Deque {

template< typename TElement, typename TAllocator >
class Block;

template< typename TElement, typename TAllocator >
inline void swap(Block< TElement, TAllocator> & x, Block< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}

template< typename TPointer, typename TAllocator, Boolean = BooleanAnd< IsEmpty<TAllocator>, NotFinal<TAllocator> >{} >
struct BlockStorage;


template< typename TPointer, typename TAllocator >
struct BlockStorage< TPointer, TAllocator, false > {
public:
	using Pointer = TPointer;

	using Allocator = TAllocator;

public:
	BlockStorage() : m_allocator(), m_storage_begin(), m_begin(), m_end(), m_storage_end() {
	}

	BlockStorage(Allocator const & allocator) : m_allocator(allocator), m_storage_begin(), m_begin(), m_end(), m_storage_end() {
	}

	BlockStorage(BlockStorage && storage) : m_allocator(move(storage.m_allocator)), m_storage_begin(move(storage.m_storage_begin)), m_begin(move(storage.m_begin)), m_end(move(storage.m_end)), m_storage_end(move(storage.m_storage_end)) {
	}

	auto allocator() noexcept -> Allocator & {
		return m_allocator;
	}

	auto allocator() const noexcept -> Allocator const & {
		return m_allocator;
	}

	auto storage_begin() noexcept -> Pointer & {
		return m_storage_begin;
	}

	auto storage_begin() const noexcept -> Pointer const & {
		return m_storage_begin;
	}

	auto begin() noexcept -> Pointer & {
		return m_begin;
	}

	auto begin() const noexcept -> Pointer const & {
		return m_begin;
	}

	auto end() noexcept -> Pointer & {
		return m_end;
	}

	auto end() const noexcept -> Pointer const & {
		return m_end;
	}

	auto storage_end() noexcept -> Pointer & {
		return m_storage_end;
	}

	auto storage_end() const noexcept -> Pointer const & {
		return m_storage_end;
	}

private:
	Allocator m_allocator;
	Pointer m_storage_begin;
	Pointer m_begin;
	Pointer m_end;
	Pointer m_storage_end;
}; // struct BlockStorage< TPointer, TAllocator, false >


template< typename TPointer, typename TAllocator >
struct BlockStorage< TPointer, TAllocator, true > : private TAllocator {
public:
	using Pointer = TPointer;

	using Allocator = TAllocator;

public:
	BlockStorage() : Allocator(), m_storage_begin(), m_begin(), m_end(), m_storage_end() {
	}

	BlockStorage(Allocator const & allocator) : Allocator(allocator), m_storage_begin(), m_begin(), m_end(), m_storage_end() {
	}

	BlockStorage(BlockStorage && storage) : Allocator(move(storage)), m_storage_begin(move(storage.m_storage_begin)), m_begin(move(storage.m_begin)), m_end(move(storage.m_end)), m_storage_end(move(storage.m_storage_end)) {
	}

	auto allocator() noexcept -> Allocator & {
		return static_cast< Allocator & >(*this);
	}

	auto allocator() const noexcept -> Allocator const & {
		return static_cast< Allocator const & >(*this);
	}

	auto storage_begin() noexcept -> Pointer & {
		return m_storage_begin;
	}

	auto storage_begin() const noexcept -> Pointer const & {
		return m_storage_begin;
	}

	auto begin() noexcept -> Pointer & {
		return m_begin;
	}

	auto begin() const noexcept -> Pointer const & {
		return m_begin;
	}

	auto end() noexcept -> Pointer & {
		return m_end;
	}

	auto end() const noexcept -> Pointer const & {
		return m_end;
	}

	auto storage_end() noexcept -> Pointer & {
		return m_storage_end;
	}

	auto storage_end() const noexcept -> Pointer const & {
		return m_storage_end;
	}

private:
	Pointer m_storage_begin;
	Pointer m_begin;
	Pointer m_end;
	Pointer m_storage_end;

}; // struct BlockStorage< TPointer, TAllocator, true >


template< typename TElement, typename TAllocator >
class Block {

public:
	using Element = TElement;

	using Allocator = TAllocator;

private:
	using Self = Block;

	using BareAllocator = RemoveReference<Allocator>;

public:
	using AllocatorTraits = BR::AllocatorTraits<BareAllocator>;

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
	Block() noexcept(HasNothrowDefaultConstructor<Allocator>{}) : m_storage() {
	}

	explicit Block(BareAllocator & allocator) : m_storage(allocator) {
	}

	explicit Block(BareAllocator const & allocator) : m_storage(allocator) {
	}

	Block(Size capacity, Size start, BareAllocator & allocator) : m_storage(allocator) {
		storage_begin() = capacity != 0 ? AllocatorTraits::allocate(allocator, capacity) : nullptr;
		begin() = end() = storage_begin() + start;
		storage_end() = storage_begin() + capacity;
	}

	Block(Self && other) noexcept(HasNothrowMoveConstructor<Allocator>{}) : m_storage(move(other.m_storage)) {
		other.storage_begin() = other.begin() = other.end() = other.storage_end() = nullptr;
	}

	Block(Self && other, BareAllocator const & allocator) : m_storage(allocator) {
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

	~Block() {
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
		return m_storage.storage_begin();
	}

	auto storage_begin() const noexcept -> Pointer const & {
		return m_storage.storage_begin();
	}

	auto begin() noexcept -> Pointer & {
		return m_storage.begin();
	}

	auto begin() const noexcept -> Pointer const & {
		return m_storage.begin();
	}

	auto end() noexcept -> Pointer & {
		return m_storage.end();
	}

	auto end() const noexcept -> Pointer const & {
		return m_storage.end();
	}

	auto storage_end() noexcept -> Pointer & {
		return m_storage.storage_end();
	}

	auto storage_end() const noexcept -> Pointer const & {
		return m_storage.storage_end();
	}

	auto allocator() noexcept -> BareAllocator & {
		return m_storage.allocator();
	}

	auto allocator() const noexcept -> BareAllocator const & {
		return m_storage.allocator();
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
			IsNothrowSwappable<BareAllocator>
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
			AllocatorTraits::destroy(allocator(), PointerTraits::to_raw(--end()));
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
	Block(Self const &) = delete;

	auto operator=(Block const &) -> Block & = delete;

private:
	// storage_begin, begin, end, storage_end, allocator
	BlockStorage< Pointer, Allocator > m_storage;
}; // class Block< TElement, TAllocator >

} // namespace Deque
} // namespace Container
} // namespace Detail
} // namespace BR