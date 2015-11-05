/**
 * @file
 * @brief memory_compare
 * @author Bromine0x23
 * @since 2015/11/5
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/relation.hpp>

namespace BR {

/**
 * @brief like C STL memcmp
 * @param[in] X
 * @param[in] Y
 * @param[in] n
 */
auto memory_compare(void const * X, void const * Y, Size n) -> Relation;

} // namespace BR

