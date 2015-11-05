/**
 * @file
 * @brief memory_move
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief like C STL memmove
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
void memory_move(void * D, void const * S, Size n);

} // namespace BR

