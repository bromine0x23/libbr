#include "test.hpp"

#include <libbr/type_traits/has_nothrow_destructor.hpp>

using namespace BR;

TEST(TypeTraits, HasNothrowDestructor) {
	HAS_TRAITS_CHECK(false, NothrowDestructor, nothrow_destructor, void);

	HAS_TRAITS_CHECK(true, NothrowDestructor, nothrow_destructor, int);
	HAS_TRAITS_CHECK(true, NothrowDestructor, nothrow_destructor, int *);
	HAS_TRAITS_CHECK(true, NothrowDestructor, nothrow_destructor, int[5]);
}