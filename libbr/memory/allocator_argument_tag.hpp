#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Memory {

struct AllocatorArgumentTag {};

constexpr static auto allocator_argument_tag = AllocatorArgumentTag();

} // namespace Memory
} // namespace BR