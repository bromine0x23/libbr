#pragma once

#include <libbr/config.hpp>

#if defined(BR_MSVC)

#include <libbr/type_operate/is_const.hpp>
#include <libbr/type_operate/is_reference.hpp>
#include <libbr/type_operate/is_volatile.hpp>

#  define BR_IS_ABSTRACT(T) __is_abstract(T)
#  define BR_IS_BASE_OF(T0, T1) __is_base_of(T0, T1)
#  define BR_IS_CLASS(T) __is_class(T)
#  define BR_IS_CONSTRUCTIBLE __is_constructible
#  define BR_IS_CONVERTIBLE(T0, T1) (__is_convertible_to(T0, T1) && !__is_abstract(T1))
#  define BR_IS_EMPTY(T) __is_empty(T)
#  define BR_IS_ENUM(T) __is_enum(T)
#  define BR_IS_POD(T) __is_pod(T)
#  define BR_IS_POLYMORPHIC(T) __is_polymorphic(T)
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

#  include <libbr/type_operate/is_same.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_volatile.hpp>

#  if __has_feature(is_abstract)
#    define BR_IS_ABSTRACT(T) __is_abstract(T)
#  endif
#  if __has_feature(is_base_of)
#    define BR_IS_BASE_OF(T0, T1) __is_base_of(T0,T1)
#  endif
#  if __has_feature(is_class)
#    define BR_IS_CLASS(T) __is_class(T)
#  endif
#  if __has_feature(is_convertible_to)
#    define BR_IS_CONVERTIBLE(T0, T1) __is_convertible_to(T0,T1)
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

#elif defined(BR_GCC) && (BR_GCC_VER >= 403)

#  include <libbr/type_operate/is_const.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_volatile.hpp>

#  define BR_IS_ABSTRACT(T) __is_abstract(T)
#  define BR_IS_BASE_OF(T0, T1) __is_base_of(T0, T1)
#  define BR_IS_CLASS(T) __is_class(T)
#  define BR_IS_EMPTY(T) __is_empty(T)
#  define BR_IS_ENUM(T) __is_enum(T)
#  define BR_IS_POD(T) __is_pod(T)
#  define BR_IS_POLYMORPHIC(T) __is_polymorphic(T)
#  define BR_IS_UNION(T) __is_union(T)

#  define BR_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T) __has_trivial_constructor(T)
#  define BR_HAS_TRIVIAL_COPY_CONSTRUCTOR(T) (__has_trivial_copy(T) && ::BR::BooleanAnd< ::BR::NotReference<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_TRIVIAL_COPY_ASSIGNMENT(T) (__has_trivial_assign(T) && ::BR::BooleanAnd< ::BR::NotConst<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#  define BR_HAS_NOTHROW_DEFAULT_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#  define BR_HAS_NOTHROW_COPY_CONSTRUCTOR(T) (__has_nothrow_copy(T) && ::BR::BooleanAnd< ::BR::NotReference<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_NOTHROW_COPY_ASSIGNMENT(T) (__has_nothrow_assign(T) && ::BR::BooleanAnd< ::BR::NotConst<T>, ::BR::NotVolatile<T> >::value)
#  define BR_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#  if BR_GCC_VER >= 407
#    define BR_IS_FINAL(T) __is_final(T)
#  endif

#  define BR_HAS_INTRINSICS

#endif
