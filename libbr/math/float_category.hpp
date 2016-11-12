/**
 * @file
 * @author Bromine0x23
 * @date 2016/10/16
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Math {

enum class FloatCategory : SInt {
	NaN = 0x0100,
	Infinite = 0x0500,
	Normal = 0x0400,
	SubNormal = 0x4400,
	Zero = 0x4000,
};

constexpr auto to_i(FloatCategory category) noexcept -> SInt {
	return static_cast<SInt>(category);
}

} // inline namespace Math
} // namespace BR
