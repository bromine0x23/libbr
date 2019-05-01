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

// 类型类别特性
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_lvalue_reference.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/is_null_pointer.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_rvalue_reference.hpp>
#include <libbr/type_traits/is_void.hpp>

// 类型属性特性
#include <libbr/type_traits/is_const.hpp>
#include <libbr/type_traits/is_volatile.hpp>

// 类型关系特性
#include <libbr/type_traits/is_same.hpp>