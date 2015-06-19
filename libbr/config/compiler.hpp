#pragma once

#if defined(__GNUC__)
#  define BR_COMPILER_CONFIG <libbr/config/compiler/gcc.hpp>
#elif defined(__clang__)
#  define BR_COMPILER_CONFIG <libbr/config/compiler/clang.hpp>
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
