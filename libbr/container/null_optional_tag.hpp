/**
 * @file
 * @brief NullOptionalTag & null_optional_tag
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Container {

/**
 * @brief Tag type to disengage optional objects.
 */
struct NullOptionalTag {
	explicit constexpr NullOptionalTag(int) noexcept {
	}
};

/**
 * @brief instance of NullOptionalTag
 */
constexpr auto null_optional_tag = NullOptionalTag(0);

} // namespace Container
} // namespace BR