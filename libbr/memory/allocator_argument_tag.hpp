#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Memory {

struct AllocatorArgumentTag {
};

constexpr auto allocator_argument_tag = AllocatorArgumentTag{};

} // namespace Memory
} // namespace BR