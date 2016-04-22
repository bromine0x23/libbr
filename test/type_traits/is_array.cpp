#include "test.hpp"

#include<libbr/type_traits/is_array.hpp>

using namespace BR;

TEST(TypeTraits, IsArray) {
	IS_TRAITS_CHECK(false, Array, void);

	IS_TRAITS_CHECK(false, Array, int);
	IS_TRAITS_CHECK(false, Array, int *);
	IS_TRAITS_CHECK(false, Array, int const *);
	IS_TRAITS_CHECK(false, Array, int * const);
	IS_TRAITS_CHECK(true , Array, int [2]);
	IS_TRAITS_CHECK(true , Array, int const [2]);
	IS_TRAITS_CHECK(true , Array, int [][3]);
	IS_TRAITS_CHECK(true , Array, int [2][3]);
	IS_TRAITS_CHECK(false, Array, int(*)[2]);
	IS_TRAITS_CHECK(false, Array, int(&)[2]);
	IS_TRAITS_CHECK(false, Array, int(&&)[2]);

	IS_TRAITS_CHECK(false, Array, Class);
	IS_TRAITS_CHECK(false, Array, Class *);
	IS_TRAITS_CHECK(false, Array, Class const *);
	IS_TRAITS_CHECK(false, Array, Class * const);
	IS_TRAITS_CHECK(true , Array, Class [2]);
	IS_TRAITS_CHECK(true , Array, Class const [2]);
	IS_TRAITS_CHECK(true , Array, Class [][3]);
	IS_TRAITS_CHECK(true , Array, Class [2][3]);
	IS_TRAITS_CHECK(false, Array, Class(*)[2]);
	IS_TRAITS_CHECK(false, Array, Class(&)[2]);
	IS_TRAITS_CHECK(false, Array, Class(&&)[2]);

	IS_TRAITS_CHECK(false, Array, Union);
	IS_TRAITS_CHECK(false, Array, Union *);
	IS_TRAITS_CHECK(false, Array, Union const *);
	IS_TRAITS_CHECK(false, Array, Union * const);
	IS_TRAITS_CHECK(true , Array, Union [2]);
	IS_TRAITS_CHECK(true , Array, Union const [2]);
	IS_TRAITS_CHECK(true , Array, Union [][3]);
	IS_TRAITS_CHECK(true , Array, Union [2][3]);
	IS_TRAITS_CHECK(false, Array, Union(*)[2]);
	IS_TRAITS_CHECK(false, Array, Union(&)[2]);
	IS_TRAITS_CHECK(false, Array, Union(&&)[2]);

	IS_TRAITS_CHECK(false, Array, Enum);
	IS_TRAITS_CHECK(false, Array, Enum *);
	IS_TRAITS_CHECK(false, Array, Enum const *);
	IS_TRAITS_CHECK(false, Array, Enum * const);
	IS_TRAITS_CHECK(true , Array, Enum [2]);
	IS_TRAITS_CHECK(true , Array, Enum const [2]);
	IS_TRAITS_CHECK(true , Array, Enum [][3]);
	IS_TRAITS_CHECK(true , Array, Enum [2][3]);
	IS_TRAITS_CHECK(false, Array, Enum(*)[2]);
	IS_TRAITS_CHECK(false, Array, Enum(&)[2]);
	IS_TRAITS_CHECK(false, Array, Enum(&&)[2]);

	IS_TRAITS_CHECK(false, Array, EnumClass);
	IS_TRAITS_CHECK(false, Array, EnumClass *);
	IS_TRAITS_CHECK(false, Array, EnumClass const *);
	IS_TRAITS_CHECK(false, Array, EnumClass * const);
	IS_TRAITS_CHECK(true , Array, EnumClass [2]);
	IS_TRAITS_CHECK(true , Array, EnumClass const [2]);
	IS_TRAITS_CHECK(true , Array, EnumClass [][3]);
	IS_TRAITS_CHECK(true , Array, EnumClass [2][3]);
	IS_TRAITS_CHECK(false, Array, EnumClass(*)[2]);
	IS_TRAITS_CHECK(false, Array, EnumClass(&)[2]);
	IS_TRAITS_CHECK(false, Array, EnumClass(&&)[2]);
}