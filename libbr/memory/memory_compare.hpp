/**
 * @file
 * @brief memory_compare
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/relation.hpp>

extern "C" {

/**
 * @brief like std::memcmp
 * @param[in] X
 * @param[in] Y
 * @param n
 */
auto libbr_memory_compare(void const * X, void const * Y, BR::Size n) -> BR::Relation;

}

namespace BR {
inline namespace Memory {

/**
 * @brief like std::memcmp
 * @param[in] X
 * @param[in] Y
 * @param n
 * @see libbr_memory_compare
 */
inline auto memory_compare(void const * X, void const * Y, Size n) -> Relation {
	return libbr_memory_compare(X, Y, n);
}

} // namespace Memory
} // namespace BR

