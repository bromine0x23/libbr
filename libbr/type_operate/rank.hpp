#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct Rank : IntegerConstant< Size, 0 > {};

template< typename T >
struct Rank< T [] > : IntegerConstant< Size, Rank< RemoveConstVolatile< T > >::value + 1 > {};

template< typename T, Size S >
struct Rank< T [S] > : IntegerConstant< Size, Rank< RemoveConstVolatile< T > >::value + 1 > {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
using Rank = IntegerConstant< Size, Detail::TypeOperate::Rank<T>::value >;

} // namespace BR
