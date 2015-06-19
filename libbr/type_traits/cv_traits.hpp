#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_volatile.hpp>
#include <libbr/type_operate/add_const_volatile.hpp>
#include <libbr/type_operate/is_const.hpp>
#include <libbr/type_operate/is_volatile.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

template< typename T >
struct CVTraits {
	constexpr static auto is_const    = IsConst   < T >::value;
	constexpr static auto is_volatile = IsVolatile< T >::value;
	using Type   = RemoveConstVolatile< T >;
	using TypeC  = AddConst        < Type >;
	using TypeV  = AddVolatile     < Type >;
	using TypeCV = AddConstVolatile< Type >;
};

} // namespace BR
