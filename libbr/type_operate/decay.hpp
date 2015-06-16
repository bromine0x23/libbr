#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/add_pointer.hpp>
#include <libbr/type_operate/is_array.hpp>
#include <libbr/type_operate/is_function.hpp>
#include <libbr/type_operate/remove_extent.hpp>
#include <libbr/type_operate/remove_reference.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using TypeDecayBasic = Conditional<
	IsArray< T >,
	AddPointer< RemoveExtent< T > >,
	Conditional<
		IsFunction< T >,
		AddPointer< T >,
		TypeWrapper< T >
	>
>;

template< typename T >
using TypeDecay = TypeDecayBasic< RemoveReference< T > >;

};

template< typename T >
struct TypeDecay : TypeRewrap< Detail::TypeDecay< T > > {};

template< typename T >
using Decay = TypeUnwrap< TypeDecay< T > >;

} // namespace TypeOperate
} // namespace BR
