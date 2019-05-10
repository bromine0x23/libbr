/**
 * @file
 * @brief 类型转化模块
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 类型转化
 */
inline namespace TypeTransform {
} // namespace TypeTransform

} // namespace BR


#include <libbr/type_transform/add_const.hpp>
#include <libbr/type_transform/add_const_volatile.hpp>
#include <libbr/type_transform/add_volatile.hpp>
#include <libbr/type_transform/remove_const.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/type_transform/remove_volatile.hpp>
#include <libbr/type_transform/copy_const_volatile.hpp>

#include <libbr/type_transform/add_pointer.hpp>
#include <libbr/type_transform/remove_pointer.hpp>

#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/type_transform/add_rvalue_reference.hpp>
#include <libbr/type_transform/remove_reference.hpp>

#include <libbr/type_transform/remove_all_extents.hpp>
#include <libbr/type_transform/remove_extent.hpp>

#include <libbr/type_transform/common.hpp>
#include <libbr/type_transform/decay.hpp>

#include <libbr/type_transform/make_signed.hpp>
#include <libbr/type_transform/make_unsigned.hpp>