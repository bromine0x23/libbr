/**
 * @file
 * @brief declare_* - 在 decltype 得非求值上下文中产生给定类型值
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/type_transform/add_rvalue_reference.hpp>
#include <libbr/type_transform/add_pointer.hpp>

namespace BR {

template< typename TValue >
auto declare_value() noexcept -> TValue;

template< typename TValue >
auto declare_rvalue() noexcept -> AddRValueReference<TValue>;

template< typename TValue >
auto declare_reference() noexcept -> AddLValueReference<TValue>;

template< typename TValue >
auto declare_pointer() noexcept -> AddPointer<TValue>;

} // namespace BR

