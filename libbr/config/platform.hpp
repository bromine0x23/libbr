/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)
#  define BR_PLATFORM_CONFIG <libbr/config/platform/linux.hpp>
#elif defined(__CYGWIN__)
#  define BR_PLATFORM_CONFIG <libbr/config/platform/cygwin.hpp>
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#  define BR_PLATFORM_CONFIG <libbr/config/platform/win32.hpp>
#else
#  error "Unknown platform."
#endif

#if !defined(BR_BYTE_ORDER)
#  pragma c("unknown byte order, set to little endian")
#  define BR_BYTE_ORDER "little endian"
#  define BR_LITTLE_ENDIAN
#endif

#if 0
#include <libbr/config/platform/linux.hpp>
#include <libbr/config/platform/cygwin.hpp>
#include <libbr/config/platform/win32.hpp>
#endif // 0

