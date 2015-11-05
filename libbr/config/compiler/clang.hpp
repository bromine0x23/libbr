/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#define BR_COMPILER "Clang version " __clang_version__

#define BR_CLANG

#define BR_CLANG_VER (__clang_major__ * 100 + __clang_minor__)

#if !defined(__has_extension)
#  define __has_extension __has_feature
#endif

#if defined(__has_builtin)
#  if __has_builtin(__builtin_expect)
#    define BR_EXCEPT(x, y) __builtin_expect(x, y)
#    define BR_LIKELY(x) BR_EXCEPT(x, true)
#    define BR_UNLIKELY(x) BR_EXCEPT(x, false)
#  endif
#endif

#if defined(__has_warning)
#  if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#    define BR_FALLTHROUGH [[clang::fallthrough]]
#  endif
#endif

#if !(defined(_WIN32) || defined(__WIN32__) || defined(WIN32))
#  define BR_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define BR_SYMBOL_IMPORT
#  define BR_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#endif

#if defined(__SIZEOF_INT128__)
#  define BR_HAS_INT128
#  define BR_SINT128   signed __int128
#  define BR_UINT128 unsigned __int128
#endif