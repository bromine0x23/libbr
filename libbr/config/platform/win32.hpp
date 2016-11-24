/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#define BR_PLATFORM "Win32"

#define BR_WIN32

#ifndef BR_SYMBOL_EXPORT
#  define BR_HAS_DECLSPEC
#  define BR_SYMBOL_EXPORT __declspec(dllexport)
#  define BR_SYMBOL_IMPORT __declspec(dllimport)
#endif

#if !defined(BR_ARCHITECTURE)
#  if defined(_M_IX86)
#    define BR_ARCHITECTURE "i386"
#    define BR_32BIT
#  elif defined(_M_X64) || defined(_M_AMD64)
#    define BR_ARCHITECTURE "x86_64"
#    define BR_64BIT
#  endif
#endif

#if !defined(BR_BYTE_ORDER)
#  define BR_BYTE_ORDER "little endian"
#  define BR_LITTLE_ENDIAN
#endif