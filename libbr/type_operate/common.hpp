#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/decay.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {
namespace TypeOperate {

template< typename ... Tn >
struct TypeCommon;

template< typename ... Tn >
using Common = TypeUnwrap< TypeCommon< Tn ... > >;

template< typename T >
struct TypeCommon< T > : TypeWrapper< Decay< T > > {
	static_assert(sizeof(T) > 0, "Type must be complete.");
};

template< typename T0, typename T1 >
struct TypeCommon< T0, T1 > : TypeWrapper<
	Decay< decltype(make_rvalue< bool >() ? make_rvalue< T0 >() : make_rvalue< T1 >()) >
> {
	static_assert(sizeof(T0) > 0, "Type must be complete.");
	static_assert(sizeof(T1) > 0, "Type must be complete.");
};

template < typename T0, typename T1, typename ... Tn >
struct TypeCommon< T0, T1, Tn ... > : TypeWrapper< Common< Common< T0, T1 >, Tn ... > > {};

} // namespace TypeOperate
} // namespace BR

