/**
 * @file
 * @brief InPlaceTag & in_place_tag
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Container {

/**
 * @brief Tag type for in-place construction.
 */
struct InPlaceTag {};

/**
 * @brief instance of InPlaceTag for in-place construction.
 */
constexpr auto in_place_tag = InPlaceTag{};

} // namespace Container
} // namespace BR