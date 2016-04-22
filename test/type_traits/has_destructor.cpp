#include "test.hpp"

#include<libbr/type_traits/has_destructor.hpp>

using namespace BR;

TEST(TypeTraits, HasDestructor) {
	HAS_TRAITS_CHECK_CV(true, Destructor, bool);
	HAS_TRAITS_CHECK_CV(true, Destructor, int);
	HAS_TRAITS_CHECK_CV(true, Destructor, void *);
	HAS_TRAITS_CHECK_CV(true, Destructor, int *);
	HAS_TRAITS_CHECK_CV(true, Destructor, Enum);
	HAS_TRAITS_CHECK_CV(true, Destructor, EnumClass);
	HAS_TRAITS_CHECK_CV(true, Destructor, Union);
	HAS_TRAITS_CHECK_CV(true, Destructor, Class);
	HAS_TRAITS_CHECK(true, Destructor, int &);
	HAS_TRAITS_CHECK(true, Destructor, int &&);
	HAS_TRAITS_CHECK(true, Destructor, int [2]);
	HAS_TRAITS_CHECK(true, Destructor, int [2][3]);
	HAS_TRAITS_CHECK(true, Destructor, int(&)[2]);
	HAS_TRAITS_CHECK(true, Destructor, int(&&)[2]);
	HAS_TRAITS_CHECK(true, Destructor, int(*)(int));
	HAS_TRAITS_CHECK(true, Destructor, int(&)(int));
	HAS_TRAITS_CHECK(true, Destructor, int(&&)(int));
	HAS_TRAITS_CHECK(true, Destructor, int Class::*);
	HAS_TRAITS_CHECK(true, Destructor, int(Class::*)(int));

	HAS_TRAITS_CHECK_CV(false, Destructor, void);
	HAS_TRAITS_CHECK_CV(false, Destructor, DeleteDestructor);
	HAS_TRAITS_CHECK_CV(false, Destructor, AbstractDeleteDestructor);
	HAS_TRAITS_CHECK(false, Destructor, void());
	HAS_TRAITS_CHECK(false, Destructor, int []);
	HAS_TRAITS_CHECK(false, Destructor, int const []);
	HAS_TRAITS_CHECK(false, Destructor, int volatile []);
	HAS_TRAITS_CHECK(false, Destructor, int const volatile []);
	HAS_TRAITS_CHECK(false, Destructor, DeleteDestructor []);
	HAS_TRAITS_CHECK(false, Destructor, DeleteDestructor [2]);
}