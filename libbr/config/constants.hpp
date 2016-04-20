/**
 * @file
 * @author Bromine0x23
 * @since 2015/12/12
 */
#pragma once

#include <libbr/config/types.hpp>

namespace BR {

/**
 * @brief 窄字符类型是否无符号
 */
constexpr static auto is_nchar_unsigned = static_cast<NChar>(0) < static_cast<NChar>(-1);

/**
 * @brief 宽字符类型是否无符号
 */
constexpr static auto is_wchar_unsigned = static_cast<WChar>(0) < static_cast<WChar>(-1);

#if defined(BR_LITTLE_ENDIAN)
constexpr static auto is_little_endian = true;
constexpr static auto is_big_endian = false;
#elif defined(BR_BIG_ENDIAN)
constexpr static auto is_little_endian = false;
constexpr static auto is_big_endian = true;
#else
constexpr static auto is_little_endian = false;
constexpr static auto is_big_endian = false;
#endif

} // namespace BR