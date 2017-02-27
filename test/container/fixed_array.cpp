#include "../test.hpp"
#include <libbr/container/fixed_array.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::FixedArray< int, 10 >;
#endif