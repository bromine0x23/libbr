/**
 * @file
 * @brief memory_set
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief like C STL memset
 * @param[out] D
 * @param[in] v
 * @param[in] n
 */
auto memory_set(void * D, Byte v, Size n) -> void *;

} // namespace BR

