/**
 * @file
 * @brief memory_copy
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL memcpy
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
void libbr_memory_copy(void * D, void const * S, BR::Size n);

}

namespace BR {

/**
 * @brief like C STL memcpy
 * @param[out] D
 * @param[in] S
 * @param[in] n
 * @see libbr_memory_copy
 */
inline void memory_copy(void * D, void const * S, Size n) {
	libbr_memory_copy(D, S, n);
}

} // namespace BR

