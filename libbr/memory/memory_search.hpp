/**
 * @file
 * @brief memory_search - 字节搜索
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * @brief 字节搜索，类似于 \p std::memchr(examined, byte, count)
 * @param[in] examined 目标内存起始地址
 * @param byte 目标字节
 * @param count 最大搜索字节数
 */
auto libbr_memory_search(void * examined, BR::Byte byte, BR::Size count) -> void *;

}

namespace BR {
inline namespace Memory {

/**
 * @brief 字节搜索，类似于 \p std::memchr(examined, byte, count)
 * @param[in] examined 目标内存起始地址
 * @param byte 目标字节
 * @param count 最大搜索字节数
 * @see libbr_memory_search
 */
//@{
inline auto memory_search(void const * examined, Byte byte, Size count) -> void const * {
	return const_cast<void const *>(libbr_memory_search(const_cast<void *>(examined), byte, count));
}

inline auto memory_search(void * examined, Byte byte, Size count) -> void * {
	return libbr_memory_search(examined, byte, count);
}
//@}

} // namespace Memory
} // namespace BR

