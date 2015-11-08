/**
 * @file
 * @brief 分配器
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/new.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

/**
 * @brief 默认分配器
 * @tparam TValue 元素类型
 */
template< typename TValue >
class Allocator;

template<>
class Allocator<void> {
public:
	using Value = void;

	using Pointer = void *;

	using ConstPointer = void const *;

	template< typename TOtherValue >
	using Rebind = Allocator<TOtherValue>;

	constexpr Allocator() noexcept = default;

	template< typename TOtherValue >
	BR_FORCE_INLINE auto operator==(Allocator<TOtherValue> const & _dummy) const noexcept -> bool {
		return true;
	}

	template< typename TOtherValue >
	BR_FORCE_INLINE auto operator!=(Allocator<TOtherValue> const & _dummy) const noexcept -> bool {
		return false;
	}

}; // class Allocator< void >

template<>
class Allocator< void const > {
public:
	using Value = void const;

	using Pointer = void const *;

	using ConstPointer = void const *;

	template< typename TOtherValue >
	using Rebind = Allocator<TOtherValue>;

	constexpr Allocator() noexcept = default;

	template< typename TOtherValue >
	BR_FORCE_INLINE auto operator==(Allocator<TOtherValue> const & _dummy) const noexcept -> bool {
		return true;
	}

	template< typename TOtherValue >
	BR_FORCE_INLINE auto operator!=(Allocator<TOtherValue> const & _dummy) const noexcept -> bool {
		return false;
	}

}; // class Allocator< void const >

template< typename TValue >
class Allocator {
public:
	using Value = TValue;

	using Pointer = TValue *;

	using ConstPointer = TValue const *;

	using Reference = TValue &;

	using ConstReference = TValue const &;

	using Size = BR::Size;

	using Difference = BR::PointerDifference;

	using IsPropagateOnContainerMoveAssignment = BooleanTrue;

	template< typename TOtherValue >
	using Rebind = Allocator<TOtherValue>;

	BR_FORCE_INLINE constexpr Allocator() noexcept {
	}

	template< typename TOtherValue >
	BR_FORCE_INLINE constexpr Allocator(Allocator<TOtherValue> const & _dummy) noexcept {
	}

	BR_FORCE_INLINE auto address(Reference reference) noexcept -> Pointer {
		return address_of(reference);
	}

	BR_FORCE_INLINE auto address(ConstReference reference) const noexcept -> ConstPointer {
		return address_of(reference);
	}

	BR_FORCE_INLINE auto allocate(Size size, Allocator<void>::ConstPointer _dummy = nullptr) -> Pointer {
		return static_cast<Pointer>(Detail::Memory::allocate(size * sizeof(Value)));
	}

	BR_FORCE_INLINE void deallocate(Pointer pointer, Size) noexcept {
		return Detail::Memory::deallocate(reinterpret_cast< void * >(pointer));
	}

	BR_FORCE_INLINE auto maxSize() const noexcept -> Size {
		return Size(~0) / sizeof(Value);
	}

	template< typename TOtherValue, typename ... TArgs >
	BR_FORCE_INLINE void construct(TOtherValue * pointer, TArgs && ... args) {
		::new(reinterpret_cast< void * >(pointer)) TOtherValue(forward<TArgs>(args) ...);
	}

	BR_FORCE_INLINE void destroy(Pointer pointer) {
		pointer->~Value();
	}

	template< typename TOtherValue >
	BR_FORCE_INLINE auto operator==(Allocator<TOtherValue> const & _dummy) const noexcept -> bool {
		return true;
	}

	template< typename TOtherValue >
	BR_FORCE_INLINE auto operator!=(Allocator<TOtherValue> const & _dummy) const noexcept -> bool {
		return false;
	}

}; // class Allocator

template< typename TValue >
class Allocator< TValue const > {
public:
	using Value = TValue;

	using Pointer = TValue const *;

	using ConstPointer = TValue const *;

	using Reference = TValue const &;

	using ConstReference = TValue const &;

	using Size = BR::Size;

	using Difference = BR::PointerDifference;

	using IsPropagateOnContainerMoveAssignment = BooleanTrue;

	template< typename TOtherValue >
	using Rebind = Allocator<TOtherValue>;

	BR_FORCE_INLINE constexpr Allocator() noexcept {
	}

	template< typename TOtherValue >
	BR_FORCE_INLINE constexpr Allocator(Allocator<TOtherValue> const & _dummy) noexcept {
	}

	BR_FORCE_INLINE auto address(ConstReference reference) const noexcept -> ConstPointer {
		return address_of(reference);
	}

	BR_FORCE_INLINE auto allocate(Size size, Allocator<void>::ConstPointer _dummy = nullptr) -> Pointer {
		return static_cast< Pointer >(Detail::Memory::allocate(size * sizeof(Value)));
	}

	BR_FORCE_INLINE void deallocate(Pointer pointer, Size) noexcept {
		return Detail::Memory::allocate(reinterpret_cast< void * >(pointer));
	}

	BR_FORCE_INLINE auto maxSize() const noexcept -> Size {
		return Size(~0) / sizeof(Value);
	}

	template< typename TOtherValue, typename ... TArguments >
	BR_FORCE_INLINE void construct(TOtherValue * pointer, TArguments && ... arguments) {
		::new(reinterpret_cast< void * >(pointer)) TOtherValue(forward<TArguments>(arguments) ...);
	}

	BR_FORCE_INLINE void destroy(Pointer pointer) {
		pointer->~Value();
	}

	template< typename TOtherValue >
	BR_FORCE_INLINE auto operator==(Allocator<TOtherValue> const & _dummy) const noexcept -> bool {
		return true;
	}

	template< typename TOtherValue >
	BR_FORCE_INLINE auto operator!=(Allocator<TOtherValue> const & _dummy) const noexcept -> bool {
		return false;
	}

}; // class Allocator< TValue const >

} // namespace BR