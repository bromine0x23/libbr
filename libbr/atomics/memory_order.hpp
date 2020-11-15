/**
 * @file
 * @brief MemoryOrder
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Atomics {

enum class MemoryOrder : UInt {
	relaxed = 0,
	consume = 1,
	acquire = 2,
	release = 4,
	acquire_release = 6, // acquire | release
	sequentially_consistent = 14 // acquire_release | 8
};

constexpr auto operator &(MemoryOrder x, MemoryOrder y) -> Boolean {
	return (static_cast<UInt>(x) & static_cast<UInt>(y)) != 0U;
}

constexpr auto operator <(MemoryOrder x, MemoryOrder y) -> Boolean {
	return (static_cast<UInt>(x) & 15U) < (static_cast< unsigned int >(y) & 15U);
}

constexpr auto operator <=(MemoryOrder x, MemoryOrder y) -> Boolean {
	return !(y < x);
}

constexpr auto operator >(MemoryOrder x, MemoryOrder y) -> Boolean {
	return y < x;
}

constexpr auto operator >=(MemoryOrder x, MemoryOrder y) -> Boolean {
	return !(x < y);
}


} // namespace Atomics
} // namespace BR