#include "test.hpp"

#include <libbr/type_traits/is_same.hpp>

using namespace BR;

TEST(TypeTraits, IsSame) {
	IS_TRAITS_CHECK(true, Same, same, void, void);
}