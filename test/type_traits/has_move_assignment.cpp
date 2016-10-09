#include "test.hpp"

#include <libbr/type_traits/has_move_assignment.hpp>

using namespace BR;

TEST(TypeTraits, HasMoveAssignment) {
	HAS_TRAITS_CHECK(false, MoveAssignment, move_assignment, void);
}