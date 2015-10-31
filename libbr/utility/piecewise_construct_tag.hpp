#pragma once

#include <libbr/config.hpp>

namespace BR {

struct PiecewiseConstructTag {
};

constexpr auto piecewise_construct_tag = PiecewiseConstructTag();

} // namespace BR