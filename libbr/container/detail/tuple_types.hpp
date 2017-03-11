#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/types.hpp>

namespace BR {
namespace Detail {
namespace Container {

template< typename ... TTypes >
struct TupleTypes : public Types< TTypes ... > {};

} // namespace Container
} // namespace Detail
} // namespace BR
