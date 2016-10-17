/**
 * @file
 * @author Bromine0x23
 * @date 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

enum class FloatCategory : SInt {
	nan = 0x0100,
	infinite = 0x0500,
	normal = 0x0400,
	subnormal = 0x4400,
	zero = 0x4000,
};

constexpr auto to_i(FloatCategory category) noexcept -> SInt {
	return static_cast<SInt>(category);
}

} // namespace BR
