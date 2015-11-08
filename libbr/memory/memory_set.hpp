/**
 * @file
 * @brief memory_set
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL memset
 * @param[out] D
 * @param[in] v
 * @param[in] n
 */
auto libbr_memory_set(void * D, BR::Byte v, BR::Size n) -> void *;

}

namespace BR {

/**
 * @brief like C STL memset
 * @param[out] D
 * @param[in] v
 * @param[in] n
 * @see libbr_memory_set
 */
inline auto memory_set(void * D, Byte v, Size n) -> void * {
	return libbr_memory_set(D, v, n);
}

} // namespace BR

