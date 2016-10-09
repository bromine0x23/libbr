#include "test.hpp"

#include <libbr/type_traits/is_trivially_constructible.hpp>

using namespace BR;

TEST(TypeTraits, IsTriviallyConstructible) {
	IS_TRAITS_CHECK(false, TriviallyConstructible, trivially_constructible, void);
}