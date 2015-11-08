/**
 * @file
 * @brief memory_search
 * @author Bromine0x23
 * @since 2015/11/5
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like C STL memchr
 * @param[out] D
 * @param[in] b
 * @param[in] n
 */
auto libbr_memory_search(void * D, BR::UInt8 b, BR::Size n) -> void *;

}

namespace BR {

/**
 * @brief like C STL memchr
 * @param[out] D
 * @param[in] b
 * @param[in] n
 * @see libbr_memory_search
 */
//@{
inline auto memory_search(void const * D, UInt8 b, Size n) -> void const * {
	return const_cast<void const *>(libbr_memory_search(const_cast<void *>(D), b, n));
}

inline auto memory_search(void * D, UInt8 b, Size n) -> void * {
	return libbr_memory_search(D, b, n);
}
//@}

} // namespace BR

