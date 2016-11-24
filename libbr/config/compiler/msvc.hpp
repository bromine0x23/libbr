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

#if !defined(_CPPUNWIND) && !defined(BR_NO_EXCEPTIONS)
#  define BR_NO_EXCEPTIONS
#endif