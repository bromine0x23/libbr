#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/algorithm/move_backward.hpp>
#include <libbr/algorithm/rotate.hpp>
#include <libbr/container/detail/dynamic_array_storage.hpp>
#include <libbr/container/detail/allocator_helpers.hpp>
#include <libbr/container/detail/deque_block.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/move_iterator.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/allocator_construct_backward.hpp>
#include <libbr/memory/allocator_construct_forward.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/has_trivial_destructor.hpp>
#include <libbr/type_traits/has_trivial_move_constructor.hpp>
#include <libbr/type_traits/is_forward_iterator.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {
namespace Detail {
namespace Container {
namespace DynamicArray {

template< typename TElement, typename TAllocator >
class Basic {

private:
	using Self = Basic;

public:
	using Element = TElement;

	using Allocator = TAllocator;

	using AllocatorTraits = BR::AllocatorTraits<TAllocator>;

	using Reference = Element &;

	using ConstReference = Element const &;

	using Size = typename AllocatorTraits ::Size;

	using Difference = typename AllocatorTraits ::Difference;

	using Pointer = typename AllocatorTraits ::Pointer;

	using ConstPointer = typename AllocatorTraits ::ConstPointer;

	using Iterator = Pointer;

	using ConstIterator = ConstPointer;

protected:
	using PointerTraits = BR::PointerTraits<Pointer>;

	using Buffer = Detail::Container::DequeBlock< Element, Allocator >;

public:
	Basic() noexcept(HasNothrowDefaultConstructor<Allocator>{}) : m_storage() {
	}

	Basic(Allocator const & allocator) : m_storage(allocator) {
	}

	Basic(Self && other) noexcept : m_storage(move(other.m_storage)) {
		other.m_begin() = other.m_end() = other.m_storage_end() = nullptr;
	}

	Basic(Self && other, Allocator const & allocator) : m_storage(allocator) {
		if (allocator == other.m_allocator()) {
			m_begin() = other.m_begin();
			m_end() = other.m_end();
			m_storage_end() = other.m_storage_end();
			other.m_begin() = other.m_end() = other.m_storage_end() = nullptr;
		} else {
			m_assign(make_move_iterator(other.m_begin()), make_move_iterator(other.m_end()));
		}
	}

	~Basic() {
		if (m_storage_begin() != nullptr) {
			m_clear();
			AllocatorTraits::deallocate(m_allocator(), m_begin(), m_capacity());
		}
	}

protected:
	auto m_storage_begin() noexcept -> Pointer & {
		return m_storage.storage_begin();
	}

	auto m_storage_begin() const noexcept -> Pointer const & {
		return m_storage.storage_begin();
	}

	auto m_begin() noexcept -> Pointer & {
		return m_storage.begin();
	}

	auto m_begin() const noexcept -> Pointer const & {
		return m_storage.begin();
	}

	auto m_end() noexcept -> Pointer & {
		return m_storage.end();
	}

	auto m_end() const noexcept -> Pointer const & {
		return m_storage.end();
	}

	auto m_storage_end() noexcept -> Pointer & {
		return m_storage.storage_end();
	}

	auto m_storage_end() const noexcept -> Pointer const & {
		return m_storage.storage_end();
	}

	auto m_allocator() noexcept -> Allocator & {
		return m_storage.allocator();
	}

	auto m_allocator() const noexcept -> Allocator const & {
		return m_storage.allocator();
	}

	void m_clear() noexcept {
		m_destruct_at_end(m_begin());
	}

	auto m_empty() const noexcept -> Boolean {
		return this->m_begin() == this->m_end();
	}

	auto m_size() const noexcept -> Size {
		return static_cast<Size>(m_end() - m_begin());
	}

	auto m_capacity() const noexcept -> Size {
		return static_cast<Size>(m_storage_end() - m_storage_begin());
	}

	auto m_max_size() const noexcept -> Size {
		return min<Size>(AllocatorTraits::max_size(m_allocator()), IntegerTraits<Size>::max() / 2);
	}

	void m_allocate(Size count) {
		if (count > this->m_max_size()) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		auto const memory = AllocatorTraits::allocate(this->m_allocator(), count);
		this->m_storage_begin() = memory;
		this->m_end() = memory;
		this->m_storage_end() = memory + count;
	}

	template< typename TIterator >
	void m_allocate_construct(TIterator first, TIterator last) {
		m_allocate_construct(first, last, typename IteratorTraits<TIterator>::Category{});
	}

	void m_construct_at_end(Size count) {
		auto & allocator = m_allocator();
		do {
			AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()));
			++m_end();
			--count;
		} while (count > 0);
	}

	void m_construct_at_end(ConstReference element, Size count) {
		auto & allocator = m_allocator();
		do {
			AllocatorTraits::construct(allocator, PointerTraits::to_raw(m_end()), element);
			++m_end();
			--count;
		} while (count > 0);
	}

	template< typename TForwardIterator >
	void m_construct_at_end(TForwardIterator first, TForwardIterator last, EnableIf< IsForwardIterator<TForwardIterator> > * = nullptr) {
		m_end() = allocator_construct_forward(m_allocator(), first, last, m_end());
	}

	void m_destruct_at_end(Pointer new_end) noexcept {
		m_destruct_at_end(new_end, HasTrivialDestructor<Element>{});
	}

	void m_reserve(Size new_capacity) {
		if (m_capacity() < new_capacity) {
			Buffer buffer(new_capacity, m_size(), m_allocator());
			m_swap_out_buffer(buffer);
		}
	}

	void m_clamp() noexcept {
		if (m_size() < m_capacity()) {
			BR_TRY {
				Buffer buffer(m_size(), m_size(), m_allocator());
				m_swap_out_buffer(buffer);
			} BR_CATCH(...) {
			}
		}
	}

	void m_assign(Self const & other) {
		if (this != &other) {
			m_copy_assign_allocator(other, typename AllocatorTraits::IsPropagateOnContainerCopyAssignment{});
			m_assign(other.m_begin(), other.m_end());
		}
	}

	void m_assign(Self && other) noexcept(
		BooleanOr< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment, typename AllocatorTraits::IsAlwaysEqual >{}
	) {
		m_move_assign(other, typename AllocatorTraits::IsPropagateOnContainerMoveAssignment{});
	}

	void m_assign(Element const & element, Size count) {
		if (m_capacity() < count) {
			m_deallocate();
			m_allocate(m_new_capacity(count));
			m_construct_at_end(count, element);
		} else {
			auto size = m_size();
			fill_n(m_begin(), min(count, size), element);
			if (size < count) {
				m_construct_at_end(count - size, element);
			} else {
				m_destruct_at_end(m_begin() + count);
			}
		}
	}

	template< typename TIterator >
	void m_assign(TIterator first, TIterator last) {
		m_assign(first, last, typename IteratorTraits<TIterator>::Category{});
	}

	template< typename ... TArgs >
	auto m_emplace(Size index, TArgs && ... args) -> Pointer {
		auto position = m_begin() + index;
		if (m_end() < m_storage_end()) {
			if (position == m_end()) {
				AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(m_end()), forward<TArgs>(args)...);
				++m_end();
			} else {
				m_move_elements(position, m_end(), position + 1);
				AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(position), forward<TArgs>(args)...);
			}
		} else {
			auto & allocator = m_allocator();
			Buffer buffer(m_new_capacity(m_size() + 1), index, allocator);
			// buffer.emplace_back(forward<TArgs>(args)...);
			AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(buffer.end()), forward<TArgs>(args)...);
			++buffer.end();
			position = m_swap_out_buffer(buffer, position);
		}
		return position;
	}

	auto m_insert(Size index, Element const & element, Size count) -> Pointer {
		auto position = m_begin() + index;
		if (count > 0) {
			if (count <= static_cast<Size>(m_storage_end() - m_end())) {
				auto old_count = count;
				Pointer old_end = m_end();
				if (count > static_cast<Size>(m_end() - position)) {
					auto c = count - (m_end() - position);
					m_construct_at_end(element, c);
					count -= c;
				}
				if (count > 0) {
					m_move_elements(position, old_end, position + old_count);
					auto pelement = BR::PointerTraits<ConstPointer>::make_pointer(element);
					if (position <= pelement && pelement < m_end()) {
						pelement += old_count;
					}
					fill_n(position, count, *pelement);
				}
			} else {
				Buffer buffer(m_new_capacity(m_size() + count), index, m_allocator());
				buffer.construct_at_end(element, count);
				position = m_swap_out_buffer(buffer, position);
			}
		}
		return position;
	}

	template< typename TIterator >
	auto m_insert(Size index, TIterator first, TIterator last) -> Pointer {
		return m_insert(index, first, last, typename IteratorTraits<TIterator>::Category{});
	}

	template< typename ... TArgs >
	void m_emplace_back(TArgs && ... args) {
		if (m_end() < m_storage_end()) {
			AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(m_end()), forward<TArgs>(args)...);
			++m_end();
		} else {
			Buffer buffer(m_new_capacity(m_size() + 1), m_size(), m_allocator());
			// buffer.emplace_back(forward<TArgs>(args)...);
			AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(buffer.end()), forward<TArgs>(args)...);
			++buffer.end();
			m_swap_out_buffer(buffer);
		}
	}

	auto m_erase(Size index) -> Pointer {
		auto const position = m_begin() + index;
		m_destruct_at_end(move(position + 1, m_end(), position));
		return position;
	}

	auto m_erase(Size index, Size count) -> Pointer {
		auto const position = m_begin() + index;
		if (count != 0) {
			m_destruct_at_end(move(position + count, m_end(), position));
		}
		return position;
	}

	void m_swap(Self & other) noexcept(
		BooleanOr< BooleanNot< typename AllocatorTraits::IsPropagateOnContainerSwap >, IsNothrowSwappable<Allocator> >{}
	) {
		using BR::swap;
		swap(m_begin(), other.m_begin());
		swap(m_end(), other.m_end());
		swap(m_storage_end(), other.m_storage_end());
		swap_allocator(m_allocator(), other.m_allocator());
	}

private:
	constexpr auto m_new_capacity(Size new_size) noexcept -> Size {
		Size max_size = m_max_size();
		if (max_size < new_size) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		Size capacity = m_capacity();
		return (capacity < max_size / 2) ? max<Size>(2 * capacity, new_size) : max_size;
	}

	void m_swap_out_buffer(Buffer & buffer) {
		using BR::swap;
		buffer.begin() = allocator_construct_backward(m_allocator(), make_move_iterator_if_noexcept(m_begin()), make_move_iterator_if_noexcept(m_end()), buffer.begin());
		BR_ASSERT(buffer.storage_begin() == buffer.begin());
		swap(m_begin(), buffer.begin());
		swap(m_end(), buffer.end());
		swap(m_storage_end(), buffer.storage_end());
		buffer.storage_begin() = buffer.begin();
	}

	auto m_swap_out_buffer(Buffer & buffer, Pointer reverse_at) -> Pointer {
		using BR::swap;
		auto const result = buffer.begin();
		buffer.begin() = allocator_construct_backward(m_allocator(), m_begin(), reverse_at, buffer.begin());
		buffer.end() = allocator_construct_forward(m_allocator(), reverse_at, m_end(), buffer.end());
		BR_ASSERT(buffer.storage_begin() == buffer.begin());
		swap(m_begin(), buffer.begin());
		swap(m_end(), buffer.end());
		swap(m_storage_end(), buffer.storage_end());
		buffer.storage_begin() = buffer.begin();
		return result;
	}

	void m_deallocate() noexcept {
		if (m_storage_begin() != nullptr) {
			m_clear();
			AllocatorTraits::deallocate(m_allocator(), m_storage_begin(), m_capacity());
			m_storage_begin() = m_end() = m_storage_end() = nullptr;
		}
	}

	void m_move_elements(Pointer from_begin, Pointer from_end, Pointer to_begin) {
		auto const old_end = m_end();
		auto const n = old_end - to_begin;
		for (auto p = from_begin + n; p < from_end; ++p, (void) ++m_end()) {
			AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(m_end()), move(*p));
		}
		move_backward(from_begin, from_begin + n, old_end);
	}

	template< typename TSinglePassIterator >
	void m_allocate_construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		for (; first != last; ++first) {
			m_emplace_back(*first);
		}
	}

	template< typename TForwardIterator >
	void m_allocate_construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		auto const count = static_cast<Size>(distance(first, last));
		if (count > 0) {
			m_allocate(count);
			m_construct_at_end(first, last);
		}
	}

	template< typename TSinglePassIterator >
	void m_assign(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		m_clear();
		for (; first != last; ++first) {
			m_emplace_back(*first);
		}
	}

	template< typename TForwardIterator >
	void m_assign(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		auto new_size = static_cast<Size>(distance(first, last));
		if (m_capacity() < new_size) {
			m_deallocate();
			m_allocate(m_new_capacity(new_size));
			m_construct_at_end(first, last);
		} else {
			auto mid = last;
			bool growing = false;
			if (m_size() < new_size) {
				growing = true;
				mid = first;
				advance(mid, m_size());
			}
			auto new_end = copy(first, mid, m_begin());
			if (growing) {
				m_construct_at_end(mid, last);
			} else {
				m_destruct_at_end(new_end);
			}
		}
	}

	void m_append(Size count) {
		if (m_storage_end() - m_end() >= count) {
			m_construct_at_end(count);
		} else {
			Buffer buffer(m_new_capacity(m_size() + count), m_size(), m_allocator());
			buffer.construct_at_end(count);
			m_swap_out_buffer(buffer);
		}
	}

	void m_append(Element const & element, Size count) {
		if (m_storage_end() - m_end() >= count) {
			m_construct_at_end(element, count);
		} else {
			Buffer buffer(m_new_capacity(m_size() + count), m_size(), m_allocator());
			buffer.construct_at_end(element, count);
			m_swap_out_buffer(buffer);
		}
	}

	void m_destruct_at_end(Pointer new_end, BooleanTrue) {
		m_end() = new_end;
	}

	void m_destruct_at_end(Pointer new_end, BooleanFalse) {
		for (auto & end = m_end(); new_end != end; ) {
			AllocatorTraits::destroy(m_allocator(), PointerTraits::to_raw(--end));
		}
	}

	void m_copy_assign_allocator(Self const & array, BooleanTrue) {
		if (m_allocator() != array.m_allocator()) {
			m_clear();
			AllocatorTraits::deallocate(m_allocator(), m_storage_begin(), m_capacity());
			m_storage_begin() = m_end() = m_storage_end() = nullptr;
		}
		m_allocator() = array.m_allocator();
	}

	void m_copy_assign_allocator(Self const & array, BooleanFalse) noexcept {
	}

	void m_move_assign(Self & other, BooleanTrue) noexcept(HasNothrowMoveAssignment<Allocator>{}) {
		m_deallocate();
		move_allocator(m_allocator(), other.m_allocator());
		m_storage_begin() = other.m_storage_begin();
		m_end() = other.m_end();
		m_storage_end() = other.m_storage_end();
		other.m_storage_begin() = other.m_end() = other.m_storage_end() = nullptr;
	}

	void m_move_assign(Self & other, BooleanFalse) noexcept(typename AllocatorTraits::IsAlwaysEqual{}) {
		if (m_allocator() == other.m_allocator()) {
			m_move_assign(other, BooleanTrue{});
		} else {
			m_assign(make_move_iterator(other.begin()), make_move_iterator(other.end()));
		}
	}

	template< typename TSinglePassIterator >
	auto m_insert(Size index, TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) -> Pointer {
		auto position = m_begin() + index;
		auto old_end = m_end();
		auto const old_size = m_size();
		for (; m_end() != m_storage_end() && first != last; ++first) {
			AllocatorTraits::construct(m_allocator(), PointerTraits::to_raw(m_end()), *first);
			++m_end();
		}
		Buffer buffer(m_allocator());
		if (first != last) {
			BR_TRY {
				buffer.construct_at_end(first, last);
				m_reserve(m_new_capacity(m_size() + buffer.size()));
				position = m_begin() + index;
			} BR_CATCH(...) {
				m_erase(old_size, m_size());
				BR_RETHROW;
			}
		}
		position = rotate(position, m_begin() + old_size, m_end());
		m_insert(position - m_begin(), make_move_iterator(buffer.begin()), make_move_iterator(buffer.end()));
		return m_begin() + index;
	}

	template< typename TForwardIterator >
	auto m_insert(Size index, TForwardIterator first, TForwardIterator last, ForwardTraversalTag) -> Pointer {
		auto position = m_begin() + index;
		Size count = distance(first, last);
		if (count > 0) {
			if (count <= static_cast<Size>(m_storage_end() - m_end())) {
				auto old_count = count;
				auto old_end = m_end();
				auto middle = last;
				Size right = m_end() - position;
				if (count > right) {
					middle = first;
					advance(middle, right);
					m_construct_at_end(middle, last);
					count = right;
				}
				if (count > 0) {
					m_move_elements(position, old_end, position + old_count);
					copy(first, middle, position);
				}
			} else {
				Buffer buffer(m_new_capacity(m_size() + count), index, m_allocator());
				buffer.construct_at_end(first, last);
				position = m_swap_out_buffer(buffer, position);
			}
		}
		return position;
	}

protected:
	Storage< Pointer, Allocator > m_storage;

}; // class Basic< TElement, TAllocator >

} // namespace DynamicArray
} // namespace Container
} // namespace Detail
} // namespace BR
