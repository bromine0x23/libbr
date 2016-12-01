/**
 * @file
 * @brief 分配器
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/utility/type.hpp>
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
	constexpr auto operator==(Allocator<TOtherElement> const &) const noexcept -> bool {
		return true;
	}

	template<typename TOtherElement>
	constexpr auto operator!=(Allocator<TOtherElement> const &) const noexcept -> bool {
		return false;
	}

}; // class Allocator< void >

template<typename TElement>
class Allocator {
public:
	using Element = TElement;

	using Pointer = Element *;

	using ConstPointer = Element const *;

	using Size = BR::Size;

	using Difference = PointerDifference;

	using IsPropagateOnContainerMoveAssignment = BooleanTrue;

	using IsAlwaysEqual = BooleanTrue;

	template<typename TOtherElement>
	using Rebind = Allocator<TOtherElement>;

	constexpr Allocator() noexcept = default;

	template<typename TOtherElement>
	constexpr Allocator(Allocator<TOtherElement> const &) noexcept {
	}

	auto allocate(Size size, Allocator<void>::ConstPointer = nullptr) -> Pointer {
		return static_cast<Pointer>(::operator new(size * sizeof(Element)));
	}

	void deallocate(Pointer pointer, Size) noexcept {
		return ::operator delete(reinterpret_cast< void * >(pointer));
	}

	template<typename TOtherElement>
	constexpr auto operator==(Allocator<TOtherElement> const &) const noexcept -> bool {
		return true;
	}

	template<typename TOtherElement>
	constexpr auto operator!=(Allocator<TOtherElement> const &) const noexcept -> bool {
		return false;
	}

}; // class Allocator<TElement>

} // namespace Memory
} // namespace BR