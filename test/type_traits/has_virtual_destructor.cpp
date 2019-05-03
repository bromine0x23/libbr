#include "test.hpp"

#include <libbr/type_traits/has_virtual_destructor.hpp>

using namespace BR;

TEST(TypeTraits, HasVirtualDestructor) {
	HAS_TRAITS_CHECK(false, VirtualDestructor, virtual_destructor, void);
}