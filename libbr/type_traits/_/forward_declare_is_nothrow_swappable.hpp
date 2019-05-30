#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace TypeTraits {

template< typename T >
struct IsNothrowSwappable;

template< typename T >
struct NotNothrowSwappable;

} // namespace TypeTraits
} // namespace BR

