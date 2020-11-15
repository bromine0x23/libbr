/**
 * @file
 * @brief 分配器
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/alignment.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief 默认分配器
 * @tparam TValue 元素类型
 */
template<typename TElement>
class Allocator;

} // namespace Memory



inline namespace Memory {

template< typename TElement >
class Allocator {
public:
	using Element = TElement;

	using Size = BR::Size;

	using Different = PointerDifference;

	constexpr static Boolean IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT = true;

	constexpr static Boolean IS_ALWAYS_EQUAL = true;

	constexpr Allocator() noexcept = default;

	constexpr Allocator(Allocator const & other) noexcept = default;

	template<typename TOtherElement>
	constexpr explicit Allocator(Allocator<TOtherElement> const &) noexcept {
	}

	~Allocator() noexcept = default;

	auto allocate(Size size) -> Element * {
		if constexpr (alignof(Element) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
			auto alignment = Alignment(alignof(Element));
			return static_cast<Element *>(::operator new(size * sizeof(Element), alignment));
		}
		return static_cast<Element *>(::operator new(size * sizeof(Element)));
	}

	void deallocate(Element * pointer, Size) noexcept {
		if constexpr (alignof(Element) > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
			::operator delete(pointer, Alignment(alignof(Element)));
			return;
		}
		return ::operator delete(pointer);
	}

	template<typename TOtherElement>
	constexpr auto operator==(Allocator<TOtherElement> const &) const noexcept -> bool {
		return true;
	}

	template<typename TOtherElement>
	constexpr auto operator!=(Allocator<TOtherElement> const &) const noexcept -> bool {
		return false;
	}

}; // class BR::Allocator<TElement>

} // namespace Memory

} // namespace BR