/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#define BR_COMPILER "Microsoft Visual C++ version " BR_STRINGIFY(_MSC_VER)

#define BR_MSVC

#define BR_MSVC_VER _MSC_VER

#if _MSC_FULL_VER <= 100000000
#  define BR_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#else
#  define BR_MSVC_FULL_VER _MSC_FULL_VER
#endif // _MSC_FULL_VER <= 100000000

#define BR_NOINLINE __declspec(noinline)
#define BR_FORCE_INLINE __forceinline

#if !defined(BR_ARCHITECTURE)
#  if defined(_M_X64) || defined(_M_AMD64)
#    define BR_ARCHITECTURE "x86_64"
#    define BR_X86_64
#    define BR_64BIT
#  elif defined(_M_IX86)
#    define BR_ARCHITECTURE "x86"
#    define BR_X86
#    define BR_32BIT
#  else
#    error "Unknown architecture."
#  endif
#endif

#if !defined(_CPPUNWIND) && !defined(BR_NO_EXCEPTIONS)
#  define BR_NO_EXCEPTIONS
#endif