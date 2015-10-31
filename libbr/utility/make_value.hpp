#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/add_pointer.hpp>

namespace BR {

template< typename TValue >
auto make_value() noexcept -> TValue;

template< typename TValue >
auto make_rvalue() noexcept -> AddRValueReference<TValue>;

template< typename TValue >
auto make_reference() noexcept -> AddLValueReference<TValue>;

template< typename TValue >
auto make_pointer() noexcept -> AddPointer<TValue>;

} // namespace BR

