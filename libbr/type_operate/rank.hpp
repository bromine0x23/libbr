#pragma once

#include <libbr/config.hpp>

#include <libbr/type_operate/integer.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
struct Rank : IntegerConstant< Size, 0 > {};

template< typename T >
struct Rank< T [] > : IntegerConstant< Size, Rank< RemoveConstVolatile< T > >::value + 1 > {};

template< typename T, Size S >
struct Rank< T [S] > : IntegerConstant< Size, Rank< RemoveConstVolatile< T > >::value + 1 > {};

} // namespace TypeOperate
} // namespace BR
