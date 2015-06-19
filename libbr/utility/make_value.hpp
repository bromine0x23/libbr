#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/add_pointer.hpp>

namespace BR {

template< typename TValue >
TValue make_value() noexcept;

template< typename TValue >
AddRValueReference< TValue > make_rvalue() noexcept;

template< typename TValue >
AddLValueReference< TValue > make_reference() noexcept;

template< typename TValue >
AddPointer< TValue > make_pointer() noexcept;

} // namespace BR

