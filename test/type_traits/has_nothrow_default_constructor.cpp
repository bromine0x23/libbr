#include "test.hpp"

#include <libbr/type_traits/has_nothrow_default_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasNothrowDefaultConstructor) {
	HAS_TRAITS_CHECK(false, NothrowDefaultConstructor, nothrow_default_constructor, void);

	HAS_TRAITS_CHECK(true, NothrowDefaultConstructor, nothrow_default_constructor, int);
	HAS_TRAITS_CHECK(true, NothrowDefaultConstructor, nothrow_default_constructor, int *);
	HAS_TRAITS_CHECK(true, NothrowDefaultConstructor, nothrow_default_constructor, int[2]);
	HAS_TRAITS_CHECK(true, NothrowDefaultConstructor, nothrow_default_constructor, Class);
}