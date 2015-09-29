/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>

#if defined(BR_DOXYGEN)
/**
 * @brief 获取当前上下文的函数名
 */
# define BR_CURRENT_FUNCTION
#elif defined(BR_GCC)
# define BR_CURRENT_FUNCTION __PRETTY_FUNCTION__
#else
# define BR_CURRENT_FUNCTION __func__
#endif
