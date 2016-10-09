#include "test.hpp"

#include <libbr/type_traits/is_union.hpp>

using namespace BR;

TEST(TypeTraits, IsUnion) {
	IS_TRAITS_CHECK(false, Union, union, void);
}