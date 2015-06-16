#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace TypeOperate {

template< bool condition, typename T = void >
struct TypeEnableIfByValue {};

template< bool condition, typename T = void >
struct TypeDisableIfValue {};

template< typename T >
struct TypeEnableIfByValue< true, T > : TypeWrapper< T > {};

template< typename T >
struct TypeDisableIfValue< false, T > : TypeWrapper< T > {};

template< typename TCondition, typename T = void >
using TypeEnableIf = TypeEnableIfByValue< TCondition::value, T >;

template< typename TCondition, typename T = void >
using TypeDisableIf = TypeDisableIfValue< TCondition::value, T >;

template< bool condition, typename T = void >
using EnableIfByValue = TypeUnwrap< TypeEnableIfByValue< condition, T > >;

template< bool condition, typename T = void >
using DisableIfValue = TypeUnwrap< TypeDisableIfValue< condition, T > >;

template< typename TCondition, typename T = void >
using EnableIf = TypeUnwrap< TypeEnableIf< TCondition, T > >;

template< typename TCondition, typename T = void >
using DisableIf = TypeUnwrap< TypeDisableIf< TCondition, T > >;

} // namespace TypeOperate
} // namespace BR