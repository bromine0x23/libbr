/**
 * @file
 * @brief Module of dynamic memory management.
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/memory/allocator_construct.hpp>
#include <libbr/memory/allocator_construct_backward.hpp>
#include <libbr/memory/allocator_construct_forward.hpp>
#include <libbr/memory/allocator_destroy.hpp>
#include <libbr/memory/allocator_destructor.hpp>
#include <libbr/memory/default_deleter.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/memory/destroy_at.hpp>
#include <libbr/memory/destroy_n>
#include <libbr/memory/new.hpp>
#include <libbr/memory/scoped_allocator_adaptor.hpp>
// #include <libbr/memory/scoped_pointer.hpp>
#include <libbr/memory/uninitialized_copy.hpp>
#include <libbr/memory/uninitialized_copy_n.hpp>
#include <libbr/memory/uninitialized_fill.hpp>
#include <libbr/memory/uninitialized_fill_n.hpp>
#include <libbr/memory/unique_pointer.hpp>

namespace BR {

/**
 * @brief Memory
 */
inline namespace Memory {
} // namespace Memory

} // namespace BR