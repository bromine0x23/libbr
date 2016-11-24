/**
 * @file
 * @brief memory_search
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief like std::memchr
 * @param[in] S
 * @param b
 * @param n
 */
auto libbr_memory_search(void * S, BR::Byte b, BR::Size n) -> void *;

}

namespace BR {
inline namespace Memory {

/**
 * @brief like std::memchr
 * @param[in] S
 * @param b
 * @param n
 * @see libbr_memory_search
 */
//@{
inline auto memory_search(void const * S, Byte b, Size n) -> void const * {
	return const_cast<void const *>(libbr_memory_search(const_cast<void *>(S), b, n));
}

inline auto memory_search(void * S, Byte b, Size n) -> void * {
	return libbr_memory_search(S, b, n);
}
//@}

} // namespace Memory
} // namespace BR

