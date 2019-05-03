#include "test.hpp"

#include <libbr/type_traits/has_move_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasMoveConstructor) {
	HAS_TRAITS_CHECK(false, MoveConstructor, move_constructor, void);
}