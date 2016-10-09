#pragma once

#include <libbr/config.hpp>

namespace BR {

struct AllocatorArgumentTag {
};

constexpr auto allocator_argument_tag = AllocatorArgumentTag{};

} // namespace BR