#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy_n.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/algorithm/rotate.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/memory/memory_set.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/string/detail/raw_string_storage.hpp>
#include <libbr/string/string_compare.hpp>
#include <libbr/string/string_move.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/type_traits/is_pod.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>

namespace BR {
namespace Detail {
namespace String {
namespace RawString {

template< typename TCodeUnit, typename TAllocator >
class Basic {
private:
	using Self = Basic;

public:
	using Allocator = TAllocator;

protected:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
	using CodeUnit = TCodeUnit;

	static_assert(IsSame< TCodeUnit, typename AllocatorTraits::Element >{}, "AllocatorTraits<Allocator>::Value must be TCodeUnit.");

	static_assert(IsPOD<TCodeUnit>{}, "TCodeUnit must be a POD.");

public:
	using Element = typename AllocatorTraits::Element;

	using Size = typename AllocatorTraits::Size;

	using Pointer = typename AllocatorTraits::Pointer;

	using ConstPointer = typename AllocatorTraits::ConstPointer;

protected:
	using PointerTraits = BR::PointerTraits<Pointer>;

	using ConstPointerTraits = BR::PointerTraits<ConstPointer>;

	using Difference = typename AllocatorTraits::Difference;

	struct Large {
		Size capacity;
		Size size;
		Pointer data;
	};

	constexpr static Size SMALL_CAPACITY = (sizeof(Large) - 1) / sizeof(Element) > 2 ? (sizeof(Large) - 1) / sizeof(Element) : 2;

	struct Small {
		union {
			UInt8 size;
			Element padding;
		};
		Element data[SMALL_CAPACITY];
	};

	struct Coalition {
		union {
			Large large;
			Small small;
		};
	};

	using Storage = RawString::Storage< Coalition, Allocator>;

	constexpr static auto ALIGNMENT = 32;

	constexpr static UInt8 SMALL_MASK =
	#if defined(BR_LITTLE_ENDIAN)
		0x01;
	#else // defined(BR_LITTLE_ENDIAN)
		0x80;
	#endif // defined(BR_LITTLE_ENDIAN)

	constexpr static UInt8 LARGE_MASK =
	#if defined(BR_LITTLE_ENDIAN)
		0x01;
	#else // defined(BR_LITTLE_ENDIAN)
		~Size(~0) >> 1;
	#endif // defined(BR_LITTLE_ENDIAN)

protected:
	Basic() noexcept(HasNothrowDefaultConstructor<Allocator>{}) : m_storage() {
	}

	Basic(Allocator const & allocator) noexcept(HasNothrowDefaultConstructor<Allocator>{}) : m_storage(allocator) {
	}

	Basic(Self && other) noexcept : m_storage(move(other.m_storage)) {
		other.m_zeroize();
	}

	Basic(Self && other, Allocator const & allocator) : m_storage(allocator) {
		if (allocator != other.m_allocator()) {
			m_construct(other.m_raw_data(), other.m_size());
		} else {
			m_coalition() = other.m_coalition();
			other.m_zeroize();
		}
	}

	~Basic() {
		if (m_is_large()) {
			AllocatorTraits::deallocate(m_allocator(), m_large_data(), m_large_capacity());
		}
	}

protected:
	constexpr static auto m_allocate_size(Size size) noexcept -> Size {
		return size < SMALL_CAPACITY ? SMALL_CAPACITY : (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
	}

	auto m_allocator() noexcept -> Allocator & {
		return m_storage.allocator();
	}

	auto m_allocator() const noexcept -> Allocator const & {
		return m_storage.allocator();
	}

	auto m_coalition() noexcept -> Coalition & {
		return m_storage.coalition();
	}

	auto m_coalition() const noexcept -> Coalition const & {
		return m_storage.coalition();
	}

	auto m_large() noexcept -> Large & {
		return m_coalition().large;
	}

	auto m_large() const noexcept -> Large const & {
		return m_coalition().large;
	}

	auto m_small() noexcept -> Small & {
		return m_coalition().small;
	}

	auto m_small() const noexcept -> Small const & {
		return m_coalition().small;
	}

	auto m_is_large() const noexcept -> Boolean {
		return Boolean(m_small().size & SMALL_MASK);
	}

	auto m_capacity() const noexcept -> Size {
		return m_is_large() ? m_large_capacity() : m_small_capacity();
	}

	auto m_large_capacity() const noexcept -> Size {
		return m_large().capacity & Size(~LARGE_MASK);
	}

	void m_large_capacity(Size capacity) noexcept {
		m_large().capacity = LARGE_MASK | capacity;
	}

	constexpr static auto m_small_capacity() noexcept -> Size {
		return SMALL_CAPACITY;
	}

	auto m_size() const noexcept -> Size {
		return m_is_large() ? m_large_size() : m_small_size();
	}

	void m_size(Size size) noexcept {
		m_is_large() ? m_large_size(size) : m_small_size(size);
	}

	auto m_large_size() const noexcept -> Size {
		return m_large().size;
	}

	void m_large_size(Size size) noexcept {
		m_large().size = size;
	}

	auto m_small_size() const -> Size {
		return
		#if defined(BR_LITTLE_ENDIAN)
			m_small().size >> 1;
		#else
			m_small().size;
		#endif // defined(BR_LITTLE_ENDIAN)
	}

	void m_small_size(Size size) noexcept {
		m_small().size =
		#if defined(BR_LITTLE_ENDIAN)
			UInt8(size << 1);
		#else
			UInt8(size);
		#endif // defined(BR_LITTLE_ENDIAN)
	}

	auto m_max_size() const noexcept -> Size {
		auto const m = AllocatorTraits::max_size(m_allocator());
		return
		#if defined(BR_LITTLE_ENDIAN)
			m - ALIGNMENT;
		#else
			(m <= ~LARGE_MASK ? m : m / 2) - ALIGNMENT;
		#endif // defined(BR_LITTLE_ENDIAN)
	}

	auto m_data() noexcept -> Pointer {
		return m_is_large() ? m_large_data() : m_small_data();
	}

	auto m_data() const noexcept -> ConstPointer {
		return m_is_large() ? m_large_data() : m_small_data();
	}

	auto m_large_data() noexcept -> Pointer {
		return m_large().data;
	}

	auto m_large_data() const noexcept -> ConstPointer {
		return m_large().data;
	}

	void m_large_data(Pointer data) noexcept {
		m_large().data = data;
	}

	auto m_small_data() noexcept -> Pointer {
		return PointerTraits::make_pointer(m_small().data[0]);
	}

	auto m_small_data() const noexcept -> ConstPointer {
		return ConstPointerTraits::make_pointer(m_small().data[0]);
	}

	auto m_raw_data() noexcept -> Element * {
		return PointerTraits::to_raw(m_data());
	}

	auto m_raw_data() const noexcept -> Element const * {
		return ConstPointerTraits::to_raw(m_data());
	}

protected:
	void m_zeroize() noexcept {
		m_small_size(0);
		for (auto & byte : m_small().data) {
			byte = 0;
		}
	}

	void m_prepare(Size size) {
		if (size > m_max_size()) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		if (size < SMALL_CAPACITY) {
			m_small_size(size);
		} else {
			auto capacity = m_allocate_size(size + 1);
			auto data = AllocatorTraits::allocate(m_allocator(), capacity);
			m_large_data(data);
			m_large_capacity(capacity);
			m_large_size(size);
		}
	}

	void m_construct(CodeUnit const * units, Size length) {
		m_construct(units, length, length);
	}

	void m_construct(CodeUnit const * units, Size length, Size reserve) {
		m_prepare(reserve);
		auto const data = m_data();
		copy_n(units, length, data);
		data[length] = CodeUnit(0);
		m_size(length);
	}

	template< typename TForwardIterator >
	void m_construct(TForwardIterator first, TForwardIterator last) {
		m_construct(first, last, IteratorTraits<TForwardIterator>::category());
	}

	auto m_compare(CodeUnit const * rhs_data, Size rhs_size) const noexcept -> Relation {
		Size lhs_size = m_size();
		auto result = string_compare(m_data(), rhs_data, min(lhs_size, rhs_size));
		if (result != Relation::EQ) {
			return result;
		}
		if (lhs_size < rhs_size) {
			return Relation::LT;
		}
		if (lhs_size > rhs_size) {
			return Relation::GT;
		}
		return Relation::EQ;
	}

	void m_reserve(Size count) {
		if (count > m_max_size()) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		auto size = m_size();
		auto old_capacity = m_capacity(), new_capacity = m_allocate_size(max(count, size) + 1);
		if (new_capacity != old_capacity) {
			Pointer old_data = m_data(), new_data;
			Boolean now_large;
			if (new_capacity == SMALL_CAPACITY) {
				new_data = m_small_data();
				now_large = false;
			} else {
				if (new_capacity > old_capacity) {
					new_data = AllocatorTraits::allocate(m_allocator(), new_capacity);
				} else {
					try {
						new_data = AllocatorTraits::allocate(m_allocator(), new_capacity);
					} catch (...) {
						return;
					}
				}
				now_large = true;
			}
			memory_copy(PointerTraits::to_raw(m_small_data()), PointerTraits::to_raw(old_data), size + 1);
			if (m_is_large()) {
				AllocatorTraits::deallocate(m_allocator(), old_data, old_capacity);
			}
			if (now_large) {
				m_large_data(new_data);
				m_large_capacity(new_capacity);
				m_large_size(size);
			} else {
				m_small_size(size);
			}
		}
	}

	void m_assign(Self const & other) {
		if (this != &other) {
			m_copy_assign_allocator(other, typename AllocatorTraits::IsPropagateOnContainerCopyAssignment{});
			m_assign(other.m_data(), other.m_size());
		}
	}

	void m_assign(Self && other) noexcept(
		BooleanOr< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment, typename AllocatorTraits::IsAlwaysEqual >{}
	) {
		m_move_assign(other, typename AllocatorTraits::IsPropagateOnContainerMoveAssignment{});
	}

	auto m_assign(CodeUnit const * units, Size length) {
		BR_ASSERT(length == 0 || units != nullptr);
		auto capacity = m_capacity();
		if (m_capacity() > length) {
			auto data = m_raw_data();
			string_move(data, units, length);
			data[length] = CodeUnit(0);
			m_size(length);
		} else {
			auto size = m_size();
			m_grow_and_replace(capacity, length - capacity, size, 0, size, length, units);
		}
	}

	template< typename TForwardIterator >
	void m_assign(TForwardIterator first, TForwardIterator last) {
		m_assign(first, last, IteratorTraits<TForwardIterator>::category());
	}

	void m_append(CString<CodeUnit> string, Size length) {
		BR_ASSERT(length == 0 || string != nullptr);
		auto capacity = m_capacity();
		auto size = m_size();
		if (capacity - size >= length) {
			if (length != 0) {
				auto data = m_data();
				copy_n(string, length, data + size);
				size += length;
				data[size] = CodeUnit(0);
				m_size(size);
			}
		} else {
			m_grow_and_replace(capacity, size + length - capacity, size, size, 0, length, string);
		}
	}

	void m_append(CodeUnit unit) {
		auto capacity = m_capacity();
		auto old_size = m_size();
		auto new_size = old_size + 1;
		if (new_size == capacity) {
			m_grow(capacity, 1, old_size, old_size, 0);
		}
		auto pointer = m_raw_data() + old_size;
		*pointer = unit;
		++pointer;
		*pointer = CodeUnit(0);
		m_size(new_size);
	}

	void m_append(CodeUnit unit, Size n) {
		if (n > 0) {
			auto capacity = m_capacity();
			auto old_size = m_size();
			auto new_size = old_size + n;
			if (capacity < new_size) {
				m_grow(capacity, new_size - capacity, old_size, old_size, 0);
			}
			auto data = m_data();
			fill_n(data + old_size, n, unit);
			data[new_size] = CodeUnit(0);
			m_size(new_size);
		}
	}

	template< typename TForwardIterator >
	void m_append(TForwardIterator first, TForwardIterator last) {
		m_append(first, last, IteratorTraits<TForwardIterator>::category());
	}

	void m_insert(Size index, CString<CodeUnit> string, Size length) {
		auto old_size = m_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		auto capacity = m_capacity();
		if (capacity - old_size >= length) {
			if (length > 0) {
				auto new_size = old_size + length;
				auto pointer = m_raw_data();
				auto move_count = old_size - index;
				if (move_count > 0) {
					if (pointer + index <= string && string < pointer + old_size) {
						string += length;
					}
					string_move(pointer + index + length, pointer + index, move_count);
				}
				string_move(pointer + index, string, length);
				pointer[new_size] = CodeUnit(0);
				m_size(new_size);
			}
		} else {
			m_grow_and_replace(capacity, old_size + length - capacity, old_size, index, 0, length, string);
		}
	}

	void m_insert(Size index, CodeUnit unit) {
		auto old_size = m_size();
		auto new_size = old_size + 1;
		auto capacity = m_capacity();
		CodeUnit * pointer;
		if (capacity == old_size) {
			m_grow(capacity, 1, old_size, index, 0, 1);
			pointer =  m_raw_data();
		} else {
			pointer =  m_raw_data();
			Size move_count = old_size - index;
			if (move_count > 0) {
				string_move(pointer + index + 1, pointer + index, move_count);
			}
		}
		pointer[index] = unit;
		pointer[new_size] = CodeUnit(0);
		m_size(new_size);
	}

	void m_insert(Size index, CodeUnit unit, Size n) {
		auto old_size = m_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		if (n > 0) {
			auto capacity = m_capacity();
			auto new_size = old_size + n;
			CodeUnit * pointer = nullptr;
			if (capacity >= new_size) {
				pointer = m_raw_data();
				Size move_count = old_size - index;
				if (move_count > 0) {
					string_move(pointer + index + n, pointer + index, move_count);
				}
			} else {
				m_grow(capacity, new_size - capacity, old_size, index, 0, n);
				pointer = m_raw_data();
			}
			fill_n(pointer + index, n, unit);
			pointer[new_size] = CodeUnit(0);
			m_size(new_size);
		}
	}

	template< typename TForwardIterator >
	auto m_insert(Size index, TForwardIterator first, TForwardIterator last) -> Size {
		return m_insert(index, first, last, IteratorTraits<TForwardIterator>::category());
	}

	void m_replace(Size index, Size count, CString<CodeUnit> string, Size length) {
		BR_ASSERT(length == 0 || string != nullptr);
		auto old_size = m_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		count = min(count, old_size - index);
		auto capacity = m_capacity();
		if (capacity - old_size + count >= length) {
			auto data = m_raw_data();
			if (count != length) {
				auto move_count = old_size - index - count;
				if (move_count > 0) {
					if (count > length) {
						string_move(data + index, string, length);
						string_move(data + index + length, data + index + count, move_count);
						goto FINISH;
					}
					if (data + index < string && string < data + length) {
						if (data + index + count <= string) {
							string += length - count;
						} else {
							string_move(data + index, string, count);
							index += count;
							string += length;
							length -= count;
							count = 0;
						}
					}
					string_move(data + index + length, data + index + count, move_count);
				}
			}
			string_move(data + index, string, length);
FINISH:
			auto new_size = old_size + length - count;
			data[new_size] = CodeUnit(0);
			m_size(new_size);
		} else {
			m_grow_and_replace(capacity, old_size - count + length - capacity, old_size, index, count, length, string);
		}
	}

	void m_replace(Size index, Size count, CodeUnit unit) {
		auto old_size = m_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		count = min(count, old_size - index);
		auto capacity = m_capacity();
		CodeUnit * data;
		auto new_size = old_size - count + 1;
		if (capacity - old_size + count >= 1) {
			data = m_raw_data();
			if (count != 1) {
				auto move_count = old_size - index - count;
				if (move_count > 0) {
					string_move(data + index + 1, data + index + count, move_count);
				}
			}
		} else {
			m_grow(capacity, new_size - capacity, old_size, index, count, 1);
			data = m_raw_data();
		}
		data[index] = unit;
		data[new_size] = CodeUnit(0);
		m_size(new_size);
	}

	void m_replace(Size index, Size count, CodeUnit unit, Size n) {
		auto old_size = m_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		count = min(count, old_size - index);
		auto capacity = m_capacity();
		CodeUnit * data;
		auto new_size = old_size - count + n;
		if (capacity - old_size + count >= n) {
			data = m_raw_data();
			if (count != n) {
				auto move_count = old_size - index - count;
				if (move_count > 0) {
					string_move(data + index + n, data + index + count, move_count);
				}
			}
		} else {
			m_grow(capacity, new_size - capacity, old_size, index, count, n);
			data = m_raw_data();
		}
		fill_n(data + index, n, unit);
		data[new_size] = CodeUnit(0);
		m_size(new_size);
	}

	template< typename TIterator >
	void m_replace(Size index, Size count, TIterator first, TIterator last) {
		for (; ; ++index, --count, (void) ++first) {
			if (count == 0) {
				if (first != last) {
					m_insert(index, first, last);
				}
				break;
			}
			if (first == last) {
				m_remove(index, count);
				break;
			}
			m_data()[index] = *first;
		}
	}

	void m_remove(Size index, Size count) {
		auto old_size = m_size();
		if (count > 0) {
			auto new_size = old_size - count;
			CodeUnit * data = m_raw_data();
			auto move_count = new_size - index;
			if (move_count > 0) {
				string_move(data + index, data + index + count, move_count);
			}
			data[new_size] = CodeUnit(0);
			m_size(new_size);
		}
	}


	void m_clear() {
		*m_data() = CodeUnit(0);
		m_size(0);
	}

private:
	template< typename TSinglePassIterator >
	void m_construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		m_zeroize();
		BR_TRY {
			for (; first != last; ++first) {
				append(*first);
			}
		} BR_CATCH(...) {
			if (m_is_large()) {
				AllocatorTraits::deallocate(m_allocator(), m_large_data(), m_large_capacity());
			}
			BR_RETHROW;
		}
	}

	template< typename TForwardIterator >
	void m_construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		m_prepare(static_cast<Size>(distance(first, last)));
		Pointer pointer = m_data();
		for (; first != last; ++first, (void) ++pointer) {
			*pointer = *first;
		}
		*pointer = CodeUnit(0);
	}

	void m_copy_assign_allocator(Self const & other, BooleanTrue) {
		if (m_allocator() != other.m_allocator()) {
			m_clear();
			m_reserve(0);
		}
		m_allocator() = other.m_allocator();
	}

	void m_copy_assign_allocator(Self const & other, BooleanFalse) noexcept {
	}

	void m_move_assign(Self & other, BooleanTrue) noexcept(HasNothrowMoveAssignment<Allocator>{}) {
		m_clear();
		m_reserve(0);
		m_coalition() = other.m_coalition();
		m_allocator() = move(other.m_allocator());
		other.m_zeroize();
	}

	void m_move_assign(Self & other, BooleanFalse) noexcept(typename AllocatorTraits::IsAlwaysEqual{}) {
		if (m_allocator() == other.m_allocator()) {
			m_move_assign(other, BooleanTrue{});
		} else {
			m_assign(other.m_data(), other.m_size());
		}
	}

	void m_grow_and_replace(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count, CodeUnit const * units) {
		auto const MAX_SIZE = m_max_size();
		if (old_capacity + delta_capacity > MAX_SIZE - 1) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		auto old_data = m_data();
		auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
			? m_allocate_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
			: MAX_SIZE;
		auto new_data = AllocatorTraits::allocate(m_allocator(), new_capacity);
		if (copy_count != 0) {
			copy_n(old_data, copy_count, new_data);
		}
		if (add_count != 0) {
			copy_n(units, add_count, new_data + copy_count);
		}
		auto const second_copy_count = old_size - delete_count - copy_count;
		if (second_copy_count != 0) {
			copy_n(old_data + copy_count + delete_count, second_copy_count, new_data + copy_count + add_count);
		}
		if (old_capacity != SMALL_CAPACITY) {
			AllocatorTraits::deallocate(m_allocator(), old_data, old_capacity);
		}
		m_large_data(new_data);
		m_large_capacity(new_capacity);
		Size new_size = copy_count + add_count + second_copy_count;
		new_data[new_size] = CodeUnit(0);
		m_large_size(new_size);
	}

	void m_grow(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count = 0) {
		auto const MAX_SIZE = m_max_size();
		if (delta_capacity > MAX_SIZE - old_capacity) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		auto old_data = m_data();
		auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
			? m_allocate_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
			: MAX_SIZE;
		auto new_data = AllocatorTraits::allocate(m_allocator(), new_capacity);
		if (copy_count != 0) {
			copy_n(old_data, copy_count, new_data);
		}
		auto const second_copy_count = old_size - delete_count - copy_count;
		if (second_copy_count != 0) {
			copy_n(old_data + copy_count + delete_count, second_copy_count, new_data + copy_count + add_count);
		}
		m_large_data(new_data);
		m_large_capacity(new_capacity);
	}

	template< typename TSinglePassIterator >
	void m_assign(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		m_clear();
		m_append(first, last, SinglePassTraversalTag{});
	}

	template< typename TForwardIterator >
	void m_assign(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		auto const count = static_cast<Size>(distance(first, last));
		auto capacity = m_capacity();
		if (capacity < count) {
			auto const size = m_size();
			m_grow(capacity, count - capacity, size, 0, size);
		}
		auto pointer = m_data();
		for (; first != last; ++first, ++pointer) {
			*pointer = *first;
		}
		*pointer = CodeUnit(0);
		m_size(count);
	}

	template< typename TSinglePassIterator >
	void m_append(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		for (; first != last; ++first) {
			m_append(*first);
		}
	}

	template< typename TForwardIterator >
	void m_append(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		auto size = m_size();
		auto capacity = m_capacity();
		auto const count = static_cast<Size>(distance(first, last));
		if (count != 0) {
			if (capacity - size < count) {
				m_grow(capacity, size + count - capacity, size, size, 0);
			}
			auto pointer = m_data() + size;
			for (; first != last; ++pointer, ++first) {
				*pointer = *first;
			}
			*pointer = CodeUnit(0);
			m_size(size + count);
		}
	}

	template< typename TSinglePassIterator >
	auto m_insert(Size index, TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) -> Size {
		auto old_size = m_size();
		for (; first != last; ++first) {
			m_append(*first);
		}
		auto data = m_data();
		rotate(data + index, data + old_size, data + m_size());
		return index;
	}

	template< typename TForwardIterator >
	auto m_insert(Size index, TForwardIterator first, TForwardIterator last, ForwardTraversalTag) -> Size {
		auto old_size = m_size();
		auto capacity = m_capacity();
		Size count = static_cast<Size>(distance(first, last));
		if (count > 0) {
			auto new_size = old_size + count;
			CodeUnit * pointer = nullptr;
			if (capacity >= new_size) {
				pointer = m_raw_data();
				Size move_count = old_size - index;
				if (move_count > 0) {
					string_move(pointer + index + count, pointer + index, move_count);
				}
			} else {
				m_grow(capacity, new_size - capacity, old_size, index, 0, count);
				pointer = m_raw_data();
			}
			pointer[new_size] = CodeUnit(0);
			m_size(new_size);
			for (pointer += index; first != last; ++pointer, (void) ++first) {
				*pointer = *first;
			}
		}
		return index;
	}

protected:
	Storage m_storage;
};

} // namespace RawString
} // namespace String
} // namespace Detail
} // namespace BR