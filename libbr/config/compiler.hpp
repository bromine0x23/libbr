/**
 * @file
 * @brief 编译器相关配置
 * @author Bromine0x23
 */
#pragma once

#if !defined(BR_COMPILER_CONFIG)

#if defined(__clang__)
#  define BR_COMPILER_CONFIG <libbr/config/compiler/clang.hpp>
#elif defined(__GNUC__)
#  define BR_COMPILER_CONFIG "libbr/config/compiler/gcc.hpp"
#elif defined(_MSC_VER)
#  define BR_COMPILER_CONFIG "libbr/config/compiler/msvc.hpp"
#else
#  error "Unknown compiler."
#endif

#endif // !BR_COMPILER_CONFIG

#if false
#include <libbr/config/compiler/gcc.hpp>
#include <libbr/config/compiler/msvc.hpp>
#include <libbr/config/compiler/clang.hpp>
#endif // 0

#if defined(BR_COMPILER_CONFIG)
#  include BR_COMPILER_CONFIG
#endif