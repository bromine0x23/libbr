#pragma once

#define BR_COMPILER "GNU C++ version " __VERSION__

#define BR_GCC

#define BR_GCC_VER (__GNUC__ * 100 + __GNUC_MINOR__)

#define BR_GCC_FULL_VER (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

#define BR_LIKELY(x) __builtin_expect(x, 1)
#define BR_UNLIKELY(x) __builtin_expect(x, 0)
#define BR_NORETURN __attribute__ ((__noreturn__))
#define BR_NOINLINE __attribute__ ((__noinline__))
#define BR_FORCEINLINE inline __attribute__ ((__always_inline__))
#define BR_ALIGNMENT(x) __attribute__ ((__aligned__(x)))

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
#endif
