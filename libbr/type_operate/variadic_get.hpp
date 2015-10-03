#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< Size I, typename ... T >
struct TypeVariadicGet;

template< Size I >
struct TypeVariadicGet<I> {
	static_assert(Conditional< BooleanFalse, IntegerConstant< Size, I >, BooleanFalse >::value, "Index out of range.");
};

template< typename THead, typename ... TTail >
struct TypeVariadicGet< 0, THead, TTail ... > : TypeWrapper<THead> {};

template< Size I, typename THead, typename ... TTail >
struct TypeVariadicGet< I, THead, TTail ... > : TypeVariadicGet< I - 1, TTail ... > {};

} // namespace TypeOperate
} // namespace Detail

template< Size I, typename ... T >
struct TypeVariadicGet : TypeRewrap< Detail::TypeOperate::TypeVariadicGet< I, T ... > > {};

template< Size I, typename ... T >
using VariadicGet = TypeUnwrap< TypeVariadicGet< I, T ... > >;

} // namespace BR

