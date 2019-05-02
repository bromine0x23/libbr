#include "test.hpp"

#include<libbr/type_traits/is_enum.hpp>

using namespace BR;

TEST(TypeTraits, IsEnum) {
	IS_TRAITS_CHECK_CV(true , Enum, enum, Enum);
	IS_TRAITS_CHECK_CV(true , Enum, enum, EnumClass);

	IS_TRAITS_CHECK(false, Enum, enum, void);
	IS_TRAITS_CHECK(false, Enum, enum, int);
	IS_TRAITS_CHECK(false, Enum, enum, int *);
	IS_TRAITS_CHECK(false, Enum, enum, int &);
	IS_TRAITS_CHECK(false, Enum, enum, int &&);
	IS_TRAITS_CHECK(false, Enum, enum, int []);
	IS_TRAITS_CHECK(false, Enum, enum, int [2]);
	IS_TRAITS_CHECK(false, Enum, enum, int Class::*);
	IS_TRAITS_CHECK(false, Enum, enum, CFunction<int, int>);
	IS_TRAITS_CHECK(false, Enum, enum, CFunction<int, int> *);
	IS_TRAITS_CHECK(false, Enum, enum, CFunction<int, int> Class::*);
	IS_TRAITS_CHECK(false, Enum, enum, NullPointer);
	IS_TRAITS_CHECK(false, Enum, enum, Class);
	IS_TRAITS_CHECK(false, Enum, enum, Struct);
	IS_TRAITS_CHECK(false, Enum, enum, Union);
}