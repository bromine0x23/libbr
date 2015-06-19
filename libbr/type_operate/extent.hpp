#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/integer.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

template< typename T, Size I = 0 >
struct Extent : IntegerConstant< Size, 0 > {};

template< typename T, Size I >
struct Extent< T [], I > : IntegerConstant< Size, Extent< RemoveConstVolatile< T >, I - 1 >::value > {};

template< typename T >
struct Extent< T [], 0 > : IntegerConstant< Size,  0 > {};

template< typename T, Size S, Size I >
struct Extent< T [S], I > : IntegerConstant< Size, Extent< RemoveConstVolatile< T >, I - 1 >::value > {};

template< typename T, Size S >
struct Extent< T [S], 0 > : IntegerConstant< Size, S > {};

} // namespace BR
