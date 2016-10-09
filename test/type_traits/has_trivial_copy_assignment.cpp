#include "test.hpp"

#include <libbr/type_traits/has_trivial_copy_assignment.hpp>

using namespace BR;

TEST(TypeTraits, HasTrivialCopyAssignment) {
	HAS_TRAITS_CHECK(false, TrivialCopyAssignment, trivial_copy_assignment, void);
}