/**
 * @file
 * @brief 宏定义
 * @author Bromine0x23
 */
#pragma once

#define _CXX17 201703L

#if __cplusplus == _CXX17
#  define BR_STANDARD "C++17"
#  define BR_CXX17
#endif

#if __cplusplus > _CXX17
#  define BR_AFTER_CXX17
#endif

#define BR_EMPTY

#define BR_STRINGIFY(X) BR_DO_STRINGIFY(X)
#define BR_DO_STRINGIFY(X) #X

#define BR_JOIN(X, Y) BR_DO_JOIN(X, Y)
#define BR_DO_JOIN(X, Y) BR_DO_JOIN2(X,Y)
#define BR_DO_JOIN2(X, Y) X##Y

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

#if !defined(BR_MAY_ALIAS)
#  define BR_NO_MAY_ALIAS
#  define BR_MAY_ALIAS
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

#if !defined(BR_FORCE_USE)
#  define BR_FORCE_USE(x) ((void)x)
#endif

#define BR_EMPTY_ARG

#if !defined(BR_FALLTHROUGH)
#  define BR_FALLTHROUGH ((void)0)
#endif

#if !defined(BR_CURRENT_FUNCTION)
#  define BR_CURRENT_FUNCTION __func__
#endif

#if defined(BR_NO_EXCEPTIONS)
#  define BR_TRY if (true)
#  define BR_CATCH(...) else if (false)
#  define BR_RETHROW
#else
#  define BR_TRY try
#  define BR_CATCH(e) catch(e)
#  define BR_RETHROW throw
#endif

#undef _CXX17