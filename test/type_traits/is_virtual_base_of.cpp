#include "test.hpp"

#include <libbr/type_traits/is_virtual_base_of.hpp>

using namespace BR;

TEST(TypeTraits, IsVirtualBaseOf) {
	IS_TRAITS_CHECK(false, VirtualBaseOf, virtual_base_of, void, void);
}