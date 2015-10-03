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
 * @see BR_IS_CLASS
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

#elif defined(BR_MSVC)

#include <libbr/type_traits/is_const.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_volatile.hpp>

#  define BR_IS_ABSTRACT(T) __is_abstract(T)
#  define BR_IS_BASE_OF(T0, T1) __is_base_of(T0, T1)
#  define BR_IS_CLASS(T) __is_class(T)
#  define BR_IS_CONSTRUCTIBLE __is_constructible
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

#  define BR_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T) __has_trivial_constructor(T)
#  define BR_HAS_TRIVIAL_COPY_CONSTRUCTOR(T) (__has_trivial_copy(T)|| ::BR::BooleanAnd< ::BR::NotVolatile<T> >::value)
#  define BR_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) (__has_trivial_move_constructor(T) && ::BR::BooleanAnd< ::BR::NotVolatile<T>, ::BR::NotReference<T> >::value)
#  define BR_HAS_TRIVIAL_COPY_ASSIGNMENT(T) (__has_trivial_assign(T) || ::BR::BooleanAnd< ::BR::NotConst<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_TRIVIAL_MOVE_ASSIGNMENT(T) (__has_trivial_move_assign(T) && ::BR::BooleanAnd< ::BR::NotConst<T>, ::BR::NotVolatile<T>, ::BR::NotReference<T> >::value)
#  define BR_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#  define BR_HAS_NOTHROW_COPY_CONSTRUCTOR(T) (__has_nothrow_copy(T) || BR_HAS_TRIVIAL_COPY_CONSTRUCTOR(T))
#  define BR_HAS_NOTHROW_DEFAULT_CONSTRUCTOR(T) (__has_nothrow_constructor(T) || BR_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T))
#  define BR_HAS_NOTHROW_COPY_ASSIGNMENT(T) (__has_nothrow_assign(T) || BR_HAS_TRIVIAL_COPY_ASSIGNMENT(T))
#  define BR_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#  define BR_HAS_INTRINSICS

#elif defined(BR_CLANG) && defined(__has_feature)

#  include <libbr/type_traits/is_same.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_volatile.hpp>

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
#  if __has_feature(is_pod)
#    define BR_IS_POD(T) __is_pod(T)
#  endif
#  if __has_feature(is_polymorphic)
#    define BR_IS_POLYMORPHIC(T) __is_polymorphic(T)
#  endif
#  if __has_feature(is_union)
#    define BR_IS_UNION(T) __is_union(T)
#  endif

#  if __has_feature(has_trivial_constructor)
#    define BR_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T) __has_trivial_constructor(T)
#  endif
#  if __has_feature(has_trivial_copy)
#    define BR_HAS_TRIVIAL_COPY_CONSTRUCTOR(T) (__has_trivial_copy(T) && ::BR::BooleanAnd< ::BR::NotReference<T>, ::BR::NotVolatile<T> >::value)
#  endif
#  if __has_feature(has_trivial_move_constructor)
#    define BR_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) __has_trivial_move_constructor(T)
#  endif
#  if __has_feature(__has_trivial_assign)
#    define BR_HAS_TRIVIAL_COPY_ASSIGNMENT(T) (__has_trivial_assign(T) && ::BR::NotVolatile<T>::value)
#  endif
#  if __has_feature(has_trivial_move_assign)
#    define BR_HAS_TRIVIAL_MOVE_ASSIGNMENT(T) __has_trivial_move_assign(T)
#  endif
#  if __has_feature(has_trivial_destructor)
#    define BR_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#  endif
#  if __has_feature(has_nothrow_constructor)
#    define BR_HAS_NOTHROW_DEFAULT_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#  endif
#  if __has_feature(has_nothrow_copy)
#    define BR_HAS_NOTHROW_COPY_CONSTRUCTOR(T) (__has_nothrow_copy(T) && ::BR::BooleanAnd< ::BR::NotReference<T>, ::BR::NotVolatile<T> >::value)
#  endif
#  if __has_feature(has_nothrow_assign)
#    define BR_HAS_NOTHROW_COPY_ASSIGNMENT(T) (__has_nothrow_assign(T) && ::BR::NotVolatile<T>::value)
#  endif
#  if __has_feature(has_virtual_destructor)
#    define BR_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#  endif

#  define BR_HAS_INTRINSICS

#elif defined(BR_GCC)

#  include <libbr/type_traits/is_const.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_volatile.hpp>

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

#  define BR_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T) __has_trivial_constructor(T)
#  define BR_HAS_TRIVIAL_COPY_CONSTRUCTOR(T) (__has_trivial_copy(T) && ::BR::BooleanAnd< ::BR::NotReference<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_TRIVIAL_COPY_ASSIGNMENT(T) (__has_trivial_assign(T) && ::BR::BooleanAnd< ::BR::NotConst<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#  define BR_HAS_NOTHROW_DEFAULT_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#  define BR_HAS_NOTHROW_COPY_CONSTRUCTOR(T) (__has_nothrow_copy(T) && ::BR::BooleanAnd< ::BR::NotReference<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_NOTHROW_COPY_ASSIGNMENT(T) (__has_nothrow_assign(T) && ::BR::BooleanAnd< ::BR::NotConst<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#  define BR_HAS_INTRINSICS

#endif
