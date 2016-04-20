#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>

namespace BR {

template< typename ... Tn >
struct DummyFalse : BooleanConstant< sizeof...(Tn) >= 0 > {
};

} // namespace BR