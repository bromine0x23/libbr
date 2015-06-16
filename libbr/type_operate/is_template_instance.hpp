#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsTemplateInstance : BooleanFalse {};

template< template< typename ... > class TemplateClass, typename ... TArguments >
struct IsTemplateInstance< TemplateClass< TArguments ... > > : BooleanTrue {};

} // namespace Detail

template< typename T >
struct IsTemplateInstance : Boolean< Detail::IsTemplateInstance< T > > {};

template< typename T >
struct NotTemplateInstance : BooleanNot< Detail::IsTemplateInstance< T > > {};

} // namespace TypeOperate
} // namespace BR