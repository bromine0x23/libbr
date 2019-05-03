#include "test.hpp"

#include <libbr/type_traits/has_nothrow_move_constructor.hpp>

using namespace BR;

TEST(TypeTraits, HasNothrowMoveConstructor) {
	HAS_TRAITS_CHECK(false, NothrowMoveConstructor, nothrow_move_constructor, void);
}