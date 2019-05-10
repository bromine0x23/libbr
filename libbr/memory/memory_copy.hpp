/**
 * @file
 * @brief memory_copy
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like \p std::memmove(destination, source, count)
 * @param[in] source
 * @param[out] destination
 * @param[in] count
 */
void libbr_memory_copy(void const * source, void * destination, BR::Size count);

}

namespace BR {
inline namespace Memory {

/**
 * @brief like \p std::memmove(destination, source, count)
 * @param[in] source
 * @param[out] destination
 * @param[in] count
 * @see libbr_memory_copy_unsafely
 */
inline void memory_copy(void const * source, void * destination, BR::Size count) {
	return libbr_memory_copy(source, destination, count);
}

} // namespace Memory
} // namespace BR

