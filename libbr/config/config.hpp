#pragma once

#ifndef BR_SYMBOL_EXPORT
# define BR_SYMBOL_EXPORT
#endif
#ifndef BR_SYMBOL_IMPORT
# define BR_SYMBOL_IMPORT
#endif
#ifndef BR_SYMBOL_VISIBLE
# define BR_SYMBOL_VISIBLE
#endif

#ifndef BR_FORCEINLINE
#  define BR_NO_FORCEINLINE
#  define BR_FORCEINLINE inline
#endif // BR_FORCEINLINE

#ifndef BR_NOINLINE
#  define BR_NO_NOINLINE
#  define BR_NOINLINE
#endif // BR_NOINLINE

#ifndef BR_NORETURN
#  define BR_NO_NORETURN
#  define BR_NORETURN
#endif // BR_NORETURN

#ifndef BR_ALIGNMENT
#  define BR_ALIGNMENT(x) alignas(x)
#endif // BR_ALIGNMENT

#ifndef BR_LIKELY
#  define BR_LIKELY(x) x
#endif // BR_LIKELY

#ifndef BR_UNLIKELY
#  define BR_UNLIKELY(x) x
#endif // BR_UNLIKELY

#define BR_NESTED_TEMPLATE template
#define BR_DEDUCED_TYPENAME typename
#define BR_NULLPTR nullptr
#define BR_DEFAULTED_FUNCTION(FUNCTION, BODY) FUNCTION = default;
#define BR_DELETED_FUNCTION(FUNCTION) FUNCTION = delete;
#define BR_NOEXCEPT noexcept
#define BR_NOEXCEPT_OR_NOTHROW noexcept
#define BR_NOEXCEPT_IF(EXPRESSION) noexcept((EXPRESSION))
#define BR_NOEXCEPT_EXPR(EXPRESSION) noexcept((EXPRESSION))
#define BR_CONSTEXPR constexpr
#define BR_CONSTEXPR_OR_CONST constexpr
#define BR_STATIC_CONSTEXPR static BR_CONSTEXPR_OR_CONST
#define BR_STATIC_CONSTANT(TYPE, ASSIGNMENT) BR_STATIC_CONSTEXPR TYPE ASSIGNMENT
#define BR_STATIC_ASSERT(EXPRESSION, MESSAGE) static_assert(EXPRESSION, MESSAGE)
#define BR_TYPEDEF(DEFINE, AS_TYPE) typedef AS_TYPE DEFINE

#define BR_STRINGIZE(X) BR_DO_STRINGIZE(X)
#define BR_DO_STRINGIZE(X) #X

#define BR_JOIN(X, Y) BR_DO_JOIN(X, Y)
#define BR_DO_JOIN(X, Y) BR_DO_JOIN2(X,Y)
#define BR_DO_JOIN2(X, Y) X##Y

#define BR_EMPTY_ARG

#ifndef BR_FALLTHROUGH
#  define BR_FALLTHROUGH ((void)0)
#endif

#if __cplusplus >= 201402L
# define BR_CPP14
#endif

#if __cplusplus > 201103L
# define BR_AFTER_CPP11
#endif

#if __cplusplus >= 201103L
# define BR_CPP11
#endif

#if defined(BR_AFTER_CPP11)
#  define BR_CONSTEXPR_AFTER_CPP11 constexpr
#else
#  define BR_CONSTEXPR_AFTER_CPP11
#endif // defined