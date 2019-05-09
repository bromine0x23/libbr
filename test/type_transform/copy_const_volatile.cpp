#include "test.hpp"

#include <libbr/type_transform/copy_const_volatile.hpp>

using namespace BR;

TEST(TypeTransform, CopyConstVolatile) {
	TRANSFORM_CHECK(CopyConstVolatile, double               , int               , double)
	TRANSFORM_CHECK(CopyConstVolatile, double const         , int const         , double)
	TRANSFORM_CHECK(CopyConstVolatile, double       volatile, int       volatile, double)
	TRANSFORM_CHECK(CopyConstVolatile, double const volatile, int const volatile, double)
}

