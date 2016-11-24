/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#define BR_PLATFORM "OSX"

#define BR_OSX

#if !defined(BR_ARCHITECTURE)
#  if defined(__i386__)
#    define BR_ARCHITECTURE "i386"
#    define BR_I386
#  elif defined(__x86_64__)
#    define BR_ARCHITECTURE "x86_64"
#    define BR_X86_64
#  endif
#endif

#if !defined(BR_BYTE_ORDER)
#  if defined(__BIG_ENDIAN__)
#    define BR_BYTE_ORDER "big endian"
#    define BR_BIG_ENDIAN
#  elif defined(__LITTLE_ENDIAN__)
#    define BR_BYTE_ORDER "little endian"
#    define BR_LITTLE_ENDIAN
#  endif
#endif