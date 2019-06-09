/**
 * @file
 * @brief TotallyOrdered
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/_/empty.hpp>
#include <libbr/operators/equivalent.hpp>
#include <libbr/operators/partially_ordered.hpp>

namespace BR {

inline namespace Operators {

template< typename TX, typename TY = TX, typename TBase = _::Operators::Empty<TX, TY> >
struct TotallyOrdered : public PartiallyOrdered< TX, TY, Equivalent< TX, TY, TBase > > {};

} // namespace Operators

} // namespace BR

