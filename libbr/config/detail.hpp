#pragma once

#if __cplusplus >= 201402L
# define BR_CXX14
#endif

#if __cplusplus > 201103L
# define BR_AFTER_CXX11
#endif

#if __cplusplus >= 201103L
# define BR_CXX11
#endif

#if defined(BR_AFTER_CXX11)
#  define BR_CONSTEXPR_AFTER_CXX11 constexpr
#else
#  define BR_CONSTEXPR_AFTER_CXX11
#endif // defined

#if !defined(BR_SYMBOL_EXPORT)
# define BR_SYMBOL_EXPORT
#endif

#if !defined(BR_SYMBOL_IMPORT)
# define BR_SYMBOL_IMPORT
#endif

#if !defined(BR_SYMBOL_VISIBLE)
# define BR_SYMBOL_VISIBLE
#endif

#if !defined(BR_FORCEINLINE)
#  define BR_NO_FORCEINLINE
#  define BR_FORCEINLINE inline
#endif

#if !defined(BR_NOINLINE)
#  define BR_NO_NOINLINE
#  define BR_NOINLINE
#endif

#if !defined(BR_LIKELY)
#  define BR_LIKELY(x) x
#endif

#if !defined(BR_UNLIKELY)
#  define BR_UNLIKELY(x) x
#endif

#define BR_STRINGIZE(X) BR_DO_STRINGIZE(X)
#define BR_DO_STRINGIZE(X) #X

#define BR_JOIN(X, Y) BR_DO_JOIN(X, Y)
#define BR_DO_JOIN(X, Y) BR_DO_JOIN2(X,Y)
#define BR_DO_JOIN2(X, Y) X##Y

#define BR_EMPTY_ARG

#if !defined(BR_FALLTHROUGH)
#  define BR_FALLTHROUGH ((void)0)
#endif

#if !defined(BR_BYTE_ORDER)
#  warning "unknown byte order, set to little endian"
#  define BR_BYTE_ORDER "little endian"
#  define BR_LITTLE_ENDIAN
#endif