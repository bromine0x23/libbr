#define BR_COMPILER "Clang version " __clang_version__

#define BR_CLANG

#define BR_CLANG_VER (__clang_major__ * 100 + __clang_minor__)

#define BR_LIKELY(x) __builtin_expect(x, 1)
#define BR_UNLIKELY(x) __builtin_expect(x, 0)