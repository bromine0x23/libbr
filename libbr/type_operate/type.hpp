#pragma once

#include <libbr/config.hpp>

namespace BR {

struct BasicTypeWrapper {};

template< typename T >
struct TypeWrapper : BasicTypeWrapper {
	using Type = T;
};

template< typename T >
using TypeUnwrap = typename T::Type;

template< typename T >
using TypeRewrap = TypeWrapper< TypeUnwrap< T > >;

template< typename ... T >
struct Types {};

} // namespace BR