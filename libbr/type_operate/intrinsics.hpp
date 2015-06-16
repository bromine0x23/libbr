#pragma once

#include <libbr/config.hpp>

#if defined(BR_MSVC)

#include <libbr/type_operate/is_const.hpp>
#include <libbr/type_operate/is_pod.hpp>
#include <libbr/type_operate/is_reference.hpp>
#include <libbr/type_operate/is_volatile.hpp>

#  define BR_TYPE_OPERATE_IS_ABSTRACT(T) __is_abstract(T)
#  define BR_TYPE_OPERATE_IS_BASE_OF(T0, T1) __is_base_of(T0, T1)
#  define BR_TYPE_OPERATE_IS_CLASS(T) __is_class(T)
#  define BR_TYPE_OPERATE_IS_CONSTRUCTIBLE __is_constructible
#  define BR_TYPE_OPERATE_IS_CONVERTIBLE(T0, T1) (__is_convertible_to(T0, T1) && !__is_abstract(T1))
#  define BR_TYPE_OPERATE_IS_EMPTY(T) __is_empty(T)
#  define BR_TYPE_OPERATE_IS_ENUM(T) __is_enum(T)
#  define BR_TYPE_OPERATE_IS_POD(T) __is_pod(T)
#  define BR_TYPE_OPERATE_IS_POLYMORPHIC(T) __is_polymorphic(T)
#  define BR_TYPE_OPERATE_IS_UNION(T) __is_union(T)

#  define BR_TYPE_OPERATE_HAS_NOTHROW_COPY_ASSIGNMENT(T) (__has_nothrow_assign(T) || BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_ASSIGNMENT(T))
#  define BR_TYPE_OPERATE_HAS_NOTHROW_COPY_CONSTRUCTOR(T) (__has_nothrow_copy(T) || BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_CONSTRUCTOR(T))
#  define BR_TYPE_OPERATE_HAS_NOTHROW_DEFAULT_CONSTRUCTOR(T) (__has_nothrow_constructor(T) || BR_TYPE_OPERATE_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T))
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_ASSIGNMENT(T) (__has_trivial_assign(T) || ::BR::TypeOperate::BooleanAnd< ::BR::TypeOperate::IsPOD<T>, ::BR::TypeOperate::NotConst<T>, ::BR::TypeOperate::NotVolatile<T> >::value)
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_CONSTRUCTOR(T) (__has_trivial_copy(T)|| ::BR::TypeOperate::BooleanAnd< ::BR::TypeOperate::IsPOD<T>::value, ::BR::TypeOperate::NotVolatile<T> >::value))
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T) __has_trivial_constructor(T)
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T) || ::BR::TypeOperate::IsPOD<T>::value)
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_ASSIGNMENT(T) (__has_trivial_move_assign(T) || ::BR::TypeOperate::IsPOD<T>::value) && ::BR::TypeOperate::BooleanAnd< ::BR::TypeOperate::NotConst<T>, ::BR::TypeOperate::NotVolatile<T>, ::BR::TypeOperate::NotReference<T> >::value)
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) ((__has_trivial_move_constructor(T) || ::BR::TypeOperate::IsPOD<T>::value) && ::BR::TypeOperate::BooleanAnd< ::BR::TypeOperate::NotVolatile<T>, ::BR::TypeOperate::NotReference<T> >::value)
#  define BR_TYPE_OPERATE_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#  define BR_TYPE_OPERATE_HAS_INTRINSICS

#elif defined(BR_GCC) && (BR_GCC_VER >= 403)

#  include <libbr/type_operate/is_const.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_volatile.hpp>

#  define BR_TYPE_OPERATE_IS_ABSTRACT(T) __is_abstract(T)
#  define BR_TYPE_OPERATE_IS_BASE_OF(T0, T1) __is_base_of(T0, T1)
#  define BR_TYPE_OPERATE_IS_CLASS(T) __is_class(T)
#  define BR_TYPE_OPERATE_IS_EMPTY(T) __is_empty(T)
#  define BR_TYPE_OPERATE_IS_ENUM(T) __is_enum(T)
#  define BR_TYPE_OPERATE_IS_POD(T) __is_pod(T)
#  define BR_TYPE_OPERATE_IS_POLYMORPHIC(T) __is_polymorphic(T)
#  define BR_TYPE_OPERATE_IS_UNION(T) __is_union(T)

#  define BR_TYPE_OPERATE_HAS_NOTHROW_COPY_ASSIGNMENT(T) (__has_nothrow_assign(T) && ::BR::TypeOperate::BooleanAnd< ::BR::TypeOperate::NotConst<T>, ::BR::TypeOperate::NotVolatile<T> >::value)
#  define BR_TYPE_OPERATE_HAS_NOTHROW_COPY_CONSTRUCTOR(T) (__has_nothrow_copy(T) && ::BR::TypeOperate::BooleanAnd< ::BR::TypeOperate::NotReference<T>, ::BR::TypeOperate::NotVolatile<T> >::value)
#  define BR_TYPE_OPERATE_HAS_NOTHROW_DEFAULT_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_ASSIGNMENT(T) (__has_trivial_assign(T) && ::BR::TypeOperate::BooleanAnd< ::BR::TypeOperate::NotConst<T>, ::BR::TypeOperate::NotVolatile<T> >::value)
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_CONSTRUCTOR(T) (__has_trivial_copy(T) && ::BR::TypeOperate::BooleanAnd< ::BR::TypeOperate::NotReference<T>, ::BR::TypeOperate::NotVolatile<T> >::value)
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T) __has_trivial_constructor(T)
#  define BR_TYPE_OPERATE_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#  define BR_TYPE_OPERATE_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#  define BR_TYPE_OPERATE_HAS_INTRINSICS

#endif
