#include "test.hpp"

#include <libbr/type_traits/has_nothrow_destructor.hpp>

using namespace BR;

TEST(TypeTraits, HasNothrowDestructor) {
	HAS_TRAITS_CHECK(false, NothrowDestructor, nothrow_destructor, void);
}