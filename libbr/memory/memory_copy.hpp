/**
 * @file
 * @brief memory_copy
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like std::memcpy
 * @param[out] D
 * @param[in] S
 * @param n
 */
void libbr_memory_copy(void * D, void const * S, BR::Size n);

}

namespace BR {
inline namespace Memory {

/**
 * @brief like std::memcpy
 * @param[out] D
 * @param[in] S
 * @param n
 * @see libbr_memory_copy
 */
inline void memory_copy(void * D, void const * S, Size n) {
	libbr_memory_copy(D, S, n);
}

} // namespace Memory
} // namespace BR

