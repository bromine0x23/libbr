#include "test.hpp"

#include<libbr/type_traits/is_enum.hpp>

using namespace BR;

TEST(TypeTraits, IsEnum) {
	IS_TRAITS_CHECK_CV(true , Enum, enum, Enum);
	IS_TRAITS_CHECK_CV(true , Enum, enum, EnumClass);

	IS_TRAITS_CHECK_CV(false, Enum, enum, void);
	IS_TRAITS_CHECK_CV(false, Enum, enum, int);
	IS_TRAITS_CHECK_CV(false, Enum, enum, Class);
	IS_TRAITS_CHECK_CV(false, Enum, enum, Union);
	IS_TRAITS_CHECK(false, Enum, enum, int *);
	IS_TRAITS_CHECK(false, Enum, enum, int &);
	IS_TRAITS_CHECK(false, Enum, enum, int &&);
	IS_TRAITS_CHECK(false, Enum, enum, int []);
	IS_TRAITS_CHECK(false, Enum, enum, int (*)[]);
	IS_TRAITS_CHECK(false, Enum, enum, int (&)[]);
	IS_TRAITS_CHECK(false, Enum, enum, int (&&)[]);
	IS_TRAITS_CHECK(false, Enum, enum, int [2]);
	IS_TRAITS_CHECK(false, Enum, enum, int (*)[2]);
	IS_TRAITS_CHECK(false, Enum, enum, int (&)[2]);
	IS_TRAITS_CHECK(false, Enum, enum, int (&&)[2]);
	IS_TRAITS_CHECK(false, Enum, enum, int(int));
	IS_TRAITS_CHECK(false, Enum, enum, int(*)(int));
	IS_TRAITS_CHECK(false, Enum, enum, int(&)(int));
	IS_TRAITS_CHECK(false, Enum, enum, int(&&)(int));
}