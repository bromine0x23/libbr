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
#include <libbr/type_transform/remove_const.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/type_transform/remove_volatile.hpp>

#include <libbr/type_transform/remove_reference.hpp>