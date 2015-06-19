#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsTemplateInstance : BooleanFalse {};

template< template< typename ... > class TemplateClass, typename ... TArguments >
struct IsTemplateInstance< TemplateClass< TArguments ... > > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTemplateInstance : Boolean< Detail::TypeOperate::IsTemplateInstance< T > > {};

template< typename T >
struct NotTemplateInstance : BooleanNot< Detail::TypeOperate::IsTemplateInstance< T > > {};

} // namespace BR