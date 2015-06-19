#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsIntegerBasic : BooleanFalse {};

template<> struct IsIntegerBasic<   signed char      > : BooleanTrue {};
template<> struct IsIntegerBasic< unsigned char      > : BooleanTrue {};
template<> struct IsIntegerBasic<   signed short     > : BooleanTrue {};
template<> struct IsIntegerBasic< unsigned short     > : BooleanTrue {};
template<> struct IsIntegerBasic<   signed int       > : BooleanTrue {};
template<> struct IsIntegerBasic< unsigned int       > : BooleanTrue {};
template<> struct IsIntegerBasic<   signed long      > : BooleanTrue {};
template<> struct IsIntegerBasic< unsigned long      > : BooleanTrue {};
template<> struct IsIntegerBasic<   signed long long > : BooleanTrue {};
template<> struct IsIntegerBasic< unsigned long long > : BooleanTrue {};

template<> struct IsIntegerBasic< bool     > : BooleanTrue {};
template<> struct IsIntegerBasic< char     > : BooleanTrue {};
template<> struct IsIntegerBasic< wchar_t  > : BooleanTrue {};
template<> struct IsIntegerBasic< char16_t > : BooleanTrue {};
template<> struct IsIntegerBasic< char32_t > : BooleanTrue {};

#if defined(BR_HAS_INT128)
template<> struct IsIntegerBasic< SInt128 > : BooleanTrue {};
template<> struct IsIntegerBasic< UInt128 > : BooleanTrue {};
#endif // BR_HAS_INT128

template< typename T >
struct IsInteger : IsIntegerBasic< RemoveConstVolatile< T > > {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsInteger : Boolean< Detail::TypeOperate::IsInteger< T > > {};

template< typename T >
struct NotInteger : BooleanNot< Detail::TypeOperate::IsInteger< T > > {};

} // namespace BR