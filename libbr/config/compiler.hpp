/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#if defined(__clang__)
#  define BR_COMPILER_CONFIG <libbr/config/compiler/clang.hpp>
#elif defined(__GNUC__)
#  define BR_COMPILER_CONFIG <libbr/config/compiler/gcc.hpp>
#elif defined(_MSC_VER)
#  define BR_COMPILER_CONFIG <libbr/config/compiler/msvc.hpp>
#else
#  error "Unknown compiler."
#endif

#if 0
#include <libbr/config/compiler/gcc.hpp>
#include <libbr/config/compiler/msvc.hpp>
#include <libbr/config/compiler/clang.hpp>
#endif // 0
