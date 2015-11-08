/**
 * @file Optional
 * @author Bromine0x23
 * @since 2015/11/7
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/has_trivial_destructor.hpp>

namespace BR {

namespace Detail {
namespace Utility {

template< typename T, bool = HasTrivialDestructor<T>::value >
class OptionalStorage;

template< typename T >
class OptionalStorage< T, true > {

};

template< typename T >
class OptionalStorage< T, false >;


} // namespace Utility
} // namespace Detail

template< typename T >
class Optional;



} // namespace BR