#include "test.hpp"

#include <libbr/type_traits/has_copy_assignment.hpp>

using namespace BR;

TEST(TypeTraits, HasCopyAssignment) {
	HAS_TRAITS_CHECK(false, CopyAssignment, copy_assignment, void);
}