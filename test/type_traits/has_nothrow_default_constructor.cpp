#include "test.hpp"

#include <libbr/type_traits/has_nothrow_default_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasNothrowDefaultConstructor) {
	HAS_TRAITS_CHECK(false, NothrowDefaultConstructor, nothrow_default_constructor, void);
}