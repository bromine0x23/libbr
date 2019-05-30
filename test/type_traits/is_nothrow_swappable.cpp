#include "test.hpp"

#include <libbr/type_traits/is_nothrow_swappable.hpp>

using namespace BR;

TEST(TypeTraits, IsNothrowSwappable) {
	IS_TRAITS_CHECK(true, NothrowSwappable, nothrow_swappable, int);
	IS_TRAITS_CHECK(true, NothrowSwappable, nothrow_swappable, int[5]);
	IS_TRAITS_CHECK(true, NothrowSwappable, nothrow_swappable, Class);
	IS_TRAITS_CHECK(true, NothrowSwappable, nothrow_swappable, Struct);
	IS_TRAITS_CHECK(true, NothrowSwappable, nothrow_swappable, Struct[5]);
}