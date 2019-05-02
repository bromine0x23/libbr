#include "test.hpp"

#include<libbr/type_traits/extent.hpp>

using namespace BR;

TEST(TypeTraits, Extent) {
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int[]);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int[][3]);
	INTEGRAL_TRAITS_CHECK(2, Extent, extent, int[2][3]);
	INTEGRAL_TRAITS_CHECK(2, Extent, extent, int[2][3][5]);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int(*)[2][3]);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int(&)[2][3]);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int(&&)[2][3]);

	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int, 1);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int[], 1);
	INTEGRAL_TRAITS_CHECK(3, Extent, extent, int[][3], 1);
	INTEGRAL_TRAITS_CHECK(3, Extent, extent, int[2][3], 1);
	INTEGRAL_TRAITS_CHECK(3, Extent, extent, int[2][3][5], 1);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int(*)[2][3], 1);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int(&)[2][3], 1);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int(&&)[2][3], 1);

	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int[2][3], 2);
	INTEGRAL_TRAITS_CHECK(5, Extent, extent, int[2][3][5], 2);

	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int[2][3][5], 3);

	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int *);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int &);
	INTEGRAL_TRAITS_CHECK(0, Extent, extent, int &&);
}