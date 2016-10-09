#include "test.hpp"

#include <libbr/type_traits/is_trivially_assignable.hpp>

using namespace BR;

TEST(TypeTraits, IsTriviallyAssignable) {
	IS_TRAITS_CHECK(false, TriviallyAssignable, trivially_assignable, void, void);
}