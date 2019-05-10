/**
 * @file
 * @brief 填充内存
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief 填充内存，类似于 \p std::memset(destination, byte, count)
 * @param[out] destination 指向目标内存的指针
 * @param[in]  count       填充字节数
 * @param[in]  byte        字节
 * @return destination
 */
auto libbr_memory_fill(void * destination, BR::Size count, BR::Byte byte) -> void *;

}

namespace BR {
inline namespace Memory {

/**
 * @brief 填充内存，类似于 \p std::memset(destination, byte, count)
 * @param[out] destination 指向目标内存的指针
 * @param[in]  count       填充字节数
 * @param[in]  byte        字节
 * @return destination
 * @see libbr_memory_set
 */
inline auto memory_fill(void * destination, Size count, Byte byte) -> void * {
	return libbr_memory_fill(destination, count, byte);
}

} // namespace Memory
} // namespace BR

