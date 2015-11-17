/**
 * @file
 * @brief InPlaceTag
 * @author Bromine0x23
 * @since 2015/11/14
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

struct NullOptional {
	explicit constexpr NullOptional(int) noexcept {
	}
};

constexpr auto null_optional = NullOptional(0);

}