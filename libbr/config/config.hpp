#pragma once

#if __cplusplus < 201103L
#  error "This library need at least C++11 support"
#endif // __cplusplus

#if !defined(BR_USER_CONFIG)
#  define BR_USER_CONFIG <libbr/config/user.hpp>
#endif // !BR_USER_CONFIG

#if !defined(NDEBUG)
#  define BR_DEBUG
#endif

#if !defined(BR_COMPILER_CONFIG)
#  include <libbr/config/compiler.hpp>
#endif // !BR_COMPILER_CONFIG

#if !defined(BR_PLATFORM_CONFIG)
#  include <libbr/config/platform.hpp>
#endif // !BR_PLATFORM_CONFIG

#if 0
#  include <libbr/config/user.hpp>
#endif // 0

#include BR_USER_CONFIG

#if defined(BR_COMPILER_CONFIG)
#include BR_COMPILER_CONFIG
#endif

#if defined(BR_PLATFORM_CONFIG)
#include BR_PLATFORM_CONFIG
#endif

#include <libbr/config/detail.hpp>