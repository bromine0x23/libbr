/**
 * @file
 * @brief 由编译期提供的检测特性的内部函数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

#if defined(BR_DOXYGEN)

/**
 * @brief 当且仅当 \em T 是抽象类(含有至少一个纯虚函数声明的类)时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_ABSTRACT(T)

/**
 * @brief 当且仅当 \em TBase 是 \em TDerived 的基类(忽略CV修饰符)时返回 \em true.
 * @pre 如果 <tt> BR_IS_CLASS(TBase)</tt> 和 <tt> BR_IS_CLASS(TDerived)</tt> 为真，则 \em TDerived 是完全类型
 */
#define BR_IS_BASE_OF(TBase, TDerived)

/**
 * @brief 当且仅当 \em T 是非联合的类类型(忽略CV修饰符)时返回 \em true.
 */
#define BR_IS_CLASS(T)

/**
 * @brief 当且仅当 \em TFrom 能被隐式装换为 \em TTo 时返回 \em true.
 * @pre \em TFrom 、 \em TTo 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_CONVERTIBLE(TFrom, TTo)

/**
 * @brief 当且仅当 \em T 是空的(除静态成员外的字段位宽为0、无虚函数、无虚基类、无非空基类，忽略CV修饰符)类类型时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_EMPTY(T)

/**
 * @brief 当且仅当 \em T 是枚举类型(忽略CV修饰符)时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_ENUM(T)

/**
 * @brief 当且仅当 \em T 是 \em final 类时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_FINAl(T)

/**
 * @brief 当且仅当 \em T 是 \em literal \em type 时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_LITERAL_TYPE(T)

/**
 * @brief 当且仅当 \em T 是POD(忽略CV修饰符)时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_POD(T)

/**
 * @brief 当且仅当 \em T 是多态类(声明或继承了至少一个虚函数的类)时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_POLYMORPHIC(T)

/**
 * @brief 当且仅当 \em T 满足 \em standard-layout 约束时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_STANDARD_LAYOUT(T)

/**
 * @brief 当且仅当 \em T 是 \em trivial 的时返回 \em true.
 * @pre \em T 是完全类型、数组或 \em void (允许带CV修饰符)
 */
#define BR_IS_TRIVIAL(T)

/**
 * @brief 当且仅当 \em T 是联合类型时返回 \em true.
 */
#define BR_IS_UNION(T)

/**
 * @brief 当且仅当 \em T 可以从参数 \em TArgs... 构造时返回 \em true.
 */
#define BR_IS_CONSTRUCTIBLE(T, TArgs...)

/**
 * @brief 当且仅当 \em T 可以从参数 \em TArgs... \em trivial 地构造时返回 \em true.
 */
#define BR_IS_TRIVIALLY_CONSTRUCTIBLE(T, TArgs...)

/**
 * @brief 当且仅当 \em T 可以从参数 \em TArgs... \em nothrow 地构造时返回 \em true.
 */
#define BR_IS_NOTHROW_CONSTRUCTIBLE(T, TArgs...)

/**
 * @brief 当且仅当 \em T 具有以 \em TArg 为参数的 \em trivial 赋值运算符时返回 \em true.
 */
#define BR_IS_TRIVIALLY_ASSIGNABLE(T, TArg)

/**
 * @brief 当且仅当 \em T 具有以 \em TArg 为参数的 \em nothrow 赋值运算符时返回 \em true.
 */
#define BR_IS_NOTHROW_ASSIGNABLE(T, TArg)

/**
 * @brief 当且仅当 \em T 具有析构函数时返回 \em true.
 */
#define BR_HAS_DESTRUCTOR(T)

/**
 * @brief 当且仅当 \em T 具有平凡的析构函数时返回 \em true.
 */
#define BR_HAS_TRIVIAL_DESTRUCTOR(T)

/**
 * @brief 当且仅当 \em T 具有虚析构函数时返回 \em true.
 */
#define BR_HAS_VIRTUAL_DESTRUCTOR(T)

#elif defined(BR_GCC)

#  define BR_IS_ABSTRACT(T) __is_abstract(T)
#  define BR_IS_BASE_OF(T0, T1) __is_base_of(T0, T1)
#  define BR_IS_CLASS(T) __is_class(T)
#  define BR_IS_EMPTY(T) __is_empty(T)
#  define BR_IS_ENUM(T) __is_enum(T)
#  define BR_IS_FINAL(T) __is_final(T)
#  define BR_IS_LITERAL_TYPE(T) __is_literal_type(T)
#  define BR_IS_POD(T) __is_pod(T)
#  define BR_IS_POLYMORPHIC(T) __is_polymorphic(T)
#  define BR_IS_STANDARD_LAYOUT(T) __is_standard_layout(T)
#  define BR_IS_TRIVIAL(T) __is_trivial(T)
#  define BR_IS_UNION(T) __is_union(T)

#  define BR_HAS_TRIVIAL_COPY_ASSIGNMENT(T) __has_trivial_assign(T)
#  define BR_HAS_TRIVIAL_COPY_CONSTURCTOR(T) __has_trivial_copy(T)
#  define BR_HAS_TRIVIAL_DEFAULT_CONSTURCTOR(T) __has_trivial_constructor(T)
#  define BR_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#  define BR_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#  define BR_HAS_INTRINSICS

#elif defined(BR_CLANG)

#if defined(__has_feature)

#  if __has_feature(is_abstract)
#    define BR_IS_ABSTRACT(T) __is_abstract(T)
#  endif
#  if __has_feature(is_base_of)
#    define BR_IS_BASE_OF(T0, T1) __is_base_of(T0, T1)
#  endif
#  if __has_feature(is_class)
#    define BR_IS_CLASS(T) __is_class(T)
#  endif
#  if __has_feature(is_convertible_to)
#    define BR_IS_CONVERTIBLE(T0, T1) __is_convertible_to(T0, T1)
#  endif
#  if __has_feature(is_empty)
#    define BR_IS_EMPTY(T) __is_empty(T)
#  endif
#  if __has_feature(is_enum)
#    define BR_IS_ENUM(T) __is_enum(T)
#  endif
#  if __has_feature(is_final)
#    define BR_IS_FINAL(T) __is_final(T)
#  endif
#  if __has_feature(__is_literal_type)
#    define BR_IS_LITERAL_TYPE(T) __is_literal_type(T)
#  endif
#  if __has_feature(is_pod)
#    define BR_IS_POD(T) __is_pod(T)
#  endif
#  if __has_feature(is_polymorphic)
#    define BR_IS_POLYMORPHIC(T) __is_polymorphic(T)
#  endif
#  if __has_feature(is_standard_layout)
#    define BR_IS_STANDARD_LAYOUT(T) __is_standard_layout(T)
#  endif
#  if __has_feature(is_trivial)
#    define BR_IS_TRIVIAL(T) __is_trivial(T)
#  endif
#  if __has_feature(is_union)
#    define BR_IS_UNION(T) __is_union(T)
#  endif

#  if __has_feature(is_constructible)
#    define BR_IS_CONSTRUCTIBLE(T, ...) __is_constructible(T, ##__VA_ARGS__)
#  endif
#  if __has_feature(is_trivially_constructible)
#    define BR_IS_TRIVIALLY_CONSTRUCTIBLE(T, ...) __is_trivially_constructible(T, ##__VA_ARGS__)
#  endif
#  if __has_feature(is_nothrow_constructible)
#    define BR_IS_NOTHROW_CONSTRUCTIBLE(T, ...) __is_nothrow_constructible(T, ##__VA_ARGS__)
#  endif
#  if __has_feature(is_trivially_assignable)
#    define BR_IS_TRIVIALLY_ASSIGNABLE(T0, T1) __is_trivially_assignable(T0, T1)
#  endif
#  if __has_feature(has_trivial_destructor)
#    define BR_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#  endif
#  if __has_feature(has_virtual_destructor)
#    define BR_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#  endif

#  define BR_HAS_INTRINSICS
#endif

#elif defined(BR_MSVC)

#  define BR_IS_ABSTRACT(T) __is_abstract(T)
#  define BR_IS_BASE_OF(T0, T1) __is_base_of(T0, T1)
#  define BR_IS_CLASS(T) __is_class(T)
#  define BR_IS_CONVERTIBLE(T0, T1) __is_convertible_to(T0, T1)
#  define BR_IS_EMPTY(T) __is_empty(T)
#  define BR_IS_ENUM(T) __is_enum(T)
#  define BR_IS_FINAl(T) __is_final(T)
#  define BR_IS_LITERAL_TYPE(T) __is_literal_type(T)
#  define BR_IS_POD(T) __is_pod(T)
#  define BR_IS_POLYMORPHIC(T) __is_polymorphic(T)
#  define BR_IS_STANDARD_LAYOUT(T) __is_standard_layout(T)
#  define BR_IS_TRIVIAL(T) __is_trivial(T)
#  define BR_IS_UNION(T) __is_union(T)

#  define BR_IS_CONSTRUCTIBLE __is_constructible
#  define BR_IS_TRIVIALLY_CONSTRUCTIBLE __is_trivially_constructible
#  define BR_IS_NOTHROW_CONSTRUCTIBLE __is_nothrow_constructible

#  define BR_IS_TRIVIALLY_ASSIGNABLE(T0, T1) __is_trivially_assignable(T0, T1)
#  define BR_IS_NOTHROW_ASSIGNABLE(T0, T1) __is_nothrow_assignable(T0, T1)

#  define BR_HAS_DESTRUCTOR(T) __is_destructible(T)
#  define BR_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#  define BR_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#  define BR_HAS_INTRINSICS

#endif
