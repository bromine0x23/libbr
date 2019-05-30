#include "test.hpp"

#include <libbr/type_traits/is_swappable.hpp>

using namespace BR;

TEST(TypeTraits, IsSwappable) {
	IS_TRAITS_CHECK(true, Swappable, swappable, int);
	IS_TRAITS_CHECK(true, Swappable, swappable, int[5]);
	IS_TRAITS_CHECK(true, Swappable, swappable, Class);
	IS_TRAITS_CHECK(true, Swappable, swappable, Class[5]);
	IS_TRAITS_CHECK(true, Swappable, swappable, Struct);
	IS_TRAITS_CHECK(true, Swappable, swappable, Struct[5]);
}