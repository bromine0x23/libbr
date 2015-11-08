/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#if defined(BR_DOXYGEN)

#else

#if __cplusplus >= 201103L
#  define BR_CXX11
#endif

#if __cplusplus > 201103L
#  define BR_AFTER_CXX11
#endif

#if __cplusplus >= 201402L
#  define BR_CXX14
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

#if !defined(BR_FORCE_INLINE)
#  define BR_NO_FORCE_INLINE
#  define BR_FORCE_INLINE inline
#endif

#if !defined(BR_NOINLINE)
#  define BR_NO_NOINLINE
#  define BR_NOINLINE
#endif

#if !defined(BR_EXPECT)
#  define BR_EXPECT(x, y) (x == y)
#endif

#if !defined(BR_LIKELY)
#  define BR_LIKELY(x) (x)
#endif

#if !defined(BR_UNLIKELY)
#  define BR_UNLIKELY(x) (x)
#endif

#define BR_EMPTY_ARG

#if !defined(BR_FALLTHROUGH)
#  define BR_FALLTHROUGH ((void)0)
#endif

#endif