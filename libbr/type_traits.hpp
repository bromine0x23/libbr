/**
 * @file
 * @brief 类型特性模块
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 类型特性
 */
inline namespace TypeTraits {
} // namespace TypeTraits

} // namespace BR

// 类型基本类别
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_class.hpp>
#include <libbr/type_traits/is_floating_point.hpp>
#include <libbr/type_traits/is_function.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/is_member_function_pointer.hpp>
#include <libbr/type_traits/is_member_object_pointer.hpp>
#include <libbr/type_traits/is_null_pointer.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/is_rvalue_reference.hpp>
#include <libbr/type_traits/is_union.hpp>
#include <libbr/type_traits/is_void.hpp>

// 类型复合类别
#include <libbr/type_traits/is_arithmetic.hpp>
#include <libbr/type_traits/is_fundamental.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/is_reference.hpp>

// 类型属性
#include <libbr/type_traits/extent.hpp>
#include <libbr/type_traits/is_const.hpp>
#include <libbr/type_traits/is_volatile.hpp>
#include <libbr/type_traits/rank.hpp>

// 类型关系
#include <libbr/type_traits/is_same.hpp>