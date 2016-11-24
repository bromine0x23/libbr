/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#define BR_PLATFORM "Linux"

#define BR_LINUX

#if !defined(BR_ARCHITECTURE)
#  if defined(__i386__)
#    define BR_ARCHITECTURE "i386"
#    define BR_32BIT
#  elif defined(__x86_64__)
#    define BR_ARCHITECTURE "x86_64"
#    define BR_64BIT
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
