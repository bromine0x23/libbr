/**
 * @file
 * @brief GCC相关配置
 * @author Bromine0x23
 */
#pragma once

#define BR_COMPILER "GNU C++ version " __VERSION__

#define BR_GCC

#define BR_GCC_VER (__GNUC__ * 100 + __GNUC_MINOR__)

#define BR_GCC_FULL_VER (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#define BR_EXPECT(x, y) __builtin_expect(x, y)
#define BR_LIKELY(x) BR_EXPECT(x, true)
#define BR_UNLIKELY(x) BR_EXPECT(x, false)
#define BR_NOINLINE __attribute__ ((__noinline__))
#define BR_FORCE_INLINE inline __attribute__ ((__always_inline__))

#define BR_SYMBOL_VISIBLE __attribute__((__visibility__("default")))

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#  define BR_HAS_DECLSPEC
#  define BR_SYMBOL_EXPORT __attribute__((__dllexport__))
#  define BR_SYMBOL_IMPORT __attribute__((__dllimport__))
#else
#  define BR_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define BR_SYMBOL_IMPORT
#endif

#if defined(__SIZEOF_INT128__)
#  define BR_HAS_INT128
#  define BR_SINT128   signed __int128
#  define BR_UINT128 unsigned __int128
#endif

#if defined(__INTPTR_TYPE__) && defined(__UINTPTR_TYPE__)
#  define BR_HAS_INTPTR
#  define BR_SINTPTR  __INTPTR_TYPE__
#  define BR_UINTPTR __UINTPTR_TYPE__
#endif

#if !defined(BR_ARCHITECTURE)
#  if defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64)
#    define BR_ARCHITECTURE "x86_64"
#    define BR_X86_64
#    define BR_64BIT
#  elif defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
#    define BR_ARCHITECTURE "x86"
#    define BR_X86
#    define BR_32BIT
#  else
#    error "Unknown architecture."
#  endif
#endif

#if !defined(BR_BYTE_ORDER)
#  if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#    define BR_BYTE_ORDER "big endian"
#    define BR_BIG_ENDIAN
#  elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define BR_BYTE_ORDER "little endian"
#    define BR_LITTLE_ENDIAN
#  endif
#endif

#if !defined(__EXCEPTIONS) && !defined(BR_NO_EXCEPTIONS)
#  define BR_NO_EXCEPTIONS
#endif

#if !defined(BR_CURRENT_FUNCTION)
#  define BR_CURRENT_FUNCTION __PRETTY_FUNCTION__
#endif

#define BR_MAY_ALIAS __attribute__((__may_alias__))