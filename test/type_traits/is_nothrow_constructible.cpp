#include "test.hpp"

#include <libbr/type_traits/is_nothrow_constructible.hpp>

using namespace BR;

TEST(TypeTraits, IsNothrowConstructible) {
	IS_TRAITS_CHECK(false, NothrowConstructible, nothrow_constructible, void);
}