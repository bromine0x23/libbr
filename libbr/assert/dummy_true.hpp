/**
 * @file
 * @brief DummyFalse
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

template< typename T, typename... Tn >
struct DummyTrue : IsSame< T, T > {};

} // namespace BR