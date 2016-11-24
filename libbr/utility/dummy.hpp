/**
 * @file
 * @brief Dummy
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

/**
 * @brief TypeDummy
 */
template< typename... >
struct TypeDummy;

/**
 * @brief Dummy
 */
template< typename... Tn >
using Dummy = TypeUnwrap< TypeDummy<Tn...> >;



template< typename... >
struct TypeDummy : public TypeWrapper<void> {};

} // namespace BR