#include "test.hpp"

#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasNothrowCopyConstructor) {
	HAS_TRAITS_CHECK(false, NothrowCopyConstructor, nothrow_copy_constructor, void);
}