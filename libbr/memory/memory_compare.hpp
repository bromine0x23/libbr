/**
 * @file
 * @brief memory_compare
 * @author Bromine0x23
 * @since 2015/11/5
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/relation.hpp>

extern "C" {

/**
 * @brief like C STL memcmp
 * @param[in] X
 * @param[in] Y
 * @param[in] n
 */
auto libbr_memory_compare(void const * X, void const * Y, BR::Size n) -> BR::Relation;

}

namespace BR {

/**
 * @brief like C STL memcmp
 * @param[in] X
 * @param[in] Y
 * @param[in] n
 * @see libbr_memory_compare
 */
inline auto memory_compare(void const * X, void const * Y, Size n) -> Relation {
	return libbr_memory_compare(X, Y, n);
}

} // namespace BR

