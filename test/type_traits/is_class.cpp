#include "test.hpp"

#include<libbr/type_traits/is_class.hpp>

using namespace BR;

TEST(TypeTraits, IsClass) {
	IS_TRAITS_CHECK_CV(true, Class, class, Class);
	IS_TRAITS_CHECK_CV(true, Class, class, Struct);
	IS_TRAITS_CHECK_CV(true, Class, class, Abstract);
	IS_TRAITS_CHECK_CV(true, Class, class, Polymorphic);
	IS_TRAITS_CHECK_CV(true, Class, class, PolymorphicDerived);
	IS_TRAITS_CHECK_CV(true, Class, class, Base);
	IS_TRAITS_CHECK_CV(true, Class, class, Derived);
	IS_TRAITS_CHECK_CV(true, Class, class, Empty);

	IS_TRAITS_CHECK(false, Class, class, void);
	IS_TRAITS_CHECK(false, Class, class, int);
	IS_TRAITS_CHECK(false, Class, class, int *);
	IS_TRAITS_CHECK(false, Class, class, int &);
	IS_TRAITS_CHECK(false, Class, class, int &&);
	IS_TRAITS_CHECK(false, Class, class, int []);
	IS_TRAITS_CHECK(false, Class, class, int [2]);
	IS_TRAITS_CHECK(false, Class, class, CFunction<int, int>);
	IS_TRAITS_CHECK(false, Class, class, CFunction<int, int> *);
	IS_TRAITS_CHECK(false, Class, class, int Class::*);
	IS_TRAITS_CHECK(false, Class, class, CFunction<int, int> Class::*);
	IS_TRAITS_CHECK(false, Class, class, Union);
	IS_TRAITS_CHECK(false, Class, class, Enum);
	IS_TRAITS_CHECK(false, Class, class, EnumClass);
}