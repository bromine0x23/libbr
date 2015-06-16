#pragma once

#include <libbr/config.hpp>

namespace BR {

struct YesTag {};

struct NoTag {
	NChar padding[0x10];
};

static_assert(sizeof(YesTag) != sizeof(NoTag), "Yes & No shouldn't have same size.");

} // namespace BR



