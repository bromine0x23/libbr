/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
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

#if !defined(BR_BYTE_ORDER)
#  if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#    define BR_BYTE_ORDER "big endian"
#    define BR_LITTLE_ENDIAN
#  elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define BR_BYTE_ORDER "little endian"
#    define BR_BIG_ENDIAN
#  endif
#endif

