/**
 * @file
 * @brief InPlaceTag
 * @author Bromine0x23
 * @since 2015/11/14
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

struct InPlaceTag {
};

constexpr auto in_place_tag = InPlaceTag();

}