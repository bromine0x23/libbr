#include "test.hpp"

#include <libbr/type_traits/has_trivial_move_assignment.hpp>

using namespace BR;

TEST(TypeTraits, HasTrivialMoveAssignment) {
	HAS_TRAITS_CHECK(false, TrivialMoveAssignment, trivial_move_assignment, void);
}