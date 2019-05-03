#include "test.hpp"

#include <libbr/type_traits/has_nothrow_move_assignment.hpp>

using namespace BR;

TEST(TypeTraits, HasNothrowMoveAssignment) {
	HAS_TRAITS_CHECK(false, NothrowMoveAssignment, nothrow_move_assignment, void);
}