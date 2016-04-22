#include "test.hpp"

#include<libbr/type_traits/extent.hpp>

using namespace BR;

TEST(TypeTraits, Extent) {
	INTEGRAL_CHECK(0, Extent, int);
	INTEGRAL_CHECK(0, Extent, int[]);
	INTEGRAL_CHECK(0, Extent, int[][3]);
	INTEGRAL_CHECK(2, Extent, int[2][3]);
	INTEGRAL_CHECK(2, Extent, int[2][3][5]);
	INTEGRAL_CHECK(0, Extent, int(*)[2][3]);
	INTEGRAL_CHECK(0, Extent, int(&)[2][3]);
	INTEGRAL_CHECK(0, Extent, int(&&)[2][3]);

	INTEGRAL_CHECK(0, Extent, int, 1);
	INTEGRAL_CHECK(0, Extent, int[], 1);
	INTEGRAL_CHECK(3, Extent, int[][3], 1);
	INTEGRAL_CHECK(3, Extent, int[2][3], 1);
	INTEGRAL_CHECK(3, Extent, int[2][3][5], 1);
	INTEGRAL_CHECK(0, Extent, int(*)[2][3], 1);
	INTEGRAL_CHECK(0, Extent, int(&)[2][3], 1);
	INTEGRAL_CHECK(0, Extent, int(&&)[2][3], 1);

	INTEGRAL_CHECK(0, Extent, int[2][3], 2);
	INTEGRAL_CHECK(5, Extent, int[2][3][5], 2);

	INTEGRAL_CHECK(0, Extent, int[2][3][5], 3);

	INTEGRAL_CHECK(0, Extent, int *);
	INTEGRAL_CHECK(0, Extent, int &);
	INTEGRAL_CHECK(0, Extent, int &&);
}