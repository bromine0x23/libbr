#include "test.hpp"

#include <libbr/type_traits/is_convertible.hpp>

using namespace BR;

TEST(TypeTraits, IsConvertible) {
	IS_TRAITS_CHECK(true, Convertible, convertible, void, void);
}