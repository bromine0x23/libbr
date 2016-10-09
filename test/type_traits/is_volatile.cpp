#include "test.hpp"

#include <libbr/type_traits/is_volatile.hpp>

using namespace BR;

TEST(TypeTraits, IsVolatile) {
	IS_TRAITS_CHECK(false, Volatile, volatile, void);
}