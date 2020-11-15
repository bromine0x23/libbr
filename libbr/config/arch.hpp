/**
 * @file
 * @brief 编译器相关配置
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config/compiler.hpp>

#if !defined(BR_ARCH_CONFIG)

#if defined(BR_GCC)

#if defined(__i386__) || defined(__x86_64__)
#  define BR_ARCH_CONFIG <libbr/config/arch/x86.hpp>
#else
#  error "Unknown compiler."
#endif

#elif defined(BR_MSVC)

#if defined(_M_IX86) || defined(_M_X64)
#  define BR_ARCH_CONFIG <libbr/config/arch/x86.hpp>
#else
#  error "Unknown compiler."
#endif

#endif // defined(BR_MSVC)

#endif // !defined(BR_ARCH_CONFIG)

#if false
#include <libbr/config/arch/x86.hpp>
#endif // 0

#if defined(BR_ARCH_CONFIG)
#  include BR_ARCH_CONFIG
#endif