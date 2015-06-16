#define BR_PLATFORM "win32"

#define BR_WIN32

#ifndef BR_SYMBOL_EXPORT
#  define BR_HAS_DECLSPEC
#  define BR_SYMBOL_EXPORT __declspec(dllexport)
#  define BR_SYMBOL_IMPORT __declspec(dllimport)
#endif
