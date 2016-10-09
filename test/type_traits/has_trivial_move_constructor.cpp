#include "test.hpp"

#include <libbr/type_traits/has_trivial_move_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasTrivialMoveConstructor) {
	HAS_TRAITS_CHECK(false, TrivialMoveConstructor, trivial_move_constructor, void);
}