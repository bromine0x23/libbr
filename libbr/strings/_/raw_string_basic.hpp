#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/copy_n.hpp>
#include <libbr/algorithms/fill_n.hpp>
#include <libbr/algorithms/max.hpp>
#include <libbr/algorithms/min.hpp>
#include <libbr/algorithms/rotate.hpp>
#include <libbr/iterators/distance.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/memory/memory_copy_unsafely.hpp>
#include <libbr/memory/memory_fill.hpp>
#include <libbr/strings/_/raw_string_storage.hpp>
#include <libbr/strings/string_compare.hpp>
#include <libbr/strings/string_copy.hpp>
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_standard_layout.hpp>
#include <libbr/type_traits/is_trivial.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_transform/make_signed.hpp>

namespace BR {
namespace _ {
namespace Strings {
namespace RawString {

template< typename TCodeUnit, typename TAllocator >
class Basic {
private:
	using Self = Basic;

public:
	using CodeUnit  = TCodeUnit;
	using Allocator = TAllocator;

protected:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

private:
	static_assert(not_array<TCodeUnit>, "TCodeUnit must not be an array");
	static_assert(is_standard_layout<TCodeUnit>, "TCodeUnit must be standard-layout");
	static_assert(is_trivial<TCodeUnit>, "TCodeUnit must be trivial");
	static_assert(is_same< TCodeUnit, typename AllocatorTraits::Element >, "AllocatorTraits<Allocator>::Value must be TCodeUnit.");

public:
	using Element = typename AllocatorTraits::Element;

	using Size = typename AllocatorTraits::Size;

	using Index = MakeSigned<Size>;

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
	Storage _storage;

protected:
	Basic() noexcept(has_nothrow_default_constructor<Allocator>) : _storage() {
	}

	Basic(Allocator const & allocator) noexcept(has_nothrow_default_constructor<Allocator>) : _storage(allocator) {
	}

	Basic(Self && other) noexcept : _storage(transfer(other._storage)) {
		other._zeroize();
	}

	Basic(Self && other, Allocator const & allocator) : _storage(allocator) {
		if (allocator != other._allocator()) {
			_construct(other._get_raw_data(), other._get_size());
		} else {
			_coalition() = other._coalition();
			other._zeroize();
		}
	}

	~Basic() {
		if (_is_large()) {
			AllocatorTraits::deallocate(_allocator(), _get_large_data(), _get_large_capacity());
		}
	}

protected:
	constexpr static auto _get_allocate_size(Size size) noexcept -> Size {
		return size < SMALL_CAPACITY ? SMALL_CAPACITY : (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
	}

	auto _allocator() noexcept -> Allocator & {
		return _storage.allocator();
	}

	auto _allocator() const noexcept -> Allocator const & {
		return _storage.allocator();
	}

	auto _coalition() noexcept -> Coalition & {
		return _storage.coalition();
	}

	auto _coalition() const noexcept -> Coalition const & {
		return _storage.coalition();
	}

	auto _large() noexcept -> Large & {
		return _coalition().large;
	}

	auto _large() const noexcept -> Large const & {
		return _coalition().large;
	}

	auto _small() noexcept -> Small & {
		return _coalition().small;
	}

	auto _small() const noexcept -> Small const & {
		return _coalition().small;
	}

	auto _is_large() const noexcept -> Boolean {
		return Boolean(_small().size & SMALL_MASK);
	}

	auto _get_capacity() const noexcept -> Size {
		return _is_large() ? _get_large_capacity() : _get_small_capacity();
	}

	auto _get_size() const noexcept -> Size {
		return _is_large() ? _get_large_size() : _get_small_size();
	}

	void _set_size(Size size) noexcept {
		_is_large() ? _set_large_size(size) : _set_small_size(size);
	}

	auto _get_max_size() const noexcept -> Size {
		auto const m = AllocatorTraits::max_size(_allocator());
		return
#if defined(BR_LITTLE_ENDIAN)
			m - ALIGNMENT;
#else
			(m <= ~LARGE_MASK ? m : m / 2) - ALIGNMENT;
#endif // defined(BR_LITTLE_ENDIAN)
	}

	auto _get_data() noexcept -> Pointer {
		return _is_large() ? _get_large_data() : _get_small_data();
	}

	auto _get_data() const noexcept -> ConstPointer {
		return _is_large() ? _get_large_data() : _get_small_data();
	}

	auto _get_raw_data() noexcept -> Element * {
		return PointerTraits::to_raw(_get_data());
	}

	auto _get_raw_data() const noexcept -> Element const * {
		return ConstPointerTraits::to_raw(_get_data());
	}

	auto _get_large_capacity() const noexcept -> Size {
		return _large().capacity & Size(~LARGE_MASK);
	}

	void _set_large_capacity(Size capacity) noexcept {
		_large().capacity = LARGE_MASK | capacity;
	}

	constexpr static auto _get_small_capacity() noexcept -> Size {
		return SMALL_CAPACITY;
	}

	auto _get_large_size() const noexcept -> Size {
		return _large().size;
	}

	void _set_large_size(Size size) noexcept {
		_large().size = size;
	}

	auto _get_small_size() const -> Size {
		return
#if defined(BR_LITTLE_ENDIAN)
			_small().size >> 1;
#else
			_small().size;
#endif // defined(BR_LITTLE_ENDIAN)
	}

	void _set_small_size(Size size) noexcept {
		_small().size =
#if defined(BR_LITTLE_ENDIAN)
			UInt8(size << 1);
#else
			UInt8(size);
#endif // defined(BR_LITTLE_ENDIAN)
	}

	auto _get_large_data() noexcept -> Pointer {
		return _large().data;
	}

	auto _get_large_data() const noexcept -> ConstPointer {
		return _large().data;
	}

	void _set_large_data(Pointer data) noexcept {
		_large().data = data;
	}

	auto _get_small_data() noexcept -> Pointer {
		return PointerTraits::make_pointer(_small().data[0]);
	}

	auto _get_small_data() const noexcept -> ConstPointer {
		return ConstPointerTraits::make_pointer(_small().data[0]);
	}

protected:
	void _zeroize() noexcept {
		_set_small_size(0);
		for (auto & byte : _small().data) {
			byte = CodeUnit();
		}
	}

	void _prepare(Size size) {
		if (size > _get_max_size()) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		if (size < SMALL_CAPACITY) {
			_set_small_size(size);
		} else {
			auto const capacity = _get_allocate_size(size + 1);
			auto const data = AllocatorTraits::allocate(_allocator(), capacity);
			_set_large_data(data);
			_set_large_capacity(capacity);
			_set_large_size(size);
		}
	}

	void _construct(CodeUnit const * units, Size length) {
		_construct(units, length, length);
	}

	void _construct(CodeUnit const * units, Size length, Size reserve) {
		_prepare(reserve);
		auto const data = _get_data();
		copy_n(units, length, data);
		data[length] = CodeUnit();
		_set_size(length);
	}

	template< typename TForwardIterator >
	void _construct(TForwardIterator first, TForwardIterator last) {
		_construct(first, last, IteratorTraits<TForwardIterator>::iterator_category());
	}

	auto _compare(CodeUnit const * rhs_data, Size rhs_size) const noexcept -> Relation {
		auto const lhs_size = _get_size();
		auto const result = string_compare(_get_data(), rhs_data, min(lhs_size, rhs_size));
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

	void _reserve(Size count) {
		if (count > _get_max_size()) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		auto const size = _get_size();
		auto const old_capacity = _get_capacity(), new_capacity = _get_allocate_size(max(count, size) + 1);
		if (new_capacity != old_capacity) {
			auto const old_data = _get_data();
			Pointer new_data;
			Boolean now_large;
			if (new_capacity == SMALL_CAPACITY) {
				new_data = _get_small_data();
				now_large = false;
			} else {
				if (new_capacity > old_capacity) {
					new_data = AllocatorTraits::allocate(_allocator(), new_capacity);
				} else {
					BR_TRY {
						new_data = AllocatorTraits::allocate(_allocator(), new_capacity);
					} BR_CATCH(...) {
						return;
					}
				}
				now_large = true;
			}
			memory_copy(PointerTraits::to_raw(_get_small_data()), PointerTraits::to_raw(old_data), size + 1);
			if (_is_large()) {
				AllocatorTraits::deallocate(_allocator(), old_data, old_capacity);
			}
			if (now_large) {
				_set_large_data(new_data);
				_set_large_capacity(new_capacity);
				_set_large_size(size);
			} else {
				_set_small_size(size);
			}
		}
	}

	auto _index(CodeUnit const * units, Size length, Size position) const noexcept -> Index {
		return 0;
	}

	void _assign(Self const & other) {
		if (this != &other) {
			_copy_assign_allocator(other, boolean_constant<AllocatorTraits::IS_PROPAGATE_ON_CONTAINER_COPY_ASSIGNMENT>);
			_assign(other._data(), other._size());
		}
	}

	void _assign(Self && other) noexcept(
		disjunction_by_value< AllocatorTraits::IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT, AllocatorTraits::IS_ALWAYS_EQUAL >
	) {
		_move_assign(other, boolean_constant<AllocatorTraits::IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT>);
	}

	void _assign(CodeUnit const * units, Size length) {
		BR_ASSERT_MESSAGE(length == 0 || units != nullptr, "Received nullptr.");
		auto capacity = _get_capacity();
		if (_get_capacity() > length) {
			auto data = _get_raw_data();
			string_copy(data, units, length);
			data[length] = CodeUnit();
			_set_size(length);
		} else {
			auto size = _get_size();
			_grow_and_replace(capacity, length - capacity, size, 0, size, length, units);
		}
	}

	template< typename TForwardIterator >
	void _assign(TForwardIterator first, TForwardIterator last) {
		_assign(first, last, IteratorTraits<TForwardIterator>::iterator_category());
	}

	void _append(CString<CodeUnit> string, Size length) {
		BR_ASSERT_MESSAGE(length == 0 || string != nullptr, "Received nullptr.");
		auto capacity = _get_capacity();
		auto size = _get_size();
		if (capacity - size >= length) {
			if (length != 0) {
				auto data = _get_data();
				copy_n(string, length, data + size);
				size += length;
				data[size] = CodeUnit();
				_set_size(size);
			}
		} else {
			_grow_and_replace(capacity, size + length - capacity, size, size, 0, length, string);
		}
	}

	void _append(CodeUnit unit) {
		auto capacity = _get_capacity();
		auto old_size = _get_size();
		auto new_size = old_size + 1;
		if (new_size == capacity) {
			_grow(capacity, 1, old_size, old_size, 0);
		}
		auto pointer = _get_raw_data() + old_size;
		*pointer = unit;
		++pointer;
		*pointer = CodeUnit();
		_set_size(new_size);
	}

	void _append(CodeUnit unit, Size count) {
		if (count > 0) {
			auto capacity = _get_capacity();
			auto old_size = _get_size();
			auto new_size = old_size + count;
			if (capacity < new_size) {
				_grow(capacity, new_size - capacity, old_size, old_size, 0);
			}
			auto data = _get_data();
			fill_n(data + old_size, count, unit);
			data[new_size] = CodeUnit();
			_set_size(new_size);
		}
	}

	template< typename TForwardIterator >
	void _append(TForwardIterator first, TForwardIterator last) {
		_append(first, last, IteratorTraits<TForwardIterator>::iterator_category());
	}

	void _insert(Size index, CString<CodeUnit> string, Size length) {
		auto old_size = _get_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		auto capacity = _get_capacity();
		if (capacity - old_size >= length) {
			if (length > 0) {
				auto new_size = old_size + length;
				auto pointer = _get_raw_data();
				auto move_count = old_size - index;
				if (move_count > 0) {
					if (pointer + index <= string && string < pointer + old_size) {
						string += length;
					}
					string_copy(pointer + index, pointer + index + length, move_count);
				}
				string_copy(string, pointer + index, length);
				pointer[new_size] = CodeUnit();
				_set_size(new_size);
			}
		} else {
			_grow_and_replace(capacity, old_size + length - capacity, old_size, index, 0, length, string);
		}
	}

	void _insert(Size position, CodeUnit unit) {
		auto old_size = _get_size();
		auto new_size = old_size + 1;
		auto capacity = _get_capacity();
		CodeUnit * pointer;
		if (capacity == old_size) {
			_grow(capacity, 1, old_size, position, 0, 1);
			pointer = _get_raw_data();
		} else {
			pointer = _get_raw_data();
			Size move_count = old_size - position;
			if (move_count > 0) {
				string_copy(pointer + position, pointer + position + 1, move_count);
			}
		}
		pointer[position] = unit;
		pointer[new_size] = CodeUnit();
		_set_size(new_size);
	}

	void _insert(Size index, CodeUnit unit, Size count) {
		auto old_size = _get_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		if (count > 0) {
			auto capacity = _get_capacity();
			auto new_size = old_size + count;
			CodeUnit * pointer = nullptr;
			if (capacity >= new_size) {
				pointer = _get_raw_data();
				Size move_count = old_size - index;
				if (move_count > 0) {
					string_copy(pointer + index, pointer + index + count, move_count);
				}
			} else {
				_grow(capacity, new_size - capacity, old_size, index, 0, count);
				pointer = _get_raw_data();
			}
			fill_n(pointer + index, count, unit);
			pointer[new_size] = CodeUnit();
			_set_size(new_size);
		}
	}

	template< typename TForwardIterator >
	auto _insert(Size index, TForwardIterator first, TForwardIterator last) -> Size {
		return minsert(index, first, last, IteratorTraits<TForwardIterator>::iterator_category());
	}

	void _replace(Size index, Size count, CString<CodeUnit> string, Size length) {
		BR_ASSERT_MESSAGE(length == 0 || string != nullptr, "Received nullptr.");
		auto old_size = _get_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		count = min(count, old_size - index);
		auto capacity = _get_capacity();
		if (capacity - old_size + count >= length) {
			auto data = _get_raw_data();
			if (count != length) {
				auto move_count = old_size - index - count;
				if (move_count > 0) {
					if (count > length) {
						string_copy(string, data + index, length);
						string_copy(data + index + count, data + index + length, move_count);
						goto FINISH;
					}
					if (data + index < string && string < data + length) {
						if (data + index + count <= string) {
							string += length - count;
						} else {
							string_copy(string, data + index, count);
							index += count;
							string += length;
							length -= count;
							count = 0;
						}
					}
					string_copy(data + index + count, data + index + length, move_count);
				}
			}
			string_copy(string, data + index, length);
FINISH:
			auto new_size = old_size + length - count;
			data[new_size] = CodeUnit();
			_set_size(new_size);
		} else {
			_grow_and_replace(capacity, old_size - count + length - capacity, old_size, index, count, length, string);
		}
	}

	void _replace(Size index, Size count, CodeUnit unit) {
		auto old_size = _get_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		count = min(count, old_size - index);
		auto capacity = _get_capacity();
		CodeUnit * data;
		auto new_size = old_size - count + 1;
		if (capacity - old_size + count >= 1) {
			data = _get_raw_data();
			if (count != 1) {
				auto move_count = old_size - index - count;
				if (move_count > 0) {
					string_copy(data + index + count, data + index + 1, move_count);
				}
			}
		} else {
			_grow(capacity, new_size - capacity, old_size, index, count, 1);
			data = _get_raw_data();
		}
		data[index] = unit;
		data[new_size] = CodeUnit();
		_set_size(new_size);
	}

	void _replace(Size index, Size count, CodeUnit unit, Size n) {
		auto old_size = _get_size();
		if (index > old_size) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		count = min(count, old_size - index);
		auto capacity = _get_capacity();
		CodeUnit * data;
		auto new_size = old_size - count + n;
		if (capacity - old_size + count >= n) {
			data = _get_raw_data();
			if (count != n) {
				auto move_count = old_size - index - count;
				if (move_count > 0) {
					string_copy(data + index + count, data + index + n, move_count);
				}
			}
		} else {
			m_grow(capacity, new_size - capacity, old_size, index, count, n);
			data = _get_raw_data();
		}
		fill_n(data + index, n, unit);
		data[new_size] = CodeUnit();
		_set_size(new_size);
	}

	template< typename TIterator >
	void _replace(Size index, Size count, TIterator first, TIterator last) {
		for (; ; ++index, --count, (void) ++first) {
			if (count == 0) {
				if (first != last) {
					_insert(index, first, last);
				}
				break;
			}
			if (first == last) {
				_remove(index, count);
				break;
			}
			_get_data()[index] = *first;
		}
	}

	void _remove(Size index, Size count) {
		auto old_size = _get_size();
		if (count > 0) {
			auto new_size = old_size - count;
			CodeUnit * data = _get_raw_data();
			auto move_count = new_size - index;
			if (move_count > 0) {
				string_copy(data + index + count, data + index, move_count);
			}
			data[new_size] = CodeUnit();
			_set_size(new_size);
		}
	}


	void _clear() {
		*_get_data() = CodeUnit();
		_set_size(0);
	}

private:
	template< typename TSinglePassIterator >
	void _construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		_zeroize();
		BR_TRY {
			for (; first != last; ++first) {
				append(*first);
			}
		} BR_CATCH(...) {
			if (_is_large()) {
				AllocatorTraits::deallocate(_allocator(), _get_large_data(), _get_large_capacity());
			}
			BR_RETHROW;
		}
	}

	template< typename TForwardIterator >
	void _construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		_prepare(static_cast<Size>(distance(first, last)));
		Pointer pointer = _get_data();
		for (; first != last; ++first, (void) ++pointer) {
			*pointer = *first;
		}
		*pointer = CodeUnit();
	}

	void m_copy_assign_allocator(Self const & other, BooleanTrue) {
		if (_allocator() != other._allocator()) {
			_clear();
			_reserve(0);
		}
		_allocator() = other._allocator();
	}

	void _copy_assign_allocator(Self const & other, BooleanFalse) noexcept {
	}

	void _move_assign(Self & other, BooleanTrue) noexcept(has_nothrow_move_assignment<Allocator>) {
		_clear();
		_reserve(0);
		_coalition() = other._coalition();
		_allocator() = transfer(other._allocator());
		other._zeroize();
	}

	void _move_assign(Self & other, BooleanFalse) noexcept(AllocatorTraits::IS_ALWAYS_EQUAL) {
		if (_allocator() == other._allocator()) {
			_move_assign(other, BooleanTrue{});
		} else {
			_assign(other._get_data(), other._get_size());
		}
	}

	void _grow_and_replace(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count, CodeUnit const * units) {
		auto const MAX_SIZE = _get_max_size();
		if (old_capacity + delta_capacity > MAX_SIZE - 1) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		auto old_data = _get_data();
		auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
			? m_allocate_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
			: MAX_SIZE;
		auto new_data = AllocatorTraits::allocate(_allocator(), new_capacity);
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
			AllocatorTraits::deallocate(_allocator(), old_data, old_capacity);
		}
		_set_large_data(new_data);
		_set_large_capacity(new_capacity);
		Size new_size = copy_count + add_count + second_copy_count;
		new_data[new_size] = CodeUnit(0);
		_set_large_size(new_size);
	}

	void _grow(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count = 0) {
		auto const MAX_SIZE = _get_max_size();
		if (delta_capacity > MAX_SIZE - old_capacity) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		auto old_data = _get_data();
		auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
			? _get_allocate_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
			: MAX_SIZE;
		auto new_data = AllocatorTraits::allocate(_allocator(), new_capacity);
		if (copy_count != 0) {
			copy_n(old_data, copy_count, new_data);
		}
		auto const second_copy_count = old_size - delete_count - copy_count;
		if (second_copy_count != 0) {
			copy_n(old_data + copy_count + delete_count, second_copy_count, new_data + copy_count + add_count);
		}
		_set_large_data(new_data);
		_set_large_capacity(new_capacity);
	}

	template< typename TSinglePassIterator >
	void _assign(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		_clear();
		_append(first, last, SinglePassTraversalTag{});
	}

	template< typename TForwardIterator >
	void m_assign(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		auto const count = static_cast<Size>(distance(first, last));
		auto capacity = _get_capacity();
		if (capacity < count) {
			auto const size = _get_size();
			m_grow(capacity, count - capacity, size, 0, size);
		}
		auto pointer = _get_data();
		for (; first != last; ++first, ++pointer) {
			*pointer = *first;
		}
		*pointer = CodeUnit();
		_set_size(count);
	}

	template< typename TSinglePassIterator >
	void _append(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		for (; first != last; ++first) {
			_append(*first);
		}
	}

	template< typename TForwardIterator >
	void _append(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
		auto size = _get_size();
		auto capacity = _get_capacity();
		auto const count = static_cast<Size>(distance(first, last));
		if (count != 0) {
			if (capacity - size < count) {
				_grow(capacity, size + count - capacity, size, size, 0);
			}
			auto pointer = _get_data() + size;
			for (; first != last; ++pointer, ++first) {
				*pointer = *first;
			}
			*pointer = CodeUnit();
			_set_size(size + count);
		}
	}

	template< typename TSinglePassIterator >
	auto _insert(Size index, TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) -> Size {
		auto old_size = _get_size();
		for (; first != last; ++first) {
			_append(*first);
		}
		auto data = _get_data();
		rotate(data + index, data + old_size, data + _get_size());
		return index;
	}

	template< typename TForwardIterator >
	auto m_insert(Size index, TForwardIterator first, TForwardIterator last, ForwardTraversalTag) -> Size {
		auto old_size = _get_size();
		auto capacity = _get_capacity();
		Size count = static_cast<Size>(distance(first, last));
		if (count > 0) {
			auto new_size = old_size + count;
			CodeUnit * pointer = nullptr;
			if (capacity >= new_size) {
				pointer = _get_raw_data();
				Size move_count = old_size - index;
				if (move_count > 0) {
					string_copy(pointer + index, pointer + index + count, move_count);
				}
			} else {
				m_grow(capacity, new_size - capacity, old_size, index, 0, count);
				pointer = _get_raw_data();
			}
			pointer[new_size] = CodeUnit();
			_set_size(new_size);
			for (pointer += index; first != last; ++pointer, (void) ++first) {
				*pointer = *first;
			}
		}
		return index;
	}
};

} // namespace RawString
} // namespace Strings
} // namespace _
} // namespace BR