/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#define BR_PLATFORM "Win32"

#define BR_WIN32

#ifndef BR_SYMBOL_EXPORT
#  define BR_HAS_DECLSPEC
#  define BR_SYMBOL_EXPORT __declspec(dllexport)
#  define BR_SYMBOL_IMPORT __declspec(dllimport)
#endif

#if !defined(BR_BYTE_ORDER)
#  define BR_BYTE_ORDER "little endian"
#  define BR_LITTLE_ENDIAN
#endif