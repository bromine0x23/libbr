/**
 * @file
 * @brief GenericallyTotallyOrdered
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/_/empty.hpp>
#include <libbr/operators/generically_equivalent.hpp>
#include <libbr/operators/generically_partially_ordered.hpp>

namespace BR {

inline namespace Operators {

template< typename T, template<typename...> class Template, typename TBase = _::Operators::Empty<T> >
struct GenericallyTotallyOrdered : public GenericallyPartiallyOrdered< T, Template, GenericallyEquivalent< T, Template, TBase > > {};

} // namespace Operators

} // namespace BR

