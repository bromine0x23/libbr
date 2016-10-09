#include "test.hpp"

#include <libbr/type_traits/is_scalar.hpp>

using namespace BR;

TEST(TypeTraits, IsScalar) {
	IS_TRAITS_CHECK(false, Scalar, scalar, void);
}