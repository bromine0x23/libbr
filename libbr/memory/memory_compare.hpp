/**
 * @file
 * @brief memory_compare
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/relation.hpp>

extern "C" {

/**
 * @brief 类似于标准库的 \p std::memcmp
 * @param[in] x,y
 * @param[in] count
 */
auto libbr_memory_compare(void const * x, void const * y, BR::Size n) -> BR::SInt;

}

namespace BR {
inline namespace Memory {

/**
 * @brief 类似于标准库的 \p std::memcmp
 * @param[in] x,y
 * @param[in] count
 * @see libbr_memory_compare
 */
inline auto memory_compare(void const * x, void const * y, Size count) -> Relation {
	return to_relation(libbr_memory_compare(x, y, count));
}

} // namespace Memory
} // namespace BR

