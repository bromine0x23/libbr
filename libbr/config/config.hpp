/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#if __cplusplus < 201103L
#  if !defined(_MSC_VER) || _MSC_VER < 1900
#    error "This library need at least C++11 support"
#  endif // __cplusplus
#endif // __cplusplus

#define BR_STRINGIFY(X) BR_DO_STRINGIFY(X)
#define BR_DO_STRINGIFY(X) #X

#define BR_JOIN(X, Y) BR_DO_JOIN(X, Y)
#define BR_DO_JOIN(X, Y) BR_DO_JOIN2(X,Y)
#define BR_DO_JOIN2(X, Y) X##Y

#if !defined(BR_USER_CONFIG)
#  define BR_USER_CONFIG <libbr/config/user.hpp>
#endif // !BR_USER_CONFIG

#if !defined(NDEBUG)
#  define BR_DEBUG
#endif

#include BR_USER_CONFIG

#if 0
#  include <libbr/config/user.hpp>
#endif // 0

#if !defined(BR_COMPILER_CONFIG)
#  include <libbr/config/compiler.hpp>
#endif // !BR_COMPILER_CONFIG

#if defined(BR_COMPILER_CONFIG)
#  include BR_COMPILER_CONFIG
#endif

#if !defined(BR_PLATFORM_CONFIG)
#  include <libbr/config/platform.hpp>
#endif // !BR_PLATFORM_CONFIG

#if defined(BR_PLATFORM_CONFIG)
#  include BR_PLATFORM_CONFIG
#endif

#if !defined(BR_BYTE_ORDER)
#  pragma message("unknown byte order, set to little endian")
#  define BR_BYTE_ORDER "little endian"
#  define BR_LITTLE_ENDIAN
#endif

#include <libbr/config/macros.hpp>
#include <libbr/config/types.hpp>