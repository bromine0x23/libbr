/**
 * @file
 * @brief 分配器
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {
inline namespace Memory {

/**
 * @brief 默认分配器
 * @tparam TValue 元素类型
 */
template<typename TElement>
class Allocator;

template<>
class Allocator<void> {
public:
	using Element = void;

	using Pointer = void *;

	using ConstPointer = void const *;

	using Size = BR::Size;

	using Difference = BR::PointerDifference;

	using IsPropagateOnContainerMoveAssignment = BooleanTrue;

	using IsAlwaysEqual = BooleanTrue;

	template<typename TOtherElement>
	using Rebind = Allocator<TOtherElement>;

	constexpr Allocator() noexcept = default;

	template<typename TOtherElement>
	BR_FORCE_INLINE auto operator==(Allocator<TOtherElement> const &) const noexcept -> bool {
		return true;
	}

	template<typename TOtherElement>
	BR_FORCE_INLINE auto operator!=(Allocator<TOtherElement> const &) const noexcept -> bool {
		return false;
	}

}; // class Allocator< void >

template<typename TElement>
class Allocator {
public:
	using Element = TElement;

	using Pointer = Element *;

	using ConstPointer = Element const *;

	using Reference = Element &;

	using ConstReference = Element const &;

	using Size = BR::Size;

	using Difference = PointerDifference;

	using IsPropagateOnContainerMoveAssignment = BooleanTrue;

	using IsAlwaysEqual = BooleanTrue;

	template<typename TOtherElement>
	using Rebind = Allocator<TOtherElement>;

	BR_FORCE_INLINE constexpr Allocator() noexcept {
	}

	template<typename TOtherElement>
	BR_FORCE_INLINE constexpr Allocator(Allocator<TOtherElement> const &) noexcept {
	}

	BR_FORCE_INLINE auto address(Reference reference) noexcept -> Pointer {
		return address_of(reference);
	}

	BR_FORCE_INLINE auto address(ConstReference reference) const noexcept -> ConstPointer {
		return address_of(reference);
	}

	BR_FORCE_INLINE auto allocate(Size size, Allocator<void>::ConstPointer = nullptr) -> Pointer {
		return static_cast<Pointer>(::operator new(size * sizeof(Element)));
	}

	BR_FORCE_INLINE void deallocate(Pointer pointer, Size) noexcept {
		return ::operator delete(reinterpret_cast< void * >(pointer));
	}

	BR_FORCE_INLINE auto maxSize() const noexcept -> Size {
		return Size(~0) / sizeof(Element);
	}

	template<typename TOtherElement, typename ... TArgs>
	BR_FORCE_INLINE void construct(TOtherElement *pointer, TArgs &&... args) {
		::new(reinterpret_cast< void * >(pointer)) TOtherElement(forward<TArgs>(args) ...);
	}

	BR_FORCE_INLINE void destroy(Pointer pointer) {
		pointer->~Value();
	}

	template<typename TOtherElement>
	BR_FORCE_INLINE auto operator==(Allocator<TOtherElement> const &) const noexcept -> bool {
		return true;
	}

	template<typename TOtherElement>
	BR_FORCE_INLINE auto operator!=(Allocator<TOtherElement> const &) const noexcept -> bool {
		return false;
	}

}; // class Allocator<TElement>

} // namespace Memory
} // namespace BR