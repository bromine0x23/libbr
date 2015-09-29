#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsRValueReference : BooleanFalse {};

template< typename T >
struct IsRValueReference<T &&> : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsRValueReference : Boolean< Detail::TypeOperate::IsRValueReference<T> > {};

template< typename T >
struct NotRValueReference : BooleanNot< Detail::TypeOperate::IsRValueReference<T> > {};

} // namespace BR