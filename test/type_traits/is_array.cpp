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

	IS_TRAITS_CHECK(false, Array, array, Class);
	IS_TRAITS_CHECK(false, Array, array, Class *);
	IS_TRAITS_CHECK(false, Array, array, Class const *);
	IS_TRAITS_CHECK(false, Array, array, Class * const);
	IS_TRAITS_CHECK(true , Array, array, Class [2]);
	IS_TRAITS_CHECK(true , Array, array, Class const [2]);
	IS_TRAITS_CHECK(true , Array, array, Class [][3]);
	IS_TRAITS_CHECK(true , Array, array, Class [2][3]);
	IS_TRAITS_CHECK(false, Array, array, Class(*)[2]);
	IS_TRAITS_CHECK(false, Array, array, Class(&)[2]);
	IS_TRAITS_CHECK(false, Array, array, Class(&&)[2]);

	IS_TRAITS_CHECK(false, Array, array, Union);
	IS_TRAITS_CHECK(false, Array, array, Union *);
	IS_TRAITS_CHECK(false, Array, array, Union const *);
	IS_TRAITS_CHECK(false, Array, array, Union * const);
	IS_TRAITS_CHECK(true , Array, array, Union [2]);
	IS_TRAITS_CHECK(true , Array, array, Union const [2]);
	IS_TRAITS_CHECK(true , Array, array, Union [][3]);
	IS_TRAITS_CHECK(true , Array, array, Union [2][3]);
	IS_TRAITS_CHECK(false, Array, array, Union(*)[2]);
	IS_TRAITS_CHECK(false, Array, array, Union(&)[2]);
	IS_TRAITS_CHECK(false, Array, array, Union(&&)[2]);

	IS_TRAITS_CHECK(false, Array, array, Enum);
	IS_TRAITS_CHECK(false, Array, array, Enum *);
	IS_TRAITS_CHECK(false, Array, array, Enum const *);
	IS_TRAITS_CHECK(false, Array, array, Enum * const);
	IS_TRAITS_CHECK(true , Array, array, Enum [2]);
	IS_TRAITS_CHECK(true , Array, array, Enum const [2]);
	IS_TRAITS_CHECK(true , Array, array, Enum [][3]);
	IS_TRAITS_CHECK(true , Array, array, Enum [2][3]);
	IS_TRAITS_CHECK(false, Array, array, Enum(*)[2]);
	IS_TRAITS_CHECK(false, Array, array, Enum(&)[2]);
	IS_TRAITS_CHECK(false, Array, array, Enum(&&)[2]);

	IS_TRAITS_CHECK(false, Array, array, EnumClass);
	IS_TRAITS_CHECK(false, Array, array, EnumClass *);
	IS_TRAITS_CHECK(false, Array, array, EnumClass const *);
	IS_TRAITS_CHECK(false, Array, array, EnumClass * const);
	IS_TRAITS_CHECK(true , Array, array, EnumClass [2]);
	IS_TRAITS_CHECK(true , Array, array, EnumClass const [2]);
	IS_TRAITS_CHECK(true , Array, array, EnumClass [][3]);
	IS_TRAITS_CHECK(true , Array, array, EnumClass [2][3]);
	IS_TRAITS_CHECK(false, Array, array, EnumClass(*)[2]);
	IS_TRAITS_CHECK(false, Array, array, EnumClass(&)[2]);
	IS_TRAITS_CHECK(false, Array, array, EnumClass(&&)[2]);
}