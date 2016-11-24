/**
 * @file
 * @brief memory_move
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like std::memmove
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
void libbr_memory_move(void * D, void const * S, BR::Size n);

}

namespace BR {
inline namespace Memory {

/**
 * @brief like std::memmove
 * @param[out] D
 * @param[in] S
 * @param[in] n
 * @see libbr_memory_move
 */
inline void memory_move(void * D, void const * S, Size n) {
	return libbr_memory_move(D, S, n);
}

} // namespace Memory
} // namespace BR

