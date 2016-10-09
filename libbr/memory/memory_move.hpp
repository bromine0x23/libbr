/**
 * @file
 * @brief memory_move
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL memmove
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
void libbr_memory_move(void * D, void const * S, ::BR::Size n);

}

namespace BR {

/**
 * @brief like C STL memmove
 * @param[out] D
 * @param[in] S
 * @param[in] n
 * @see libbr_memory_move
 */
inline void memory_move(void * D, void const * S, Size n) {
	return libbr_memory_move(D, S, n);
}

} // namespace BR

