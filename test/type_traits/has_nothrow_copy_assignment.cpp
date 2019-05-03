#include "test.hpp"

#include <libbr/type_traits/has_nothrow_copy_assignment.hpp>

using namespace BR;

TEST(TypeTraits, HasNothrowCopyAssignment) {
	HAS_TRAITS_CHECK(false, NothrowCopyAssignment, nothrow_copy_assignment, void);
}