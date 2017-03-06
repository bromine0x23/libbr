#include "../test.hpp"
#include <libbr/container/fixed_array.hpp>

#include <libbr/type_traits/is_standard_layout.hpp>
#include <libbr/type_traits/is_trivial.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::FixedArray< int, 10 >;
#endif

static_assert(IsStandardLayout< FixedArray< int, 10 > >{}, "FixedArray should be standard layout");
static_assert(IsTrivial< FixedArray< int, 10 > >{}, "FixedArray should be trivial");