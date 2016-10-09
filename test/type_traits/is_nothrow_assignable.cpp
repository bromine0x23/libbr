#include "test.hpp"

#include <libbr/type_traits/is_nothrow_assignable.hpp>

using namespace BR;

TEST(TypeTraits, IsNothrowAssignable) {
	IS_TRAITS_CHECK(false, NothrowAssignable, nothrow_assignable, void, void);
}