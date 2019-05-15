/**
 * @file
 * @brief 内存管理
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 内存管理
 */
inline namespace Memory {
} // namespace Memory

} // namespace BR

#include <libbr/memory/alignment.hpp>

#include <libbr/memory/allocator.hpp>

#include <libbr/memory/address_of.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/memory/memory_copy_unsafely.hpp>
#include <libbr/memory/memory_fill.hpp>
#include <libbr/memory/memory_search.hpp>

#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>