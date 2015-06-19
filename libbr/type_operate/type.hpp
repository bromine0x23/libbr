#pragma once

#include <libbr/config.hpp>

namespace BR {

struct TypeWrapperBase {};

template< typename T >
struct TypeWrapper : TypeWrapperBase {
	using Type = T;
};

template< typename T >
using TypeUnwrap = typename T::Type;

template< typename T >
using TypeRewrap = TypeWrapper< TypeUnwrap< T > >;

template< typename ... T >
struct Types {};

} // namespace BR