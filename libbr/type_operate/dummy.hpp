/**
 * @file
 * @brief Dummy
 * @author Bromine0x23
 * @since 2016/10/10
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename... >
struct TypeDummy;

template< typename... Tn >
using Dummy = TypeUnwrap< TypeDummy<Tn...> >;



template< typename... >
struct TypeDummy : public TypeWrapper<void> {};

} // namespace BR