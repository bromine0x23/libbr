/**
 * @file
 * @brief memory_search
 * @author Bromine0x23
 * @since 2015/11/5
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

//@{
/**
 * @brief like C STL memchr
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
auto memory_search(void const * D, UInt8 b, Size n) -> void const *;

auto memory_search(void * D, UInt8 b, Size n) -> void *;
//@}

} // namespace BR

