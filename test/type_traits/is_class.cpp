#include "test.hpp"

#include<libbr/type_traits/is_class.hpp>

using namespace BR;

TEST(TypeTraits, IsClass) {
	IS_TRAITS_CHECK_CV(true, Class, Class);
	IS_TRAITS_CHECK_CV(true, Class, Abstract);
	IS_TRAITS_CHECK_CV(true, Class, Polymorphic);
	IS_TRAITS_CHECK_CV(true, Class, PolymorphicDerived);
	IS_TRAITS_CHECK_CV(true, Class, Base);
	IS_TRAITS_CHECK_CV(true, Class, Derived);
	IS_TRAITS_CHECK_CV(true, Class, Empty);

	IS_TRAITS_CHECK(false, Class, Union);
	IS_TRAITS_CHECK(false, Class, Enum);
	IS_TRAITS_CHECK(false, Class, EnumClass);
	IS_TRAITS_CHECK(false, Class, void);
	IS_TRAITS_CHECK(false, Class, int);
	IS_TRAITS_CHECK(false, Class, float);
	IS_TRAITS_CHECK(false, Class, char);
	IS_TRAITS_CHECK(false, Class, int *);
	IS_TRAITS_CHECK(false, Class, int &);
	IS_TRAITS_CHECK(false, Class, int &&);
	IS_TRAITS_CHECK(false, Class, int []);
	IS_TRAITS_CHECK(false, Class, int [2]);
	IS_TRAITS_CHECK(false, Class, int(int));
	IS_TRAITS_CHECK(false, Class, int(*)(int));
	IS_TRAITS_CHECK(false, Class, int(&)(int));
	IS_TRAITS_CHECK(false, Class, int(&&)(int));
	IS_TRAITS_CHECK(false, Class, int(Class::*));
	IS_TRAITS_CHECK(false, Class, int(Class::*)(int));
}