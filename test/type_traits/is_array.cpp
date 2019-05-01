#include "test.hpp"

#include<libbr/type_traits/is_array.hpp>

using namespace BR;

TEST(TypeTraits, IsArray) {
	IS_TRAITS_CHECK(false, Array, array, void);

	IS_TRAITS_CHECK(false, Array, array, int);
	IS_TRAITS_CHECK(false, Array, array, int *);
	IS_TRAITS_CHECK(false, Array, array, int const *);
	IS_TRAITS_CHECK(false, Array, array, int * const);
	IS_TRAITS_CHECK(true , Array, array, int [2]);
	IS_TRAITS_CHECK(true , Array, array, int const [2]);
	IS_TRAITS_CHECK(true , Array, array, int [][3]);
	IS_TRAITS_CHECK(true , Array, array, int [2][3]);
	IS_TRAITS_CHECK(false, Array, array, int(*)[2]);
	IS_TRAITS_CHECK(false, Array, array, int(&)[2]);
	IS_TRAITS_CHECK(false, Array, array, int(&&)[2]);
}