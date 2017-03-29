/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)
#  define BR_PLATFORM_CONFIG "libbr/config/platform/linux.hpp""
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#  define BR_PLATFORM_CONFIG "libbr/config/platform/win32.hpp"
#elif defined(__APPLE__)
#  define BR_PLATFORM_CONFIG "libbr/config/platform/apple.hpp"
#else
#  error "Unknown platform."
#endif

#if false
#include <libbr/config/platform/apple.hpp>
#include <libbr/config/platform/linux.hpp>
#include <libbr/config/platform/win32.hpp>
#endif // 0